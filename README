
![Alttext](https://github.com/heshamelmatary/rtems-riscv/blob/master/screenshot_hello.png "RTEMS Hello World (on seL4) ")

This is RTEMS port for RISC-V architecture (currently riscv32). It runs 
Hello World and Ticker (with sim timer), on both Spike simulator and 
seL4 microkernel (two cores).

There are two BSPs currently: 

1) riscv_generic: This BSP is intended to run in Machine mode, and has
been tested on Spike.

To run it configure and build RTEMS with:

$../rtems/configure --target=riscv32-rtems4.12 --disable-posix --disable-networking
--disable-itron --enable-rtemsbsp=riscv_generic

$ make

Command to run on Spike: 

$ spike --isa=RV32 riscv32-rtems4.11/c/riscv_generic/testsuites/samples/ticker/ticker.exe

2) riscv_seL4: This BSP assumes it run with support of seL4 microkernel, 
and it runs in Supervisor mode (on another core). seL4 application would allocate
and map memory for it from its untyped memory (userspace), before off-loading it to
another core.

To run it with seL4, you need to get seL4-rtems project first, configure it,
but before building seL4 two shell variables have to be exported so that seL4
can know about where/which RTEMS image to load. 

export RTEMS_IMAGE="Absolute path to the RTEMS .exe image"
export RTEMS_IMG_NAME="Name of the RTEMS image you would use, i.e hello.exe, ticker.exe"

For how to build/run seL4-rtems
project follow the exact same instructions here [1] with the only difference 
replacing:

repo init -u https://github.com/heshamelmatary/sel4riscv-manifest.git

with

repo init -u https://github.com/heshamelmatary/sel4riscv-rtems-manifest.git

Which fetches the seL4-rtems project.

[1] http://heshamelmatary.blogspot.co.uk/2015/07/howto-build-and-run-sel4-on-risc-v.html

*******************************************************************
This is the Real-Time Executive for Multiprocessing Systems (RTEMS).
The version number for this software is indicated in the VERSION file.

See the documentation manuals in doc/ with daily builds available online at
http://rtems.org/onlinedocs/doc-current/share/rtems/html/ and released builds
at http://www.rtems.org/onlinedocs/releases/ for information on building,
installing, and using RTEMS. The INSTALL file tells you to come back here.

See the RTEMS Wiki at http://devel.rtems.org for community knowledge and
tutorials.

RTEMS Doxygen available at http://www.rtems.org/onlinedocs/doxygen/cpukit/html

The RTEMS Project maintains mailing lists which are used for most
discussions:

* For general-purpose questions related to using RTEMS, use the
  rtems-users ml: https://lists.rtems.org/mailman/listinfo/users
* For questions and discussion related to development of RTEMS, use the
  rtems-devel ml: https://lists.rtems.org/mailman/listinfo/devel

See https://devel.rtems.org/ to view existing or file a new issue
report ticket.

