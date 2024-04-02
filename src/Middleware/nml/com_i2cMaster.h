/***********************************************************************************************************************
 * File Name    : com_i2cMaster.h
 * Description  : 
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2024 by TinhNN. All rights reserved.
 **********************************************************************************************************************/


#ifndef COM_I2CMASTER_H
#define COM_I2CMASTER_H

#include "nml.h"

int32_t com_i2c_init(uint32_t *Config);
int32_t com_i2c_deinit();
uint32_t com_i2c_eventcallback();

int32_t com_i2c_write(
    int32_t *DeviceHandle,
    uint8_t address,
    uint8_t *TxBuffer,
    uint16_t length);

int32_t com_i2c_read(
    int32_t *DeviceHandle,
    uint8_t address,
    uint8_t *RxBuffer,
    uint16_t length);

#endif /* COM_I2CMASTER_H */
