//
// Created by ml212fz on 7/18/2023.
//

#ifndef QMULTIMEDIAMANAGER_NAVIGATORBAR_H
#define QMULTIMEDIAMANAGER_NAVIGATORBAR_H

#include <QObject>
#include <QMenu>
#include <QWidget>
#include <memory>
#include <QListWidget>
#include <QString>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QCheckBox>
#include "../io/SqilteServices.h"
#include "../models/defs/SearchKeyword.h"
#include "MovieListView.h"
#include "MovieListView.h"

namespace elf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class NavigatorBar; }
    QT_END_NAMESPACE

    class NavigatorBar : public QWidget {
    Q_OBJECT
    
    public:
        explicit NavigatorBar(QWidget *parent = nullptr);

        QPushButton *getSearchBut();

        QLineEdit *getSearchLineEdit();
        QCheckBox *getIgnoredCheckBox();
        QCheckBox *getHidVRCheckBox();

        MovieListView *getMovieListView();

        ~NavigatorBar() override;

    signals:

        void updateListBySearch(elf::SearchKeyword type, const QString &word);


    public slots:

        void onComboBoxIndexChanged(int index);

    private:
        Ui::NavigatorBar *ui;
        MovieListView *movieList;
        bool isIgnoredChecked;
        bool ishideVRCheckd;
    };
} // elf

#endif //QMULTIMEDIAMANAGER_NAVIGATORBAR_H
