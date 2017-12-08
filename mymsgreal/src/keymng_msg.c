


#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "keymng_msg.h"
#include "itcast_asn1_der.h"
#include "itcastderlog.h"

//���ı���
int Teacher_Encode_(Teacher *pstruct, ITCAST_ANYBUF **tmpNode)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;

	unsigned char		*tmpOut = NULL;
	int					tmpOutLen = 0;

	// ����name
	//C���Ե�char buf���� ת�� ITASN1_PRINTABLESTRING
	ret = DER_ITCAST_String_To_AnyBuf(&pTmp, pstruct->name, strlen(pstruct->name));
	if (ret != 0)
	{
		printf("func DER_ITCAST_String_To_AnyBuf() err:%d \n", ret);
		return ret;
	}

	//��name����TLV����
	ret = DER_ItAsn1_WritePrintableString(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_WritePrintableString() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	pTmpBuf = pHeadBuf;

	//����age
	ret = DER_ItAsn1_WriteInteger(pstruct->age, &(pTmpBuf->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);  //�ͷ����� ͷ�ڵ�
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmpBuf = pTmpBuf->next; //����ָ����� ����

	//����p
	ret = EncodeChar(pstruct->p, pstruct->plen, &pTmpBuf->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);  //�ͷ����� ͷ�ڵ�
		printf("func EncodeChar() err:%d \n", ret);
		return ret;
	}
	pTmpBuf = pTmpBuf->next; //����ָ����� ����

	//����plen
	ret = DER_ItAsn1_WriteInteger(pstruct->plen, &(pTmpBuf->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);  //�ͷ����� ͷ�ڵ�
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}

	//TLV�ṹ��
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);  //�ͷ����� ͷ�ڵ�
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	DER_ITCAST_FreeQueue(pHeadBuf);  //�ͷ����� ͷ�ڵ�

	/* 
	//�����ڴ� 
	tmpOut = (unsigned char *)malloc(pOutData->dataLen);
	memcpy(tmpOut, pOutData->pData, pOutData->dataLen);

	//��Ӹ�ֵ ��ָ������������
	*p = tmpOut;
	*len = pOutData->dataLen;
	*/
	*tmpNode = pOutData;
	//DER_ITCAST_FreeQueue(pOutData);  //�ͷ����� ͷ�ڵ�

	return ret;
}


