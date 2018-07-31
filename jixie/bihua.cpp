/*获得笔画*/
#include<iostream>
#include"bihua.h"
#include<stdlib.h>
#include<cstring>
#include<memory.h>
#include<string.h>

#include "the_main.h"

#define max 100



class neighborhood
{
public:
	int number;
	int x, y;
};

class bi_hua
{
public:
	int flag = 0;
	int self[max][max] = { 0 };
};

class one_room
{
public:                                                   
	void get_room(int * * img, int x, int y, int w, int h);
	void get_room(int img[3][3]);
	
	int neighbor[8] = { 0 };
	neighborhood nerghbord[8];
	int width, high;
};


void one_room::get_room(int * * img, int x, int y,int w,int h)
{
	width = w;
	high = h;
	neighbor[0] = x-1>=0 && y-1 >=0 ? img[x - 1][y - 1]:0;
	nerghbord[0].x = x - 1;
	nerghbord[0].y = y - 1;
	nerghbord[0].number = neighbor[0];

	neighbor[1] = x-1>=0 ? img[x - 1][y]:0;
	nerghbord[1].x = x - 1;
	nerghbord[1].y = y;
	nerghbord[1].number = neighbor[1];

	neighbor[2] = x-1>=0&&y+1<width ?img[x - 1][y + 1]:0;
	nerghbord[2].x = x - 1;
	nerghbord[2].y = y + 1;
	nerghbord[2].number = neighbor[2];


	neighbor[3] = y-1>=0 ? img[x][y - 1]:0;
	nerghbord[3].x = x ;
	nerghbord[3].y = y - 1;
	nerghbord[3].number = neighbor[3];

	neighbor[4] = y+1<width? img[x][y + 1]:0;
	nerghbord[4].x = x;
	nerghbord[4].y = y + 1;
	nerghbord[4].number = neighbor[4];

	neighbor[5] = x+1<high&&y-1>=0 ?img[x + 1][y - 1]:0;
	nerghbord[5].x = x + 1;
	nerghbord[5].y = y - 1;
	nerghbord[5].number = neighbor[5];

	neighbor[6] = x+1<high ?img[x + 1][y]:0;
	nerghbord[6].x = x + 1;
	nerghbord[6].y = y ;
	nerghbord[6].number = neighbor[6];

	neighbor[7] = x+1<high&&y+1<width ? img[x + 1][y + 1]:0;
	nerghbord[7].x = x +1;
	nerghbord[7].y = y + 1;
	nerghbord[7].number = neighbor[7];



	return;
}

void one_room::get_room(int  img[3][3])
{
	neighbor[0] = img[0][0];
	neighbor[1] = img[0][1];
	neighbor[2] = img[0][2];
	neighbor[3] = img[1][0];
	neighbor[4] = img[1][2];
	neighbor[5] = img[2][0];
	neighbor[6] = img[2][1];
	neighbor[7] = img[2][2];
	return;
}


int count_point(one_room new_room);
/*获得其中一个笔画*/



bi_hua * get_one_hua(int ** arry,int x,int y,bi_hua * new_bi)
{
	one_room new_room;
	new_room.get_room(arry, x, y, max, max);
	if (count_point(new_room) == 0)
		return new_bi;
	for (int i = 0; i < 8; i++)
	{
		if (new_room.neighbor[i] == 1)
		{
			arry[x][y] = 0;
			new_bi->self[x][y] = 1;
			new_bi->flag = 1;
			get_one_hua(arry, new_room.nerghbord[i].x, new_room.nerghbord[i].y,new_bi);
		}
	}

	
}
int count_point(one_room new_room)
{
	int i;
	int count = 0;
	for (i = 0; i < 8; i++)
	{
		if (new_room.neighbor[i] == 1)
			count++;
	}
	return count;
}

//交点处理
int do_main(Mat &srcimage) //传递的为单通道图像
{
	int col, row;
	col = srcimage.cols;
	row = srcimage.rows;

    one_room test;

	/*存放像素点的二维数组*/
	int **array1;
	array1 = new int *[srcimage.rows];
	for (int i = 0; i<srcimage.rows; ++i)
		array1[i] = new int[srcimage.cols];

	/*二维数组复制*/
	for (int i = 0; i<row; i++)
		for (int j = 0; j < col; j++)
		{
			int b = srcimage.at<uchar>(i, j);
			if (b < 20)
				array1[i][j] = 0;
			else
				array1[i][j] = 1;
	
		}

	/*删除孤立点*/
/*	for (int i = 0; i<row; i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1, i, j,col,row);
			if (count_point(test) == 0)
			{
				array1[i][j] = 0;
			}
		}
		*/
	
	/*删除交点坐标*/

	for(int i=0;i<row;i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1,i,j,col,row);
			if (count_point(test) > 2)
			{
				array1[i][j] = 0;
			}
		}

	/*笔画提取*/
	int m=0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
		
			if (array1[i][j] == 1)
			{
				bi_hua new_bi;
				get_one_hua(array1, i, j, &new_bi);


				for (int k = 0; k< row; k++)
				{
					for (int m= 0; m < col; m++)
					{
						if (new_bi.flag == 1)
						{
							if (new_bi.self[k][m]== 0)
							{
								std::cout << ' ';
							}
							else
								std::cout << '1';
						}
					}
					std::cout << std::endl;
				}
				m++;
			}
		}
		cout << endl;
	}

	/*print 测试*/
	
	
	return 1;
}




