#ifndef SP_212_H
#define SP_212_H

#include "common.h"

/*
 * Returns: SP-212 reading in W/m^-2
 * SP-212 has a conversion factor of 0.5 W/m^-2 per mV
 */
uint32_t sp212_read(void);

#endif
