//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIECONTENTVIEW_H
#define QMULTIMEIDAMANAGER_MOVIECONTENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "../models/MovieContentModel.h"


namespace elf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MovieContentView; }
    QT_END_NAMESPACE

    class MovieContentView : public QWidget {
    Q_OBJECT

    public:
        explicit MovieContentView(QWidget *parent = nullptr);

        ~MovieContentView() override;

        void displayMovieContent(const MovieMeta &content);

        void displayMovieActors(const MovieMeta &content);

        void displayMovieTags(const MovieMeta &content);

        void displayCoverIcon(const QString &path);

        QPushButton *getLibLinkButton();

        QPushButton *getTorrentLinkButton();

        QPushButton *getLocalFileLinkButton();

        QPushButton *getCoverButton();

    private:
        Ui::MovieContentView *ui;
        std::vector<QLineEdit *> actorLabels;
        std::vector<QLabel *> tagLabels;
        QIcon coverIcon;
        QPixmap pixmap;
    };
}

#endif //QMULTIMEIDAMANAGER_MOVIECONTENTVIEW_H
