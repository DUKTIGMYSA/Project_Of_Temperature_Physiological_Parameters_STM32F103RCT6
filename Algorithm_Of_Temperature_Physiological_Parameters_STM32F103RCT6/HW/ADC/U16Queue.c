/*********************************************************************************************************
* ģ�����ƣ�U16Queue.c
* ժ    Ҫ��U16Queueģ��
* ��ǰ�汾��1.0.0
* ��    �ߣ�SZLY(COPYRIGHT 2018 - 2020 SZLY. All rights reserved.)
* ������ڣ�2020��01��01�� 
* ��    �ݣ�
* ע    �⣺                                                                  
**********************************************************************************************************
* ȡ���汾��
* ��    �ߣ�
* ������ڣ�
* �޸����ݣ�
* �޸��ļ���
*********************************************************************************************************/

/*********************************************************************************************************
*                                              ����ͷ�ļ�
*********************************************************************************************************/
#include "U16Queue.h"

/*********************************************************************************************************
*                                              �궨��
*********************************************************************************************************/

/*********************************************************************************************************
*                                              ö�ٽṹ�嶨��
*********************************************************************************************************/

/*********************************************************************************************************
*                                              �ڲ�����
*********************************************************************************************************/

/*********************************************************************************************************
*                                              �ڲ���������
*********************************************************************************************************/

/*********************************************************************************************************
*                                              �ڲ�����ʵ��
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API����ʵ��
*********************************************************************************************************/

/*********************************************************************************************************
* �������ƣ�InitU16Queue
* �������ܣ���ʼ������ 
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ��pBuf-���е�Ԫ�ش洢����ַ��len-���е�����
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* �� �� ֵ��void
* �������ڣ�2018��01��01��
* ע    �⣺
*********************************************************************************************************/
void  InitU16Queue(StructU16CirQue* pQue, u16* pBuf, i16 len)
{
  i16 i;

  pQue->front   = 0;    //��ͷ
  pQue->rear    = 0;    //��β
  pQue->bufLen  = len;  //���������ȣ�����������
  pQue->elemNum = 0;    //��ǰ������Ԫ�صĸ���
  pQue->pBuffer = pBuf; //ָ�����pBuf����ָ�����pQue->pBuffer
  
  for(i = 0; i < len; i++)
  {
    pQue->pBuffer[i]  = 0;  //��ָ�����pQue->pBuffer��ָ���Ԫ�ؾ�����ֵ0
  }
}

/*********************************************************************************************************
* �������ƣ�ClearU16Queue
* �������ܣ������ 
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* �� �� ֵ��void
* �������ڣ�2018��01��01��
* ע    �⣺
*********************************************************************************************************/
void  ClearU16Queue(StructU16CirQue* pQue)
{
  pQue->front   = 0; //��ͷ
  pQue->rear    = 0; //��β
  pQue->elemNum = 0; //��ǰ������Ԫ�صĸ���
}

/*********************************************************************************************************
* �������ƣ�QueueEmpty
* �������ܣ��ж϶����Ƿ�Ϊ�գ�1Ϊ�գ�0Ϊ�ǿ� 
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* �� �� ֵ�����ض����Ƿ�Ϊ�գ�1Ϊ�գ�0Ϊ�ǿ�
* �������ڣ�2018��01��01��
* ע    �⣺
*********************************************************************************************************/
u8    U16QueueEmpty(StructU16CirQue* pQue)
{
  return(0 == pQue->elemNum);
}

/*********************************************************************************************************
* �������ƣ�U16QueueLength
* �������ܣ����ض�����Ԫ�ظ���
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* �� �� ֵ��������Ԫ�صĸ���
* �������ڣ�2018��01��01��
* ע    �⣺
*********************************************************************************************************/
i16   U16QueueLength(StructU16CirQue* pQue)
{
  return(pQue->elemNum);
}

/*********************************************************************************************************
* �������ƣ�EnU16Queue
* �������ܣ�����len��Ԫ�أ��������ʼ��ַΪpInput�Ĵ洢���У������� 
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ��pInput-���������ĵ�ַ��len-�������Ԫ�ص�����
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ
* �� �� ֵ���ɹ���ӵ�Ԫ�ص�����
* �������ڣ�2018��01��01��
* ע    �⣺ÿ�β���һ��Ԫ�أ�rear��������rear��ֵ���ڵ��ڶ�������bufLenʱ��rearֵ��Ϊ0����Ҫע����ǣ�����
*           ���е�Ԫ���������ϴ�д���Ԫ������������������ʱ����������д���Ԫ���������ڶ����е�Ԫ������+��д
*           ���Ԫ������-���е���������EnQueue�������ڳ���Ԫ�ز�ȡ�����ǵ�̬�ȡ�
*********************************************************************************************************/
i16 EnU16Queue(StructU16CirQue* pQue, u16* pInput, i16 len)
{
  i16 wLen = 0; //����ӵ�Ԫ����len����wLen��0���ӵ�len-1
  
  while((pQue->elemNum < pQue->bufLen) && (wLen < len))
  {
    pQue->pBuffer[pQue->rear] = pInput[wLen]; //������ӵĵ�wLen��Ԫ��pInput[wLen]�������
    pQue->rear++;     //��βrear��������ָ���βԪ�ص���һ��λ��
    
    if(pQue->rear >= pQue->bufLen)
    {
      pQue->rear = 0; //�����βԪ�ص���һ��λ��ΪpQue->bufLen����rearָ���ͷ��ѭ�������ڴ˴�
    }

    wLen++;
    pQue->elemNum++;  //��ǰ�����е�Ԫ������
  }

  return wLen;  //�������ֵwLenΪ0����ʾû��Ԫ�����
}

/*********************************************************************************************************
* �������ƣ�DeU16Queue
* �������ܣ��Ӷ�����ȡ��len��Ԫ�أ�������ʼ��ַΪpOutput�Ĵ洢�� 
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ��len-Ԥ�ڳ���Ԫ�ص�����
* ���������pQue-�ṹ��ָ�룬��ָ��ṹ������ĵ�ַ��pOutput-����Ԫ�ش�ŵ�����ĵ�ַ
* �� �� ֵ���ɹ����ӵ�Ԫ�ص�����
* �������ڣ�2018��01��01��
* ע    �⣺ÿ��ȡ��һ��Ԫ�أ�front��������front��ֵ���ڵ��ڶ�������bufLenʱ��frontֵ��Ϊ0����Ҫ�ر�ע�⣬��
*           �����ж�ȡԪ�ص�ǰ���Ƕ�������Ҫ������һ��Ԫ�أ�������ȡ����Ԫ������lenС�ڻ���ڶ�����Ԫ�ص�����
*           ʱ�����԰�����ȡ��len��Ԫ�أ�����ֻ��ȡ�����������е�����Ԫ�ء� 
*********************************************************************************************************/
i16 DeU16Queue(StructU16CirQue* pQue, u16* pOutput, i16 len)
{
  i16 rLen = 0; //����ȡ��len��Ԫ�أ�������ȡ��rLen��Ԫ��
  
  while((pQue->elemNum > 0) && (rLen < len))
  {
    pOutput[rLen] = pQue->pBuffer[pQue->front];
    pQue->front++;
    
    if( pQue->front >= pQue->bufLen )
    {
      pQue->front = 0;//�����ͷԪ�ص���һ��λ��ΪpQue->bufLen����frontָ���ͷ��ѭ�������ڴ˴�
    }

    rLen++;
    pQue->elemNum--;  //��ǰ�����е�Ԫ������
  }

  return rLen;  //�������ֵrLenΪ0����ʾ������û��Ԫ��
}
