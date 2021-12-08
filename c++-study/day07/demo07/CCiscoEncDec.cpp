#include "des.h"
#include "CCiscoEncDec.h"

// 编码数据
int CCiscoEncDec::EncData(unsigned char* plain, int plainlen, unsigned char* cryptdata, int* cryptlen) {
	int ret = 0;
	//用户使用函数enc加密
	ret = DesEnc(plain, plainlen, cryptdata, cryptlen);
	if (ret != 0)
	{
		printf("func DesEnc() err:%d \n ", ret);
		return ret;
	}
	return ret;
}

// 解码数据
int CCiscoEncDec::DecData(unsigned char* cryptdata, int cryptlen, unsigned char* plain, int* plainlen) {
	int ret = 0;
	//用户使用函数dec解密
	ret = DesDec(cryptdata, cryptlen, plain, plainlen);
	if (ret != 0)
	{
		printf("func DesDec() err:%d \n ", ret);
		return ret;
	}
	return ret;
}