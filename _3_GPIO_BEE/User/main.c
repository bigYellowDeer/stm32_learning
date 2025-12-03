#include "stm32f10x.h"                  // Device header,一些
#include "delay.h"

int main(void) 
{	
	/* 1. 在rcc.h中定义了总线配置，外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* 2. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	while(1)
	{
		/* 3. 库函数置位,gpio.h */
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);	
		Delay_ms(100);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		Delay_ms(100);
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);	
		Delay_ms(100);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		Delay_ms(700);
	}
}