int Teacher_Decode_(unsigned char *p, int len, Teacher **pstruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pTmpDABuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;
	int					tmpNum = 0;
	Teacher				*pTmpStru = NULL;

	inAnyBuf = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (inAnyBuf == NULL)
	{
		ret = 1;
		printf("func Teacher_Decode() err: %d. malloc err \n", ret);
		return ret;
	}
	memset(inAnyBuf, 0, sizeof(ITCAST_ANYBUF)); //��ֵ����Ҫ
	inAnyBuf->pData = (unsigned char *)malloc(len);
	if (inAnyBuf->pData == NULL)
	{
		ret = 2;
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func Teacher_Decode() err: %d. malloc err \n", ret);
		return ret;
	}
	inAnyBuf->dataLen = len;
	memcpy(inAnyBuf->pData, p, len);

	ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(inAnyBuf);
	pTmp = pHead;

	//������ʦ�ṹ��
	pTmpStru = (Teacher *)malloc(sizeof(Teacher));
	if (pTmpStru == NULL)
	{
		DER_ITCAST_FreeQueue(pHead);
		ret = 3;
		printf("func Teacher_Decode() err: %d. malloc err \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(Teacher));

	//����name
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	strncpy(pTmpStru->name, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//����age
	ret = DER_ItAsn1_ReadInteger(pTmp, &pTmpStru->age);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//����p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	pTmpStru->p = (unsigned char *)malloc(pTmpDABuf->dataLen + 1);
	if (pTmpStru->p == NULL)
	{
		DER_ITCAST_FreeQueue(pTmpDABuf);
		DER_ITCAST_FreeQueue(pHead);
		ret = 4;
		printf("func Teacher_Decode() err: %d. malloc err \n", ret);
		return ret;
	}
	memcpy(pTmpStru->p, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmpStru->p[pTmpDABuf->dataLen] = '\0';
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//����plen
	ret = DER_ItAsn1_ReadInteger(pTmp, &pTmpStru->plen);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	*pstruct = pTmpStru;
	DER_ITCAST_FreeQueue(pHead);

	return ret;
}

//һ��ָ��
void Teacher_Free_(Teacher *pStruct)
{
	if (pStruct == NULL)
	{
		return;
	}
	if (pStruct->p)
	{
		free(pStruct->p);
	}

	free(pStruct);
}

//������ָ����ָ����ڴ�ռ��ͷ�,ͬʱ��ʵ���޸ĳ�NULL ����Ұָ��
void Teacher_Free2_(Teacher **pStruct)
{
	Teacher *tmp = NULL;

	if (pStruct == NULL)
	{
		return;
	}
	tmp = *pStruct;

	if (tmp == NULL)
	{
		return;
	}


	if (tmp->p)
	{
		free(tmp->p);
	}

	free(tmp);
	*pStruct = NULL;

}


// itype tlv
// teacher tlv sequence
// all sequence tlv

int MsgEncode(
	void			*pStruct, /*in*/
	int				type,
	unsigned char	**outData, /*out*/
	int				*outLen)
{
	ITCAST_ANYBUF	*pHeadbuf = NULL, *pTemp = NULL;
	ITCAST_ANYBUF			*pOutData = NULL;
	int				ret = 0;
	unsigned char * tmpOut = NULL;
	int				tmpOutLen = 0;

	if (pStruct == NULL || outData == NULL || outLen == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgEncode() err��%d check pStruct == NULL || outData == NULL || outLen == NULL\n", ret);
		return ret;
	}

	//����type ��ǩ
	ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_WriteInteger() err��%d \n", ret);
		return ret;
	}

	//����type����������͵Ľṹ��

	switch (type)
	{
	case ID_MsgType_Teacher:
		ret = Teacher_Encode_(pStruct, &(pHeadbuf->next));
		if (ret != 0)
		{
			DER_ITCAST_FreeQueue(pHeadbuf);
			printf("func DER_ItAsn1_WriteInteger() err��%d \n", ret);
			return ret;
		}
		break;
	case ID_MsgKey_Req:
		//...
		break;
	case ID_MsgKey_Res:
		//...
		break;
	default:
		ret = -2;
		printf("�����type��֧��\n");
		break;
	}

	//all 
	ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d\n", ret);
		return ret;
	}

	//�����ڴ�
	*outData = (unsigned char *)malloc(pOutData->dataLen);
	if (*outData == NULL)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		ret = KeyMng_MallocErr;
		printf("func MsgEncode() func malloc err:%d\n", ret);
		return ret;
	}

	//��Ӹ�ֵ
	memcpy(*outData, pOutData->pData, pOutData->dataLen);
	*outLen = pOutData->dataLen;

	printf("ttttttt\n");
	DER_ITCAST_FreeQueue(pHeadbuf);
	DER_ITCAST_FreeQueue(pOutData);

	return 0;
}

int MsgDecode(
	unsigned char *inData,/*in*/
	int           inLen,
	void          **pStruct /*out*/,
	int           *type /*out*/)
{
	ITCAST_ANYBUF		*pHeadBuf = NULL, *pTmp = NULL;
	int					ret = 0;
	unsigned long		itype = 0;

	if (inData == NULL || pStruct == NULL || type == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgDecode() err :%d\n", ret);
		return ret;
	}

	//��C ����������  ת���� ITCAST_ANYBUF
	pTmp = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = KeyMng_MallocErr;
		printf("func MsgDecode() err :%d\n", ret);
		return ret;
	}
	//pTmp->next = NULL; ע������ Ҫ�н�����־
	//pTmp->prev = NULL;
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));
	pTmp->pData = (unsigned char *) malloc(inLen);
	if (pTmp->pData == NULL)
	{
		ret = KeyMng_MallocErr;
		printf("func MsgDecode() err :%d\n", ret);
		return ret;
	}

	memcpy(pTmp->pData, inData, inLen);
	pTmp->dataLen = inLen;

	//������ṹ��
	ret = DER_ItAsn1_ReadSequence(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_ReadSequence() err :%d\n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp); //�ڴ�й© modify by wbm

	//����tag
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &itype);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_ReadInteger() err :%d\n", ret);
		return ret;
	}

	//����itype���и������͵Ľ���
	switch (itype)
	{
	case ID_MsgType_Teacher:
		ret = Teacher_Decode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (Teacher**)pStruct);
		if (ret != 0)
		{
			DER_ITCAST_FreeQueue(pHeadBuf);
			printf("func Teacher_Decode_() err :%d\n", ret);
			return ret;
		}
		break;

	case ID_MsgKey_Req:
		break;
	case ID_MsgKey_Res:
		break;
	default:
		ret = 3;
		printf("itype���Ͳ�֧�֣�%d\n",ret);
		break;
	}
	//
	*type = itype;

	DER_ITCAST_FreeQueue(pHeadBuf);

	return 0;
}



int MsgMemFree(void **point, int type)
{
	if (point == NULL)
	{
		return 0;
	}
	if (type == 0)
	{
		if (*point != NULL)
		{
			free(*point);
		}
		*point = NULL;
	}
	else
	{
		switch (type)
		{
		case ID_MsgType_Teacher:
			Teacher_Free_(*point);
			*point = NULL;
			break;
		default:
			break;
		}
	}
	return 0;
}