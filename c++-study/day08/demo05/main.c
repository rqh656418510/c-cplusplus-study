/*
 * 1. ͨ������ָ�����ͣ���̬����DLL���API��������̬����DLL��
*/

#include <stdio.h>
#include <windows.h>

// ���庯��ָ������
typedef int (*SocketInit)(void** handle);
typedef int (*SocketSend)(void* handle, unsigned char* buf, int buflen);
typedef int (*SocketRev)(void* handle, unsigned char* buf, int* buflen);
typedef int (*SocketDestory)(void* handle);

int main() {

	HINSTANCE hInstance;

	// ����DLL��̬���ӿ�
	hInstance = LoadLibrary("./socket-client.dll");
	if (hInstance == NULL)
	{
		printf("LoadLibrary() ����ʧ��, ErrorCode: %d", GetLastError());
		return -1;
	}

	// ����DLL��̬���ӿ�
	SocketInit socketInit = (SocketInit)GetProcAddress(hInstance, "socketclient_init");
	SocketSend socketSend = (SocketSend)GetProcAddress(hInstance, "socketclient_send");
	SocketRev socketRev = (SocketRev)GetProcAddress(hInstance, "socketclient_recv");
	SocketDestory socketDestory = (SocketDestory)GetProcAddress(hInstance, "socketclient_destory");

	if (socketInit == NULL)
	{
		return -1;
	}

	unsigned char inbuf[128];
	int inbuflen = 128;
	unsigned char outbuf[4096];
	int outbuflen = 4096;

	void* handle = NULL;
	int initResult = socketInit(&handle);
	int sendResult = socketSend(handle, inbuf, inbuflen);
	int revResult = socketRev(handle, outbuf, &outbuflen);
	int destoryResult = socketDestory(handle);

	printf("initResult = %d\n", initResult);
	printf("sendResult = %d\n", sendResult);
	printf("revResult = %d\n", revResult);
	printf("destoryResult = %d\n", destoryResult);

	// �ͷ�DLL��̬���ӿ�
	if (hInstance != NULL) {
		FreeLibrary(hInstance);
	}

	return 0;
}