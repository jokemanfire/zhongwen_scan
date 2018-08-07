/*获得笔画*/
#include<iostream>
#include"bihua.h"
#include<stdlib.h>
#include<cstring>
#include<memory.h>
#include<string.h>
#include<vector>
#include "the_main.h"



using namespace std;

class neighborhood
{
public:
	int number;
	int x, y;
};


bi_hua & bi_hua::operator=(bi_hua & coper)
{
	
	for(int i=0;i<max_size;i++)
		for (int j = 0; j < max_size; j++)
		{
			if (coper.self[i][j] == 1)
				this->self[i][j] = 1;
			else if (coper.self[i][j] == 2)
				this->self[i][j] = 2;
		}
	return * this;
}

bi_hua * delete_self(bi_hua * head)
{
	bi_hua * temp;
	bi_hua * sd=head;
	if (sd->next != NULL)
	{
		temp = sd->next;
		if (sd->before != NULL)
		{
			sd->before->next = temp;
			temp->before = sd->before;
			delete head;
			return temp;
		}
		else
		{
			temp->before = NULL;
			delete head;
			return temp;
		}
	}
	else
	{
		temp = sd->before;
		temp->next = NULL;
		delete head;
		return temp;
	}
}

bi_hua * create_next(bi_hua * head)
{
	head->next = new bi_hua;
	head->next->flag = 1;
	head->next->before = head;
	return head->next;
	
}

