#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H
#include <sqlite3.h>
#include "batdata.h"

void init_db(sqlite3 **db); //数据库初始化


void insert_data(sqlite3 *db, tBatData *data) ;  // 插入数据

int get_recent_data(sqlite3 *db, tBatData *buffer, int count, int *ids); //获取最近n条数据(倒序)

void delete_data_by_ids(sqlite3 *db, int *ids, int count);  //删除指定的id记录

#endif