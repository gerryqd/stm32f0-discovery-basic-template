#include "stm32f0xx_conf.h"

#include <stdbool.h>

// ----------------
//  LED3: PC9
//  LED4: PC8
//
// Control method
//  GPIO 1:  LED on
//  GPIO 0:  LED off

#define LED3_GPIO_PORT  GPIOC
#define LED3_GPIO_PIN   GPIO_Pin_9

#define LED4_GPIO_PORT  GPIOC
#define LED4_GPIO_PIN   GPIO_Pin_8

static void led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LED4_GPIO_PIN;
  GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);
}

static void led_on(void)
{
  GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
  GPIO_SetBits(LED4_GPIO_PORT, LED4_GPIO_PIN);
}

static void led_off(void)
{
  GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
  GPIO_ResetBits(LED4_GPIO_PORT, LED4_GPIO_PIN);
}

static void led_toggle(void)
{
  static bool is_led_off = true;

  if (is_led_off)
  {
    led_on();
  }
  else
  {
    led_off();
  }
  is_led_off = !is_led_off;
}

void SysTick_Handler(void)
{
  static uint16_t tick = 0;

  switch (tick++) {
    case 100:
      led_toggle();
      tick = 0;
      break;
  }
}

int main(void)
{
  led_init();
  led_off();
  SysTick_Config(SystemCoreClock/100);

  while(1);
}
