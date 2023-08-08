//
// Created by ml212fz on 7/13/2023.
//

#ifndef QMULTIMEIDAMANAGER_FILESYSTEMTREEMODEL_H
#define QMULTIMEIDAMANAGER_FILESYSTEMTREEMODEL_H

#include <QFileSystemModel>

namespace elf {
    class FileSystemTreeModel : public QFileSystemModel {
    public:
        explicit FileSystemTreeModel(const QString &path) {
            setRootPath(path);
        }

    private:
    };
}


#endif //QMULTIMEIDAMANAGER_FILESYSTEMTREEMODEL_H
