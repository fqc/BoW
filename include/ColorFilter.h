#ifndef _COLORFILTER
#define _COLORFILTER
#include "ColorHist.h"
#include <cv.h>
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <iostream>

using namespace std;

typedef struct PCM
{
	string loc;	//ͼƬ·��
	long index;//����
	double matchValue;	//����ɫ�Ƚϻ�õ�Ȩֵ
} PCM;

class ColorFilter 
{
public:
	vector<PCM> pcm;	//����ͼƬ��Ϣ
private:
	ColorHist hist;
	int h_bins, s_bins;
public:
	//��ColorHist::h_bins, ColorHist::s_bins��ֵ
	void setBins(int h, int s);
	//rgb��ɫת��Ϊhsv��ɫ
	void RGBToHSV(vector<CvScalar> &rgb, vector<CvScalar> &hsv);
	//hsv��ɫתhsv��ɫ
	void HSVToRGB(vector<CvScalar> &hsv, vector<CvScalar> &rgb);
	//pL��ͼƬ������, hsv:��ɫ��
	//���ܣ�ͼƬ����hsv������ƥ�䣬��ͼƬ��������������
	void match(vector<int> &pL, vector<CvScalar> &hsv, vector<CvScalar> &notHsv, exData &database);
	~ColorFilter();
};
#endif
