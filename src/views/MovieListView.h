//
// Created by elecfrog on 2023/7/18.
//

#ifndef QMULTIMEDIAMANAGER_MOVIELISTVIEW_H
#define QMULTIMEDIAMANAGER_MOVIELISTVIEW_H

#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QMenu>
#include <QContextMenuEvent>
#include <QModelIndex>
#include <QListView>
#include <QFileDialog>


namespace elf {
    class MovieListView : public QListView {
    Q_OBJECT

    public:
        explicit MovieListView(QWidget *parent = nullptr);

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

    signals:
        void fileSelected(const QString &filePath, const QString &unicode);

    protected:
        void selectLocalFile(const QString &unicode) {
            QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("All Files (*)"));
            
            if (!filePath.isEmpty()) {
                qDebug() << "Selected file path is :" << filePath;
                emit fileSelected(filePath, unicode);
            } else {
                qDebug() << "No file was selected.";
            }
        }


    public:
        QStandardItemModel *model;
    };

} // elf

#endif //QMULTIMEDIAMANAGER_MOVIELISTVIEW_H
