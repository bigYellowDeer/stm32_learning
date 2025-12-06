#include "stm32f10x.h"
#include "delay.h"

/* 变量定义 */
uint8_t keyNum = 0;

/* led init */
void ledInit(void)
{
	/* 1. 在rcc.h中定义了总线配置，外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 2. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* 3. 先关闭 */
	GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
}

/* led turn on or off */
void greenTurn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	}
}

/* 状态翻转 */
void redTurn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
}

/* key init */
void keyInit(void)
{
	/* 1. 在rcc.h中定义了总线配置，外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	/* 2. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/*  哪个按键按下 */
uint8_t getKeyNum(void)
{
	uint8_t keyNum = 0;
	
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0) /* 按键按下 */
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0);
		Delay_ms(20);
		keyNum = 3;
	}
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0) /* 按键按下 */
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);
		Delay_ms(20);
		keyNum = 4;
	}

	return keyNum;
}

int main(void) 
{	
	/* 1. led and key init */
	ledInit();
	keyInit();
	
	while(1)
	{
		keyNum = getKeyNum(); /* 接线时注意，短的接mcu */
		switch (keyNum)
		{
			case 3:
				greenTurn();
				break;

			case 4:
				redTurn();
				break;

			default:
				break;
		}
	}
}
