//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIECONTENTMODEL_H
#define QMULTIMEIDAMANAGER_MOVIECONTENTMODEL_H

#include "../io/SqliteDriver.h"
#include "../io/SqilteServices.h"

namespace elf {
    class MovieContentModel : public QObject {
    Q_OBJECT

    public:
        explicit MovieContentModel(QObject *parent = nullptr) : QObject(parent) {
        }

        MovieMeta getMovieContent(const QString &unicodeStr) {

            MovieMeta meta;

            
            auto record = SqliteServices::selectRowFromMovies("unicode", unicodeStr);

            meta.unicode = record.field("unicode").value().toString();
            meta.title = record.value("title").toString();
            meta.releaseDate = record.value("releaseTime").toString();
            meta.duration = record.value("duration").toString();
            meta.score = record.value("score").toString();

            meta.actors.resize(0);
            auto records = SqliteServices::selectActorsFromMoviesByUnicode(unicodeStr);
            for (auto &r: records) {
                qDebug() << r.field("name").value().toString();
                meta.actors.emplace_back(r.field("name").value().toString());
            }

            meta.tags.resize(0);
            records = SqliteServices::selectTagsFromMoviesByUnicode(unicodeStr);
            for (auto &r: records) {
                qDebug() << r.field("name").value().toString();
                meta.tags.emplace_back(r.field("name").value().toString());
            }

            meta.libLink = record.value("libLink").toString();
            meta.coverLink = record.value("coverLink").toString();
            meta.torrentLink = record.value("torrentLink").toString();
            meta.localFile = record.value("localFile").toString();

            m_data = meta;

            return meta;
        }

        QString getLibLink() const { return m_data.libLink; }

        QString getTorrentMag() const { return m_data.torrentLink; }

        QString getLocalFilePath() const { return m_data.localFile; }

    private:
        MovieMeta m_data;
    };
}
#endif //QMULTIMEIDAMANAGER_MOVIECONTENTMODEL_H
