/* ------------------------------------------------------------------------------
    File:     btl_reset_handler.S
    Author:   C67846
    Date:     2025-06-4
    Purpose:  This code handles the data initialization for Cortex-M0+
		devices and is called after each processor reset.
		This program copies functions from .data to the data RAM and then
		executes the main function.
    Reasoning: The bootloader startup logic is implemented in assembly language to
        avoid issues encountered with the XC32 compiler at optimization level 2.
        When this code was previously implemented in C, the compiler could apply
        optimizations such as loop distribution or fission, which might insert
        memset calls into the startup code. Since the necessary library functions
        in RAM are not yet initialized at this stage, invoking memset from C code
        may result in a system crash with certain compiler versions. Therefore,
        performing data initialization in assembly is the preferred approach to
        ensure reliability and maintain optimal performance and code size.
    Note: The C code that this file was ported from is included at the bottom of
        the file. If any issues arise from this file in the future consider using
        the C code instead but remember that loop distribution or fission optimizations
        should used on some XC32 versions. These optimization issues can be avoided
        by using the `-fno-tree-loop-distribute-patterns` compiler option.
------------------------------------------------------------------------------
    Revision History:
    2025-06-4  Initial version ported from C code.
------------------------------------------------------------------------------
*/

    .section .romfunc.Reset_Handler, "ax", %progbits
    .global Reset_Handler
    .type Reset_Handler, %function

Reset_Handler:
    /* Load addresses of _etext, _sdata, _edata */
    LDR     r0, =_etext
    LDR     r1, =_sdata
    LDR     r2, =_edata

    /* Calculate number of 32-bit words to copy: (_edata - _sdata) / 4 */
    SUB     r3, r2, r1
    LSR     r3, r3, #2

    /* If rcx == 0, skip .data copy */
    CMP     r3, #0
    BEQ     init_bss

copy_data_loop:
    /* Load word from .text */
    LDR     r4, [r0]
    /* Store word in data region */
    STR     r4, [r1]
    /** Increment addresses */
    ADD     r0, r0, #4
    ADD     r1, r1, #4
    /** Decrement the loop counter */
    SUB     r3, r3, #1
    
    /** Loop till r3 == 0 */
    CMP     r3, #0
    BNE     copy_data_loop

init_bss:
    /* Load addresses of _sbss, _ebss */
    LDR     r1, =_sbss
    LDR     r2, =_ebss

    /* Calculate number of 32-bit words to init to zero: (_ebss - _sbss) / 4 */
    SUB     r3, r2, r1
    LSR     r3, r3, #2

    /* If r3 == 0, skip .bss zero */
    CMP     r3, #0
    BEQ     call_main

zero_bss_loop:
    /** Set the data address to 0 */
    MOVS    r4, #0
    STR     r4, [r1]
    /* Increment data address */
    ADD     r1, r1, #4
    /** Decrement the loop counter */
    SUB     r3, r3, #1
    
    /** Loop till r3 == 0 */
    CMP     r3, #0
    BNE     zero_bss_loop

call_main:
    LDR     r0, =main
    BLX     r0

hang:
    B       hang

    .size Reset_Handler, . - Reset_Handler

.end

/**
    If you desire to use the C code for startup, copy and paste this code into the startup_xc32.c file,
    and remove the btl_reset_handler.s file from the project.
  ----------------------------------------------------------------------------
    // Step 1: Remove the extern qualifier from the Reset_Handler prototype when using C code
    void __attribute__((noinline)) Reset_Handler(void);

    // Step 2: Add the following code to the startup_xc32.c
    // Linker-defined symbols for data initialization.
    extern uint32_t _sdata, _edata, _etext;
    extern uint32_t _sbss, _ebss;

    void __attribute__((noinline, section(".romfunc.Reset_Handler"))) Reset_Handler(void)
    {
        register uint32_t count;

        uint32_t *pSrc, *pDst;
        uintptr_t src, dst;


        src = (uintptr_t) & _etext;
        pSrc = (uint32_t *) src; // flash functions start after .text
        dst = (uintptr_t) & _sdata;
        pDst = (uint32_t *) dst; // boundaries of .data area to init

        // Init .data
        for (count = 0U; count < (((uint32_t) & _edata - (uint32_t) dst) / 4U); count++)
        {
            pDst[count] = pSrc[count];
        }

        // Init .bss
        dst = (uintptr_t) & _sbss;
        pDst = (uint32_t *) dst;
        for (count = 0U; count < (((uint32_t) & _ebss - (uint32_t) dst) / 4U); count++)
        {
            pDst[count] = 0U;
        }


        // Branch to application's main function
        (void) main();
#if (defined(__DEBUG) || defined(__DEBUG_D)) && defined(__XC32)
        __builtin_software_breakpoint();
#endif
    }
  ----------------------------------------------------------------------------
*/
