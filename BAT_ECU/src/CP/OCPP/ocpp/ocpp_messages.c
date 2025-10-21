#include "ocpp_messages.h"
#include <json-c/json.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "message_queue.h"
#include "project.h"
#include "updownfile.h"
#include "log/log.h"
void handle_call_message(struct lws *wsi, json_object *json);
void handle_call_result_message(struct lws *wsi, json_object *json);
void handle_call_error_message(struct lws *wsi, json_object *json);
void handle_heartbeat(struct lws *wsi, json_object *json);
void handle_update_firmware(struct lws *wsi, json_object *json);
void handle_get_diagnostics(struct lws *wsi, json_object *json);
void handle_firmware_status_notification(struct lws *wsi, json_object *json);
void handle_diagnostics_status_notification(struct lws *wsi, json_object *json);


// 发送OCPP消息  /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/
int send_ocpp_message(json_object *msg) {

    if(enqueue_message(msg))
    {
        return 0;
    }
    else
    {
        printf("enqueu_msg error\n");
        return -1;
    }
    // int len = strlen(message);
    // char *send_buffer = malloc(LWS_PRE + len);
    // if (!send_buffer) {
    //     printf("内存分配失败\n");
    //     return -1;
    // }
    
    // memcpy(send_buffer + LWS_PRE, message, len);
    // lws_write(wsi, (unsigned char *)(send_buffer + LWS_PRE), len, LWS_WRITE_TEXT);
    // free(send_buffer);
    
    // save_message_to_db(message, 0);
    
}

// 处理OCPP消息
int process_ocpp_message(struct lws *wsi, const char *message) 
{
    json_object *json = json_tokener_parse(message);
    if (!json) {
        printf("解析JSON消息失败\n");
        return -1;
    }
    
    if (json_object_get_type(json) != json_type_array || json_object_array_length(json) < 3) {
        printf("无效的OCPP消息格式\n");
        json_object_put(json);
        return -1;
    }
    
    json_object *msg_type_obj = json_object_array_get_idx(json, 0);
    int msg_type = json_object_get_int(msg_type_obj);
    
    switch (msg_type) {
        case 2:
            handle_call_message(wsi, json);
            break;
        case 3:
            handle_call_result_message(wsi, json);
            break;
        case 4:
            handle_call_error_message(wsi, json);
            break;
        default:
            printf("未知的OCPP消息类型: %d\n", msg_type);
            break;
    }
    
    json_object_put(json);
    return 0;
}

// 处理CALL消息
void handle_call_message(struct lws *wsi, json_object *json) {
    json_object *action_obj = json_object_array_get_idx(json, 2);
    const char *action = json_object_get_string(action_obj);
    
    printf("收到CALL消息，动作: %s\n", action);
    
    if (strcmp(action, "Heartbeat") == 0) {
        handle_heartbeat(wsi, json);
    }
    else if (strcmp(action, "UpdateFirmware") == 0) {
        handle_update_firmware(wsi, json);
    }
    else if (strcmp(action, "GetDiagnostics") == 0) {
        handle_get_diagnostics(wsi, json);
    }
    else if (strcmp(action, "FirmwareStatusNotification") == 0) {
        handle_firmware_status_notification(wsi, json);
    }
    else if (strcmp(action, "DiagnosticsStatusNotification") == 0) {
        handle_diagnostics_status_notification(wsi, json);
    }
    else if (strcmp(action, "DataTransfer") == 0){
        printf("DataTransfer---TriggerReportEnergyStorageStatusV2: %s\n", action);
        //TriggerReportEnergyStorageStatusV2动作实现函数
        handle_trigger_report_energy_storage_status_v2(wsi, json);
    }
    else {
        printf("未实现的OCPP动作: %s\n", action);
    }
}


char *generate_unique_id() {
    static char id[32];
    static unsigned counter = 0;
    snprintf(id, sizeof(id), "%ld%05u", time(NULL), counter++);
    return id;
}

