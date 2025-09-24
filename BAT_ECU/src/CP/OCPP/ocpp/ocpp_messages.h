#ifndef OCPP_MESSAGES_H
#define OCPP_MESSAGES_H
#include <json-c/json.h>
#include <zstd.h>
#include <libwebsockets.h>
#include "batdata.h"
#include "sqlite_storage.h"

struct json_object *build_boot_notification();
struct json_object *build_heartbeat();
struct json_object *build_update_firmware();
struct json_object *build_firmware_status_notification();
struct json_object *build_get_diagnostics();
struct json_object *build_diagnostics_status_notification();

struct json_object *build_status_notification();

struct json_object *compress_detail_data(sqlite3 *db, int *out_ids, int *out_id_count);

int process_ocpp_message(struct lws *wsi, const char *message);
int send_ocpp_message(json_object *msg);
#endif