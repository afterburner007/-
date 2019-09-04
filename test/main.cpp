#include <windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;

HHOOK keybordHook;
HHOOK mouseHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const char *info = NULL;
	char text[50], data[20];
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
		if (p->vkCode == 65 && wParam == WM_KEYDOWN)
		{
			cout << "AAA";
			cout << text << endl;
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
		if (wParam == WM_MOUSEMOVE)                 info = "����ƶ���������";
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
		cout << text << "--" << pData << "--" << mData << endl;
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
int main()
{
	MSG Msg;
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
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);//�������ϵİ�������Ϣ������ַ���Ϣ
		DispatchMessage(&Msg);//����������Ϣ�ٴη��뵽�������Ϣ������
	}
	return Msg.wParam;
}