// 处理CALLRESULT消息
void handle_call_result_message(struct lws *wsi, json_object *json) {
    json_object *msg_id_obj = json_object_array_get_idx(json, 1);
    const char *msg_id = json_object_get_string(msg_id_obj);
    // printf("处理CALLRESULT消息，ID: %s\n", msg_id);
    
    // 标记对应的消息为已发送
    // 实际实现中需要根据消息ID查找对应的记录并更新状态
}

// 处理CALLERROR消息
void handle_call_error_message(struct lws *wsi, json_object *json) {
    json_object *msg_id_obj = json_object_array_get_idx(json, 1);
    const char *msg_id = json_object_get_string(msg_id_obj);
    
    json_object *error_code_obj = json_object_array_get_idx(json, 2);
    const char *error_code = json_object_get_string(error_code_obj);
    
    json_object *error_description_obj = json_object_array_get_idx(json, 3);
    const char *error_description = json_object_get_string(error_description_obj);
    
    printf("处理CALLERROR消息，ID: %s，错误码: %s，描述: %s\n", 
            msg_id, error_code, error_description);
}


// 处理心跳请求
void handle_heartbeat(struct lws *wsi, json_object *json) {
    json_object *response = json_object_new_array();//创建一个JSON数组对象
    json_object_array_add(response, json_object_new_int(3));//增加一个元素到json数组的末尾 ；//创建josn的int 32对象
    
    json_object *msg_id_obj = json_object_array_get_idx(json, 1);//按照索引获取json数组的对象
    json_object_array_add(response, msg_id_obj);//增加一个元素到json数组的末尾
    
    json_object *payload = json_object_new_object();//创建一个新的JSON对象，引用计数为1，该指针具有唯一的所有权
    time_t now = time(NULL);
    char timestamp[26];
    ctime_r(&now, timestamp);
    timestamp[24] = '\0';
    json_object_object_add(payload, "currentTime", json_object_new_string(timestamp));//添加一个键值对到JSON对象中
    json_object_array_add(response, payload);//增加一个元素到json数组的末尾
    
    send_ocpp_message(response); /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/; 
}

// 处理固件更新请求
const char* extract_after_xc(const char* url) {
    const char *xc_pos = strstr(url, "XC");
    return xc_pos ? xc_pos : NULL;
}


void handle_update_firmware(struct lws *wsi, json_object *json) {
    // json: [2, "messageId", "UpdateFirmware", { "location": "...", "retrieveDate": "..." }]
    if (!json_object_is_type(json, json_type_array)) {
        printf("Invalid message: not a JSON array.\n");
        return;
    }

    json_object *msg_type = json_object_array_get_idx(json, 0);
    json_object *msg_id = json_object_array_get_idx(json, 1);
    //json_object *command = json_object_array_get_idx(json, 2);
    json_object *payload = json_object_array_get_idx(json, 3);

    if (!msg_type || !msg_id || !payload || !json_object_is_type(msg_id, json_type_string) || !json_object_is_type(payload, json_type_object)) {
        printf("Invalid UpdateFirmware message structure.\n");
        return;
    }

    const char *message_id = json_object_get_string(msg_id);

    // 1. 回复 CALLRESULT 消息
    json_object *ack = json_object_new_array();
    json_object_array_add(ack, json_object_new_int(3));  // CALLRESULT
    json_object_array_add(ack, json_object_new_string(message_id)); // Same ID as request
    json_object_array_add(ack, json_object_new_object()); // Empty payload

    send_ocpp_message(ack);
    //json_object_put(ack);  // 释放内存

    // 2. 提取参数
    json_object *location_obj = NULL;
    json_object *retrieve_date_obj = NULL;

    json_object_object_get_ex(payload, "location", &location_obj);
    json_object_object_get_ex(payload, "retrieveDate", &retrieve_date_obj);

    if (!location_obj || !retrieve_date_obj || !json_object_is_type(location_obj, json_type_string) || !json_object_is_type(retrieve_date_obj, json_type_string)) {
        printf("Missing or invalid location/retrieveDate in payload.\n");
        return;
    }

    const char *location = json_object_get_string(location_obj);
    const char *retrieve_date = json_object_get_string(retrieve_date_obj);

    printf("UpdateFirmware: location=%s, retrieveDate=%s\n", location, retrieve_date);
    char *filetype = extract_after_xc(location);
    if (filetype) {
        printf("固件文件名为: %s\n", filetype);
    } else {
        printf("提取文件名失败。\n");
    }
    // 3. 下载固件文件
    int success = download_file(location,filetype);

    // 4. 发送 FirmwareStatusNotification CALL 消息
    json_object *status_msg = json_object_new_array();
    json_object_array_add(status_msg, json_object_new_int(2)); // CALL
    json_object_array_add(status_msg, json_object_new_string("firmware-status-001")); // 随机唯一 ID
    json_object_array_add(status_msg, json_object_new_string("FirmwareStatusNotification"));

    json_object *status_payload = json_object_new_object();
    json_object_object_add(status_payload, "status", json_object_new_string((success ==0) ? "Downloaded" : "DownloadFailed"));
    json_object_array_add(status_msg, status_payload);

    send_ocpp_message(status_msg);
    //json_object_put(status_msg);

}


