//
// Created by elecfrog on 2023/7/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TestWidget.h" resolved

#include "MovieListView.h"

namespace elf {
    MovieListView::MovieListView(QWidget *parent) :
            QListView(parent) {

        model = new QStandardItemModel(this);
        setModel(model);
    }


    void MovieListView::contextMenuEvent(QContextMenuEvent *event) {
        QPoint pos = mapFromParent(event->pos());
        QModelIndex index = indexAt(pos);
        if (index.isValid()) {  
            QMenu menu(this);

            
            QAction selectLocalFieAction("Select Local File", this);
            connect(&selectLocalFieAction, &QAction::triggered, this, [&, index]() {
                QString text = model->data(index, Qt::DisplayRole).toString();
                qDebug() << "You selected item: " << text;
                selectLocalFile(text);
            });

            menu.addAction(&selectLocalFieAction);
            menu.exec(event->globalPos());
        }
    }
}