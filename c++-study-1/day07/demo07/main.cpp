/*
企业信息系统框架集成第三方产品的案例
	案例背景：一般的企业信息系统都有成熟的框架，软件框架一般不发生变化，能自由的集成第三方厂商的产品
	案例需求：在企业信息系统框架中集成第三方厂商的Socket通信产品和第三方厂商加密产品
		1）第三方厂商的Socket通信产品：负责完成两点之间的通信
		2）第三方厂商加密产品：负责完成数据发送时加密；数据解密时解密
	案例要求：
		1）能支持多个厂商的Socket通信产品入围
		2）能支持多个第三方厂商加密产品的入围
		3）企业信息系统框架不轻易发生框架

Windows 系统编译命令：cl main.cpp Operation.cpp CCiscoEncDec.cpp CHwEncDec.cpp CSckFactoryImp1.cpp CSckFactoryImp2.cpp des.cpp /EHsc
Windows 系统运行命令：main
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

	// Socket通信厂商
	CSocketProtocol* sp = new CSckFactoryImp1();
	// CSocketProtocol* sp = new CSckFactoryImp2();

	// 加密厂商
	CEncDesProtocol* ed = new CCiscoEncDec();
	// CEncDesProtocol* ed = new CHwEncDec();

	Operation* operation = new Operation(sp, ed);

	// 业务操作
	ret = operation->SckSendAndRec_EncDec(in, inlen, out, &outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRec() err:%d \n", ret);
		return ret;
	}
	cout << "result code: " << ret << endl;
	return 0;
}