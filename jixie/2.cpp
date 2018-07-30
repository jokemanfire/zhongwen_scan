/*��ñʻ�*/
#include<iostream>
#include"2d.h"
#include<stdlib.h>
#include<cstring>
#include<memory.h>
#include<string.h>
using namespace std;
typedef unsigned char BYTE;

void HilditchThinning(int w, int h, int *imgBuf);
int Get8Connectivity(int* neighbor);
void sort_it(int w, int h, int * *imgBuf, int * *cp_img);

//ϸ��ģ��

//��һ��
 int a1[3][3] = { 0,0,0,
						0,2,0,
						1,1,1 };
 int a2[3][3] = { 1,0,0,
						1,2,0,
						1,0,0};
int a3[3][3] = { 1,1,1,
						0,2,0,
						0,0,0};
int a4[3][3] = { 0,0,1,
						0,2,1,
						0,0,1 };

class one_room
{
public:
	void get_room(int * imgBuf, int x, int y, int w,int h);//           p3  p2  p1
												// 8����     p4  p   p0
     											//           p5  p6  p7
	void get_room(int * * img, int x, int y);
	void get_room(int img[3][3]);
	one_room * next_room = NULL;
	one_room * head = NULL;
	int length = 0;
	int neighbor[8] = { 0 };
	int row, col;
	int width, high;
};