// 发送固件状态通知
void send_firmware_status_notification(struct lws *wsi, const char *status) {
    json_object *notification = json_object_new_array();//
    json_object_array_add(notification, json_object_new_int(2));
    json_object_array_add(notification, json_object_new_string("firmware-status"));
    json_object_array_add(notification, json_object_new_string("FirmwareStatusNotification"));
    
    json_object *payload = json_object_new_object();
    json_object_object_add(payload, "status", json_object_new_string(status));
    json_object_array_add(notification, payload);
    
    send_ocpp_message(notification); /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/
}

// 处理获取诊断信息请求
void handle_get_diagnostics(struct lws *wsi, json_object *json) {
    if (!json_object_is_type(json, json_type_array)) {
        printf("Invalid message: not a JSON array.\n");
        return;
    }

    //json_object *msg_type = json_object_array_get_idx(json, 0);
    json_object *msg_id = json_object_array_get_idx(json, 1);
    //json_object *action = json_object_array_get_idx(json, 2);
    json_object *payload = json_object_array_get_idx(json, 3);

    if (!msg_id || !json_object_is_type(msg_id, json_type_string) ||
        !payload || !json_object_is_type(payload, json_type_object)) {
        printf("Invalid GetDiagnostics message structure.\n");
        return;
    }

    const char *message_id = json_object_get_string(msg_id);

    // Step 1: 立即发送 CALLRESULT 响应
    json_object *ack = json_object_new_array();
    json_object_array_add(ack, json_object_new_int(3));  // CALLRESULT
    json_object_array_add(ack, json_object_new_string(message_id));
    
    // payload: 可返回 fileName（选填），我们这里返回固定 diagnostic-id
    json_object *ack_payload = json_object_new_object();
    json_object_object_add(ack_payload, "fileName", json_object_new_string("log.bz2"));
    json_object_array_add(ack, ack_payload);

    send_ocpp_message(ack);

    // Step 2: 获取 location 字段
    json_object *location_obj = NULL;
    json_object_object_get_ex(payload, "location", &location_obj);

    if (!location_obj || !json_object_is_type(location_obj, json_type_string)) {
        printf("No valid location provided in GetDiagnostics.\n");
        return;
    }

    const char *upload_url = json_object_get_string(location_obj);

    printf("Uploading diagnostics to %s\n", upload_url);

    // Step 3: 调用上传函数
    int success = ocpp_upload_file(upload_url);

    // Step 4: 发送 DiagnosticsStatusNotification
    json_object *status_msg = json_object_new_array();
    json_object_array_add(status_msg, json_object_new_int(2));  // CALL
    json_object_array_add(status_msg, json_object_new_string("diagnostics-status-001"));  // 唯一 ID
    json_object_array_add(status_msg, json_object_new_string("DiagnosticsStatusNotification"));

    json_object *status_payload = json_object_new_object();
    json_object_object_add(status_payload, "status",
    json_object_new_string((success==0) ? "Uploaded" : "UploadFailed"));
    json_object_array_add(status_msg, status_payload);

    send_ocpp_message(status_msg);

    if (success == 0) {
    if (remove(UPLOAD_FILE_PATH) == 0) {
        printf("文件 %s 删除成功。\n", UPLOAD_FILE_PATH);
    } else {
        perror("删除文件失败");
    }
    } else {
        fprintf(stderr, "文件上传失败，不删除压缩包。\n");
    }
}

