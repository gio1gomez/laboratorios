#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"  // 📌 Agregado para definir correctamente INT_TIMER0A_TM4C129
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#define LED GPIO_PIN_0  // PN0

void Timer0A_Handler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  // Limpiar interrupción
    GPIOPinWrite(GPIO_PORTN_BASE, LED, GPIOPinRead(GPIO_PORTN_BASE, LED) ^ LED);  // Toggle LED
}

void Timer0A_Init(uint32_t period_ms) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));  // Esperar que esté listo
    
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (120000 * period_ms) - 1);  // 120MHz clock

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0A_Handler); // 📌 Registrar interrupción
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    IntPrioritySet(INT_TIMER0A_TM4C129, 0x00);  // 📌 Definición correcta
    IntEnable(INT_TIMER0A_TM4C129);  // 📌 Usar la definición correcta
    TimerEnable(TIMER0_BASE, TIMER_A);
}

int main(void) {
    // Configurar el reloj a 120MHz
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
    
    // Habilitar Puerto N
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));

    // Configurar PN0 como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, LED);

    // Habilitar interrupciones globales
    IntMasterEnable();

    // Inicializar Timer0A con 1s (1000ms)
    Timer0A_Init(5000);

    while (1);
}

