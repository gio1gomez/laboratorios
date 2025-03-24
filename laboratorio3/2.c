#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif
volatile uint32_t ui32Loop;
volatile uint32_t counter=0;
//*****************************************************************************
int main(void)
{
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),120000000);
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)|!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)|!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    { 
    }
    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);// led1 interno
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);//led2 interno
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);//led3 interno
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);//led4 interno
    //
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);//boton1 interno
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);//boton2 interno
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //
    // Loop forever.
    //
    while(1)
    {
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
    	SysCtlDelay(80000000);

    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
    	SysCtlDelay(80000000);

    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
 	SysCtlDelay(80000000);

    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
    	SysCtlDelay(80000000);

    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
    	SysCtlDelay(80000000);
    }
}
