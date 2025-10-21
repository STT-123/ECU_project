#include "ws_client.h"
#include "message_queue.h"
#include <libwebsockets.h>
#include <string.h>
#include <unistd.h>
#include <json-c/json.h>
#include <stdio.h>
#include "project.h"
#include "log/log.h"
static const char *ocpp_url = "wss://ocpp.xcharger.net:7274/ocpp";
static const char *ocpp_id = "C8A215DPWUDYDTAWLL";
// 保存当前连接 wsi
static struct lws *global_wsi = NULL;
static pthread_mutex_t wsi_lock = PTHREAD_MUTEX_INITIALIZER;
void handle_writeable(struct lws *wsi);
// 外部调用函数，请求触发写事件
void websocket_request_write(void)
{
    pthread_mutex_lock(&wsi_lock);
    if (global_wsi)
    {
        lws_callback_on_writable(global_wsi);
    }
    pthread_mutex_unlock(&wsi_lock);
}

static int callback_ws(struct lws *wsi, enum lws_callback_reasons reason,
                       void *user, void *in, size_t len)
{
    switch (reason)
    {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        pthread_mutex_lock(&wsi_lock);
        global_wsi = wsi;
        pthread_mutex_unlock(&wsi_lock);
        lwsl_user("WebSocket connected\n");
        // websocket_send("[2,\"1915669379150258176\",\"BootNotification\",{\
            // \"chargeBoxSerialNumber\":\"C8A215DPWUDYDTAWLL\",\
            // \"chargePointModel\":\"C8EU\",\
            // \"chargePointSerialNumber\":\"C8A215DPWUDYDTAWLL\",\
            // \"chargePointVendor\":\"xcharge\",\
            // \"firmwareVersion\":\"V1.0.0_C8EU_OCPP_STA_250508\",\
            // \"iccid\":\"\"}]");
        lws_callback_on_writable(wsi);
        break;
    case LWS_CALLBACK_CLIENT_WRITEABLE:
    {
        handle_writeable(wsi);
        break;
    }
    case LWS_CALLBACK_CLIENT_RECEIVE:
        // printf("Received: %.*s\n", (int)len, (char *)in);
        process_ocpp_message(wsi, (char *)in);
        break;
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        if (in)
        {
            // 打印出连接错误的具体信息
            lwsl_err("WebSocket connection error: %s\n", (char *)in);
        }
        else
        {
            lwsl_err("WebSocket connection error: Unknown error\n");
        }
        break;
    case LWS_CALLBACK_CLIENT_CLOSED:
        lwsl_err("WebSocket closed, reason: %s\n", in ? (char *)in : "Unknown reason");
        break;
    default:
        break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    {"ocpp1.6", callback_ws, 0, 2048},
    {NULL, NULL, 0, 0}};

void *websocket_client_thread(void *arg)
{
    struct lws_context_creation_info info = {0};
    struct lws_context *context;

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

    // lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG, NULL);

    context = lws_create_context(&info);

    while (1)
    {
        struct lws_client_connect_info ccinfo = {0};
        ccinfo.context = context;
        // ccinfo.address = "ocpp.xcharger.net";
        // ccinfo.port = 7274;
        // ccinfo.path = "/ocpp/C8A215DPWUDYDTAWLL";

        // ccinfo.address = "101.200.216.48";
        // ccinfo.port = 8080;
        // ccinfo.path = "/steve/websocket/CentralSystemService/lanxin123";

        ccinfo.address = "ocpp.xcharger.net";
        ccinfo.port = 7274;
        ccinfo.path = "/ocpp/C8A215DPLEXHGRKLGU";

        ccinfo.host = ccinfo.address;
        ccinfo.origin = ccinfo.address;
        ccinfo.protocol = protocols[0].name;
        // ccinfo.ssl_connection = LCCSCF_USE_SSL |
        //                         LCCSCF_ALLOW_SELFSIGNED |
        //                         LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        ccinfo.ssl_connection = LCCSCF_USE_SSL |
                                LCCSCF_ALLOW_SELFSIGNED |
                                LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK |
                                LCCSCF_ALLOW_EXPIRED |
                                LCCSCF_ALLOW_INSECURE; // LCCSCF_ALLOW_INSECURE 客户端跳过ssl校验

        // ccinfo.ssl_connection = LCCSCF_ALLOW_SELFSIGNED |
        //                         LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        // ccinfo.client_id = ocpp_id;

        struct lws *wsi = lws_client_connect_via_info(&ccinfo);
        if (!wsi)
        {
            LOG("WebSocket connection failed, retrying...");
        }

        while (lws_service(context, 1000) >= 0)
            ;

        sleep(5); // 自动重连等待
    }

    lws_context_destroy(context);
    return NULL;
}

// 写状态保存结构（绑定到 user 或用静态变量）
typedef struct
{
    struct json_object *msg;
    const char *text;
    size_t total_len;
    size_t sent_pos;
} send_state_t;

static send_state_t send_state = {0}; // 线程安全时应加锁访问

// void handle_writeable(struct lws *wsi) {
//     static unsigned char buf[LWS_PRE + 2048];

//     // 没有正在发送的消息？取一条新的
//     if (send_state.msg == NULL) {
//         send_state.msg = dequeue_message();
//         if (!send_state.msg) {
//             return; // 队列空了
//         }

//         //send_state.text = json_object_to_json_string(send_state.msg);
//         send_state.text = json_object_to_json_string_ext(send_state.msg, JSON_C_TO_STRING_NOSLASHESCAPE);
//         send_state.total_len = strlen(send_state.text);
//         send_state.sent_pos = 0;
//     }

//     while (send_state.sent_pos < send_state.total_len) {
//         size_t remaining = send_state.total_len - send_state.sent_pos;
//         size_t chunk_size = remaining > 2048 ? 2048 : remaining;

//         memcpy(&buf[LWS_PRE], send_state.text + send_state.sent_pos, chunk_size);

//         int n = lws_write(wsi, &buf[LWS_PRE], chunk_size, LWS_WRITE_TEXT);
//         if (n < 0) {
//             fprintf(stderr, "lws_write failed: %d\n", n);
//             // 清理当前发送状态
//             json_object_put(send_state.msg);
//             memset(&send_state, 0, sizeof(send_state));
//             return;
//         }

//         send_state.sent_pos += n;

//         // 如果没写完，就等下次回调继续写
//         if (send_state.sent_pos < send_state.total_len) {
//             lws_callback_on_writable(wsi);
//             return;
//         }
//     }

//     // 写完一个完整消息，清理
//     printf("send: %s\n", send_state.text);
//     json_object_put(send_state.msg);
//     memset(&send_state, 0, sizeof(send_state));

//     // 继续处理下一条消息（触发下一次回调）
//     lws_callback_on_writable(wsi);
// }

void handle_writeable(struct lws *wsi)
{
    static unsigned char buf[LWS_PRE + 2048];

    if (!send_state.msg)
    {
        send_state.msg = dequeue_message();
        if (!send_state.msg)
            return;
#if (BUILD_X86)
        send_state.text = json_object_to_json_string(send_state.msg);
#else
        send_state.text = json_object_to_json_string_ext(send_state.msg, JSON_C_TO_STRING_NOSLASHESCAPE);
#endif
        send_state.total_len = strlen(send_state.text);
        send_state.sent_pos = 0;
    }

    size_t remaining = send_state.total_len - send_state.sent_pos;
    size_t chunk_size = remaining > 2048 ? 2048 : remaining;

    memcpy(&buf[LWS_PRE], send_state.text + send_state.sent_pos, chunk_size);

    int flags = 0;
    if (send_state.sent_pos == 0 && remaining > 2048)
    {
        flags = LWS_WRITE_TEXT | LWS_WRITE_NO_FIN; // 第一个帧，且不是最后
    }
    else if (remaining > 2048)
    {
        flags = LWS_WRITE_CONTINUATION | LWS_WRITE_NO_FIN; // 中间帧
    }
    else if (send_state.sent_pos == 0)
    {
        flags = LWS_WRITE_TEXT; // 一次发完（小消息）
    }
    else
    {
        flags = LWS_WRITE_CONTINUATION; // 最后一帧
    }

    int n = lws_write(wsi, &buf[LWS_PRE], chunk_size, flags);
    if (n < 0)
    {
        fprintf(stderr, "lws_write failed: %d\n", n);
        json_object_put(send_state.msg);
        memset(&send_state, 0, sizeof(send_state));
        return;
    }

    send_state.sent_pos += n;

    if (send_state.sent_pos < send_state.total_len)
    {
        lws_callback_on_writable(wsi);
        // 有问题
        return;
    }

    // 完成发送
    // printf("send: %s\n", send_state.text);
    json_object_put(send_state.msg);
    memset(&send_state, 0, sizeof(send_state));

    // 准备下一条
    lws_callback_on_writable(wsi);
}
