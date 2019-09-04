#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "opencv2\opencv.hpp"
#include "showPicture.h"
#include <thread>

using namespace cv;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")



HWND hq;
HHOOK keybordHook;
HHOOK mouseHook;

int   processWidth = SIZEW;
int   processHigth = SIZEH;
/************************************************************************
*���̻ص�����

************************************************************************/
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == 113)   //F2
	{
		showPictureEquipment();
		processHigth = SIZEH;
		processWidth = SIZEW;
	}
	else if (wParam == 114)  //F3
	{
		showPicturelingfeng();
		processHigth = SIZEH;
		processWidth = SIZEW;
	}
	else if (wParam == 115)  //F4
	{
		processHigth = SIZEH;
		processWidth = SIZEW;
		showChampionDropRates();
	}
	else if (wParam == 116)	//F5
	{
		processHigth = SIZEH;
		processWidth = SIZEW;
		showNewPlayOne();
	}
	else if (wParam == 117)	//F6
	{

		processHigth = SIZEH;
		processWidth = SIZEW;
		showNewPlayTwo();
	}
	else if (wParam == 77)		//M
	{
		processHigth = 0.0F;
		processWidth = 0.0F;
	}
	else if (wParam == 46)
	{
		UnhookWindowsHookEx(keybordHook);			//ж��hook
		exit(1);
	}

	return CallNextHookEx(keybordHook, nCode, wParam, lParam);
}



LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCTEX* wheelData = (MOUSEHOOKSTRUCTEX*)lParam;
	if (nCode < 0)
	{
		return ::CallNextHookEx(mouseHook, nCode, wParam, lParam);
	}
	if (wParam == WM_MOUSEWHEEL || wParam == WM_MBUTTONUP)
	{
		if (wheelData->mouseData == (WHEEL_DELTA << 16))   //up
		{
			processHigth += 10;
			processWidth += 10;
			resizePicture();
		}
		else if (wheelData->mouseData == (-WHEEL_DELTA << 16))		//down   wheelDataΪunsinged char תΪint������-WHEEL_DELTA << 16)���
		{
			processHigth -= 10;
			processWidth -= 10;
			resizePicture();
		}
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}


int main(void)
{

	showPictureEquipment();

	
	hq = FindWindow(NULL, "show");   /*��ȡ���ھ��*/

	if (hq == 0)
	{
		MessageBox(NULL, "no show", "remain", MB_OK);
		return 0;
	}

	LONG lStyle = ::GetWindowLong(hq, GWL_STYLE);
	SetWindowLong(hq, GWL_STYLE, lStyle & ~WS_CAPTION);   //����ǰ���ڷ�����޴��ڱ���������ȡ��

	

	HINSTANCE instance = GetModuleHandle("setPhotoTop.exe");			//��ȡ������
	if (instance == NULL)
	{
		printf("get instance failure!\n");
	}
	DWORD threadId = 0;
	threadId = getThreadID(getPID("setPhotoTop.exe"));
	if (threadId == 0)
	{
		printf("get thread id failure!\n");
	}
	keybordHook = SetWindowsHookEx(						//��װhook
		WH_KEYBOARD,     // �������͡����̡�
		KeyboardProc,       // ������
		instance,                  // ��ǰʵ�����
		threadId                  // �������ھ��(NULLΪȫ�ּ���)
		);

	keybordHook = SetWindowsHookEx(						//��װ���hook
		WH_MOUSE,    
		MouseProc,      
		instance,                  
		threadId                 
		);


	while (1)
	{
		SetWindowPos(hq, HWND_TOPMOST, 0, 0, processHigth, processWidth, SWP_NOACTIVATE | SWP_FRAMECHANGED);
		waitKey(100);
	}


	return  0;
}

