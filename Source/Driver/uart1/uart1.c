/*******************************************************************************
 *
 * �ļ�����: uart1.c
 *
 * �ļ�����: ����1��ʼ��
 * ��    ��: WLB
 * ����ʱ��: 2015-2-1
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/



/*******************************************************************************
 *                                  ͷ�ļ�����                                 *
 *******************************************************************************/

#include    "config.h"

/*******************************************************************************
 *                          ���ļ������ȫ�ֱ����ͺ�������                     *
 *******************************************************************************/


/*******************************************************************************
 *                             �ⲿ�����ͺ�������                              *
 *******************************************************************************/


/********************************************************

//�������ƣ�USART_Configuration(void)
//�����������Դ���1���г�ʼ��
//�����������
//���أ���

//˵������ʼ����Ϊ����飬��������ʹ��I/O�ڵĳ�ʼ���ʹ��ڹ��ܵĳ�ʼ����
//����USART����Ҫ�õ����ţ����������ݷ���Ҫ������ΪGPIO_M_IN_FLOATING��������
//��GPIO_Mode_AF_PP������������������ĺ�GPIO��������һ����
********************************************************/
void USART_Configuration(void)
{
	USART_InitTypeDef	USART_InitStructure;
	GPIO_InitTypeDef 	GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//ʹ�ܴ���1ʱ��		 ����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ�ܴ���2ʱ��		 ����ʱ��
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//ʹ�ܴ���3ʱ��		 ����ʱ��
	//����USART1 RX ��PA.10��Ϊ��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//����USART1 RX ��PA.9��Ϊ�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//******************************************************************************
	// ����1������ʼ�����岿��,����1����Ϊ38400 �� 8 ��1 ��N  �����жϷ�ʽ
	//******************************************************************************
	USART_InitStructure.USART_BaudRate=115200;						//�趨��������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//��������λ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//�趨ֹͣλ����	
    USART_InitStructure.USART_Parity = USART_Parity_No; 			//���ü���λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
																	//������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ʹ�÷��ͺͽ��ն˿�
	USART_Init(USART1,&USART_InitStructure);						//��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  				//ʹ�ܴ���1�����ж�
	USART_Cmd(USART1,ENABLE);										//ʹ�ܴ���1
}

/*****************************************************
//�������ƣ�void NVIC_Configuration(void)
//�����������ж�����	
//�����������
//���أ���
*****************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	   //��ռ���ȼ�1λ�������ȼ�3λ
	//ʹ�ܴ���1�ж�
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/******************************************************************************* 
 * ��������: Usart1_Init(*)
 * ��������: ����1����
 * ��    ��: WLB
 * �������: 
 * �������: 
 * �� �� ֵ: 
 * ����˵��: 
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void Usart1_Init(void)
{
    USART_Configuration();
    NVIC_Configuration();

    return;
}
/*****************************************************
//�������ƣ�Uart1_PutChar
//��������������1���͵��ֽں���
//���������unsigned char ch	Ҫ���͵�����
//���أ���
*****************************************************/
void Usart1_PutChar(u8 ch)
{	
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); 	//�ȴ����ݷ������
}

/*****************************************************
//�������ƣ�Uart1_PutChar
//��������������1���͵��ֽں���
//���������unsigned char ch	Ҫ���͵�����
//���أ���
*****************************************************/
void Usart1_Write(u8 *p, uint32 ulLen)
{	
	while(ulLen--)
	{
		Usart1_PutChar(*p);
		p++;
	}
}
/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

