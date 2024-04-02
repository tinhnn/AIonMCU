/***********************************************************************************************************************
 * File Name    : com_i2cMaster.c
 * Description  : 
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2024 by TinhNN. All rights reserved.
 **********************************************************************************************************************/

#include "com_i2cMaster.h"

#define TIMEOUT_REQUEST 1000	// max waiting response is 1s

int32_t com_i2c_init(uint32_t *Config)
{
    FSP_PARAMETER_NOT_USED(Config);
    return 0;
}

int32_t com_i2c_deinit()
{
    //
    return 0;
}

uint32_t com_i2c_eventcallback()
{
    //
    return 0;
}


int i2c_write(int *DeviceHandle, uint8_t address, uint8_t *TxBuffer, uint16_t length)
{
#ifdef _RENESAS_RA_
    return 0;
#else
    return (int)HAL_I2C_Master_Transmit(DeviceHandle, address, TxBuffer, length, TIMEOUT_REQUEST);
#endif

}

int i2c_read(int *DeviceHandle, uint8_t address, uint8_t *RxBuffer, uint16_t length)
{
#ifdef _RENESAS_RA_
    return 0;
#else
    return (int)HAL_I2C_Master_Receive(DeviceHandle, address, RxBuffer, length, TIMEOUT_REQUEST);
#endif
}
