/***********************************************************************************************************************
 * File Name    : nml.h
 * Description  :
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2024 by TinhNN. All rights reserved.
 **********************************************************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_data.h"
#include "SEGGER_RTT/SEGGER_RTT.h"

#define LVL_ERR      (1u)
#define SEGGER_INDEX            (0)

#define PRINT_INFO_STR(fn_, ...)    (SEGGER_RTT_printf (SEGGER_INDEX,(fn_), ##__VA_ARGS__))
#define PRINT_ERR_STR(fn_, ...)     ({\
                                        if(LVL_ERR)\
                                        SEGGER_RTT_printf (SEGGER_INDEX, "[ERR] In Function: %s(), %s",__FUNCTION__,(fn_),##__VA_ARGS__);\
                                    })
#define ERROR_TRAP(err)             ({\
                                        if((err)) {\
                                        SEGGER_RTT_printf(SEGGER_INDEX, "\r\nReturned Error Code: 0x%x  \r\n", (err));\
                                        __asm("BKPT #0\n");} /* trap upon the error  */\
                                    })


#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H */