class one_room
{
public:                                                   
	void get_room(int * * img, int x, int y, int w, int h);
	void get_room(int img[max_size][max_size], int x, int y, int w, int h);
	
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

void one_room::get_room(int img[max_size][max_size], int x, int y, int w, int h)
{
	width = w;
	high = h;
	neighbor[0] = x - 1 >= 0 && y - 1 >= 0 ? img[x - 1][y - 1] : 0;
	nerghbord[0].x = x - 1;
	nerghbord[0].y = y - 1;
	nerghbord[0].number = neighbor[0];

	neighbor[1] = x - 1 >= 0 ? img[x - 1][y] : 0;
	nerghbord[1].x = x - 1;
	nerghbord[1].y = y;
	nerghbord[1].number = neighbor[1];

	neighbor[2] = x - 1 >= 0 && y + 1<width ? img[x - 1][y + 1] : 0;
	nerghbord[2].x = x - 1;
	nerghbord[2].y = y + 1;
	nerghbord[2].number = neighbor[2];


	neighbor[3] = y - 1 >= 0 ? img[x][y - 1] : 0;
	nerghbord[3].x = x;
	nerghbord[3].y = y - 1;
	nerghbord[3].number = neighbor[3];

	neighbor[4] = y + 1<width ? img[x][y + 1] : 0;
	nerghbord[4].x = x;
	nerghbord[4].y = y + 1;
	nerghbord[4].number = neighbor[4];

	neighbor[5] = x + 1<high&&y - 1 >= 0 ? img[x + 1][y - 1] : 0;
	nerghbord[5].x = x + 1;
	nerghbord[5].y = y - 1;
	nerghbord[5].number = neighbor[5];

	neighbor[6] = x + 1<high ? img[x + 1][y] : 0;
	nerghbord[6].x = x + 1;
	nerghbord[6].y = y;
	nerghbord[6].number = neighbor[6];

	neighbor[7] = x + 1<high&&y + 1<width ? img[x + 1][y + 1] : 0;
	nerghbord[7].x = x + 1;
	nerghbord[7].y = y + 1;
	nerghbord[7].number = neighbor[7];

	return;
}


int count_point(one_room new_room);
int count_point2(one_room new_room);
float get_slope(bi_hua * bi,int flag);
bool is_in(bi_hua * bi_1, bi_hua * bi_2);
bool is_none(bi_hua * bi);
void print_bihua2(bi_hua * head);
/*笔画合并函数*/

void combine_bihua(bi_hua * yuan1,bi_hua * yuan2)
{
	bi_hua * now_bi = yuan1;
	bi_hua * now_bi1 = yuan2;
	bi_hua * second_bi = yuan1;
	bi_hua * second_bi1 = yuan2;//yuan1有交点，yuan2无交点

	float now_bi_slope = 0;
	float second_bi_slope = 0;

	while (now_bi != NULL&& now_bi1!=NULL)
	{
		cout << "now" << endl;
		now_bi_slope = get_slope(now_bi1,1);
		if (now_bi_slope == 500000)
		{
			now_bi1 = now_bi1->next;
			now_bi = now_bi->next;
			continue;
		}
		second_bi = yuan1;
		second_bi1 = yuan2;
		while (second_bi != NULL&&second_bi1 != NULL)
		{
			//print_bihua2(now_bi);
			//print_bihua2(second_bi);

			second_bi_slope = get_slope(second_bi1, 1);
			if (second_bi_slope != 500000 &&fabs(now_bi_slope - second_bi_slope) == 0&& second_bi != now_bi)
			{

				if (is_in(now_bi, second_bi) == true)
				{
					print_bihua2(now_bi1);
					print_bihua2(second_bi1);
					*now_bi = *second_bi;
					second_bi = delete_self(second_bi);
					second_bi1 = delete_self(second_bi1);
					now_bi->flag = 0;
					combine_bihua(yuan1, yuan2);
					second_bi = yuan1;
					second_bi1 = yuan2;
					continue;
					
				}
			}
			second_bi = second_bi->next;
			second_bi1 = second_bi1->next;
		}
		now_bi1 = now_bi1->next;
		now_bi = now_bi->next;
	}


	
}

void combine_bihua2(bi_hua * yuan1, bi_hua * yuan2) //竖直方向合并
{
	bi_hua * now_bi = yuan1;
	bi_hua * now_bi1 = yuan2;
	bi_hua * second_bi = yuan1;
	bi_hua * second_bi1 = yuan2;//yuan1有交点，yuan2无交点

	float now_bi_slope = 0;
	float second_bi_slope = 0;

	while (now_bi != NULL && now_bi1 != NULL )
	{

		now_bi_slope = get_slope(now_bi1, 2);
		if (now_bi_slope == 500000)
		{
			now_bi1 = now_bi1->next;
			now_bi = now_bi->next;
			continue;
		}
		second_bi = yuan1;
		second_bi1 = yuan2;
		while (second_bi != NULL && second_bi1 != NULL)
		{
			//print_bihua2(now_bi);
			//print_bihua2(second_bi);
			second_bi_slope = get_slope(second_bi1, 2);
			if (second_bi_slope != 500000 && fabs(now_bi_slope - second_bi_slope) ==0&& second_bi != now_bi)
			{
				if (is_in(now_bi, second_bi) == true)
				{
					*now_bi = *second_bi;
					second_bi = delete_self(second_bi);
					second_bi1 = delete_self(second_bi1);
					now_bi->flag = 0;
					combine_bihua2(yuan1, yuan2);
					second_bi = yuan1;
					second_bi1 = yuan2;
					continue;

				}
			}
			second_bi = second_bi->next;
			second_bi1 = second_bi1->next;
		}
		now_bi1 = now_bi1->next;
		now_bi = now_bi->next;
	}
}

/*获得其中一个笔画*/
bi_hua * get_one_hua(int ** arry,int x,int y,bi_hua * new_bi)
{
	one_room new_room;
	new_room.get_room(arry, x, y, max_size, max_size);
	if (count_point(new_room) == 0)
	{
		new_bi->self[x][y] = 1;
		return new_bi;
	}
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
/*判断提取的笔画是否为空*/
bool is_none(bi_hua * bi)
{
	bi_hua * had=bi;
	int count = 0;
	for (int i = 0; i <max_size; i++)
		for (int j = 0; j < max_size; j++)
			if (had->self[i][j] == 1)
				count++;
	if (count == 0||count<=2)
		return false;
	else
		return true;
}

/*剔除多余交点*/
bi_hua * delet_more(bi_hua * bi, int x, int y, int array1[max_size][max_size] = { 0 })
{
	one_room new_room;
	new_room.get_room(array1, x, y, max_size, max_size);
	if (count_point2(new_room) == 0)
		return bi;
	
	for (int k = 0; k < 8; k++)
	{
		if (new_room.neighbor[k] == 1)
		{
			array1[x][y] = 0;
			bi->self[x][y] = 3;
			bi->flag = 1;
			delet_more(bi, new_room.nerghbord[k].x, new_room.nerghbord[k].y, array1);
		}
		else if (new_room.neighbor[k] == 2)
		{
			array1[x][y] = 0;
			bi->self[x][y] = 4;
			bi->flag = 1;
			delet_more(bi, new_room.nerghbord[k].x, new_room.nerghbord[k].y, array1);
		}
	}
		
}

//获得离散笔画斜率
float get_slope(bi_hua * bi,int flag)
{
	one_room new_room;
	int x1=0, y1=0, x2=0, y2=0;
	int count = 0;
	float slope=0;
	float slope2 = 0;
	for(int i=0;i<max_size;i++)
		for (int j = 0; j < max_size; j++)
		{
			new_room.get_room(bi->self, i, j, max_size, max_size);
			if (count_point(new_room) == 1 && bi->self[i][j] == 1)
			{
				if (count == 0)
				{
					x1 = i; y1 = j;
					count++;
				}
				else if (count == 1)
				{
					x2 = i; y2 = j;
					count++;
				}
			}
		}
	if (count > 2||count<2)
		return 500000;
	else
	{
		if (flag == 1 && y2 - y1 != 0)
		{
			slope = (x2 - x1) / (y2 - y1);
			cout << x1 << y1 << ' ' << x2 << y2 << endl;
			return slope;
		}
		else if (flag == 2 && x2 - x1 != 0)
		{
			slope2 = (y2 - y1) / (x2 - x1);
			cout << x1 << y1 << ' ' << x2 << y2 << endl;
			return slope2;
		}
		else
			return 500000;
	}
}


//判断重合
bool is_in(bi_hua * bi_1, bi_hua * bi_2)
{
	for (int i = 0; i<max_size; i++)
		for (int j = 0; j < max_size; j++)
		{
			if (bi_1->self[i][j] == bi_2->self[i][j]&& bi_1->self[i][j] ==2)
			{
				return true;
			}
		}
	return false;
}

/*笔画打印测试 打印该链表所有笔画*/
void print_bihua(bi_hua * head)
{
	bi_hua * print_bi = head;
	while (print_bi != NULL)
	{
		/*if (is_none(print_bi) == false)
		{
			print_bi = print_bi->next;
			continue;
		}*/
		std::cout << "打印壁画" << endl;
		for (int i = 0; i < max_size; i++)
		{
			for (int j = 0; j <max_size; j++)
				{
					if (print_bi->self[i][j] == 1)
						std::cout << '1';
					else if (print_bi->self[i][j] == 2)
						std::cout << '2';
					else
						std::cout << ' ';
				}
			std::cout << endl;
		}
		std::cout << "该壁画结束" << endl;
		print_bi = print_bi->next;
	}

}


/* 打印一个笔画*/
void print_bihua2(bi_hua * head)
{
	bi_hua * print_bi= head;
	/*if (is_none(print_bi) == false)
		return ;
		*/
	std::cout << "该壁画开始" << endl;
		for (int i = 0; i < max_size; i++)
		{
			for (int j = 0; j < max_size; j++)
			{
				if (print_bi->self[i][j] == 1)
					std::cout << '1';
				else if (print_bi->self[i][j] == 2)
					std::cout << '2';
				else
					std::cout << ' ';
			}
			std::cout << endl;
		}
		std::cout << "该壁画结束" << endl;
	
}
//得到周围8点的权值不包括标记为2的点
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


//计算周围8点权值包括标记的交点
int count_point2(one_room new_room)
{
	int i;
	int count = 0;
	for (i = 0; i < 8; i++)
	{
		if (new_room.neighbor[i] == 1||new_room.neighbor[i] == 2)
			count++;
	}
	return count;
}


//交点处理
bi_hua * do_main(Mat &srcimage) //传递的为单通道图像
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


	int **array2;
	array2 = new int *[srcimage.rows];
	for (int i = 0; i<srcimage.rows; ++i)
		array2[i] = new int[srcimage.cols];
	

	for (int i = 0; i<row; i++)
		for (int j = 0; j < col; j++)
		{
			array2[i][j] = 0;
		}
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

	/*删除零散点*/
	for (int i = 0; i<row; i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1, i, j, col, row);
			if (count_point(test) == 0 && array1[i][j] == 1)
			{
				array1[i][j] = 0;
			}
		}
	
