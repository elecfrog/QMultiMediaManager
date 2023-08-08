//
// Created by elecfrog on 2023/7/13.
//

#ifndef QMULTIMEIDAMANAGER_MAINWINDOW_H
#define QMULTIMEIDAMANAGER_MAINWINDOW_H

#include <QMainWindow>
#include "../controllers/FileSystemTreeController.h"
#include "../controllers/MovieListController.h"

#include "../models/FileSystemTreeModel.h"
#include "../models/MovieListModel.h"

#include "MovieContentView.h"
#include "../controllers/MovieContentController.h"

namespace elf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;
        
    private:

        
    private:
        Ui::MainWindow *ui;
        
        FileSystemTreeController* fsTreeController;
        FileSystemTreeModel * fsTreeModel;
        
        MovieListModel* movieListModel;
        MovieListView*  movieListView;
        MovieListController* movieListController;

        MovieContentModel* movieContentModel;
        MovieContentController * movieContentController;
        
        QLineEdit* selectorLineEdit = nullptr;
    };
} // elf

#endif //QMULTIMEIDAMANAGER_MAINWINDOW_H
