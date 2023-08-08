//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIELISTCONTROLLER_H
#define QMULTIMEIDAMANAGER_MOVIELISTCONTROLLER_H

#include "../models/MovieListModel.h"
#include "../models/defs/SearchKeyword.h"
#include "../views/NavigatorBar.h"
#include "../views/MovieListView.h"
#include <QPushButton>
#include <QLineEdit>

namespace elf {
    class MovieListController : public QObject {
    Q_OBJECT

    public:
        MovieListController(MovieListModel *model, elf::NavigatorBar *view, QObject *parent = nullptr)
                : QObject(parent), m_model(model), m_view(view) {
            auto multi_ignored = m_view->getIgnoredCheckBox()->isChecked();
            auto vr_ignored = m_view->getHidVRCheckBox()->isChecked();
            auto movie_List = elf::SqliteServices::getAllMovieListWithFilter(multi_ignored, vr_ignored);
            for (const auto &movie: movie_List) {

                // 创建一个QStandardItem对象
                QStandardItem *item = new QStandardItem();

                // 设置项目的图标和文本
                item->setIcon(QIcon("./assets/icon.png"));
                item->setText(movie);

                // 将项目添加到模型
                m_view->getMovieListView()->model->appendRow(item);
            }

            connect(m_view->getMovieListView(), &elf::MovieListView::fileSelected, this,
                    &MovieListController::handleFileSelected);
            connect(m_view, &elf::NavigatorBar::updateListBySearch, this, &MovieListController::handleSearch);
        }

        void updateList() {
            m_view->getMovieListView()->model->clear();

            auto movie_List = elf::SqliteServices::getAllMovieList();
            for (const auto &movie: movie_List) {
                // 创建一个QStandardItem对象
                QStandardItem *item = new QStandardItem();

                // 设置项目的图标和文本
                item->setIcon(QIcon("./assets/icon.png"));
                item->setText(movie);

                // 将项目添加到模型
                m_view->getMovieListView()->model->appendRow(item);
            }
        }

        void updateList(std::vector<QString> movie_List) {
            m_view->getMovieListView()->model->clear();

            for (const auto &movie: movie_List) {
                // 创建一个QStandardItem对象
                QStandardItem *item = new QStandardItem();

                // 设置项目的图标和文本
                item->setIcon(QIcon("./assets/icon.png"));
                item->setText(movie);

                // 将项目添加到模型
                m_view->getMovieListView()->model->appendRow(item);
            }
        }

        void handleSearch(elf::SearchKeyword type, const QString &word) {
            if (type == elf::SearchKeyword::All) {
                qDebug() << "Select All Search";
                connect(m_view->getSearchBut(), &QPushButton::clicked, [this] {
                    updateList(elf::SqliteServices::getAllMovieList());
                });

                connect(m_view->getSearchLineEdit(), &QLineEdit::returnPressed, [this] {
                    updateList(elf::SqliteServices::getAllMovieList());
                });
            } else if (type == elf::SearchKeyword::Actor) {
                qDebug() << "Select Actor Search";
                connect(m_view->getSearchBut(), &QPushButton::clicked, [this, word] {
                    updateList(elf::SqliteServices::getMovieListByActorName(word));
                });
            } else if (type == elf::SearchKeyword::Studio) {
                qDebug() << "Select Studio Search";
                connect(m_view->getSearchBut(), &QPushButton::clicked, [this, word] {
                    updateList(elf::SqliteServices::getMovieListByUnicodePrefix(word));
                });
            } else if (type == elf::SearchKeyword::Unicode) {
                qDebug() << "Select Unicode Search";
                connect(m_view->getSearchBut(), &QPushButton::clicked, [this, word] {
                    updateList(elf::SqliteServices::getMovieListByUnicode(word));
                });
            }
        }

    public slots:

        void handleFileSelected(const QString &filePath, const QString &unicode) {
            QFileInfo fileInfo = QFileInfo(filePath);
            QString dir = fileInfo.path();
            QString filename = fileInfo.fileName();
            QString suffix = fileInfo.suffix();
            qDebug() << filename;

            QFile file(filePath);
            if (file.exists()) {
                QString newpath = dir + "/" + unicode + "." + suffix;
                elf::SqliteServices::updateMovieLocalFileLink(newpath, unicode);
                if (file.rename(filePath, newpath)) {
                    qDebug() << "Rename successful!";
                } else {
                    qDebug() << "Rename failed!";
                }
            } else {
                qDebug() << "The file does not exist!";
            }

        }

    private:
        MovieListModel *m_model;
        elf::NavigatorBar *m_view;

    };
}

#endif //QMULTIMEIDAMANAGER_MOVIELISTCONTROLLER_H
