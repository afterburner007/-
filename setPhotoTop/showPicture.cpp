#include "showPicture.h"

Mat img;

/************************************************************************
* ��ʾװ���ϳ�ͼ

************************************************************************/
void showPictureEquipment()
{
	img=imread("..\\photo.png");
	resize(img, img, Size(200, 200), 0, 0, INTER_LINEAR);
	namedWindow("show", CV_WINDOW_AUTOSIZE);
	imshow("show", img);
}

/************************************************************************
* ��ʾ�������ͼ

************************************************************************/
void showPicturelingfeng()
{
	img = imread("..\\���.jpg");
	resize(img, img, Size(200, 200), 0, 0, INTER_LINEAR);
	//namedWindow("show", CV_WINDOW_AUTOSIZE);
	imshow("show", img);
}


/************************************************************************
* ��ʾȭͷͼƬ����С

************************************************************************/
void showPicturefist()
{
	img = imread("..\\fist.jpg");
	resize(img, img, Size(20, 20), 0, 0, INTER_LINEAR);
	namedWindow("show", CV_WINDOW_AUTOSIZE);
	imshow("show", img);
}