// 发送诊断状态通知
void send_diagnostics_status_notification(struct lws *wsi, const char *status) {
    json_object *notification = json_object_new_array();
    json_object_array_add(notification, json_object_new_int(2));
    json_object_array_add(notification, json_object_new_string("diagnostics-status"));
    json_object_array_add(notification, json_object_new_string("DiagnosticsStatusNotification"));
    
    json_object *payload = json_object_new_object();
    json_object_object_add(payload, "status", json_object_new_string(status));
    json_object_array_add(notification, payload);
    
    send_ocpp_message(notification); /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/
}

// 处理固件状态通知
void handle_firmware_status_notification(struct lws *wsi, json_object *json) {
    json_object *payload = json_object_array_get_idx(json, 3);
    json_object *status_obj = json_object_object_get(payload, "status");
    const char *status = json_object_get_string(status_obj);
    
    printf("收到固件状态通知: %s\n", status);
    
    json_object *response = json_object_new_array();
    json_object_array_add(response, json_object_new_int(3));
    
    json_object *msg_id_obj = json_object_array_get_idx(json, 1);
    json_object_array_add(response, msg_id_obj);
    
    json_object *response_payload = json_object_new_object();
    json_object_array_add(response, response_payload);
    
    send_ocpp_message(response); /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/;
}

// 处理诊断状态通知
void handle_diagnostics_status_notification(struct lws *wsi, json_object *json) {
    json_object *payload = json_object_array_get_idx(json, 3);
    json_object *status_obj = json_object_object_get(payload, "status");
    const char *status = json_object_get_string(status_obj);
    
    printf("收到诊断状态通知: %s\n", status);
    
    json_object *response = json_object_new_array();
    json_object_array_add(response, json_object_new_int(3));
    
    json_object *msg_id_obj = json_object_array_get_idx(json, 1);
    json_object_array_add(response, msg_id_obj);
    
    json_object *response_payload = json_object_new_object();
    json_object_array_add(response, response_payload);
    
    send_ocpp_message(response); /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/;
}


// // 处理触发报告能量存储状态V2
// void handle_trigger_report_energy_storage_status_v2(struct lws *wsi, json_object *json) {
//     if (!json_object_is_type(json, json_type_array)) {
//         printf("Invalid TriggerReportEnergyStorageStatusV2 message: not a JSON array.\n");
//         return;
//     }

//     json_object *msg_id_obj = json_object_array_get_idx(json, 1);
//     if (!msg_id_obj || !json_object_is_type(msg_id_obj, json_type_string)) {
//         printf("Missing or invalid message ID in TriggerReportEnergyStorageStatusV2.\n");
//         return;
//     }

//     const char *message_id = json_object_get_string(msg_id_obj);

//     json_object *response = json_object_new_array();
//     json_object_array_add(response, json_object_new_int(3));  
//     json_object_array_add(response, json_object_new_string(message_id));

