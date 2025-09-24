#include "sqlite_storage.h"

#include <stdio.h>
#include <unistd.h>
#include <zstd.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"




#define DB_PATH "batdata.db"
void create_limit_trigger(sqlite3 *db);
// 数据库初始化
void init_db(sqlite3 **db) {
    if (sqlite3_open(DB_PATH, db) != SQLITE_OK) {
        fprintf(stderr, "Can't open DB: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS batdata ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "timestamp INTEGER, "
                      "data BLOB);";
    char *errmsg = NULL;
    if (sqlite3_exec(*db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Create table failed: %s\n", errmsg);
        sqlite3_free(errmsg);
        exit(1);
    }
    create_limit_trigger(*db);  // 确保表已经存在后调用
}

// 插入数据
void insert_data(sqlite3 *db, tBatData *data) {
    const char *insert_sql = "INSERT INTO batdata (timestamp, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    // 插入数据
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, (int)data->uiTimeStamp);
    sqlite3_bind_blob(stmt, 2, data, sizeof(tBatData), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    /* 此功能放到初始化函数中，使用aqlite的触发器自动删除老记录
        详情 create_limit_trigger函数
    // 查询当前记录数
    const char *count_sql = "SELECT COUNT(*) FROM batdata;";
    int count = 0;
    sqlite3_prepare_v2(db, count_sql, -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    // 超过最大记录数才执行删除
    if (count > MAX_RECORDS) {
        const char *cleanup_sql = "DELETE FROM batdata WHERE id NOT IN (SELECT id FROM batdata ORDER BY id DESC LIMIT ?);";
        sqlite3_prepare_v2(db, cleanup_sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, MAX_RECORDS);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }*/
}


void create_limit_trigger(sqlite3 *db) {
    char trigger_sql[512];

    snprintf(trigger_sql, sizeof(trigger_sql),
        "CREATE TRIGGER IF NOT EXISTS limit_batdata_records "
        "AFTER INSERT ON batdata "
        "BEGIN "
        "DELETE FROM batdata "
        "WHERE id NOT IN ("
        "SELECT id FROM batdata ORDER BY id DESC LIMIT %d"
        "); "
        "END;",
        MAX_RECORDS
    );

    char *errmsg = NULL;
    int rc = sqlite3_exec(db, trigger_sql, NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create trigger: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}



// 获取最近 N 条数据（倒序）
int get_recent_data(sqlite3 *db, tBatData *buffer, int count, int *ids) {
    const char *sql = "SELECT id, data FROM batdata ORDER BY timestamp DESC LIMIT ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, count);

    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && i < count) {
        ids[i] = sqlite3_column_int(stmt, 0);
        const void *blob = sqlite3_column_blob(stmt, 1);
        memcpy(&buffer[i], blob, sizeof(tBatData));
        ++i;
    }
    sqlite3_finalize(stmt);
    return i;
}

// 删除指定 ID 的记录
void delete_data_by_ids(sqlite3 *db, int *ids, int count) {
    char sql[1024] = "DELETE FROM batdata WHERE id IN (";
    char tmp[32];
    for (int i = 0; i < count; ++i) {
        sprintf(tmp, "%d%s", ids[i], (i < count - 1 ? "," : ""));
        strcat(sql, tmp);
    }
    strcat(sql, ");");
    char *errmsg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Delete failed: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}