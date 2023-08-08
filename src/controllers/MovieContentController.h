//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIECONTENTCONTROLLER_H
#define QMULTIMEIDAMANAGER_MOVIECONTENTCONTROLLER_H

#include <QDesktopServices>
#include <QClipboard>
#include <QApplication>

#include "../models/MovieListModel.h"
#include "../models/MovieContentModel.h"

#include "../views/MovieContentView.h"
#include "../views/NavigatorBar.h"
#include "../views/MovieListView.h"

namespace elf {
    class MovieContentController : public QObject {
    Q_OBJECT

    public:
        explicit MovieContentController(MovieListModel *movieListModel,
                                        elf::NavigatorBar *movieListView,
                                        MovieContentModel *movieContentModel,
                                        MovieContentView *movieContentView,
                                        QPushButton *libLinkButton,
                                        QPushButton *copyMagButton,
                                        QPushButton *openLocalButton,
                                        QObject *parent = nullptr)
                : QObject(parent), movieListModel(movieListModel), movieListView(movieListView),
                  movieContentModel(movieContentModel), movieContentView(movieContentView) {

            connect(movieListView->getMovieListView(), &elf::MovieListView::clicked, this,
                    [this, movieListView](const QModelIndex &index) {
                        QString itemText = movieListView->getMovieListView()->model->data(index,
                                                                                          Qt::DisplayRole).toString();
                        onMovieListItemClicked(itemText);
                    });

            connect(libLinkButton, &QPushButton::clicked, this, [this, movieContentModel]() {
                QDesktopServices::openUrl(QUrl(movieContentModel->getLibLink()));
            });

            connect(copyMagButton, &QPushButton::clicked, this, [this, movieContentModel]() {

                QClipboard *clipboard = QApplication::clipboard();
                clipboard->setText(movieContentModel->getTorrentMag());
            });

            connect(openLocalButton, &QPushButton::clicked, this, [this, movieContentModel]() {
//            qDebug() << "clicked";
                qDebug() << movieContentModel->getLocalFilePath();
                QProcess::startDetached("mpv", QStringList() << movieContentModel->getLocalFilePath());
            });

            connect(movieContentView->getCoverButton(), &QPushButton::clicked, this, [this, movieContentModel]() {
//            qDebug() << "clicked";
                qDebug() << movieContentModel->getLocalFilePath();
                QProcess::startDetached("mpv", QStringList() << movieContentModel->getLocalFilePath());
            });
        }

    public slots:

        void onMovieListItemClicked(const QString &itemText) {
            qDebug() << "Movie Item clicked:" << itemText;
            auto meta = movieContentModel->getMovieContent(itemText);

            movieContentView->displayMovieContent(meta);
            movieContentView->displayMovieActors(meta);
            movieContentView->displayMovieTags(meta);
            movieContentView->displayCoverIcon(meta.coverLink);
        }

    private:
        MovieListModel *movieListModel;
        elf::NavigatorBar *movieListView;
        MovieContentModel *movieContentModel;
        MovieContentView *movieContentView;
    };
}

#endif //QMULTIMEIDAMANAGER_MOVIECONTENTCONTROLLER_H
