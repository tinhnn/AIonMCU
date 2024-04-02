#include "usb_thread.h"
#include "com_pcdcacm.h"

uint8_t RevFlg = 0;

/* USB Thread entry function */
void usb_thread_entry(void)
{
    /* TODO: add your own code here */
    USB_Dev_Config Device;
    Device.Control = (int32_t*)&g_basic0_ctrl;
    Device.Config = (int32_t*)&g_basic0_cfg;

    com_usb_init(&Device);

    while (1)
    {
        tx_thread_sleep (1);
    }
}
