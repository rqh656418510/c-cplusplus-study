#include "des.h"
#include "CHwEncDec.h"

// ��������
int CHwEncDec::EncData(unsigned char* plain, int plainlen, unsigned char* cryptdata, int* cryptlen)
{
	int ret = 0;
	//�û�ʹ�ú���enc����
	ret = DesEnc(plain, plainlen, cryptdata, cryptlen);
	if (ret != 0)
	{
		printf("func DesEnc() err:%d \n ", ret);
		return ret;
	}
	return ret;
}

// ��������
int CHwEncDec::DecData(unsigned char* cryptdata, int cryptlen, unsigned char* plain, int* plainlen)
{
	int ret = 0;
	//�û�ʹ�ú���dec����
	ret = DesDec(cryptdata, cryptlen, plain, plainlen);
	if (ret != 0)
	{
		printf("func DesDec() err:%d \n ", ret);
		return ret;
	}
	return ret;
}