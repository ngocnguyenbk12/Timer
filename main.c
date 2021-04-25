#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"


void Timer0IntHandler(void);
void Timer0Init(void);
void Delayms(int time);

int main(void)
{
			SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);  //40MHz 
			Timer0Init();
	
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2|GPIO_PIN_3);
	
			while(1)
			{
			}
}

void Timer0Init(void)
{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);  // Enable Timer Peripheral
		
	
		TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC_UP);   // Timer Auto Reload
//		Timerconfigure(TIMER0_BASE, TIMER_CFG_A_ONE_SHOT);		// timer OneShot
	
		TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/1)/2);	// Sysctl
	
		IntEnable(INT_TIMER0A);		// Enable Interupt	
		TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  
		IntMasterEnable();
	
		TimerEnable(TIMER0_BASE, TIMER_A);

		//		TimerDisable(TIMER0_BASE, TIMER_A);
	
}

void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0f);
	Delayms(1000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0x00);
	Delayms(1000);
}

void Delayms(int time)    // SysCtlDelay : Delay for 3cycles 
{
	uint32_t time2= time*40000/3;
	SysCtlDelay(time2);
}