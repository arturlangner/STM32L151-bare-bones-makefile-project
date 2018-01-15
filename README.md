# STM32L151 bare bones Makefile project
This is a basic STM32L151RB project using the GNU toolchain. It can be modified to run on STM32L152. Features:

  - `make`-based build system
  - Startup code from ST
  - Linker script from ST
  - STM32L1xx standard peripheral drivers library
  - SEGGER RTT (debug terminal-over-JTAG) code
  - Handy [hard fault handler](https://mcuoneclipse.com/2012/11/24/debugging-hard-faults-on-arm-cortex-m/) for debugging

# How to run
1. Download the [GNU ARM Embedded toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm), extract anywhere and add the `bin` directory to your `$PATH`
2. Simply type `make`
3. Load `main.elf` with your JTAG adapter. I highly recommend using [J-Link](https://www.segger.com/products/debug-probes/j-link/models/j-link-edu/) and [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/).
4. The application will print a hello message in RTT console.
5. Default clock configuration code will try to use a high-speed external crystal (HSE) but will fallback to internal 2.1MHz clock if that one fails.

# My other projects [www.lb9mg.no]
