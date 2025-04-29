// #include "Serial_Led_Task.h"
// #include "../GLB/G_GloabalVariable.h"
// #include "../FUNC/Func_LEDShow.h"

// pthread_t SerialLed_TASKHandle;

// void *SerialLedTask_func(void* arg)
// {
//     LED_Mode LED_Mode_t =soc_flashing_mode;
//     while (1)
//     {
//         Func_update_led_mode(&LED_Mode_t);
//         if( Func_LEDShow(&LED_Mode_t) )
//         {

//         }
//         else
//         {
//             printf("SerialLed task running abnormal...\n");
//         }
//        usleep(100*1000);
//     }
//     return NULL;
// }

// void SerialLedTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&SerialLed_TASKHandle, NULL, SerialLedTask_func, NULL);
//         if (ret != 0) {
//             zlog_info(debug_out,"Failed to create SerialLedTask thread : %s",strerror(ret));
//             sleep(1); 
//         }
//         else
//         {
//             zlog_info(debug_out,"SerialLedTask thread created successfully.\r\n");
//         }
//     } while (ret != 0);
// }
