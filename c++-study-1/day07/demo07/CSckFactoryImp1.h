#pragma once

#include "CSocketProtocol.h"

// 实现类一
class CSckFactoryImp1 : public CSocketProtocol {

public:

	// 客户端初始化
	virtual int cltSocketInit( /*out*/);

	// 客户端发报文
	virtual int cltSocketSend(unsigned char* buf /*in*/, int buflen /*in*/);

	// 客户端收报文
	virtual int cltSocketRev(unsigned char* buf /*in*/, int* buflen /*in out*/);

	// 客户端释放资源
	virtual int cltSocketDestory();

private:
	unsigned char* p;
	int len;

};