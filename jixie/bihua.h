#pragma once
#include <opencv2/opencv.hpp>
#define max_size 100
using namespace cv;


//int iss_none(int arry2[3][3]);
class bi_hua
{
public:
	int flag = 0;

	int self[max_size][max_size] = { 0 };
	bi_hua * next = NULL;
	bi_hua * head = NULL;
	bi_hua & operator=(bi_hua & coper); //±Ê»­¸´ÖÆ²Ù×÷·ûÖØÔØ

};
bi_hua * do_main(Mat &srcimage);
void get_before(bi_hua * head, int array2[max_size][max_size]);
class lines {
public:
	lines(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) :startp_x(x1), startp_y(y1), endp_x(x2), endp_y(y2) {};
	void get_one(int x1, int x2, int y1, int y2)
	{
		startp_x = x1;
		startp_y = y1;
		endp_x = x2;
		endp_y = y2;
	}
	int get_sx() { return startp_x; }
	int get_sy() { return startp_y; }
	int get_ex() { return endp_x; }
	int get_ey() { return endp_y; }
private:
	int startp_x, startp_y;
	int endp_x, endp_y;
};



