/******************************************************************************
 * Copyright (C) 2019-2025 debugger999 <debugger999@163.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#ifndef __AIOTC_DB_H__
#define __AIOTC_DB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mongoc.h"

#define DB_NAME "aiotc"

typedef struct {
    int masterEnable; // 1:master, 0:slave, 2:master&slave
    int masterRestPort;
    int masterStreaminPort;
    int masterStreaminProcNum;
    int masterObjMax;

    int slaveRestPort;
    int slaveStreaminPort;
    int slaveStreaminProcNum;
    int slaveObjMax;

    int shmKey;
    int shmHeadSize;

    int videoMax;
    int videoFrameSizeMax;
    int videoDefaultPixW;
    int videoDefaultPixH;
    int videoQueLen;

    int captureMax;
    int captureFrameSizeMax;
    int captureQueLen;
    int captureSaveDays;

    int msgKeyStart;
    int msgKeyMax;

    char dbType[32];
    char dbHost[64];
    int dbPort;
    char dbUser[64];
    char dbPassword[64];
    char dbName[64];

    char workdir[256];

    void *arg; // aiotcParams
} configParams;

typedef struct {
    char type[16]; // "sqlite"/"mysql"/"mongodb"
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    mongoc_database_t *database;
    char uri_string[256];
    void *arg; // aiotcParams
} dbParams;

int configInit(configParams *pConfigParams);
int dbInit(void *aiotcArg);
int dbOpen(void *dbArgs);
int dbWrite(void *dbArgs, const char *table, const char *name, char *json, 
        const char *selectName, const void *selIntVal, const void *selStrVal);
int dbUpdate(void *dbArgs, const char *table, bool upsert, const char *cmd,
        const char *selectName, const void *selIntVal, const void *selStrVal, 
        const char *updateName, const void *updIntVal, const void *updStrVal);
int dbUpdateIntById(char *buf, void *dbArgs, const char *name, int val);
int dbExsit(void *dbArgs, const char *table, 
        const char *selectName, const void *selIntVal, const void *selStrVal);
int dbTraverse(void *dbArgs, const char *table, void *arg, int (*callBack)(char *buf, void *arg));
int dbDel(void *dbArgs, const char *table, 
        const char *selectName, const void *selIntVal, const void *selStrVal);
int dbClose(void *dbArgs);
int initHttpPort(void *aiotcArg);

#endif