//     json_object *payload = json_object_new_object();
//     json_object_object_add(payload, "EnergyStorageValue", json_object_new_double(bms_B.CANFDUnpack1_o30));

//     json_object_array_add(response, payload);


//     send_ocpp_message(response);  /*消息队列存放json对象指针，发送后统一调用 json_object_put释放*/
// }
void handle_trigger_report_energy_storage_status_v2(struct lws *wsi, json_object *json) {
    if (!json_object_is_type(json, json_type_array)) {
        printf("Invalid TriggerReportEnergyStorageStatusV2 message: not a JSON array.\n");
        return;
    }

    json_object *msg_id_obj = json_object_array_get_idx(json, 1);
    if (!msg_id_obj || !json_object_is_type(msg_id_obj, json_type_string)) {
        printf("Missing or invalid message ID in TriggerReportEnergyStorageStatusV2.\n");
        return;
    }

    const char *message_id = json_object_get_string(msg_id_obj);

    // ✅ 这里判断是否接受该请求，可替换为你自己的条件判断逻辑
    const char *status = "Accepted";  // 或 "Rejected"

    // 构造 CALLRESULT 消息
    json_object *response = json_object_new_array();
    json_object_array_add(response, json_object_new_int(3));  // CALLRESULT 类型
    json_object_array_add(response, json_object_new_string(message_id));

    json_object *payload = json_object_new_object();
    json_object_object_add(payload, "status", json_object_new_string(status));  // status: CiString
    json_object_array_add(response, payload);

    // ✅ 发送消息（会统一释放）
    send_ocpp_message(response);

    printf("已回复 TriggerReportEnergyStorageStatusV2，status: %s\n", status);
}












struct json_object *build_boot_notification() {
    // 第四个参数对象
    struct json_object *params = json_object_new_object();
    json_object_object_add(params, "chargeBoxSerialNumber", json_object_new_string("C8A215DPWUDYDTAWLL"));
    json_object_object_add(params, "chargePointModel", json_object_new_string("C8EU"));
    json_object_object_add(params, "chargePointSerialNumber", json_object_new_string("C8A215DPWUDYDTAWLL"));
    json_object_object_add(params, "chargePointVendor", json_object_new_string("xcharge"));
    json_object_object_add(params, "firmwareVersion", json_object_new_string("V1.0.0_C8EU_OCPP_STA_250508"));
    json_object_object_add(params, "iccid", json_object_new_string(""));

    // 外层数组
    struct json_object *msg = json_object_new_array();
    json_object_array_add(msg, json_object_new_int(2));  // [0] 消息类型 2 = CALL
    json_object_array_add(msg, json_object_new_string("1915669379150258176")); // [1] 消息 ID
    json_object_array_add(msg, json_object_new_string("BootNotification"));    // [2] 动作名
    json_object_array_add(msg, params);                                        // [3] 参数对象

    return msg;
}

struct json_object *build_status_notification() {
    // 获取当前 UTC 时间，格式为 ISO 8601，例如 "2025-05-23T06:45:00Z"
    char timestamp[32];
    time_t now = time(NULL);
    struct tm *utc_tm = gmtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", utc_tm);

    // 构建第四个参数对象（Payload）
    struct json_object *params = json_object_new_object();
    json_object_object_add(params, "connectorId", json_object_new_int(1)); // 通常 0 表示整机状态
    json_object_object_add(params, "status", json_object_new_string("Available"));  // 示例状态
    json_object_object_add(params, "errorCode", json_object_new_string("NoError"));
    json_object_object_add(params, "timestamp", json_object_new_string(timestamp));

    // 构建最外层的数组消息
    struct json_object *msg = json_object_new_array();
    json_object_array_add(msg, json_object_new_int(2));  // 消息类型 CALL = 2
    json_object_array_add(msg, json_object_new_string("1915669379150258178")); // 消息 ID，应唯一
    json_object_array_add(msg, json_object_new_string("StatusNotification"));  // 动作名
    json_object_array_add(msg, params);  // 参数对象

