
#include"feature.h"

using namespace std;
int extraction(int ** src, float  src2[min_size][min_size],string distpath)
{
	//用10*10的矩阵表示特征向量

	float sum = 0;
	int i, j, k, m;
	for (k = 0; k < 10; k++)
	{
		for (m = 0; m<10; m++)
		{

			for (i = 0 + k * 10; i < 10 + k * 10; i++)
			{
				for (j = 0 + m * 10; j < 10 + m * 10; j++)
				{
					sum += src[i][j];
				}
			}
			src2[k][m] = sum/100;
			sum = 0;
		}
	}
	string distfile = distpath;
	ofstream stn;
	stn.open(distfile, ios::app);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			stn << src[i][j]<<' ';
			//cout << src[i][j];
		}
	
	}
	stn << endl;
	//cout << "写入完毕";
	return 1;
}
//将特征向量存入文件中