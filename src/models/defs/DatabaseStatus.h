//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_DATABASESTATUS_H
#define QMULTIMEIDAMANAGER_DATABASESTATUS_H

namespace elf {
    enum class DatabaseStatus {
        None = 0,
        Connected = 1,
        Ok = 2,
        Error = 3
    };
}
#endif //QMULTIMEIDAMANAGER_DATABASESTATUS_H
