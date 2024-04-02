/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
            [1] = usbfs_resume_handler, /* USBFS RESUME (USBFS resume interrupt) */
            [2] = usbfs_d0fifo_handler, /* USBFS FIFO 0 (DMA transfer request 0) */
            [3] = usbfs_d1fifo_handler, /* USBFS FIFO 1 (DMA transfer request 1) */
            [4] = usbhs_interrupt_handler, /* USBHS USB INT RESUME (USBHS interrupt) */
            [5] = usbhs_d0fifo_handler, /* USBHS FIFO 0 (DMA transfer request 0) */
            [6] = usbhs_d1fifo_handler, /* USBHS FIFO 1 (DMA transfer request 1) */
            [7] = dmac_int_isr, /* DMAC0 INT (DMAC0 transfer end) */
            [8] = dmac_int_isr, /* DMAC1 INT (DMAC1 transfer end) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_USBFS_INT,GROUP0), /* USBFS INT (USBFS interrupt) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_USBFS_RESUME,GROUP1), /* USBFS RESUME (USBFS resume interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_USBFS_FIFO_0,GROUP2), /* USBFS FIFO 0 (DMA transfer request 0) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_USBFS_FIFO_1,GROUP3), /* USBFS FIFO 1 (DMA transfer request 1) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_USBHS_USB_INT_RESUME,GROUP4), /* USBHS USB INT RESUME (USBHS interrupt) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_USBHS_FIFO_0,GROUP5), /* USBHS FIFO 0 (DMA transfer request 0) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_USBHS_FIFO_1,GROUP6), /* USBHS FIFO 1 (DMA transfer request 1) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_DMAC0_INT,GROUP7), /* DMAC0 INT (DMAC0 transfer end) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_DMAC1_INT,GROUP0), /* DMAC1 INT (DMAC1 transfer end) */
        };
        #endif
        #endif
