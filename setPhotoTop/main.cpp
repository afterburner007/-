#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "opencv2\opencv.hpp"
#include "showPicture.h"
#include <thread>
using namespace cv;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


MSG Msg;

HHOOK keybordHook;
HHOOK mouseHook;
DWORD pCopy;
WPARAM wParmCopy;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const char *info = NULL;
	char text[50], data[20];
	wParmCopy = wParam;
	
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)      info = "��ͨ���I����";
		else if (wParam == WM_KEYUP)        info = "��ͨ���I̧��";
		else if (wParam == WM_SYSKEYDOWN)   info = "ϵ�y���I̧��";
		else if (wParam == WM_SYSKEYUP)     info = "ϵ�y���I����";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));

		wsprintf(text, "%s - ������ [%04d], ɨ���� [%04d]  ", info, p->vkCode, p->scanCode);
		wsprintf(data, "���IĿ�y�飺 %c  ", p->vkCode);
		if (p->vkCode == 46 && wParam == WM_KEYDOWN)   //delete
		{
			destroyWindow("show");
			exit(1);
		}
		if (p->vkCode == 113 && wParam == WM_KEYDOWN)
		{
			pCopy = p->vkCode;
		}
		else if (p->vkCode == 114 && wParam == WM_KEYDOWN)
		{
			pCopy = p->vkCode;
		}
	}

	return CallNextHookEx(keybordHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT p = (LPMSLLHOOKSTRUCT)lParam;
	POINT   pt = p->pt;
	DWORD   mouseData = p->mouseData;
	const char *info = NULL;
	char text[60], pData[50], mData[50];

	if (nCode >= 0)
	{
		if (wParam == WM_MOUSEMOVE)			 info = "����ƶ���������";
		else if (wParam == WM_LBUTTONDOWN)   info = "��꡾���������";
		else if (wParam == WM_LBUTTONUP)     info = "��꡾�����̧��";
		else if (wParam == WM_LBUTTONDBLCLK) info = "��꡾�����˫��";
		else if (wParam == WM_RBUTTONDOWN)   info = "��꡾�Ҽ�������";
		else if (wParam == WM_RBUTTONUP)     info = "��꡾�Ҽ���̧��";
		else if (wParam == WM_RBUTTONDBLCLK) info = "��꡾�Ҽ���˫��";
		else if (wParam == WM_MBUTTONDOWN)   info = "��꡾���֡�����";
		else if (wParam == WM_MBUTTONUP)     info = "��꡾���֡�̧��";
		else if (wParam == WM_MBUTTONDBLCLK) info = "��꡾���֡�˫��";
		else if (wParam == WM_MOUSEWHEEL)    info = "��꡾���֡�����";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(pData, sizeof(pData));
		ZeroMemory(mData, sizeof(mData));

		wsprintf(text, "��ǰ״̬�� %10s   ", info);
		wsprintf(pData, "0x%x - X: [%04d], Y: [%04d]  ", wParam, pt.x, pt.y);
		wsprintf(mData, "�������ݣ� %16u   ", mouseData);
	}

	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}


void  globalMonitoringKeyboardAndMouse()
{
	while (1)
	{
		if (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		waitKey(1000);
	}
}




int main(void)
{
	int numCnt=0;
	//init
	pCopy=0;
	wParmCopy = 0;

	keybordHook = SetWindowsHookEx(
		WH_KEYBOARD_LL,     // �������͡����̡�
		KeyboardProc,       // ������
		NULL,                  // ��ǰʵ�����
		NULL                  // �������ھ��(NULLΪȫ�ּ���)
		);
	mouseHook = SetWindowsHookEx(
		WH_MOUSE_LL,      // �������͡���꡿
		MouseProc,        // ������
		NULL,                // ��ǰʵ�����
		NULL              // �������ھ��(NULLΪȫ�ּ���)
		);


	showPictureEquipment();
	//topTheWindowInit();

	std::thread  monitor(globalMonitoringKeyboardAndMouse);
	//std::thread  topTheWindows(topTheWindow);
	monitor.detach();
	//topTheWindows.detach();

	HWND hq;

	hq = FindWindow(NULL, "show");   /*��ȡ���*/

	if (hq == 0)
	{
		MessageBox(NULL, "true", "remain", MB_OK);
		return 0;
	}

	LONG lStyle = ::GetWindowLong(hq, GWL_STYLE);
	SetWindowLong(hq, GWL_STYLE, lStyle & ~WS_CAPTION);   //����ǰ���ڷ�����޴��ڱ���������ȡ��

	while (1)
	{
		if (pCopy == 113)   //F2
		{
			showPicturelingfeng();
		}
		else if (pCopy == 114)  //F3
		{
			showPictureEquipment();
		}
		else
		{
			SetWindowPos(hq, HWND_TOPMOST, 0, 0, 200, 200, SWP_NOACTIVATE | SWP_FRAMECHANGED);
			numCnt = 0;
		}
		if (numCnt>SWITCHCNT)
		{
			pCopy = 0;
		}
		waitKey(1000);
		numCnt++;
	}


	return  0;
}

