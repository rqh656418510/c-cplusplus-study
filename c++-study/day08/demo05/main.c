/*
 * 1. 通过函数指针类型，动态调用DLL里的API函数（动态加载DLL）
*/

#include <stdio.h>
#include <windows.h>

// 定义函数指针类型
typedef int (*SocketInit)(void** handle);
typedef int (*SocketSend)(void* handle, unsigned char* buf, int buflen);
typedef int (*SocketRev)(void* handle, unsigned char* buf, int* buflen);
typedef int (*SocketDestory)(void* handle);

int main() {

	HINSTANCE hInstance;

	// 加载DLL动态链接库
	hInstance = LoadLibrary("./socket-client.dll");
	if (hInstance == NULL)
	{
		printf("LoadLibrary() 调用失败, ErrorCode: %d", GetLastError());
		return -1;
	}

	// 调用DLL动态链接库
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

	// 释放DLL动态链接库
	if (hInstance != NULL) {
		FreeLibrary(hInstance);
	}

	return 0;
}