    return msg;
}


// struct json_object *build_heartbeat() {
//     // 获取当前时间戳
//     struct timespec ts;
//     clock_gettime(CLOCK_REALTIME, &ts);  // 秒 + 纳秒
//     long sec = ts.tv_sec;
//     long nsec = ts.tv_nsec;

//     // 加入随机数混合生成 messageId
//     srand((unsigned int)(sec ^ nsec));  // 初始化随机种子
//     int r = rand() % 1000000;

//     // 生成长一点的唯一 ID
//     char message_id[48];
//     snprintf(message_id, sizeof(message_id), "%ld%06d", sec, r);

//     // 构建 heartbeat 消息
//     struct json_object *msg = json_object_new_array();
//     json_object_array_add(msg, json_object_new_int(2));
//     json_object_array_add(msg, json_object_new_string(message_id));  // 更长的唯一 ID
//     json_object_array_add(msg, json_object_new_string("Heartbeat"));
//     json_object_array_add(msg, json_object_new_object());

//     return msg;
// }

struct json_object *build_heartbeat() {
    struct json_object *msg = json_object_new_array();
    json_object_array_add(msg, json_object_new_int(2));
    json_object_array_add(msg, json_object_new_string("1915669379150258177"));
    json_object_array_add(msg, json_object_new_string("Heartbeat"));
    json_object_array_add(msg, json_object_new_object());  // 无参数
    return msg;
}

struct json_object *build_update_firmware() {
    struct json_object *msg = json_object_new_object();
    json_object_object_add(msg, "action", json_object_new_string("UpdateFirmware"));
    json_object_object_add(msg, "location", json_object_new_string("http://firmware-server/update.bin"));
    json_object_object_add(msg, "retrieveDate", json_object_new_string("2025-05-08T12:00:00Z"));
    return msg;
}

struct json_object *build_firmware_status_notification() {
    struct json_object *msg = json_object_new_object();
    json_object_object_add(msg, "action", json_object_new_string("FirmwareStatusNotification"));
    json_object_object_add(msg, "status", json_object_new_string("Downloaded"));
    return msg;
}

struct json_object *build_get_diagnostics() {
    struct json_object *msg = json_object_new_object();
    json_object_object_add(msg, "action", json_object_new_string("GetDiagnostics"));
    json_object_object_add(msg, "location", json_object_new_string("http://diagnostics-server/get.zip"));
    return msg;
}

struct json_object *build_diagnostics_status_notification() {
    struct json_object *msg = json_object_new_object();
    json_object_object_add(msg, "action", json_object_new_string("DiagnosticsStatusNotification"));
    json_object_object_add(msg, "status", json_object_new_string("Uploaded"));
    return msg;
}



struct json_object *build_data_transfer(const char *base64_str, size_t size) {
    // 构建 status[0] 对象
    static int soc ;
    struct json_object *status_item = json_object_new_object();
    json_object_object_add(status_item, "num", json_object_new_int(1));
    json_object_object_add(status_item, "status", json_object_new_string("idle"));

    struct json_object *errorInfo = json_object_new_array();  // 空数组
    json_object_object_add(status_item, "errorInfo", errorInfo);

    json_object_object_add(status_item, "voltage", json_object_new_int(800));
    json_object_object_add(status_item, "current", json_object_new_int(20));
    json_object_object_add(status_item, "power", json_object_new_int(7));
    soc++;
    if(soc ==100)
    {
        soc = 0;
    }
    json_object_object_add(status_item, "soc", json_object_new_int(soc));
    json_object_object_add(status_item, "soh", json_object_new_int(95));
    json_object_object_add(status_item, "batteryTemperature", json_object_new_double(25.3));

    // ISO8601 时间戳
    time_t now = time(NULL);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
    json_object_object_add(status_item, "timestamp", json_object_new_string(timestamp));

