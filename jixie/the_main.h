#pragma once

#include <opencv2/opencv.hpp>
#include<math.h>
#include<string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "bihua.h"
#include <random>
#include"feature.h"
#include <assert.h>
#include<io.h>

using namespace std;
using namespace cv;
class img_print_test
{
public:
	void single_img_print(Mat & src2);
	void multi_img_print(Mat & img2);

};
