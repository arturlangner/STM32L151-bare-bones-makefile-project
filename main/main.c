#include <SEGGER/SEGGER_RTT.h>
#include <stm32l1xx.h>

int main(void){
    //Disables write buffering - makes all bus faults precise, but slows everything down
    SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;

    SEGGER_RTT_Init();

    SEGGER_RTT_printf(0, "Hello from STM32!\n");

    while(1){

    }
    __builtin_unreachable();
}
