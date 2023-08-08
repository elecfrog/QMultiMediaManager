#ifndef FILESYSTEMTREEVIEW_H
#define FILESYSTEMTREEVIEW_H

#include <memory>
#include <QFileSystemModel>
#include <QTreeView>
#include <QMenu>
#include <QProcess>
#include <QDebug>

namespace elf {
    class FileSystemTreeView : public QTreeView {
    Q_OBJECT

    public:
        FileSystemTreeView(QWidget *parent = nullptr) : QTreeView(parent) {
            setContextMenuPolicy(Qt::CustomContextMenu);
            setColumnWidth(0, 250);
        }

    // we dont have need to create any slots to handle menu click,
    // when we choosing the policy of Qt::CustomContextMenu,
    // it will do all stuff.
    //private slots:

    };
}

#endif // FILESYSTEMTREEVIEW_H
