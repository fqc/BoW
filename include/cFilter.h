#ifndef _CFILTER
#define _CFILTER
#include "ColorFilter.h"
#include <iostream>


using namespace std;
using namespace cv;
/*
������match������ɸѡ�����飻rgb:�����е���ɫ���飻notRgb:�����е���ɫ����; database:���ݿ���󣨳�Աimage�Ѿ�����ֵ��
*/
void cFilter(vector<int> &match, vector<CvScalar> &rgb, vector<CvScalar> &notRgb, exData &database);
#endif
