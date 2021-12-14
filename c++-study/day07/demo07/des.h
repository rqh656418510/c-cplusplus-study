/*********************************************************
 *  des.h
 *  �û�ʹ��des�㷨��ͷ�ļ�
 *
 *********************************************************/
#ifndef _OPENDESS_H_
#define _OPENDESS_H_

#ifdef __cplusplus
extern "C" {
#endif

	//�û�ʹ�õļ��ܺ���
	int DesEnc(
		unsigned char* pInData,
		int            nInDataLen,
		unsigned char* pOutData,
		int* pOutDataLen);

	//�û�ʹ�õĽ��ܺ���
	int DesDec(
		unsigned char* pInData,
		int            nInDataLen,
		unsigned char* pOutData,
		int* pOutDataLen);

#ifdef __cplusplus
}
#endif

#endif