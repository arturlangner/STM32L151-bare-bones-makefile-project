#include <stm32l1xx.h>
#include <core_cm3.h>

//as seen on TV... https://mcuoneclipse.com/2012/11/24/debugging-hard-faults-on-arm-cortex-m/

void HardFault_HandlerC(unsigned long *hardfault_args);
/**
 * HardFaultHandler_C:
 * This is called from the HardFault_HandlerAsm with a pointer the Fault stack
 * as the parameter. We can then read the values from the stack and place them
 * into local variables for ease of reading.
 * We then read the various Fault Status and Address Registers to help decode
 * cause of the fault.
 * The function ends with a BKPT instruction to force control back into the debugger
 */
void HardFault_HandlerC(unsigned long *hardfault_args){

    /* Attribute unused is to silence compiler warnings,
     * the variables are placed here, so they can be inspected
     * by the debugger.
     */
    volatile unsigned long __attribute__((unused)) stacked_r0;
    volatile unsigned long __attribute__((unused)) stacked_r1;
    volatile unsigned long __attribute__((unused)) stacked_r2;
    volatile unsigned long __attribute__((unused)) stacked_r3;
    volatile unsigned long __attribute__((unused)) stacked_r12;
    volatile unsigned long __attribute__((unused)) stacked_lr;
    volatile unsigned long __attribute__((unused)) stacked_pc;
    volatile unsigned long __attribute__((unused)) stacked_psr;

    stacked_r0 = ((unsigned long)hardfault_args[0]) ;
    stacked_r1 = ((unsigned long)hardfault_args[1]) ;
    stacked_r2 = ((unsigned long)hardfault_args[2]) ;
    stacked_r3 = ((unsigned long)hardfault_args[3]) ;
    stacked_r12 = ((unsigned long)hardfault_args[4]) ;
    stacked_lr = ((unsigned long)hardfault_args[5]) ;
    stacked_pc = ((unsigned long)hardfault_args[6]) ;
    stacked_psr = ((unsigned long)hardfault_args[7]) ;
    
    // Configurable Fault Status Register
    // Consists of MMSR, BFSR and UFSR
    volatile unsigned long __attribute__((unused)) _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

    // Hard Fault Status Register
    volatile unsigned long __attribute__((unused)) _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

    // Debug Fault Status Register
    volatile unsigned long __attribute__((unused)) _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

    // Auxiliary Fault Status Register
    volatile unsigned long __attribute__((unused)) _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

    // Read the Fault Address Registers. These may not contain valid values.
    // Check BFARVALID/MMARVALID to see if they are valid values
    // MemManage Fault Address Register
    volatile unsigned long __attribute__((unused)) _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
    // Bus Fault Address Register
    volatile unsigned long __attribute__((unused)) _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;


    __BKPT(1); //Break into the debugger or reset
}

extern void HardFault_Handler(void);

__attribute__((naked)) void HardFault_Handler(void)
{
        __asm volatile (
                        " movs r0,#4       \n"
                        " movs r1, lr      \n"
                        " tst r0, r1       \n"
                        " beq _MSP         \n"
                        " mrs r0, psp      \n"
                        " b _HALT          \n"
                        "_MSP:               \n"
                        " mrs r0, msp      \n"
                        "_HALT:              \n"
                        " ldr r1,[r0,#20]  \n"
                        " b HardFault_HandlerC \n"
                        " bkpt #0          \n"
        );
}
