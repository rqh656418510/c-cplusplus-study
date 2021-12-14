/*
��ҵ��Ϣϵͳ��ܼ��ɵ�������Ʒ�İ���
	����������һ�����ҵ��Ϣϵͳ���г���Ŀ�ܣ�������һ�㲻�����仯�������ɵļ��ɵ��������̵Ĳ�Ʒ
	������������ҵ��Ϣϵͳ����м��ɵ��������̵�Socketͨ�Ų�Ʒ�͵��������̼��ܲ�Ʒ
		1�����������̵�Socketͨ�Ų�Ʒ�������������֮���ͨ��
		2�����������̼��ܲ�Ʒ������������ݷ���ʱ���ܣ����ݽ���ʱ����
	����Ҫ��
		1����֧�ֶ�����̵�Socketͨ�Ų�Ʒ��Χ
		2����֧�ֶ�����������̼��ܲ�Ʒ����Χ
		3����ҵ��Ϣϵͳ��ܲ����׷������

Windows ϵͳ�������cl main.cpp Operation.cpp CCiscoEncDec.cpp CHwEncDec.cpp CSckFactoryImp1.cpp CSckFactoryImp2.cpp des.cpp /EHsc
Windows ϵͳ�������main
*/

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "CSckFactoryImp1.h"
#include "CSckFactoryImp2.h"
#include "CCiscoEncDec.h"
#include "CHwEncDec.h"
#include "Operation.h"

int main() {
	int ret = 0;
	int inlen = 9;
	int outlen = 0;
	unsigned char in[4096];
	unsigned char out[4096];
	strcpy((char*)in, "123456789");

	// Socketͨ�ų���
	CSocketProtocol* sp = new CSckFactoryImp1();
	// CSocketProtocol* sp = new CSckFactoryImp2();

	// ���ܳ���
	CEncDesProtocol* ed = new CCiscoEncDec();
	// CEncDesProtocol* ed = new CHwEncDec();

	Operation* operation = new Operation(sp, ed);

	// ҵ�����
	ret = operation->SckSendAndRec_EncDec(in, inlen, out, &outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRec() err:%d \n", ret);
		return ret;
	}
	cout << "result code: " << ret << endl;
	return 0;
}