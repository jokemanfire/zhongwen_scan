/*��ñʻ�*/
#include<iostream>
#include"bihua.h"
#include<stdlib.h>
#include<cstring>
#include<memory.h>
#include<string.h>
#include<vector>
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
	bi_hua * next=NULL;
	bi_hua * head=NULL;
	bi_hua & operator=(bi_hua & coper); //�ʻ����Ʋ���������
	
};
bi_hua & bi_hua::operator=(bi_hua & coper)
{
	
	for(int i=0;i<max;i++)
		for (int j = 0; j < max; j++)
		{
			if (coper.self[i][j] == 1)
				this->self[i][j] = 1;
		}
	return * this;
}
class one_room
{
public:                                                   
	void get_room(int * * img, int x, int y, int w, int h);
	void get_room(int img[max][max], int x, int y, int w, int h);
	
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

void one_room::get_room(int img[max][max], int x, int y, int w, int h)
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
/*�ʻ��ϲ�����*/

void combine_bihua(bi_hua * yuan1,bi_hua * yuan2,bi_hua * bi_yuan)
{
	bi_hua * head1= yuan1;   //head1Ϊ�н���  head2Ϊ�޽���
	bi_hua * head1_2 = yuan1;
	bi_hua * head2 = yuan2;
	bi_hua * head2_2 = yuan2;
	float slope1 = 0;
	float slope2 = 0;

	
	bi_hua * bi_result = bi_yuan;
	
	while (head1 != NULL)   /*��һ�ֵ���*/
	{
		head1_2 = yuan1;
		head2_2 = yuan2;
		slope1 = get_slope(head2,1);
		if (slope1 == 500000)
		{
			head1 = head1->next;
			head2 = head2->next;
			continue;
		}
		while (head1_2 != NULL)
		{
			slope2 = get_slope(head2_2,1);
			if (slope2 == 500000)
			{
				head1_2 = head1_2->next;
				head2_2 = head2_2->next;
				continue;
			}
			if (fabs(slope1 - slope2)<0.37 && head1_2->flag != 0 ) //��б�ʽ����ж�
			{
				if (is_in(head1, head1_2) == true&&head1!= head1_2&& head1_2->flag == 1)  //�Խ��������ж�
				{
					//cout << "the before 1" << endl;
					//print_bihua2(head1);
					*bi_result = *head1;
					*bi_result = *head1_2;
					//cout << "the second " << endl;
					//print_bihua2(head1_2);
					//print_bihua2(bi_result);
					bi_result->next = new bi_hua;
					bi_result->flag = 1;
					bi_result = bi_result->next;
					head1->flag = 0;
				}
			}
			head1_2 = head1_2->next;
			head2_2 = head2_2->next;
		}
		head1 = head1->next;
		head2 = head2->next;
	}

	head1 = yuan1;
	head2 = yuan2;
	while (head1 != NULL)  /*�ڶ��ֵ���*/
	{
		head1_2 = yuan1;
		head2_2 = yuan2;
		slope1 = get_slope(head2,2);
		if (slope1 == 500000)
		{
			head1 = head1->next;
			head2 = head2->next;
			continue;
		}
		while (head1_2 != NULL)
		{
			slope2 = get_slope(head2_2,2);
			if (slope2 == 500000)
			{
				head1_2 = head1_2->next;
				head2_2 = head2_2->next;
				continue;
			}
			if (fabs(slope1-slope2) <0.37 && head1_2->flag != 0 &&head1 != head1_2) //��б�ʽ����ж�
			{
				if (is_in(head1, head1_2) == true)  //�Խ��������ж�
				{
					*bi_result = *head1;
					*bi_result = *head1_2;
					//print_bihua2(bi_result);
					bi_result->next = new bi_hua;
					bi_result->flag = 1;
					bi_result = bi_result->next;
					head1->flag = 0;
				}
			}
			head1_2 = head1_2->next;
			head2_2 = head2_2->next;
		}
		head1 = head1->next;
		head2 = head2->next;
	}
	head1 = yuan1;
	
	while (head1 != NULL)
	{
		if (head1->flag == 1 && is_none(head1))
		{
			*bi_result = *head1;
			bi_result->flag = 1;
			bi_result->next = new bi_hua;
			bi_result = bi_result->next;
			
		}
		head1 = head1->next;
	}
	return;
}
/*�������һ���ʻ�*/
bi_hua * get_one_hua(int ** arry,int x,int y,bi_hua * new_bi)
{
	one_room new_room;
	new_room.get_room(arry, x, y, max, max);
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
/*�ж���ȡ�ıʻ��Ƿ�Ϊ��*/
bool is_none(bi_hua * bi)
{
	int count = 0;
	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
			if (bi->self[i][j] == 1)
				count++;
	if (count == 0||count<=2)
		return false;
	else
		return true;
}

/*�޳����ཻ��*/
bi_hua * delet_more(bi_hua * bi, int x, int y, int array1[max][max] = { 0 })
{
	one_room new_room;
	new_room.get_room(array1, x, y, max, max);
	if (count_point2(new_room) == 0)
		return bi;
	
	for(int k=0;k<8;k++)
	      if (new_room.neighbor[k] == 1||new_room.neighbor[k] == 2)
		  {
			  array1[x][y] = 0;
			  bi->self[x][y] = 3;
			  bi->flag = 1;
			  delet_more(bi, new_room.nerghbord[k].x, new_room.nerghbord[k].y,array1);
		  }
		
}

//�����ɢ�ʻ�б��
float get_slope(bi_hua * bi,int flag)
{
	one_room new_room;
	int x1=0, y1=0, x2=0, y2=0;
	int count = 0;
	float slope=0;
	float slope2 = 0;
	for(int i=0;i<max;i++)
		for (int j = 0; j < max; j++)
		{
			new_room.get_room(bi->self, i, j, max, max);
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
		if(flag == 1)
		slope = fabs(x2 - x1) / fabs(y2 - y1);
		return slope;
		if(flag == 2)
		slope2 = fabs(y2 - y1) / fabs(x2 - x1);
		return slope2;
	}
}


//�ж��غ�
bool is_in(bi_hua * bi_1, bi_hua * bi_2)
{
	for (int i = 0; i<max; i++)
		for (int j = 0; j < max; j++)
		{
			if (bi_1->self[i][j] == bi_2->self[i][j]&& bi_1->self[i][j] == 1)
			{
				return true;
			}
		}
	return false;
}

/*�ʻ���ӡ���� ��ӡ���������бʻ�*/
void print_bihua(bi_hua * head)
{
	bi_hua * print_bi = head;
	while (print_bi != NULL)
	{
		if (is_none(print_bi) == false)
		{
			print_bi = print_bi->next;
			continue;
		}
		cout << "��ӡ�ڻ�" << endl;
		for (int i = 0; i < max; i++)
		{
			for (int j = 0; j <max; j++)
				{
					if (print_bi->self[i][j] == 1)
						cout << '1';
					else if (print_bi->self[i][j] == 2)
						cout << '2';
					else
						cout << ' ';
				}
			cout << endl;
		}
		cout << "�ñڻ�����" << endl;
		print_bi = print_bi->next;
	}

}


/* ��ӡһ���ʻ�*/
void print_bihua2(bi_hua * head)
{
	bi_hua * print_bi= head;
	if (is_none(print_bi) == false)
		return ;
	cout << "�ñڻ���ʼ" << endl;
		for (int i = 0; i < max; i++)
		{
			for (int j = 0; j < max; j++)
			{
				if (print_bi->self[i][j] == 1)
					cout << '1';
				else if (print_bi->self[i][j] == 2)
					cout << '2';
				else
					cout << ' ';
			}
			cout << endl;
		}
		cout << "�ñڻ�����" << endl;
	
}
//�õ���Χ8���Ȩֵ���������Ϊ2�ĵ�
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


//������Χ8��Ȩֵ������ǵĽ���
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


//���㴦��
int do_main(Mat &srcimage) //���ݵ�Ϊ��ͨ��ͼ��
{
	int col, row;
	col = srcimage.cols;
	row = srcimage.rows;

    one_room test;

	/*������ص�Ķ�ά����*/
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
	/*��ά���鸴��*/
	for (int i = 0; i<row; i++)
		for (int j = 0; j < col; j++)
		{
			int b = srcimage.at<uchar>(i, j);
			if (b < 20)
				array1[i][j] = 0;
			else
				array1[i][j] = 1;
	
		}

	/*ɾ����ɢ��*/
	for (int i = 0; i<row; i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1, i, j, col, row);
			if (count_point(test) == 0 && array1[i][j] == 1)
			{
				array1[i][j] = 0;
			}
		}
	
	/*���ɾ����������*/
	int flag[max][max] = { 0 };
	for(int i=0;i<row;i++)
		for (int j = 0; j <col; j++)
		{
			test.get_room(array1,i,j,col,row);
			if (count_point(test) > 2&&array1[i][j] == 1)
			{
				flag[i][j] = 1;
			}
		}

	/*��ǽ����*/
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (flag[i][j] == 1)
			{
		
				array1[i][j] = 2;
			}
		}
		cout << endl;
	}

	/*��������ȡ�����ɢ�����*/
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

	/*��ӡɾ�����*/
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (array1[i][j] == 1)
			{
				cout << '1';
			}
			else
				cout << ' ';
		}
		cout << endl;
	}
	
	
	/*�ʻ���ȡ   ����ȡ�ʻ�Ϊ��ɢ��*/
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
				new_bi->next = new bi_hua;
				new_bi = new_bi->next;
				new_bi->head = head;
			}
		}
	}
	/*����new_bi��old_bi*/
	new_bi = head;
	while (new_bi != NULL)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				old_bi->self[i][j] = new_bi->self[i][j];
				old_bi->flag = 1;
			}
		}
		old_bi->next = new bi_hua;
		old_bi = old_bi->next;
		new_bi = new_bi->next;
	}
	
	//�����������ɢ�ʻ���
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


	/*���Բ鿴��ɢ�ʻ�
	 input_bi = head;
	while (input_bi != NULL)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{

				if (input_bi->self[i][j] == 1)
				{
					array2[i][j] = 1;
				}
				else if (input_bi->self[i][j] == 2)
				{
					array2[i][j] = 2;
				}
			}
		}

		input_bi = input_bi->next;
	}
	cout << "����" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (array2[i][j] == 1)
			{
				cout << '1';
			}
			else if (array2[i][j] == 2)
			{
				cout << ' ';
			}
			else
				cout << ' ';
		}
		cout << endl;
	}
	*/
	/*�޳����ཻ��*/
	input_bi = head;
	while (input_bi != NULL)
	{
		int array1[max][max] = { 0 };
		
		for (int k = 0; k < max; k++)
			for (int f = 0; f < max; f++)
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
		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
			{
				if (input_bi->self[i][j] != 3)
					input_bi->self[i][j] = 0;
				else if (input_bi->self[i][j] == 3)
					input_bi->self[i][j] = 1;
			}
		input_bi = input_bi->next;
	}
    //print_bihua(head);

	/*����ɢ�ʻ��ϲ�*/
	bi_hua * second_bi; /*�洢�ϲ��ıʻ�*/
	bi_hua * head2;  /*�洢�ϲ��ʻ�����ı�ͷ*/
	bi_hua * now_bi = head; /*�ںϽ����ıʻ���ָ��*/
	bi_hua * jisuan_old_bi = old_head; /*û���ںϽ����ָ��*/
	
	second_bi = new bi_hua;
	second_bi->head = second_bi;

	head2 = second_bi;

	cout << "�ϲ���ʼ:" << endl;
	combine_bihua(now_bi, jisuan_old_bi, head2);
	/*print ����*/
	bi_hua * print_bi = head2;
	print_bihua(print_bi);
	
	/*�ʻ���ԭ*/
	
	
	cout << "end" << endl;
	return 1;
}




