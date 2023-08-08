//
// Created by elecfrog on 2023/7/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MovieContentView.h" resolved

#include <QDesktopServices>
#include "MovieContentView.h"
#include "ui_MovieContentView.h"
#include "../components/ImageButton/NetworkImageButton.h"

namespace elf {
    MovieContentView::MovieContentView(QWidget *parent) :
            QWidget(parent), ui(new Ui::MovieContentView) {
        ui->setupUi(this);
    }

    MovieContentView::~MovieContentView() {
        delete ui;
    }

    void MovieContentView::displayMovieContent(const MovieMeta &content) {
        ui->unicodeLineEdit->setText(content.unicode);
        ui->titleEdit->setText(content.title);
        ui->releaseDateLineEdit->setText(content.releaseDate);
        ui->durationLineEdit->setText(content.duration);
        ui->scoreLineEdit->setText(content.score);
    }

    void MovieContentView::displayMovieActors(const MovieMeta &content) {

        if (actorLabels.size() != 0) {
            for (int i = 0; i < actorLabels.size(); i++) {
                ui->ActressLayout->removeWidget(actorLabels[i]);
                delete actorLabels[i];  // 删除 QLabel 对象
            }

            actorLabels.clear();
        }

        //    if(!actorLabels.empty())
        for (int i = 0; i < content.actors.size(); i++) {
            auto label = new QLineEdit(content.actors[i]);
            actorLabels.emplace_back(label);
            ui->ActressLayout->addWidget(label);

        }
        //->setText(content.unicode);
    }

    void MovieContentView::displayMovieTags(const MovieMeta &content) {

        if (tagLabels.size() != 0) {
            for (int i = 0; i < tagLabels.size(); i++) {
                ui->TagLayout->removeWidget(tagLabels[i]);
                delete tagLabels[i];
            }
            tagLabels.clear();
        }

        //    if(!tagLabels.empty())
        for (int i = 0; i < content.tags.size(); i++) {
            auto label = new QLabel(content.tags[i]);
            tagLabels.emplace_back(label);
            ui->TagLayout->addWidget(label);

        }
    }

    void MovieContentView::displayCoverIcon(const QString &url) {

        ui->coverBut->changePic(url);
    }

    QPushButton *MovieContentView::getLibLinkButton() {
        return ui->OpenLibWebBut;
    }

    QPushButton *MovieContentView::getTorrentLinkButton() {
        return ui->CopyMagBut;
    }

    QPushButton *MovieContentView::getLocalFileLinkButton() {
        return ui->OpenLocalFileBut;
    }

    QPushButton *MovieContentView::getCoverButton() {
        return ui->coverBut;
    }
}