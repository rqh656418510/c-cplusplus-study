#pragma once

#include "CEncDesProtocol.h"

// ˼�Ƶļ��ܽ���ʵ����
class CCiscoEncDec : public CEncDesProtocol {

public:
	// ��������
	virtual int EncData(unsigned char* plain, int plainlen, unsigned char* cryptdata, int* cryptlen);

	// ��������
	virtual int DecData(unsigned char* cryptdata, int cryptlen, unsigned char* plain, int* plainlen);

};