	/*标记删除交点坐标*/
	int flag[max_size][max_size] = { 0 };
	for(int i=0;i<row;i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1,i,j,col,row);
			if (count_point(test) > 2&&array1[i][j] == 1)
			{
				flag[i][j] = 1;
			}
		}

	/*标记交叉点*/
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (flag[i][j] == 1)
			{
		
				array1[i][j] = 2;
			}
		}
		std::cout << endl;
	}

	/*将交点提取后的零散点放入*/
	for (int i = 0; i<row; i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1, i, j, col, row);
			if (count_point(test) == 0 && array1[i][j] == 1)
			{
				array1[i][j] = 2;
				flag[i][j] = 1;
			}
		}

	/*打印删除后的*/
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (array1[i][j] == 1)
			{
				std::cout << '1';
			}
			else
				std::cout << ' ';
		}
		std::cout << endl;
	}
	
	
	/*笔画提取   该提取笔画为零散的*/
	bi_hua * new_bi;
	bi_hua * old_bi, * old_head;
	bi_hua * head;
	new_bi = new bi_hua;
	old_bi = new bi_hua;
	
	head = new_bi;
	old_head = old_bi;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
		
			if (array1[i][j] == 1)
			{
				get_one_hua(array1, i, j, new_bi);
				new_bi = create_next(new_bi);
			}
		}
	}
	new_bi = head;
	while (new_bi != NULL)
	{

		if (is_none(new_bi) == false)
		{
			//print_bihua2(new_bi);
			new_bi = delete_self(new_bi);
		}
		else
			new_bi = new_bi->next;
	}
	//print_bihua(head);
	/*复制new_bi到old_bi*/
	new_bi = head;
	while (new_bi != NULL)
	{
			*old_bi = *new_bi;
			//print_bihua2(old_bi);
			//print_bihua2(new_bi);
			old_bi = create_next(old_bi);
		    new_bi = new_bi->next;
	}
