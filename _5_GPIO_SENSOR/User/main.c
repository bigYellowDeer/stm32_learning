#include "stm32f10x.h"
#include "delay.h"

/* bee init */
void beeInit(void)
{
	/* 1. 在rcc.h中定义了总线配置，外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 2. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* 3. 先关闭 */
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}


/* sensor init */
void sensorInit(void)
{
	/* 1. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t lightSensorGet(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);  /* 读取光敏的数组输出 */
}

int main(void) 
{	
	/* 1. led and key init */
	beeInit();
	sensorInit();
	
	while(1)
	{
		if (lightSensorGet() == 1) /* 光线暗，电阻大，分压多，输出为1 */
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		}
	}
} /* 逆时针电阻变小，顺时针变大 */
 