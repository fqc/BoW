#ifndef _MATCHBASECOLOR
#define _MATCHBASECOLOR
#include <iostream>
#include <fstream>
#include "ColorHist.h"
#include <ctime>

using namespace cv;
using namespace std;
/*
������pictureName[�ļ�·��]�� database:���ݿ���󣨳�Աimage�ѱ���ֵ����indexResult:���ҽ��ͼƬ����
���ܣ��������ݿ�����pictureNameͼƬƥ���ͼƬ�����ҵ���ͼƬ�������浽indexResult��
*/
void matchBaseColor(const char pictureName[], exData &database, vector<int> &indexResult);
#endif