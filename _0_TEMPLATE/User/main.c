#include "stm32f10x.h"                  /* header file */
#include "delay.h"

int main(void)
{
	/************** 方法1：寄存器的方法实现 *************/
	/* step 1: 使能B口时钟 */
	RCC->APB2ENR = 0x00000008;
	
	/* step 2: 配置模式，推挽和50MHz */
	GPIOB->CRL = 0x00300000;
	
	/* step 3: 输出高低电平，低电平点亮 */
	GPIOB->ODR = 0x00000000;
	
	/************** 方法2：库函数的方法实现 *************/
	/* step 1: 使能E口时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	/* step 2: 配置模式，推挽和50MHz */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* step 3: 输出高低电平，低电平点亮 */
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
	
	while(1)
	{
		
	}
}
