#pragma once

#include "CSckFactoryImp2.h"

// �ͻ��˳�ʼ��
int CSckFactoryImp2::cltSocketInit( /*out*/)
{
	p = NULL;
	len = 0;
	return 0;
}

// �ͻ��˷�����
int CSckFactoryImp2::cltSocketSend(unsigned char* buf /*in*/, int buflen /*in*/)
{
	p = (unsigned char*)malloc(sizeof(unsigned char) * buflen);
	if (p == NULL)
	{
		return -1;
	}
	memcpy(p, buf, buflen);
	len = buflen;
	return 0;
}

// �ͻ����ձ���
int CSckFactoryImp2::cltSocketRev(unsigned char* buf /*in*/, int* buflen /*in out*/)
{
	if (buf == NULL || buflen == NULL)
	{
		return -1;
	}

	*buflen = this->len;
	memcpy(buf, this->p, this->len);
	return 0;
}

// �ͻ����ͷ���Դ
int CSckFactoryImp2::cltSocketDestory()
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
		len = 0;
	}
	return 0;
}