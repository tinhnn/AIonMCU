/***********************************************************************************************************************
 * File Name    : com_pcdcacm.h
 * Description  : USB Peripheral CDC-ACM with USBX
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2024 by TinhNN. All rights reserved.
 **********************************************************************************************************************/

#ifndef COM_PCDCACM_H
#define COM_PCDCACM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nml.h"

/* USBx device configuration settings */
#define DEVICE_FRAME_LENGTH_HIGH_SPEED              (103U)
#define DEVICE_FRAME_LENGTH_FULL_SPEED              (93U)
#define STRING_FRAMEWORK_LENGTH                     (77U)
#define LANGUAGE_ID_FRAME_WORK_LENGTH               (2U)
#define CONFIG_NUMB                                 (1U)
#define INTERFACE_NUMB0                             (0x00)
#define INTERFACE_NUMB1                             (0x01)
#define MEMPOOL_SIZE                                (18432U)
#define BYTE_SIZE                                   (4U)
#define DATA_LEN                                    (2048U)
#define WRITE_DATA_LEN                              (62U)
#define MAX_PACKET_SIZE_HS                          (512U)
#define MAX_PACKET_SIZE_FS                          (64U)

typedef struct s_USB_Dev_Config
{
    int32_t *Control;
    int32_t *Config;
} USB_Dev_Config;


int32_t com_usb_init(USB_Dev_Config *Device);
int32_t com_usb_deinit();
uint32_t com_usb_eventcallback(uint32_t status);
int32_t usb_connection_status_check(void);

int32_t com_usb_read(
    uint32_t *handle,
    uint8_t *RXBuffer,
    uint32_t requested_length,
    uint32_t *actual_length);

int32_t com_usb_write(
    uint32_t *handle,
    uint8_t *TXBuffer,
    uint32_t requested_length,
    uint32_t *actual_length);

#ifdef __cplusplus
}
#endif
#endif /* COM_PCDCACM_H */
