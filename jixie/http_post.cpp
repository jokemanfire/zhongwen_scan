#include<iostream>
#include"signed.h"
#include <fstream>  
#include<regex>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

using namespace std;
//转码utf-8 to gbk
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
//正则表达式

void get_word(char buf[1024*1024])
{
	regex reg1("\"character\":\"(.{1,2})\",\"confidence\"");
	smatch r1;
	string bm;
	bm = buf;
	regex_search(bm, r1, reg1);
	cout << "正则：" << endl;
	cout << r1.str(1)<< endl;
	
	return;
}
class HttpConnect
{
public:
	HttpConnect();
	~HttpConnect();
	void socketHttp(std::string host, std::string request);
	void postData(std::string host, std::string path, std::string post_content,std::string auth);
	void getData(std::string host, std::string path, std::string get_content);
	void postData_img(std::string host, std::string path, std::string post_content, std::string auth);
};
HttpConnect::HttpConnect()
{
#ifdef WIN32
	//此处一定要初始化一下，否则gethostbyname返回一直为空
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}
HttpConnect::~HttpConnect()
{
}
void HttpConnect::socketHttp(std::string host, std::string request)
{
	int sockfd;
	struct sockaddr_in address;
	struct hostent *server;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(80);
	server = gethostbyname(host.c_str());
	memcpy((char *)&address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	if (-1 == connect(sockfd, (struct sockaddr *)&address, sizeof(address))) {
		std::cout << "connection error!" << std::endl;
		return;
	}
	std::cout << request << std::endl;
#ifdef WIN32
	send(sockfd, request.c_str(), request.size(), 0);
#else
	write(sockfd, request.c_str(), request.size());
#endif
	char buf[1024 * 1024] = { 0 };
	char * buf2;
	buf2 = new char[1024*1024];
	int offset = 0;
	int rc;
#ifdef WIN32
	while (rc = recv(sockfd, buf + offset, 1024, 0))
#else
	while (rc = read(sockfd, buf + offset, 1024))
#endif
	{
		offset += rc;
	}
#ifdef WIN32
	closesocket(sockfd);
#else
	close(sockfd);
#endif

	buf[offset] = 0;
	buf2 = U2G(buf);
	std::cout << buf2 << std::endl;
	get_word(buf2);
}
void HttpConnect::postData(std::string host, std::string path, std::string post_content,std::string auth)
{
	//POST请求方式
	std::stringstream stream;
	stream << "POST " << path;
	stream << " HTTP/1.0\r\n";
	stream << "Accept-Encoding: gzip,deflate";
	stream << "Host: " << "recognition.image.myqcloud.com " << "\r\n";
	stream << "User-Agent:Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Content-Type:application/json\r\n";
	stream << "Content-Length:" << post_content.length() << "\r\n";
	stream << "Authorization:" << auth << "\r\n";
	stream << "Connection:close\r\n\r\n";
	stream << post_content.c_str();
	socketHttp(host, stream.str());
}
// post方式传递文件
void HttpConnect::postData_img(std::string host, std::string path, std::string post_content, std::string auth)
{
	//POST请求方式
	std::stringstream stream;
	stream << "POST " << path;
	stream << " HTTP/1.1\r\n";
	stream << "Authorization:" << auth << "\r\n";
	stream << "Content-Type:multipart/form-data;boundary=71ebdf13572468\r\n";
	stream << "Host: " << "recognition.image.myqcloud.com " << "\r\n\r\n";
	
	stream << "--71ebdf13572468\r\n\
Content-Disposition:form-data;name=\"appid\";\r\n\r\n\
1253112332\r\n\
--71ebdf13572468\r\n\
Content-Disposition:form-data;name=\"bucket\";\r\n\r\n\
do_test\r\n\
--71ebdf13572468\r\n\
Content-Disposition:form-data;name=\"image\"; filename=\"d0_test.jpg\"\r\n\
Content-Type:image/jpeg\r\n\
";
	stream << post_content.c_str();
	stream << "--71ebdf13572468--";
	socketHttp(host, stream.str());
}

void HttpConnect::getData(std::string host, std::string path, std::string get_content)
{
	//GET请求方式
	std::stringstream stream;
	stream << "GET " << path << "?" << get_content;
	stream << "HTTP/1.0\r\n";
	stream << "Host: " << "recognition.image.myqcloud.com "<< "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Connection:close\r\n\r\n";
	socketHttp(host, stream.str());
}

//调用腾讯ocr
int http_post()
{

	std::string sta;
	std::string s;
	std::string m;
	char ms[1024] = { '1' };
	
	char filename[] = "D:\\Users\\hubaba\\workplace\\jpg\\m.jpg";
	int length2;
	int length;
	FILE* fp;

	//以二进制方式打开图像
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		cout << "Open image failed!" << endl;
		exit(0);
	}
	//获取图像数据总长度
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);
	//根据图像数据长度分配内存buffer
	char* ImgBuffer = (char*)malloc(length * sizeof(char));
	//将图像数据读入buffer
	fread(ImgBuffer, length, 1, fp);
	//for (int i = 0; i<length; i++)
		//printf("%c", ImgBuffer[i]);
	m = ImgBuffer;
	sta = do_signed();
	HttpConnect http;
	//post的url请求方式
	http.postData("116.31.68.142", "/ocr/handwriting","{\r\n \"appid\":\"1253112332\", \r\n \"url\":\"http://nun-1253112332.picsh.myqcloud.com/u=827695224,2790795436&fm=27&gp=0.jpg\"\r\n} ", sta);
	//http.getData("116.31.68.142","/ocr/handwriting", "");
	//http.postData_img("116.31.68.142", "/ocr/handwriting", ImgBuffer, sta);
	getchar();
	return 0;
}