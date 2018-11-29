


#include <regex>
#include "the_main.h"


/*img_print class*/

class img_operate {
public:
	void do_img(string srcpath, string midpath, string distpath);
};
void img_print_test::single_img_print(Mat & src2)
{
	for (int row = 0; row < src2.rows; row++)
	{
		for (int col = 0; col < src2.cols; col++)
		{

			int b = src2.at<uchar>(row, col);
			if (b < 50)
			{
				cout << ' ';
			}
			else
			{
				cout << '1';
			}
		}
		cout << endl;
	}
}

/*squre class*/
class squre_line{
public:
	void get_line(int flag,int x1, int x2, int y1, int y2 );
	void print_line()
	{
		/*cout << "水平方向为:"<<endl;
		cout << "start:";
		cout << level.get_sx() << "," << level.get_sy() << endl;
		cout << "end:";
		cout << level.get_ex() << "," << level.get_ey()<< endl;
		cout << "垂直方向为:";
		cout << "start:";
		cout << vechel.get_sx() << "," << vechel.get_sy() << endl;
		cout << "end:";
		cout << vechel.get_ex() << "," << vechel.get_ey() << endl;
		cout << "顶点坐标:";
		cout << level.get_sx() << "," << vechel.get_sy() << endl;*/
		dis_x = level.get_sx();
		dis_y = vechel.get_sy();
	}
	int dis_x=0, dis_y=0;
private:
	lines level;
	lines vechel;
};



void squre_line::get_line(int flag, int x1, int x2, int y1, int y2)
{
	if (flag == 1)
	{
		level.get_one(x1, x2, y1, y2);
	}
	if (flag == 2)
	{
		vechel.get_one(x1, x2, y1, y2);
	}
}
squre_line line_member; //方块成员




/*获得边界顶点坐标*/
void get_border(int ** num,int hight,int width)
{
	int count = 0;
	int x1, y1;
	int x2, y2;
	for (int row = 0; row < hight; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (num[row][col] == 1)
			{
				if (count == 0)
				{
					x1 = row;
					y1 = col;
				}
				count++;
				x2 = row;
				y2 = col;
			}
		
		}
		if (count >= 3)
		{
			line_member.get_line(1, x1, x2, y1, y2);
			break;
		}
	}

	count = 0;
	for (int col = 0; col < width; col++)
	{
		for (int row = 0; row < hight; row++)
		{
			if (num[row][col] == 1)
			{
				if (count == 0)
				{
					x1 = row;
					y1 = col;
				}
				count++;
				x2 = row;
				y2 = col;
			}

		}
		if (count >= 2)
		{
			line_member.get_line(2, x1, x2, y1, y2);
			break;
		}
	}
	
	return;
}


