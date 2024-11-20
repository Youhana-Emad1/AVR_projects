#include <stdint.h>

/* UTILES_LIB */
#include "STM32F303xx.h"
#include "ERROR_TYPE.h"
#include "BIT_MATH.h"

/* MCAL */
#include "RCC_interface.h"
#include "RCC_private.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "SSD_interface.h"


int main(void)
{
	SSD_voidInit();
    /* Main loop */
    for (;;) {

    	SSD_voidDisplayNumber(8,1);

    }
    return 0;
}
