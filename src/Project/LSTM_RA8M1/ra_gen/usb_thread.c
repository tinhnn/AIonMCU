/* generated thread source file - do not edit */
#include "usb_thread.h"

TX_THREAD usb_thread;
void usb_thread_create(void);
static void usb_thread_func(ULONG thread_input);
static uint8_t usb_thread_stack[1024] BSP_PLACE_IN_SECTION(".stack.usb_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
dmac_instance_ctrl_t g_transfer1_ctrl;
transfer_info_t g_transfer1_info =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) 0,
  .p_src = (void const*) USB_SRC_ADDRESS,
  .num_blocks = 0,
  .length = 0, };
const dmac_extended_cfg_t g_transfer1_extend =
{ .offset = 0, .src_buffer_size = 1,
#if defined(VECTOR_NUMBER_DMAC1_INT)
    .irq                 = VECTOR_NUMBER_DMAC1_INT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (3),
  .channel = 1, .p_callback = NULL, .p_context = NULL, .activation_source = ELC_EVENT_USBHS_FIFO_0, };
const transfer_cfg_t g_transfer1_cfg =
{ .p_info = &g_transfer1_info, .p_extend = &g_transfer1_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{ .p_ctrl = &g_transfer1_ctrl, .p_cfg = &g_transfer1_cfg, .p_api = &g_transfer_on_dmac };
dmac_instance_ctrl_t g_transfer0_ctrl;
transfer_info_t g_transfer0_info =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) USB_DEST_ADDRESS,
  .p_src = (void const*) 0,
  .num_blocks = 0,
  .length = 0, };
const dmac_extended_cfg_t g_transfer0_extend =
{ .offset = 0, .src_buffer_size = 1,
#if defined(VECTOR_NUMBER_DMAC0_INT)
    .irq                 = VECTOR_NUMBER_DMAC0_INT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (3),
  .channel = 0, .p_callback = usb_ip1_d1fifo_callback, .p_context = NULL, .activation_source = ELC_EVENT_USBHS_FIFO_1, };
const transfer_cfg_t g_transfer0_cfg =
{ .p_info = &g_transfer0_info, .p_extend = &g_transfer0_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{ .p_ctrl = &g_transfer0_ctrl, .p_cfg = &g_transfer0_cfg, .p_api = &g_transfer_on_dmac };
usb_instance_ctrl_t g_basic0_ctrl;

#if !defined(NULL)
extern usb_descriptor_t NULL;
#endif
#define RA_NOT_DEFINED (1)
const usb_cfg_t g_basic0_cfg =
{ .usb_mode = USB_MODE_PERI, .usb_speed = USB_SPEED_HS, .module_number = 1, .type = USB_CLASS_PCDC,
#if defined(NULL)
                .p_usb_reg = NULL,
#else
  .p_usb_reg = &NULL,
#endif
  .usb_complience_cb = NULL,
#if defined(VECTOR_NUMBER_USBFS_INT)
                .irq       = VECTOR_NUMBER_USBFS_INT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_RESUME)
                .irq_r     = VECTOR_NUMBER_USBFS_RESUME,
#else
  .irq_r = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_FIFO_0)
                .irq_d0    = VECTOR_NUMBER_USBFS_FIFO_0,
#else
  .irq_d0 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_FIFO_1)
                .irq_d1    = VECTOR_NUMBER_USBFS_FIFO_1,
#else
  .irq_d1 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
                .hsirq     = VECTOR_NUMBER_USBHS_USB_INT_RESUME,
#else
  .hsirq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_FIFO_0)
                .hsirq_d0  = VECTOR_NUMBER_USBHS_FIFO_0,
#else
  .hsirq_d0 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_FIFO_1)
                .hsirq_d1  = VECTOR_NUMBER_USBHS_FIFO_1,
#else
  .hsirq_d1 = FSP_INVALID_VECTOR,
#endif
  .ipl = (12),
  .ipl_r = (12), .ipl_d0 = (12), .ipl_d1 = (12), .hsipl = (12), .hsipl_d0 = (12), .hsipl_d1 = (12),
#if (BSP_CFG_RTOS == 0) && defined(USB_CFG_HMSC_USE)
                .p_usb_apl_callback = NULL,
#else
  .p_usb_apl_callback = NULL,
#endif
#if defined(NULL)
                .p_context = NULL,
#else
  .p_context = &NULL,
#endif
#if (RA_NOT_DEFINED == g_transfer0)
#else
  .p_transfer_tx = &g_transfer0,
#endif
#if (RA_NOT_DEFINED == g_transfer1)
#else
  .p_transfer_rx = &g_transfer1,
#endif
        };
#undef RA_NOT_DEFINED

/* Instance structure to use this module. */
const usb_instance_t g_basic0 =
{ .p_ctrl = &g_basic0_ctrl, .p_cfg = &g_basic0_cfg, .p_api = &g_usb_on_usb, };

extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void usb_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&usb_thread, (CHAR*) "USB Thread", usb_thread_func, (ULONG) NULL, &usb_thread_stack, 1024,
                            2, 2, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&usb_thread, 0);
    }
}

static void usb_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    usb_thread_entry ();
}
