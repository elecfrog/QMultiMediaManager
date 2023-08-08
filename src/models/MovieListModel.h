//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIELISTMODEL_H
#define QMULTIMEIDAMANAGER_MOVIELISTMODEL_H


#include <QtSql>
#include <QDebug>
#include "defs/DatabaseStatus.h"
#include "../io/SqliteDriver.h"

namespace elf {
    class MovieListModel : public QObject {
    Q_OBJECT

    public:
        explicit MovieListModel(QObject *parent = nullptr) : QObject(parent) {
        }


    private:
        std::vector<QString> m_data;
    };
}

#endif //QMULTIMEIDAMANAGER_MOVIELISTMODEL_H