void one_room::get_room(int * * img, int x, int y)
{
	neighbor[0] = img[x - 1][y - 1];
	neighbor[1] = img[x-1][y];
	neighbor[2] = img[x -1][y + 1];
	neighbor[3] = img[x][y-1];
	neighbor[4] = img[x][y+1];
	neighbor[5] = img[x +1][y - 1];
	neighbor[6] = img[x+1][y ];
	neighbor[7] = img[x+1][y+1];
	
	width = x;
	high = y;
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

void one_room::get_room(int * imgBuf,int x,int y,int w,int h)
{
	if (x < 0 || y < 0)
	{
		for (int i = 0; i < 8; i++)
			neighbor[i] = 0;
	}
	else
	{
		neighbor[0] = x + 1 < w ? imgBuf[y*w + x + 1] : 0;

		neighbor[1] = y - 1 > 0 && x + 1 < w ? imgBuf[(y - 1)*w + x + 1] : 0;

		neighbor[2] = y - 1 > 0 ? imgBuf[(y - 1)*w + x] : 0;

		neighbor[3] = y - 1 > 0 && x - 1 < 0 ? imgBuf[(y - 1)*w + x - 1] : 0;

		neighbor[4] = x - 1 > 0 ? imgBuf[y*w + x - 1] : 0;

		neighbor[5] = x - 1 > 0 && y + 1 < h ? imgBuf[(y + 1)*w + x - 1] : 0;

		neighbor[6] = y + 1 < h ? imgBuf[(y + 1)*w + x] : 0;

		neighbor[7] = y + 1 < h&&x + 1 < w ? imgBuf[(y + 1)*w + x + 1] : 0;
	}
	row = y;
	col = x;
	width = w;
	high = h;
}




void do_main(int ** array2,int rows ,int cols)
{
	int **array1;
	array1 = new int *[rows];
	for (int i = 0; i<rows; ++i)
		array1[i] = new int[cols];
 
	//array2[0][1] = 1;
	//for (int row = 0; row < rows; row++) //����ϸ��������
	//{
		//HilditchThinning(cols, rows, array2[row]);
		/*for (int col = 0; col < cols; col++)
		{
			iteral_arry(array1, array2, row, col);
		}*/
//	}
    
	for (int row = 0; row < rows; row++)  //��ʼ��array1
	{
		for (int col = 0; col < cols; col++)
		{
			array1[row][col] = array2[row][col];	
		}
	}


   //���ø�ʴ��������

	sort_it(rows, cols, array2,array1);
							

	for (int row = 0; row < rows-1; row++)  //��ӡ���
	{
		for (int col = 0; col < cols-1; col++)
		{
			cout << array1[row][col];
		}
		cout << endl;
	}
	
}
//��ȡ�ʻ�
int iss_none(int ** arry2,int row,int col)
{
	int i, j;
	for(i=-1;i<=1;i++)
		for (j = -1; j <= 1; j++)
		{
			if (arry2[row + i][col + j] == 0 && i != 0 && j != 0)
				return 0;
				
		}
	//if (arry2[row + 1][col + 1] == 0&& arry2[row + 1][col + 0] == 0&& arry2[row + 1][col -1] == 0&& arry2[row + 0][col + 1] == 0
		//&& arry2[row + 0][col + 0] == 0&& arry2[row + 0][col -1] == 0&& arry2[row -1][col + 0] == 0%%arry2[row + 1][col + 0] == 0)
	return 1;
}

int iteral_arry(int ** arry1,int ** arry2,int row,int col)
{
	if (iss_none(arry2,row,col) == 0)
		return 0;
	int i, j;
	for(i=0;i<=1;i++)
		for (j = 0; j <= 1; j++)
		{
			if (arry2[row + i][col + j] == 1)
				lines new_line(row, col, row + i, col + j);
		   //���new_line��old_line�ĽǶȵ���180�Ȼ����135�ȱ�����������
			lines old_line();
		}
	return iteral_arry(arry1, arry2,row,col);
}
//��ȡ�ʻ�


//��Ҫ�Ժ��ֽ��и�ʴ������ (������ʴ��)
void sort_it(int w, int h, int * *imgBuf, int **cp_img)
{

	one_room new__room;
	one_room a1_room;
	one_room a2_room,a3_room,a4_room;
	a1_room.get_room(a1);
	a2_room.get_room(a2);
	a3_room.get_room(a3);
	a4_room.get_room(a4);
	
	int flag=1;
	int i, j;
	for ( i = 1; i < w-2; i++)
	{
		for ( j = 1; j < h-2; j++)
		{
	
				new__room.get_room(cp_img, i, j);
				if (cp_img[new__room.width][new__room.col] == 1)
				{
					flag = 1;
					for (int m = 0; m < 8; m++)
					{
						if (new__room.neighbor[m] != a1_room.neighbor[m])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 1)
						cp_img[i][j] = 0;
					flag = 1;
					for (int m = 0; m < 8; m++)
					{
						if (new__room.neighbor[m] != a2_room.neighbor[m])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 1)
						cp_img[i][j] = 0;
					flag = 1;
					for (int m = 0; m < 8; m++)
					{
						if (new__room.neighbor[m] != a3_room.neighbor[m])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 1)
						cp_img[i][j] = 0;
					flag = 1;
					for (int m = 0; m < 8; m++)
					{
						if (new__room.neighbor[m] != a4_room.neighbor[m])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 1)
						cp_img[i][j] = 0;
				}


			cout << cp_img[i][j];
		}
		cout << endl;
	}
	return;
}
//��ʴ������


void HilditchThinning(int w, int h, int *imgBuf)  //ʹ��Hilditch ϸ���㷨���о�ûɶ�ã�

{

	//           p3  p2  p1

	// 8����     p4  p   p0

	//           p5  p6  p7

	int neighbor[8];

	int *mask = new int[w*h];

	memset(mask, 0, w*h);
	bool loop = true;

	int x, y, k, index;
	int loopNum = 0;


	while (loop)

	{

		loop = false;

		loopNum++;
		for (y = 0; y<h; y++)

		{

			for (x = 0; x<w; x++)

			{

				index = y * w + x;

				//����1��p������ǰ����

				if (imgBuf[index] == 0) continue;



				neighbor[0] = x + 1<w ? imgBuf[y*w + x + 1] : 0;

				neighbor[1] = y - 1>0 && x + 1<w ? imgBuf[(y - 1)*w + x + 1] : 0;

				neighbor[2] = y - 1>0 ? imgBuf[(y - 1)*w + x] : 0;

				neighbor[3] = y - 1>0 && x - 1<0 ? imgBuf[(y - 1)*w + x - 1] : 0;

				neighbor[4] = x - 1>0 ? imgBuf[y*w + x - 1] : 0;

				neighbor[5] = x - 1>0 && y + 1<h ? imgBuf[(y + 1)*w + x - 1] : 0;

				neighbor[6] = y + 1<h ? imgBuf[(y + 1)*w + x] : 0;

				neighbor[7] = y + 1<h&&x + 1<w ? imgBuf[(y + 1)*w + x + 1] : 0;



				//����2��p0,p2,p4,p6��ȫΪǰ��ɫ������ѵ�pɾ�ˣ�ͼ����ģ�

				if (neighbor[0] && neighbor[2] && neighbor[4] && neighbor[6])

					continue;



				//����3��p0~p7�У������и�Ϊǰ��ɫ

				//����ֻ��һ��Ϊ����Ϊ�˵㣬��û��Ϊ�ģ���Ϊ�����㣩

				int count = 0;

				for (int i = 0; i<8; i++)
				{
					if (neighbor[i] == 255)

						count++;
				}
				if (count<2)

				{
					continue;
				}

				//����4��p�İ˽�������������Ϊ1

				if (Get8Connectivity(neighbor) != 1) continue;



				//����5����p2�Ѿ������ɾ������p2Ϊ����ɫʱ��P������������Ϊ1

				k = (y - 1)*w + x;

				if (y - 1>0 && mask[k] == 1)

				{
					imgBuf[k] = 0;

					if (Get8Connectivity(neighbor) != 1) continue;

					imgBuf[k] = 1;

				}
				//����6����p4�Ѿ������ɾ������p4Ϊ����ɫʱ��P������������Ϊ1

				k = y * w + x - 1;

				if (x - 1>0 && mask[k] == 1)

				{

					imgBuf[k] = 0;

					if (Get8Connectivity(neighbor) != 1) continue;

					imgBuf[k] = 1;

				}
				//���ɾ��

				mask[w*y + x] = 1;

				loop = true;
			}
		}

		//�����ɾ���ĵ���Ϊ����ɫ

		for (y = 0; y<h; y++)

		{

			for (x = 0; x<w; x++)

			{

				k = y * w + x;

				if (mask[k] == 1) imgBuf[k] = 0;

			}
		}
	}

}

//                                  p3  p2  p1

//*************������ڵ�������     p4  p   p0

//                                  p5  p6  p7

int Get8Connectivity(int* neighbor)

{



	//���㲹��x^=1-x;

	for (int i = 0; i<8; i++)

	{

		neighbor[i] = neighbor[i] == 0 ? 1 : 0;

	}



	int count = neighbor[0] - (neighbor[0] & neighbor[1] & neighbor[2]);

	count += neighbor[2] - (neighbor[2] & neighbor[3] & neighbor[4]);

	count += neighbor[4] - (neighbor[4] & neighbor[5] & neighbor[6]);

	count += neighbor[6] - (neighbor[6] & neighbor[7] & neighbor[0]);



	return count;

}
//���ֵ�ϸ������