    // 已是 base64 字符串，无需编码

    //json_object_object_add(status_item, "detail", json_object_new_string_len(base64_str, size));
    // detail 是一个 Base64 字符串，直接作为字符串加入
    json_object_object_add(status_item, "detail", json_object_new_string(base64_str));
    //json_object_object_add(status_item, "detail", json_object_new_string(base64_str));

    
    // 构建 status 数组
    struct json_object *status_array = json_object_new_array();
    json_object_array_add(status_array, status_item);

    // 构建 data 对象（嵌套 JSON 字符串）
    struct json_object *data_obj = json_object_new_object();
    json_object_object_add(data_obj, "status", status_array);
#if(BUILD_X86)
    const char *data_json_str = json_object_to_json_string(data_obj);
#else
    const char *data_json_str = json_object_to_json_string_ext(data_obj, JSON_C_TO_STRING_NOSLASHESCAPE);
#endif
    struct json_object *data_str_obj = json_object_new_string(data_json_str);
    json_object_put(data_obj); 


    // 构建 DataTransfer.req 消息体
    struct json_object *params = json_object_new_object();
    json_object_object_add(params, "vendorId", json_object_new_string("xcharge"));
    json_object_object_add(params, "messageId", json_object_new_string("ReportEnergyStorageStatusV2"));
    json_object_object_add(params, "data", data_str_obj);

    struct json_object *msg = json_object_new_array();
    json_object_array_add(msg, json_object_new_int(2));
    json_object_array_add(msg, json_object_new_string(generate_unique_id()));  // 可替换为实际唯一 ID
    json_object_array_add(msg, json_object_new_string("DataTransfer"));
    json_object_array_add(msg, params);

    return msg;
}

static const char base64_encode_table[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// Base64 编码函数
char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)
{
    *output_length = 4 * ((input_length + 2) / 3); // 计算输出长度
    
    char *encoded_data = malloc(*output_length + 1); // 分配内存，+1 用于 null 终止符
    if (encoded_data == NULL) {
        return NULL;
    }
    
    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;
        
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        
        encoded_data[j++] = base64_encode_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = base64_encode_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = base64_encode_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = base64_encode_table[(triple >> 0 * 6) & 0x3F];
    }
    
    // 添加填充字符 '='
    for (size_t i = 0; i < (3 - input_length % 3) % 3; i++) {
        encoded_data[*output_length - 1 - i] = '=';
    }
    
    encoded_data[*output_length] = '\0'; // 添加 null 终止符
    return encoded_data;
}

#pragma pack(push, 1)
typedef struct {
    unsigned short usDataStyle;      /* 数据格式版本号（2字节），固定为1，用于指定后面数据的协议版本*/
    unsigned short usPackCount;      /* Pack数量（2字节），目前为15个Pack*/
    unsigned short usVoltCount;      /* 电池电压数量（2字节），目前为240个电池电压（15个Pack，每个16个）*/
    unsigned short usTempCount;      /* 电池温度数量（2字节），目前为120个采集点（15个Pack，每个8个）*/
    unsigned int   uiArrayLength;    /* 数组长度（4字节），最大255，无数据则为0*/
} tDetailHead;
#pragma pack(pop)
// ✅ 构建并压缩 detail 字段数据，输出 JSON 对象（需要手动释放）
struct json_object *compress_detail_data(sqlite3 *db, int *out_ids, int *out_id_count) {
    tBatData buffer[REPORT_COUNT];
    int ids[REPORT_COUNT];
    int n = get_recent_data(db, buffer, REPORT_COUNT, ids);

    if (n <= 0) return NULL;
    if (n > 255) n = 255;

    printf("get_recent_data n = %d...data =%lu,\n", n,sizeof(tBatData));
    memcpy(out_ids, ids, sizeof(int) * n);
    *out_id_count = n;