//细化算法2
void zhang_thinimage_improve(Mat &srcimage)//单通道、二值化后的图像  
{
	vector<Point> deletelist1;
	int Zhangmude[9];
	int nl = srcimage.rows;
	int nc = srcimage.cols;
	while (true)
	{
		for (int j = 1; j<(nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i<(nc - 1); i++)
			{
				if (data[i] == 255)
				{
					Zhangmude[0] = 1;
					if (data_last[i] == 255) Zhangmude[1] = 1;
					else  Zhangmude[1] = 0;
					if (data_last[i + 1] == 255) Zhangmude[2] = 1;
					else  Zhangmude[2] = 0;
					if (data[i + 1] == 255) Zhangmude[3] = 1;
					else  Zhangmude[3] = 0;
					if (data_next[i + 1] == 255) Zhangmude[4] = 1;
					else  Zhangmude[4] = 0;
					if (data_next[i] == 255) Zhangmude[5] = 1;
					else  Zhangmude[5] = 0;
					if (data_next[i - 1] == 255) Zhangmude[6] = 1;
					else  Zhangmude[6] = 0;
					if (data[i - 1] == 255) Zhangmude[7] = 1;
					else  Zhangmude[7] = 0;
					if (data_last[i - 1] == 255) Zhangmude[8] = 1;
					else  Zhangmude[8] = 0;
					int whitepointtotal = 0;
					for (int k = 1; k < 9; k++)
					{
						//得到1的个数
						whitepointtotal = whitepointtotal + Zhangmude[k];
					}
					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
					{
						//得到01的个数
						int ap = 0;
						if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
						if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
						if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
						if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
						if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
						if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
						if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
						if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
						//计算bp
						int bp = 0;
						bp += Zhangmude[1];
						bp += Zhangmude[2] << 1;
						bp += Zhangmude[3] << 2;
						bp += Zhangmude[4] << 3;
						bp += Zhangmude[5] << 4;
						bp += Zhangmude[6] << 5;
						bp += Zhangmude[7] << 6;
						bp += Zhangmude[8] << 7;

						if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54)
						{
							if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0))
							{
								deletelist1.push_back(Point(i, j));  //满足条件，去除该点
							}
						}
					}
				}
			}
		}
		if (deletelist1.size() == 0) break;
		for (size_t i = 0; i < deletelist1.size(); i++)
		{
			Point tem;
			tem = deletelist1[i];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deletelist1.clear();


		for (int j = 1; j<(nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i<(nc - 1); i++)
			{
				if (data[i] == 255)
				{
					Zhangmude[0] = 1;
					if (data_last[i] == 255) Zhangmude[1] = 1;
					else  Zhangmude[1] = 0;
					if (data_last[i + 1] == 255) Zhangmude[2] = 1;
					else  Zhangmude[2] = 0;
					if (data[i + 1] == 255) Zhangmude[3] = 1;
					else  Zhangmude[3] = 0;
					if (data_next[i + 1] == 255) Zhangmude[4] = 1;
					else  Zhangmude[4] = 0;
					if (data_next[i] == 255) Zhangmude[5] = 1;
					else  Zhangmude[5] = 0;
					if (data_next[i - 1] == 255) Zhangmude[6] = 1;
					else  Zhangmude[6] = 0;
					if (data[i - 1] == 255) Zhangmude[7] = 1;
					else  Zhangmude[7] = 0;
					if (data_last[i - 1] == 255) Zhangmude[8] = 1;
					else  Zhangmude[8] = 0;
					int whitepointtotal = 0;
					for (int k = 1; k < 9; k++)
					{
						whitepointtotal = whitepointtotal + Zhangmude[k];
					}
					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
					{
						int ap = 0;
						if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
						if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
						if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
						if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
						if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
						if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
						if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
						if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
						int bp = 0;
						bp += Zhangmude[1];
						bp += Zhangmude[2] << 1;
						bp += Zhangmude[3] << 2;
						bp += Zhangmude[4] << 3;
						bp += Zhangmude[5] << 4;
						bp += Zhangmude[6] << 5;
						bp += Zhangmude[7] << 6;
						bp += Zhangmude[8] << 7;
						if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54)
						{
							if ((Zhangmude[1] * Zhangmude[3] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[1] * Zhangmude[7] == 0))
							{
								deletelist1.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		if (deletelist1.size() == 0) break;
		for (size_t i = 0; i < deletelist1.size(); i++)
		{
			Point tem;
			tem = deletelist1[i];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deletelist1.clear();
	}
}




//图像保存
void create_jpg(bi_hua * bi, Mat & srcimage,string path)
{
	for(int i=0;i<max_size;i++)
		for (int j = 0; j < max_size; j++)
		{
			if (bi->self[i][j] == 1||bi->self[i][j] == 2)
				srcimage.at<uchar>(i, j) = 0;
			else
				srcimage.at<uchar>(i, j) = 255;
		}
//	imshow("ff", srcimage);
	imwrite(path, srcimage);
}

void get_bihua(string path,string distpath) //获得二值图像  
{
	Mat src;
	Mat src2;

	std::vector<Mat> channels;
	src = imread(path);



	split(src, channels);
	src2 = channels.at(1);
	resize(src2, src2, Size(max_size, max_size), (0, 0), (0, 0), INTER_LINEAR);

	//存储r
	int **array1;
	array1 = new int *[src2.rows];
	for (int i = 0; i<src2.rows; ++i)
		array1[i] = new int[src2.cols];

	int **array2;
	array2 = new int *[src2.rows];
	for (int i = 0; i<src2.rows; ++i)
		array2[i] = new int[src2.cols];

	/*图像单值化处理*/
			for (int row = 0; row < src2.rows; row++)
			{
				for (int col = 0; col < src2.cols; col++)
				{

					int b = src2.at<uchar>(row, col);
					array1[row][col] = b;
					if (array1[row][col] < 150)  //调整阈值
					{
						src2.at<uchar>(row, col) = 255;
						array2[row][col] = 1;
						//std::cout << '1';
					}

					else
					{
						src2.at<uchar>(row, col) = 0;

						array2[row][col] = 0;
						//std::cout << '0';
					}
				}
				//std::cout << endl;
			}


	
	//调用细化算法1
	zhang_thinimage_improve(src2);
	//imshow("3",src2);




	//print
	//img_print_test my_print;
	//my_print.single_img_print(src2);


	// 调用笔画获取的主函数
	bi_hua * my_bi; //获得笔画骨架
	my_bi = do_main(src2);
	bi_hua * head;
	head = my_bi->next;

	int array3[max_size][max_size];
	for(int i=0;i<max_size;i++)
		for (int j = 0; j < max_size; j++)
		{
			array3[i][j] = array2[i][j];
		}
	//将笔画骨架还原
	get_before(my_bi, array3);

	my_bi = head;
	int rd = 1;
	char str[10000];
	
	while (my_bi != NULL)
	{
		Mat srcf(max_size,max_size, CV_8UC1);
		string my_path;
		sprintf(str, "%d",rd);
		my_path = distpath + str + ".jpg";
		//cout << my_path;
		rd++;
		//将每个笔画放入左上角顶点
		for(int i= 0;i<max_size;i++)
			for (int j = 0; j < max_size; j++)
			{
				array2[i][j] = my_bi->self[i][j];
			}
		get_border(array2, max_size, max_size);
		//std::cout << endl;
		line_member.print_line();

		for (int i = 0; i < max_size; i++)
			for (int j = 0; j < max_size; j++)
			{
				 my_bi->self[i][j]=0;
			}
		for(int i =line_member.dis_x;i<max_size;i++)
			for (int j = line_member.dis_y; j < max_size; j++)
			{
				my_bi->self[i - line_member.dis_x][j - line_member.dis_y] = array2[i][j];
			}
		//print_bihua2(my_bi);


		 //保存笔画
		create_jpg(my_bi,srcf,my_path);
		my_bi = my_bi->next;
	}
	
	for (int i = 0; i < src2.rows; ++i)
	{
		delete[]array1[i];
		delete[]array2[i];
	}

	my_bi = head;
	bi_hua * bi_next = my_bi->next;
	if (my_bi->next == NULL)
		return;
	while (my_bi != NULL)
	{
		if (my_bi->next != NULL)
		{
			 bi_next = my_bi->next;
		}
		else if (my_bi->next == NULL)
		{
			delete my_bi;
			return;
		}
		delete my_bi;
		my_bi = bi_next;
	}
}




string new_img(string path,string midpath) //获得灰度图像
{
	Mat src, dst;
	src = imread(path);
	if (src.empty())
	{
		printf("can not load image \n");
		assert(src.empty());
	}
	

	//namedWindow("input");
	//imshow("input", src);

	dst.create(src.size(), src.type());

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int b = src.at<Vec3b>(row, col)[0];
			int g = src.at<Vec3b>(row, col)[1];
			int r = src.at<Vec3b>(row, col)[2];
			//cout<<row<<' ' << b << g<< r <<' '<<col<< endl;
			//fe <<'('<< b << ','<<g<<',' << r <<')'<<'\t';


			dst.at<Vec3b>(row, col)[0] = max(r, max(g, b)); //图形灰度处理
			dst.at<Vec3b>(row, col)[1] = max(r, max(g, b));
			dst.at<Vec3b>(row, col)[2] = max(r, max(g, b));


			int b1 = dst.at<Vec3b>(row, col)[0]; //获得灰度处理图像的bgr
			int g1 = dst.at<Vec3b>(row, col)[1];
			int r1 = dst.at<Vec3b>(row, col)[2];
			//fe2 << '('<<b1 << ',' << g1<< ',' << r1<<')'<<'\t';
		}
		//fe <<row<<"over"<< endl;
		//fe2 <<row<<"over"<< endl;
	}
	string outfile = midpath + "test.jpg";
	imwrite(outfile, dst);
	//namedWindow("output");
	//imshow("output", dst);
	return outfile;
}


void  img_operate:: do_img(string srcpath,string midpath,string distpath)
{
	string outfile;
	//像素操作
	outfile = new_img(srcpath,midpath);

	get_bihua(outfile,distpath);


	/*Mat bit_img;
	bit_img = imread(dst_bit_path);
	do_main(bit_img);
	*/

}

//获取特定格式的文件名  
void GetAllFormatFiles(string path, vector<string>& files, string format)
{
	//文件句柄    
	long long   hFile = 0;
	//文件信息    
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}




//汉字笔画提取

int main(int argc,char * argv[])
{
	if (argc >= 3)
	{
		std::cout << "请输入图片的源文件夹位置,中间生成文件位置，目标文件夹位置" << endl;
	}
	else
	{
		/*string filePath = "D:\\Users\\hubaba\\workplace\\HDWDB1.1trn\\HWDB1.1trn_gnt\\png\\傈335.png";
		string midpath = "D:\\Users\\hubaba\\workplace\\jpg\\";
		string distpath = "D:\\Users\\hubaba\\workplace\\bi\\傈335.png";
		img_operate test;
		test.do_img(filePath, midpath, distpath);*/




		string filePath = "D:\\Users\\hubaba\\workplace\\HDWDB1.1trn\\HWDB1.1trn_gnt\\png\\";
		string midpath = "D:\\Users\\hubaba\\workplace\\jpg\\";
		string distpath = "D:\\Users\\hubaba\\workplace\\bi\\";
		string distpath2;
		string srcpath;
		vector<string> files;
		const char * distAll = "AllFiles.txt";

		//读取所有格式为jpg的文件
		string format = ".png";
		GetAllFormatFiles(filePath, files, format);
		ofstream ofn(distAll);
		int size = files.size();
		regex rg1(".+\\\\(.+).png");
		for (int i = 0; i < size; i++)
		{
			ofn << files[i] << endl;
			//cout << files[i] << endl;
			smatch rr1;
			if (regex_match(files[i], rr1, rg1) == 1)
			{
				distpath2 = distpath + rr1.str(1);
				//cout << distpath2 << endl;
				string echo = "md " + distpath2;
				//cout << echo.c_str();
				system(echo.c_str());
				distpath2 = distpath2 + "\\"+rr1.str(1);
				
				srcpath = filePath + rr1.str(1)+".png";
				cout << srcpath<<endl;
				img_operate test;
				test.do_img(srcpath, midpath, distpath2);
				
			}
				
		}

		/*test
		string srcpath = "D:\\Users\\hubaba\\workplace\\HDWDB1.1trn\\HWDB1.1trn_gnt\\png\\咯158.png";
		string midpath = "D:\\Users\\hubaba\\workplace\\jpg\\";
		string distpath = "D:\\Users\\hubaba\\workplace\\bi\\";
	
		do_img(srcpath, midpath, distpath);
		*/
		
	}
}
