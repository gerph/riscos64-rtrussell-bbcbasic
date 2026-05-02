#ifndef RISCOSSWI_H
#define RISCOSSWI_H

#include <stdint.h>
#include "kernel.h"

_kernel_oserror *_kernel_swi_flags(int swinum, int *inregs, int *outregs, uint32_t *flagsp);

#endif
