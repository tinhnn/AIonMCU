/* generated thread source file - do not edit */
#include "main_thread.h"

TX_THREAD main_thread;
void main_thread_create(void);
static void main_thread_func(ULONG thread_input);
static uint8_t main_thread_stack[0x8000] BSP_PLACE_IN_SECTION(".stack.main_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void main_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&main_thread, (CHAR*) "Main Thread", main_thread_func, (ULONG) NULL, &main_thread_stack,
                            0x8000, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&main_thread, 0);
    }
}

static void main_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    main_thread_entry ();
}
