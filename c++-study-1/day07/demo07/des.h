/*********************************************************
 *  des.h
 *  用户使用des算法的头文件
 *
 *********************************************************/
#ifndef _OPENDESS_H_
#define _OPENDESS_H_

#ifdef __cplusplus
extern "C" {
#endif

	//用户使用的加密函数
	int DesEnc(
		unsigned char* pInData,
		int            nInDataLen,
		unsigned char* pOutData,
		int* pOutDataLen);

	//用户使用的解密函数
	int DesDec(
		unsigned char* pInData,
		int            nInDataLen,
		unsigned char* pOutData,
		int* pOutDataLen);

#ifdef __cplusplus
}
#endif

#endif