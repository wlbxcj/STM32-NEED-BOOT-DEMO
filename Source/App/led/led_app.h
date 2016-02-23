#ifndef	_LED_APP_H_
#define	_LED_APP_H_



#if 0
#define ON  0
#define OFF 1

#define LED0(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_3)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_4)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_5)

void LED_GPIO_Config(void);
#endif

#endif	// _LED_APP_H_
