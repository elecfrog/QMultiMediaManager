//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_SQLITEDRIVER_H
#define QMULTIMEIDAMANAGER_SQLITEDRIVER_H

#include <QtSql>
#include "../base/Singleton.hpp"
#include "../models/defs/DatabaseStatus.h"
#include "../models/defs/MovieMeta.h"

namespace elf {
class SqliteDriver : public elf::base::Singleton<SqliteDriver> {
    public:
        explicit SqliteDriver() = default;

        void connect(const QString &db_path) {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(db_path);
            if (!db.open()) {
                status = DatabaseStatus::Error;
                qDebug() << "Error opening database:" << db.lastError().text();
                return;
            }
            status = DatabaseStatus::Connected;
            qDebug() << "Connected";
        }
        
    private:
        DatabaseStatus status;
        QSqlDatabase db;
    };
}
#endif //QMULTIMEIDAMANAGER_SQLITEDRIVER_H
