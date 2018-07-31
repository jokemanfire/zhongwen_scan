

#include <opencv2/opencv.hpp>
#include<math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "the_main.h"


#include "bihua.h"







#define src_input_path "D://Users//hubaba//workplace//jpg//2.jpg"
#define src_output_path "D://Users//hubaba//workplace//jpg//m.jpg"
#define src_bit_path "D://Users//hubaba//workplace//jpg//bit.jpg"
#define dst_bit_path "D://Users//hubaba//workplace//jpg//bit2.jpg"





/*img_print class*/


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
		cout << "水平方向为:"<<endl;
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
		cout << level.get_sx() << "," << vechel.get_sy() << endl;
	}
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

//细化算法1
void chao_thinimage(Mat &srcimage)//单通道、二值化后的图像
{
	vector<Point> deletelist1;
	int Zhangmude[9];
	int nl = srcimage.rows;
	int nc = srcimage.cols;
	while (true)
	{
		for (int j = 1; j < (nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
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
						if (ap == 1)
						{
							if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0))
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

		for (int j = 1; j < (nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
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
						if (ap == 1)
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

void get_bihua(const char path[100]) //获得二值图像  
{
	Mat src;
	Mat src2;

	std::vector<Mat> channels;
	src = imread(path);
	//src2.create(src.size(), src.type());
	//存储r
	int **array1;
	array1 = new int *[src.rows];
	for (int i = 0; i<src.rows; ++i)
		array1[i] = new int[src.cols];

	int **array2;
	array2 = new int *[src.rows];
	for (int i = 0; i<src.rows; ++i)
		array2[i] = new int[src.cols];

	split(src, channels);
	src2 = channels.at(1);

	/*图像单值化处理*/
	for (int row = 0; row < src2.rows; row++)
	{
		for (int col = 0; col < src2.cols; col++)
		{

			int b = src2.at<uchar>(row, col);
			array1[row][col] = b;
			if (array1[row][col] < 30)
			{
				src2.at<uchar>(row, col) = 255;
				array2[row][col] = 1;
				std::cout << '1';
			}

			else
			{
				src2.at<uchar>(row, col) = 0;

				array2[row][col] = 0;
				std::cout << '0';
			}
		}
		std::cout << endl;
	}
	get_border(array2,src.rows,src.cols);
	std::cout << endl;
	line_member.print_line();  

	//调用细化算法1
	imshow("3",src2);
	zhang_thinimage_improve(src2);



	//print
	img_print_test my_print;
	my_print.single_img_print(src2);

	//保存图像
	imwrite(dst_bit_path,src2);
	imshow("4", src2);
	// 调用笔画获取的主函数
	do_main(src2);
}

void get_binary_file(const char  filename1[100], const char filename2[100]) //获得二进制文件
{
	FILE *fpw = fopen(filename2, "wb");
	if (fpw == NULL)
	{
		cout << "Open error!" << endl;
		fclose(fpw);
		return;
	}

	Mat image = imread(filename1);
	if (!image.data || image.channels() != 3)
	{
		cout << "Image read failed or image channels isn't equal to 3."
			<< endl;
		return;
	}

	// write image to binary format file
	int labelw = 1;
	int rows = image.rows;
	int cols = image.cols;

	fwrite(&labelw, sizeof(char), 1, fpw);

	char* dp = (char*)image.data;
	for (int i = 0; i<rows*cols; i++)
	{
		fwrite(&dp[i * 3], sizeof(char), 1, fpw);
		fwrite(&dp[i * 3 + 1], sizeof(char), 1, fpw);
		fwrite(&dp[i * 3 + 2], sizeof(char), 1, fpw);
	}
	fclose(fpw);

	// read image from binary format file
	FILE *fpr = fopen(filename2, "rb");
	if (fpr == NULL)
	{
		cout << "Open error!" << endl;
		fclose(fpr);
		return;
	}

	int labelr(0);
	fread(&labelr, sizeof(char), 1, fpr);

	cout << "label: " << labelr << endl;

	Mat image2(rows, cols, CV_8UC3, Scalar::all(0));

	char* pData = (char*)image2.data;
	for (int i = 0; i<rows*cols; i++)
	{
		fread(&pData[i * 3], sizeof(char), 1, fpr);
		fread(&pData[i * 3 + 1], sizeof(char), 1, fpr);
		fread(&pData[i * 3 + 2], sizeof(char), 1, fpr);
	}
	fclose(fpr);

	imshow("1", image2);
	waitKey(0);
}


int new_img(const char path[100]) //获得灰度图像
{
	Mat src, dst;
	ofstream fe("D://Users//hubaba//workplace//jpg//1.txt");
	ofstream fe2("D://Users//hubaba//workplace//jpg//2.txt");
	src = imread(path);
	if (src.empty())
	{
		printf("can not load image \n");
		return -1;
	}
	

	namedWindow("input");
	imshow("input", src);

	dst.create(src.size(), src.type());

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int b = src.at<Vec3b>(row, col)[0];
			int g = src.at<Vec3b>(row, col)[1];
			int r = src.at<Vec3b>(row, col)[2];
			//cout<<row<<' ' << b << g<< r <<' '<<col<< endl;
			fe <<'('<< b << ','<<g<<',' << r <<')'<<'\t';


			dst.at<Vec3b>(row, col)[0] = max(r, max(g, b)); //图形灰度处理
			dst.at<Vec3b>(row, col)[1] = max(r, max(g, b));
			dst.at<Vec3b>(row, col)[2] = max(r, max(g, b));


			int b1 = dst.at<Vec3b>(row, col)[0]; //获得灰度处理图像的bgr
			int g1 = dst.at<Vec3b>(row, col)[1];
			int r1 = dst.at<Vec3b>(row, col)[2];
			fe2 << '('<<b1 << ',' << g1<< ',' << r1<<')'<<'\t';
		}
		fe <<row<<"over"<< endl;
		fe2 <<row<<"over"<< endl;
	}
	imwrite(src_output_path, dst);
	namedWindow("output");
	imshow("output", dst);

}


int main()
{

	//像素操作
	new_img(src_input_path);
  //get_binary_file("D://Users//hubaba//workplace//jpg//4.jpg", "D://Users//hubaba//workplace//jpg//1.bin");
	get_bihua(src_output_path);


	/*Mat bit_img;
	bit_img = imread(dst_bit_path);
	do_main(bit_img);
	*/
	waitKey();

}