#pragma once

#include "define.h"

// 抽象类（接口类）
class CEncDesProtocol {

public:

	CEncDesProtocol() {

	}

	// 虚析构函数
	virtual ~CEncDesProtocol() {

	}

	// 编码数据
	virtual int EncData(unsigned char* plain, int plainlen, unsigned char* cryptdata, int* cryptlen) = 0;

	// 解码数据
	virtual int DecData(unsigned char* cryptdata, int cryptlen, unsigned char* plain, int* plainlen) = 0;

};