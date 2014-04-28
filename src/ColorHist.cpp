
#include "ColorHist.h"

bool ColorHist::readFewData(vector<int> &fewPicture, exData &database)
{
	data.clear();
	dataVec.clear();
	//database.readHS(h_bins, s_bins);
	for(int i = 0; i < fewPicture.size(); i++)
	{
		NAH t;
		t.loc = database.image[fewPicture[i]].imagePath;
		dataVec.push_back(&(database.image[fewPicture[i]].hs[0]));
		t.hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, hist_ranges, 1);
		cvMakeHistHeaderForArray(2, hist_size, t.hist, &(database.image[fewPicture[i]].hs[0]), hist_ranges, 1);
		t.index = fewPicture[i];
		data.push_back(t);
	}
	return true;
}

bool ColorHist::readData(const char *db, exData &database)
{
	data.clear();
	dataVec.clear();
	//database.readHS(h_bins, s_bins);
	for(int i = 0; i < database.image.size(); i++)
	{
		NAH t;
		t.loc = database.image[i].imagePath;
		dataVec.push_back(&(database.image[i].hs[0]));
		t.hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, hist_ranges, 1);
		cvMakeHistHeaderForArray(2, hist_size, t.hist, &(database.image[i].hs[0]), hist_ranges, 1);
		t.index = i;
		data.push_back(t);
	}
	return true;
	/*char line[100000];
	float *d;
	stringstream s;*/
	//������ݿ�
	/*data.clear();
	dataVec.clear();
	while(!fileIn.eof())
	{
		NAH t;
		fileIn.getline(line, sizeof(line));
		if(strlen(line) == 0)
			continue;
		s << line;
		t.hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, hist_ranges, 1); 
		s >> t.loc;
		d = new float[s_bins * h_bins + 1];
		dataVec.push_back(d);
		for(int i = 0; !s.eof(); i++)
		{
			if(i >= s_bins * h_bins + 1)
				return false;
			s >> d[i];
		}
		cvMakeHistHeaderForArray(2, hist_size, t.hist, d, hist_ranges, 1);
		data.push_back(t);
		s.clear();
	}*/
	/*return true;*/
}

bool cmp(const MR &a,const MR &b)
{
	return a.d > b.d;
}

void ColorHist::add(MR t)
{
	int i;
	for(i = result.size() - 2; i >= 0; i--)
	{
		if((int)(result[i].d * 10000)< (int)(t.d * 10000))
			result[i + 1] = result[i];
		else 
		{
			result[i + 1] = t;
			break;
		}
	}
	if(i == -1)
		result[0] = t;
}

int ColorHist::match(CvHistogram *toMatch, vector<int> &index, int n, double lowestPre)
{
	//��ȡn��ƥ��ͼƬ
	result.clear();
	MR t; 
	if(n > 0)
	{
		for(int i = 0; i < index.size(); i++)
		{
			t.loc = data[index[i]].loc;
			t.index = data[index[i]].index;
			t.d = cvCompareHist(toMatch, data[index[i]].hist, CV_COMP_INTERSECT);
			if(i < n)
			{
				result.push_back(t); continue;
			}
			else if(i == n)
				sort(result.begin(), result.end(), cmp);
			if(t.d > result[result.size() - 1].d)
				add(t);	
		}	
	}
	//��ȡ���ȴ��ڵ���lowestPre��ͼƬ
	else
	{
		for(int i = 0; i < index.size(); i++)
		{
			t.loc = data[index[i]].loc;
			t.index = data[index[i]].index;
			t.d = cvCompareHist(toMatch, data[index[i]].hist, CV_COMP_INTERSECT);
			if(t.d >= lowestPre)
			{
				result.push_back(t);
			}
		}
		sort(result.begin(), result.end(), cmp);
	}
	return 0;
}

bool ColorHist::buildHist(const char * plLoc, exData &database)
{
	NAH t;
	data.clear();
	for(int i = 0; i < database.image.size(); i++)
	{
		t.loc = database.image[i].imagePath;
		t.index = i;
		pictureHist(t.loc.c_str(), t.hist);
		data.push_back(t);
	}
	return true;
	//NAH t;
	//char img_file_name[MAX_PATH];	//����ͼƬ·��
	//data.clear();
	//ifstream file(plLoc);
	//if(!file.is_open())
	//{
	//	return false;
	//}
	//while(!file.eof())
	//{
	//	file.getline(img_file_name, 5000);
	//	if(strlen(img_file_name) == 0)
	//		continue;
	//	t.loc = img_file_name;
	//	pictureHist(img_file_name,  t.hist);
	//	data.push_back(t);
	//}
	//file.close();
	//return true;
}

void ColorHist::buildHist(vector<string> &imgs)
{
	NAH t;
	data.clear();
	for(int i = 0; i < imgs.size(); i++)
	{
		t.loc = imgs[i];
		pictureHist(imgs[i].c_str(), t.hist);
		data.push_back(t);
	}
}

void ColorHist::pictureHist(const char * pictureName, CvHistogram *& hist)
{
	IplImage * src;
  src=cvLoadImage(pictureName);
	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane };

	/** ����ͼ��ת����HSV��ɫ�ռ� */
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
	/** ����ֱ��ͼ����ά, ÿ��ά���Ͼ��� */
	hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, hist_ranges, 1 );
	/** ����H,S����ƽ������ͳ��ֱ��ͼ */
	cvCalcHist( planes, hist, 0, 0 );
	float * f = cvGetHistValue_2D(hist, 0, 0);
	(*f) = 0;

	cvNormalizeHist(hist, 1);
	cvThreshHist(hist, 0.0001);
	cvReleaseImage(&src);
	cvReleaseImage(&hsv);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);
}

void ColorHist::release()
{
	for(int i = 0; i < data.size(); i++)
	{
		cvReleaseHist(&data[i].hist);
	}
	/*for(int i = 0; i < dataVec.size(); i++)
	{
		delete[] dataVec[i];
	}*/
	dataVec.clear();
	data.clear();
	result.clear();
}

bool ColorHist::writeData(const char *db, exData &database)
{

	database.hbin = h_bins;
	database.sbin = s_bins;
	for(int i = 0; i < data.size(); i++)
	{
		for(int j = 0; j < h_bins; j++)
			for(int k = 0; k < s_bins; k++)
				database.image[i].hs.push_back(cvQueryHistValue_2D(data[i].hist, j, k));
	}
	database.writeHS();
	return true;
	/*ofstream fileOut(db);
	if(!fileOut.is_open())
		return false;
	for(int i = 0; i < data.size(); i++)
	{
		fileOut << data[i].loc << " ";
		for(int j = 0; j < h_bins; j++)
			for(int k = 0; k < s_bins; k++)
			{
				fileOut << cvQueryHistValue_2D(data[i].hist, j, k) << " ";
			}
		fileOut << endl;
	}
	fileOut.close();
	return true;*/
}

void ColorHist::setBins(int h, int s)
{
	h_bins = h, s_bins = s;
	hist_size[0] = h_bins, hist_size[1] = s_bins;
	/** H �����ı仯��Χ */
	h_ranges[0] = 0;h_ranges[1] = 180;
	/** S �����ı仯��Χ*/
	s_ranges[0] = 0;s_ranges[1] = 255;
	hist_ranges[0] = h_ranges;hist_ranges[1] =s_ranges;
}

ColorHist::~ColorHist()
{
	release();
}
