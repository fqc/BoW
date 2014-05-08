#ifndef _COLORHIST
#define _COLORHIST
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "exData.hpp"

using namespace std;


//�������ļ��еĽṹ��
typedef struct nameAndHist
{
	string loc;	//ͼƬ�ļ�·��	
	CvHistogram *hist;//��ɫֱ��ͼ
	int index;	//ͼƬ���ڴ������ж�Ӧ���±�
} NAH;
//ƥ�����ṹ��
typedef struct matchResult
{
	string loc;	//ͼƬ·��
	long index;	//ͼƬ���ڴ������ж�Ӧ���±�
	double d;	//ƥ���
} MR;

class ColorHist
{
public:
	//ͼƬƥ����
	vector<MR> result;
	//ͼƬ��ֱ��ͼ
	vector<NAH> data;
private:
	vector<float *> dataVec;	//����mat�е�data����ָ��
	void add(MR t);	//��t��ӵ�result��ǡ����λ��
	int h_bins, s_bins;	//h������s�����Ļ���
	int hist_size[2];
	/** H �����ı仯��Χ */
	float h_ranges[2]; 	
	/** S �����ı仯��Χ*/
	float s_ranges[2];
	float *hist_ranges[2];
private:
public:
	//��ȡһ��ͼƬ��ֱ��ͼ������ֱ��ͼ������hist��
	//pictureName:ͼƬ·��,hist������ͼƬֱ��ͼ
	void pictureHist(const char * pictureName, CvHistogram *& hist);
	//��h_bins, s_bins��ֵ
	void setBins(int h, int s);	
	//��ȡ���ݿ��е����ݵ�data��
	void readData(exData &database);
	//��ȡ���ݿ��в������ݵ�data��
	//fewPictue:ͼƬ�����ݿ��е�������database:���ݿ������
	void readFewData(vector<int> &fewPicture, exData &database);	
	//toMatchֱ��ͼ��ֱ��ͼ���ݿ���бȽϣ�ƥ�������浽����result�У�
	//���n >= 0 ʹ��n������ʹ�þ��ȣ�����ƥ��ƥ����ͼƬ��
	//toMatchƥ���ͼƬֱ��ͼ��nƥ����������lowestPre��С����
	int match(CvHistogram* toMatch, int n, double lowestPre = 0);
	//toMatchֱ��ͼ�����ݿ���������index�������е�ֱ��ͼ���бȽϣ�ƥ�������浽����result�У�
	//���n >= 0 ʹ��n������ʹ�þ��ȣ�����ƥ��ƥ����ͼƬ��
	//toMatchƥ���ͼƬֱ��ͼ��nƥ����������lowestPre��С����
	int match(CvHistogram *toMatch, vector<int> &index, int n, double lowestPre);
	//д���ݵ����ݿ���
	void writeData(exData &database);
	//����ֱ��ͼ,ʧ�ܷ���false
	void buildHist(exData &database);
	//��������ͼƬ��ֱ��ͼ
	//imgs:����ͼƬ·��	
	void buildHist(vector<string> &imgs);
	//�ͷ����ݿռ�
	void release();
	~ColorHist();
};
#endif
