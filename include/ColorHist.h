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
	//exData database;	//���ݿ����
	vector<float *> dataVec;	//����mat�е�data����ָ��
	void add(MR t);	//��t��ӵ�resultʸ����ǡ����λ��
	int h_bins, s_bins;	//h������s�����Ļ���
	int hist_size[2];
	/** H �����ı仯��Χ */
	float h_ranges[2]; 
	
	/** S �����ı仯��Χ*/
	float s_ranges[2];
	float *hist_ranges[2];
private:
public:
	//��ȡһ��ͼƬ��ֱ��ͼ
	void pictureHist(const char * pictureName, CvHistogram *& hist);
	void setBins(int h, int s);	//��h_bins, s_bins��ֵ
	//��ȡȫ�����ݵ�data��
	bool readData(const char *db, exData &database);
	//��ȡ�������ݵ�data��
	bool readFewData(vector<int> &fewPicture, exData &database);
	//fileNameƥ���ͼƬ·����index:siftƥ����������,nƥ����������lowestPre��С����
	//��fileName����ֱ��ͼ����������index���бȽϣ����n >= 0 ʹ��n������ʹ�þ��ȣ�����ƥ��ͼƬ����
	int match(CvHistogram *toMatch, vector<int> &index, int n, double lowestPre);
	//д���ݵ�db�ļ���
	bool writeData(const char *db, exData &database);
	//����plLocռλ������������,�������ݿ���ͼƬ·������ɫֱ��ͼ
	bool buildHist(const char * plLoc, exData &database);
	//imgs:����ͼƬ·��
	//��������ͼƬ��ֱ��ͼ
	void buildHist(vector<string> &imgs);
	//�ͷ����ݿռ�
	void release();
	~ColorHist();
};
#endif