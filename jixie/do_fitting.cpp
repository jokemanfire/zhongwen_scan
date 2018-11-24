#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include<stdio.h>
#include <memory.h>
#include "do_fitting.h"
using namespace std;

//��С���������غ�������
double sum(vector<double> Vnum, int n);
double MutilSum(vector<double> Vx, vector<double> Vy, int n);
double RelatePow(vector<double> Vx, int n, int ex);
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex);
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[]);
void CalEquation(int exp, double coefficient[]);
double F(double c[], int l, int m);
double Em[6][4];

//�����������ｫ������ϳɶ�������
double * do_fitting(int arry1[max_size][max_size])
{
	int counts = 0;
	for (int i = 0; i<max_size; i++)
		for (int j = 0; j<max_size; j++)
		{
			if (arry1[i][j] == 1)
			{
				counts++;
				break;
			}
		}
	//cout << counts << endl;
	double *array1 = new double[counts];
	double *array2 = new double[counts];

	int k = 0;
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
		{
			if (arry1[i][j] == 1)
			{
				array1[k] = i;
				array2[k] = j;
				k++;
				cout << i << j << "  ";
				break;
			}
			if (k >= counts)
				break;
		}
		if (k >= counts)
			break;
	}
	static double coefficient[5];
	memset(coefficient, 0, sizeof(double) * 5);
	vector<double> vx, vy;
	for (int i = 0; i<counts; i++)
	{

		vx.push_back(array1[i]);
		vy.push_back(array2[i]);
	}
	EMatrix(vx, vy, counts, 3, coefficient);
	//for(int i=1;i<4;i++)
	//{
	//if( isnan(coefficient[i]) == 1 )
	// }
	printf("��Ϸ���Ϊ��y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
	return coefficient;
}

//�ۼ�
double sum(vector<double> Vnum, int n)
{
	double dsum = 0;
	for (int i = 0; i<n; i++)
	{
		dsum += Vnum[i];
	}
	return dsum;
}
//�˻���
double MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
	double dMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dMultiSum += Vx[i] * Vy[i];
	}
	return dMultiSum;
}
//ex�η���
double RelatePow(vector<double> Vx, int n, int ex)
{
	double ReSum = 0;
	for (int i = 0; i<n; i++)
	{
		ReSum += pow(Vx[i], ex);
	}
	return ReSum;
}
//x��ex�η���y�ĳ˻����ۼ�
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
	double dReMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dReMultiSum += pow(Vx[i], ex)*Vy[i];
	}
	return dReMultiSum;
}
//���㷽������������
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[])
{
	for (int i = 1; i <= ex; i++)
	{
		for (int j = 1; j <= ex; j++)
		{
			Em[i][j] = RelatePow(Vx, n, i + j - 2);
		}
		Em[i][ex + 1] = RelateMutiXY(Vx, Vy, n, i - 1);
	}
	Em[1][1] = n;
	CalEquation(ex, coefficient);
}
//��ⷽ��
void CalEquation(int exp, double coefficient[])
{
	for (int k = 1; k<exp; k++) //��Ԫ����
	{
		for (int i = k + 1; i<exp + 1; i++)
		{
			double p1 = 0;

			if (Em[k][k] != 0)
				p1 = Em[i][k] / Em[k][k];

			for (int j = k; j<exp + 2; j++)
				Em[i][j] = Em[i][j] - Em[k][j] * p1;
		}
	}
	coefficient[exp] = Em[exp][exp + 1] / Em[exp][exp];
	for (int l = exp - 1; l >= 1; l--)   //�ش����
		coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
}
//��CalEquation��������
double F(double c[], int l, int m)
{
	double sum = 0;
	for (int i = l; i <= m; i++)
		sum += Em[l - 1][i] * c[i];
	return sum;
}