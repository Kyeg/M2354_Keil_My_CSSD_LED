/**************************************************************************//**
 * @file     main_ns.c
 * @version  V1.00
 * @brief    Non-secure sample code for Collaborative Secure Software Development
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <arm_cmse.h>
#include "NuMicro.h"                    /* Device header */
#include "cssd_lib.h"                   /* Collaborative Secure Software Development Library header */

void LED_On(uint32_t us);
void LED_Off(uint32_t us);
void SysTick_Handler(void);

/*----------------------------------------------------------------------------
  NonSecure Functions from NonSecure Region
 *----------------------------------------------------------------------------*/
void LED_On(uint32_t us)
{
    (void)us;
    printf("NS LED On call by NS\n");
    PC0_NS = 0;
}

void LED_Off(uint32_t us)
{
    (void)us;
    printf("NS LED Off call by NS\n");
    PC0_NS = 1;
}

/*----------------------------------------------------------------------------
  SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
    static uint32_t u32Ticks;

    switch(u32Ticks++)
    {
        case 200:
            // second developer handle
						printf("                                \n");
						printf("                                NS: +200 \n");
				    printf("                                NS: S-Yellow LED On\n");
            Secure_PD2_LED_On(0u);
						break;
				case 400:
						printf("                                \n");
						printf("                                NS: +400 \n");
				    printf("                                NS: NS-Yellow LED Off (No effect)\n");
						PD2_NS = 1; // NO Hardware Fault, but also NO light off
						//PD2 = 1; // DROP Hardware Fault, and also NO light off
            break;
        case 600:
            // second developer handle
						printf("                                \n");
						printf("                                NS: +600 \n");
				    printf("                                NS: S-Yellow LED Off\n");
            Secure_PD2_LED_Off(0u);
						break;
				case 800:
						printf("                                \n");
						printf("                                NS: +800 \n");
						printf("                                NS: NS-Yellow LED On (No effect)\n");
						PD2_NS = 0; // NO Hardware Fault, but also NO light on
						//PD2 = 0; // DROP Hardware Fault, and also NO light on
            break;
        case 1000:
            u32Ticks = 0;
            break;

        default:
            if(u32Ticks > 1000)
            {
                u32Ticks = 0;
            }
    }
}

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main(void)
{

    printf("-----------------------------\n");
		printf("Nonsecure code is running ...\n");
		printf("-----------------------------\n");

    /* Init GPIO Port C for non-secure LED control */
    GPIO_SetMode(PC_NS, BIT0, GPIO_MODE_OUTPUT);

    /* Call secure API to get system core clock */
    SystemCoreClock = GetSystemCoreClock();

    /* Generate Systick interrupt each 10 ms */
    SysTick_Config(SystemCoreClock / 100);

    /* Waiting for secure/non-secure SysTick interrupt */
    while(1);
}