//	cout << count << "--" << count1 << endl;
	//print_bihua(old_head);
	//将交点放入零散笔画中
	bi_hua * input_bi = head;
	while (input_bi != NULL)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{

				if (flag[i][j] == 1)
				{
					input_bi->self[i][j] = 2;
				}
			}
		}
	
		input_bi = input_bi->next;
	}
	//print_bihua(head);


	/*剔除多余交点*/
	input_bi = head;
	while (input_bi != NULL)
	{
		int array1[max_size][max_size] = { 0 };
		
		for (int k = 0; k < max_size; k++)
			for (int f = 0; f < max_size; f++)
				array1[k][f] = input_bi->self[k][f];
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{

				if (array1[i][j] == 1)
				{
					delet_more(input_bi, i, j,array1);
				}
			}
		}
		input_bi = input_bi->next;
	}
	input_bi = head;
	while (input_bi != NULL)
	{
		for (int i = 0; i < max_size; i++)
			for (int j = 0; j < max_size; j++)
			{
				if (input_bi->self[i][j] == 2)
					input_bi->self[i][j] = 0;
				else if (input_bi->self[i][j] == 3)
					input_bi->self[i][j] = 1;
				else if (input_bi->self[i][j] == 4)
					input_bi->self[i][j] = 2;
			}
		input_bi = input_bi->next;
	}
    //print_bihua(head);

	/*将零散笔画合并*/

	bi_hua * now_bi = head; /*融合交点后的笔画的指针*/
	bi_hua * jisuan_old_bi = old_head; /*没有融合交点的指针*/
	




	std::cout << "合并开始:" << endl;
	combine_bihua(now_bi, jisuan_old_bi);
	//bi_hua * print_bi = head;
	//print_bihua(print_bi);
	combine_bihua2(now_bi, jisuan_old_bi);

	
	now_bi = head;


	
	/*print 测试*/

	std::cout << "end" << endl;
	return head;
}


//迭代法笔画还原
void bi_hua_before(int array2[max_size][max_size], bi_hua * do_head,int x, int y)
{
	one_room new_room;
	one_room other_room;
	new_room.get_room(array2, x, y, max_size, max_size);
	other_room.get_room(do_head->self, x, y, max_size,max_size);
	if (count_point(new_room) == 0)
	{
		do_head->self[x][y] = 1;
		return;
	}
	for (int i = 0; i < 8; i++)
		if (other_room.neighbor[i] == 2)
		{
			do_head->self[x][y] = 1;
			return;
		}

	for(int i=0;i<8;i++)
		if (new_room.neighbor[i] == 1)
		{
			array2[x][y] = 0;
			do_head->self[x][y] = 1;
			bi_hua_before(array2, do_head, new_room.nerghbord[i].x, new_room.nerghbord[i].y);
		}
}

//笔画还原处理
void get_before(bi_hua * head, int array2[max_size][max_size] )
{
	bi_hua * do_head = head;
	vector< vector<int> > array1(max_size);
	for (int i = 0; i<max_size; i++)
		array1[i].resize(max_size);




	while (do_head != NULL) //扩大交点腐蚀
	{
		for (int i = 0; i < max_size; i++)
			for (int j = 0; j < max_size; j++)
				array1[i][j] = 0;
		for(int i=0;i<max_size;i++)
			for (int j = 0; j < max_size; j++)
			{
				if (do_head->self[i][j] == 2)
				{
					one_room new_room;
					new_room.get_room(do_head->self, i, j, max_size, max_size);
					array1[i][j] = 5;
					for (int m = 0; m < 8; m++)
					{
						array1[new_room.nerghbord[m].x][new_room.nerghbord[m].y] = 5;
					}
						
				}
			}
		for (int i = 0; i<max_size; i++)
			for (int j = 0; j < max_size; j++)
			{
				if (array1[i][j] == 5)
					do_head->self[i][j] = 2;
			}
		do_head = do_head->next;
	}
	
	//运用迭代法还原处理
	do_head = head;
	while (do_head != NULL)
	{
		int arry3[max_size][max_size];
		for (int i = 0; i<max_size; i++)
			for (int j = 0; j < max_size; j++)
			{
				arry3[i][j] = array2[i][j];
			}
		for(int i=0;i<max_size;i++)
			for (int j = 0; j < max_size; j++)
			{
				if (do_head->self[i][j] == 1)
					bi_hua_before(arry3, do_head,i,j);
			}
		do_head = do_head->next;
	}
	//print_bihua(head);

}
