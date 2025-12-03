#include "stm32f10x.h"                  // Device header,一些
#include "delay.h"

/* 定义 LED 端口数组 */
uint16_t led_ports[] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_5, GPIO_Pin_4};

int main(void) 
{
	/* 1. 在rcc.h中定义了总线配置，外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* 2. 配置IO口模式 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	uint8_t i = 0; /* 用于循环 */
	uint8_t size = sizeof(led_ports) / sizeof(led_ports[0]);
	
	while(1)
	{
		/* 3. 库函数置位,gpio.h */
		for (uint8_t j = 0; j < size; j++)
		{
			GPIO_WriteBit(GPIOA, led_ports[j], Bit_SET); /* 关闭所有 LED */
		}
		GPIO_WriteBit(GPIOA, led_ports[i], Bit_RESET); /* 循环点灯 */
		Delay_ms(500);
		
		i++;
        if (i >= size)
		{
            i = 0;
        }
	}
}
