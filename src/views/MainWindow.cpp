//
// Created by elecfrog on 2023/7/13.
//
#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../components/LineInputDialog/LineInputDialog.h"

namespace elf {
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);

        fsTreeModel = new FileSystemTreeModel("D:/TV");
        fsTreeController = new FileSystemTreeController(fsTreeModel, ui->fileSystemTreeView);

        movieListModel = new MovieListModel(ui->navigatorBar->getMovieListView());
        
        
        movieListController = new MovieListController(movieListModel, ui->navigatorBar);

        movieContentModel = new MovieContentModel();
        movieContentController = new MovieContentController(movieListModel,
                                                            ui->navigatorBar,
                                                            movieContentModel,
                                                            ui->movieContentView,
                                                            ui->movieContentView->getLibLinkButton(),
                                                            ui->movieContentView->getTorrentLinkButton(),
                                                            ui->movieContentView->getLocalFileLinkButton()
        );

        connect(ui->ActionImport, &QAction::triggered, [&]() {
            LineInputDialog dialog;
            if (dialog.exec() == QDialog::Accepted) {
                movieListController->updateList();
                // User clicked OK
            } else {
                // User clicked Cancel or closed the dialog
            }
        });


    }

    MainWindow::~MainWindow() {
        delete ui;
    }


} // elf
