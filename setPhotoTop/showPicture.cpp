#include "showPicture.h"
#include <tlhelp32.h>
Mat img;


extern  int processWidth;
extern  int processHigth;
unsigned char showFlag=0;	//ȷ����ʾͼƬ�ı�ʶ��
/************************************************************************
* ��ʾװ���ϳ�ͼ

************************************************************************/
void showPictureEquipment()
{
	img=imread("..\\photo.jpg");
	resize(img, img, Size(processHigth, processWidth), 0, 0, INTER_LINEAR);
	imshow("show", img);
	showFlag = SHOWEQUIPMENT;
}

/************************************************************************
* ��ʾ�������ͼ

************************************************************************/
void showPicturelingfeng()
{
	img = imread("..\\���.jpg");
	resize(img, img, Size(processHigth, processWidth), 0, 0, INTER_LINEAR);
	imshow("show", img);
	showFlag = SHOWLINGFENG;
}


/************************************************************************
* ��ʾȭͷͼƬ����С

************************************************************************/
void showNewPlayOne()
{
	img = imread("..\\one.jpg");
	resize(img, img, Size(processHigth, processWidth), 0, 0, INTER_LINEAR);
	imshow("show", img);
	showFlag = SHOWNEWPLAYONE;
}

/************************************************************************
* ��ʾȭͷͼƬ����С

************************************************************************/
void showNewPlayTwo()
{
	img = imread("..\\two.jpg");
	resize(img, img, Size(processHigth, processWidth), 0, 0, INTER_LINEAR);
	imshow("show", img);
	showFlag = SHOWPLAYTWO;
}

/************************************************************************
* ��ʾÿ���ȼ����ĳ���

************************************************************************/
void showChampionDropRates()
{
	img = imread("..\\championDropRates.jpg");
	resize(img, img, Size(processHigth, processWidth), 0, 0, INTER_LINEAR);
	imshow("show", img);
	showFlag = SHOWCHAMPIONDROPRATES;
}

/************************************************************************
* ������ʾͼƬ��С

************************************************************************/
void resizePicture()
{
	switch (showFlag)
	{
	case SHOWEQUIPMENT:
		showPictureEquipment();
		break;
	case SHOWLINGFENG:
		showPicturelingfeng();
		break;
	case SHOWNEWPLAYONE:
		showNewPlayOne();
		break;
	case SHOWPLAYTWO:
		showNewPlayTwo();
		break;
	case SHOWCHAMPIONDROPRATES:
		showChampionDropRates();
		break;
	default:
		break;
	}
}



/************************************************************************
* ����߳�id

************************************************************************/
int getThreadID(int pid)
{
	THREADENTRY32 te32;
	te32.dwSize = sizeof(te32);
	HANDLE Snapshot_thread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (Snapshot_thread != INVALID_HANDLE_VALUE)
	{
		if (Thread32First(Snapshot_thread, &te32))
		{
			do
			{
				if (te32.th32OwnerProcessID == pid)
				{
					return te32.th32ThreadID;
				}
			} while (Thread32Next(Snapshot_thread, &te32));
		}
	}
	CloseHandle(Snapshot_thread);
	return 0;
}


/************************************************************************
* ��ʾ����id

************************************************************************/
int getPID(char *target)
{
	PROCESSENTRY32 pe32;
	MODULEENTRY32 me32;
	HANDLE hProcess, hSnapshot_proc, hSnapshot_mod;
	pe32.dwSize = sizeof(pe32);
	hSnapshot_proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hSnapshot_proc, &pe32))
	{
		do
		{
			if (!strcmp(pe32.szExeFile, target))
			{
				return pe32.th32ProcessID;
			}
		} while (Process32Next(hSnapshot_proc, &pe32));
	}
	CloseHandle(hSnapshot_proc);
	return 0;
}