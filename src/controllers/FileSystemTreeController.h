//
// Created by ml212fz on 7/13/2023.
//

#ifndef QMULTIMEIDAMANAGER_FILESYSTEMTREECONTROLLER_H
#define QMULTIMEIDAMANAGER_FILESYSTEMTREECONTROLLER_H

#include <QFileSystemModel>
#include "../views/FileSystemTreeView.h"
#include "../models/FileSystemTreeModel.h"


namespace elf {
    class FileSystemTreeController : public QObject {
    Q_OBJECT

    public:
        FileSystemTreeController(FileSystemTreeModel *model, FileSystemTreeView *view, QObject *parent = nullptr)
                : QObject(parent), m_model(model), m_view(view) {


            m_view->setModel(m_model);
            m_view->setRootIndex(m_model->index("D:/TV"));

            connect(m_view, &FileSystemTreeView::customContextMenuRequested, this,
                    &FileSystemTreeController::customContextMenu);
        }

    public slots:

        void customContextMenu(const QPoint &pos) {
            QModelIndex index = m_view->indexAt(pos);
            if (!index.isValid())
                return;

            QString filepath = m_model->filePath(index);
            QMenu *menu = new QMenu(m_view);

            QFileInfo fileInfo(filepath);
            QString ext = fileInfo.suffix(); // "txt"

            if (ext == "mp4") {
                // Play Function
                QAction *playAction = menu->addAction("Play");

                QProcess process(m_view);

                connect(playAction, &QAction::triggered, this, [this, filepath]() {
                    QProcess::startDetached("mpv", QStringList() << filepath);
                });

                // Setup MetaInfo
                QAction *editMetaAction = menu->addAction("Edit Meta Info");
                connect(editMetaAction, &QAction::triggered, this, [this, filepath]() {
                    // ...
                });

                QAction *parseMetaAction = menu->addAction("Parse Meta Info");
                connect(parseMetaAction, &QAction::triggered, this, [this, filepath]() {
                    auto fileInfo = QFileInfo(filepath);


                    qDebug() << fileInfo.fileName();
                    qDebug() << fileInfo.baseName();
                    qDebug() << fileInfo.completeBaseName();
                    qDebug() << fileInfo.suffix();
                    qDebug() << fileInfo.completeSuffix();
                    qDebug() << fileInfo.bundleName();
                    qDebug() << fileInfo.bundleName();
                });

            } else if (ext == "zip") {
                QAction *moveToTrashAction = menu->addAction("Move To Trash Bin");

                connect(moveToTrashAction, &QAction::triggered, this, [this, index]() {
                    if (m_model->remove(index))
                        qDebug() << "File Removed Successfully";
                    else
                        qDebug() << "Failed to remove file";
                });
            } else return;

            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->popup(m_view->viewport()->mapToGlobal(pos));
        }

    private:
        FileSystemTreeModel *m_model;
        FileSystemTreeView *m_view;
    };
}

#endif //QMULTIMEIDAMANAGER_FILESYSTEMTREECONTROLLER_H
