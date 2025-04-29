#include "C_OTAListenMonitor.h"
#include "C_OTAStateMonitor.h"
#include "C_OTADataMonitor.h"

pthread_t lwipDataTaskThread;
// pthread_mutex_t task_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t* pLwIPTCPDataTaskHandle_c = &lwipDataTaskThread;


void* Lwip_Listen_TASK(void* param)
{
    printf("Lwip_Listen_TASK\n");

    struct sockaddr_in address, remote;
    socklen_t size;
    memset(&address, 0, sizeof(address));

    otasock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (otasock < 0) {
        printf("OTA socket create error\n");
        return NULL;
    }

    int optval = 1;
    if (setsockopt(otasock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        printf("setsockopt failed\n");
        close(otasock);
        return NULL;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(10030);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(otasock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("bind error!\n");
        close(otasock);
        return NULL;
    }

    listen(otasock, 1); // 监听

    size = sizeof(remote);
    while (1)
    {
        printf("otasock1 before accept: %d\n", otasock1);
        otasock1 = accept(otasock, (struct sockaddr *)&remote, &size);
        if (otasock1 > 0)
        {
            setClientConnected(1);
            // clientConnected = 1;
            printf("otasock1 = %d\n", otasock1);
            printf("Client connected: %s:%d\n",
                         inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));

            if (pLwIPTCPDataTaskHandle_c == NULL || *pLwIPTCPDataTaskHandle_c == 0)
            {
                pthread_mutex_lock(&task_mutex); // 临界区保护
                if (pthread_create(&lwipDataTaskThread, NULL, lwip_data_TASK, NULL) == 0) {
                    printf("create lwip_data_TASK success\n");
                } else {
                    printf("create lwip_data_TASK failed\n");
                }
                pthread_mutex_unlock(&task_mutex);
            }
            else
            {
                printf("lwip_data_TASK already running!\n");
            }
        }
        else
        {
            printf("otasock1 error: %d\n", otasock1);
        }

        // 防止任务卡死
        usleep(100 * 1000); // 等价于 vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    printf("Lwip_Listen_TASK exited\n");
    return NULL;
}
