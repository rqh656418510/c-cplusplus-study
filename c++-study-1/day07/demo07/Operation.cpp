#include "Operation.h"

Operation::Operation()
{
	this->sp = NULL;
	this->ed = NULL;
}

Operation::Operation(CSocketProtocol* sp, CEncDesProtocol* ed)
{
	this->sp = sp;
	this->ed = ed;
}

Operation::~Operation() {
	if (this->sp != NULL) {
		delete this->sp;
	}
	if (this->ed != NULL) {
		delete this->ed;
	}
}

CSocketProtocol* Operation::getSp()
{
	return this->sp;
}

CEncDesProtocol* Operation::getEd()
{
	return this->ed;
}

void Operation::setSp(CSocketProtocol* sp)
{
	this->sp = sp;
}

void Operation::setEd(CEncDesProtocol* ed)
{
	this->ed = ed;
}

int Operation::SckSendAndRec_EncDec(unsigned char* in, int inlen, unsigned char* out, int* outlen)
{
	int ret = 0;
	unsigned char data[4096];
	int datalen = 0;

	ret = this->sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}

	// 发送数据之前对数据加密
	ret = this->ed->EncData(in, inlen, data, &datalen);
	if (ret != 0)
	{
		goto End;
	}

	ret = this->sp->cltSocketSend(data, datalen);
	if (ret != 0)
	{
		goto End;
	}

	// 收到的数据是密文,需要进行解密
	ret = sp->cltSocketRev(data, &datalen);
	if (ret != 0)
	{
		goto End;
	}

	ret = ed->DecData(data, datalen, out, outlen);
	if (ret != 0)
	{
		goto End;
	}

End:
	ret = sp->cltSocketDestory();
	return 0;
}

int Operation::SckSendAndRec_EncDec(CSocketProtocol* sp, CEncDesProtocol* ed, unsigned char* in, int inlen, unsigned char* out, int* outlen)
{
	int ret = 0;
	unsigned char data[4096];
	int datalen = 0;

	ret = sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}

	// 发送数据之前对数据加密
	ret = ed->EncData(in, inlen, data, &datalen);
	if (ret != 0)
	{
		goto End;
	}

	ret = sp->cltSocketSend(data, datalen);
	if (ret != 0)
	{
		goto End;
	}

	ret = sp->cltSocketRev(data, &datalen);
	if (ret != 0)
	{
		goto End;
	}

	// 收到的数据是密文,需要进行解密
	ret = ed->DecData(data, datalen, out, outlen);
	if (ret != 0)
	{
		goto End;
	}
End:
	ret = sp->cltSocketDestory();
	return 0;
}