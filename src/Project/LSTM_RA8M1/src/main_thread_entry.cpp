#include "main_thread.h"
#include "model_lstm.h"


/* Main Thread entry function */
void main_thread_entry(void)
{
    s_input TC;
    s_output inferOut[1];
    s_output out;
    // Normal case
    TC.data[0] = 1.7765;
    TC.data[1] = 1.9228;
    TC.data[2] = 2.9628;
    TC.data[3] = 2.9627;
    TC.data[4] = -0.0342;
    TC.data[5] = 0.5746;
    TC.data[6] = 5.5499;
    TC.data[7] = 0.5736;
    TC.data[8] = 7.0607;
    TC.data[9] = -8.6051;
    TC.data[10] = -8.4526;
    TC.data[11] = -5.9708;
    for(int i = 0; i < 1000; i++){
        predict(&TC, inferOut);
        out = inferOut[0];
        (void)out;
    }
    // Abnormal case
    TC.data[0] = 2.3118;
    TC.data[1] = 2.5286;
    TC.data[2] = 2.2768;
    TC.data[3] = 2.2767;
    TC.data[4] = -0.0357;
    TC.data[5] = 0.5409;
    TC.data[6] = 5.7182;
    TC.data[7] = 0.5398;
    TC.data[8] = 7.1786;
    TC.data[9] = -16.0769;
    TC.data[10] = -16.0662;
    TC.data[11] = -9.3099;
    predict(&TC, inferOut);
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
