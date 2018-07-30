#pragma once
void do_main(int ** array2, int rows, int cols);
//int iss_none(int arry2[3][3]);
int iss_none(int ** array2);
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