    tDetailHead head = {
        .usDataStyle = 1,
        .usPackCount = 15,
        .usVoltCount = 240,
        .usTempCount = 120,
        .uiArrayLength = n
    };
    tDetailHead head_be;
    head_be.usDataStyle = htons(head.usDataStyle);
    head_be.usPackCount = htons(head.usPackCount);
    head_be.usVoltCount = htons(head.usVoltCount);
    head_be.usTempCount = htons(head.usTempCount);
    head_be.uiArrayLength = htonl(head.uiArrayLength);

    ZSTD_CStream *cstream = ZSTD_createCStream();
    // 设置压缩参数
#if(BUILD_X86)
    ZSTD_initCStream(cstream, 3);  // 压缩等级 3
#else
    ZSTD_CCtx_setParameter(cstream, ZSTD_c_compressionLevel, 3);              // 压缩等级
    ZSTD_CCtx_setParameter(cstream, ZSTD_c_checksumFlag, 0);                 // 关闭 checksum（--no-check）
    ZSTD_CCtx_setParameter(cstream, ZSTD_c_contentSizeFlag, 0);              // 不在 header 中写 content size（默认不写，可显式设置）
    ZSTD_CCtx_setParameter(cstream, ZSTD_c_dictIDFlag, 0);                   // 不写字典 ID（--no-dictID）
#endif
    size_t max_dst_size = ZSTD_compressBound(sizeof(tDetailHead) + sizeof(tBatData) * n);
    void *compressed = malloc(max_dst_size);
    ZSTD_outBuffer out = { compressed, max_dst_size, 0 };

    // 压缩头
    ZSTD_inBuffer inHead = { &head_be, sizeof(head_be), 0 };
    while (inHead.pos < inHead.size) {
        size_t ret = ZSTD_compressStream(cstream, &out, &inHead);
        if (ZSTD_isError(ret)) {
            // fprintf(stderr, "compressStream head failed: %s\n", ZSTD_getErrorName(ret));
            zlog_error(zlog_get_category("debug_file"), "compressStream head failed: %s", ZSTD_getErrorName(ret));
            free(compressed);
            ZSTD_freeCStream(cstream);
            return NULL;
        }
    }

    // 压缩数据
    ZSTD_inBuffer inData = { buffer, sizeof(tBatData) * n, 0 };
    while (inData.pos < inData.size) {
        size_t ret = ZSTD_compressStream(cstream, &out, &inData);
        if (ZSTD_isError(ret)) {
            // fprintf(stderr, "compressStream data failed: %s\n", ZSTD_getErrorName(ret));
             zlog_error(zlog_get_category("debug_file"), "compressStream data failed: %s", ZSTD_getErrorName(ret));
            free(compressed);
            ZSTD_freeCStream(cstream);
            return NULL;
        }
    }

    // 刷尾
    size_t remaining;
    do {
        remaining = ZSTD_endStream(cstream, &out);
        if (ZSTD_isError(remaining)) {
            // fprintf(stderr, "endStream failed: %s\n", ZSTD_getErrorName(remaining));
            zlog_error(zlog_get_category("debug_file"), "endStream failed: %s", ZSTD_getErrorName(remaining));
            free(compressed);
            ZSTD_freeCStream(cstream);
            return NULL;
        }
    } while (remaining > 0);

    ZSTD_freeCStream(cstream);

    // for(int i=0;i<out.pos;i++)
    // {
    //     printf("base64_str 压缩前是%x \n", ((unsigned char*)compressed)[i]);
    // }


    size_t base64_len;
    char *base64_str = base64_encode(compressed, out.pos, &base64_len);
    if (!base64_str) {
        printf("Base64 编码失败\n");
        free(compressed);
        return NULL;
    }
    //printf("base64_str: %s 压缩后字节是%d \n",base64_str,out.pos);
    // 构建 JSON
    struct json_object *json = build_data_transfer(base64_str, base64_len);
    free(base64_str);
    free(compressed);
    return json;
}
