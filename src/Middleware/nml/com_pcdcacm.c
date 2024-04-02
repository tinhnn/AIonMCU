/***********************************************************************************************************************
 * File Name    : com_pcdcacm.c
 * Description  : USB Peripheral CDC-ACM with USBX
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2024 by TinhNN. All rights reserved.
 **********************************************************************************************************************/

#include "com_pcdcacm.h"
#include "r_usb_basic_api.h"
#include "r_usb_basic.h"
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"
#include "logger/logger.h"

#define CDCACM_FLAG                         ((ULONG) 0x0001)
#define CDCACM_ACTIVATE_FLAG                ((ULONG) 0x0004)
#define CDCACM_DEACTIVATE_FLAG              ((ULONG) 0x0008)

extern uint8_t g_device_framework_full_speed[];
extern uint8_t g_device_framework_hi_speed[];
extern uint8_t g_language_id_framework[];
extern uint8_t g_string_framework[];


static uint32_t g_memory_pool[MEMPOOL_SIZE / BYTE_SIZE];
static UX_SLAVE_CLASS_CDC_ACM_PARAMETER g_usb_params;
static UX_SLAVE_CLASS_CDC_ACM * g_usb_handle;
#ifdef _RENESAS_RA_
static usb_cfg_t *_DeviceConfig;
static usb_instance_ctrl_t *_DeviceControl;
#else
#endif

static void usb_instance_active(void *usb_handle);
static void usb_instance_deactive(void *usb_handle);
extern uint32_t usb_peri_usbx_initialize(uint32_t dcd_io);

int32_t com_usb_init(USB_Dev_Config *Device)
{
    uint32_t status = UX_SUCCESS;
    int32_t err;
    uint32_t actual_flags = 0x0000;

    _DeviceConfig = (usb_cfg_t*)Device->Config;
    _DeviceControl = (usb_instance_ctrl_t*)Device->Control;

    /* ux_system_initialization */
    status = ux_system_initialize(g_memory_pool, MEMPOOL_SIZE, UX_NULL, 0);
    if (UX_SUCCESS != status)
    {
        PRINT_ERR_STR("_ux_system_initialize api failed..");
        ERROR_TRAP(status);
        return status;
    }

    /* ux_device stack initialization */
    status = ux_device_stack_initialize( g_device_framework_hi_speed,
                                         DEVICE_FRAME_LENGTH_HIGH_SPEED,
                                         g_device_framework_full_speed,
                                         DEVICE_FRAME_LENGTH_FULL_SPEED,
                                         g_string_framework,
                                         STRING_FRAMEWORK_LENGTH,
                                         g_language_id_framework,
                                         LANGUAGE_ID_FRAME_WORK_LENGTH,
                                         &com_usb_eventcallback);
    if (UX_SUCCESS != status)
    {
        PRINT_ERR_STR("ux_device_stack_initialize api failed..");
        ERROR_TRAP(status);
        return status;
    }

    g_usb_params.ux_slave_class_cdc_acm_instance_activate = usb_instance_active;
    g_usb_params.ux_slave_class_cdc_acm_instance_deactivate = usb_instance_deactive;
    status = ux_device_stack_class_register ( _ux_system_slave_class_cdc_acm_name,
                                              _ux_device_class_cdc_acm_entry,
                                              CONFIG_NUMB,
                                              INTERFACE_NUMB0,
                                              (void*) &g_usb_params);
    if (UX_SUCCESS != status)
    {
        PRINT_ERR_STR("ux_device_stack_class_register api failed..");
        ERROR_TRAP(status);
        return status;
    }

    /* Initialize the peripheral mode according to the USB speed selection */
    if (USB_SPEED_HS == _DeviceConfig->usb_speed)
    {
        /* Peri mode initialization with HIGH Speed */
        status = usb_peri_usbx_initialize (R_USB_HS0_BASE);
    }
    else
    {
        /* Peri mode initialization with FULL  Speed */
        status = usb_peri_usbx_initialize (R_USB_FS0_BASE);
    }
    if (UX_SUCCESS != status)
    {
        PRINT_ERR_STR("usb_peri_usbx_initialize api failed..");
        ERROR_TRAP(status);
        return status;
    }

    /* Open usb driver */
    err = R_USB_Open(_DeviceControl, _DeviceConfig);
    if (FSP_SUCCESS != err)
    {
        PRINT_ERR_STR("R_USB_OPEN api failed..");
        ERROR_TRAP(status);
        return err;
    }

    status = tx_event_flags_get(&g_cdcacm_event_flags0, CDCACM_ACTIVATE_FLAG, TX_OR, &actual_flags, TX_WAIT_FOREVER);
    if((actual_flags & CDCACM_ACTIVATE_FLAG) && (TX_SUCCESS == status))
    {
        PRINT_INFO_STR("USB Enumeration completed!");
    }
    else if(!(actual_flags & CDCACM_ACTIVATE_FLAG))
    {
        PRINT_INFO_STR("USB instance deactivated");
    }

    return status;
}

int32_t com_usb_deinit()
{
    //
    return 0;
}

uint32_t com_usb_eventcallback(uint32_t status)
{
    switch (status)
    {
        case UX_DEVICE_ATTACHED:
        {
            tx_event_flags_set(&g_cdcacm_event_flags0, CDCACM_FLAG, TX_OR);
        }
        break;

        case UX_DEVICE_REMOVED:
        {
            tx_event_flags_set(&g_cdcacm_event_flags0, ~CDCACM_FLAG, TX_AND);
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }
    return 0;
}

int32_t usb_connection_status_check(void)
{
    ULONG actual_flags = 0;

    tx_event_flags_get (&g_cdcacm_event_flags0, CDCACM_FLAG, TX_OR, &actual_flags, TX_WAIT_FOREVER);

    if(actual_flags & CDCACM_FLAG)
    {
        return 1;   // USB Device is Attached
    }
    else
    {
        return 0;   // USB Device is removed
    }
}


int32_t com_usb_read(uint32_t *handle, uint8_t *RXBuffer, uint32_t requested_length, uint32_t *actual_length)
{
    UINT status = UX_SUCCESS;
    status = ux_device_class_cdc_acm_read ((UX_SLAVE_CLASS_CDC_ACM*)handle, RXBuffer, requested_length, actual_length);

    return status;
}

int32_t com_usb_write(uint32_t *handle, uint8_t *TXBuffer, uint32_t requested_length, uint32_t *actual_length)
{
    UINT status = UX_SUCCESS;
    status = ux_device_class_cdc_acm_write ((UX_SLAVE_CLASS_CDC_ACM*)handle, TXBuffer, requested_length, actual_length);

    return status;
}




static void usb_instance_active(void *usb_handle)
{
    g_usb_handle = (UX_SLAVE_CLASS_CDC_ACM *)usb_handle;
    tx_event_flags_set(&g_cdcacm_event_flags0, CDCACM_ACTIVATE_FLAG, TX_OR);
}

static void usb_instance_deactive(void *usb_handle)
{
    FSP_PARAMETER_NOT_USED(usb_handle);
    g_usb_handle = NULL;
    tx_event_flags_set(&g_cdcacm_event_flags0, CDCACM_DEACTIVATE_FLAG, TX_OR);
}
