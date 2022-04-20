#pragma once

#include "CSocketProtocol.h"
#include "CEncDesProtocol.h"

// 主操作类
class Operation {

public:
	Operation();
	Operation(CSocketProtocol* sp, CEncDesProtocol* ed);

	~Operation();

	CSocketProtocol* getSp();
	CEncDesProtocol* getEd();
	void setSp(CSocketProtocol* sp);
	void setEd(CEncDesProtocol* ed);

public:
	int SckSendAndRec_EncDec(unsigned char* in, int inlen, unsigned char* out, int* outlen);
	int SckSendAndRec_EncDec(CSocketProtocol* sp, CEncDesProtocol* ed, unsigned char* in, int inlen, unsigned char* out, int* outlen);

private:
	CSocketProtocol* sp;
	CEncDesProtocol* ed;

};