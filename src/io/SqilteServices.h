//
// Created by elecfrog on 2023/7/17.
//

#ifndef QMULTIMEIDAMANAGER_SQILTESERVICES_H
#define QMULTIMEIDAMANAGER_SQILTESERVICES_H

#include <QString>
#include <QSqlRecord>
#include "SqliteDriver.h"

namespace elf {
    class SqliteServices {
    public:
        static bool updateMovieLocalFileLink(const QString &filepath, const QString &unicode) {
            QString query = "UPDATE movies SET localFile = '" + filepath + "' WHERE movies.unicode = '" + unicode + "'";
            selectAllFrom(query);
            return true;
        }

        // query all movie list from database
        static std::vector<QString> getAllMovieList() {
            std::vector<QString> ret{};
            auto records = selectAllFrom("SELECT unicode FROM movies");
            if (records.empty() || records[0].fieldName(0) != QString("unicode"))
                return ret;

            for (auto &r: records) {
                QString unicode = r.field(0).value().toString();
//                qDebug() << unicode;
                ret.emplace_back(unicode);
            }

            return ret;
        }

        // query all movie list from database
        static std::vector<QString> getAllMovieListWithFilter(bool ignore, bool hideVR) {
            std::vector<QString> ret{};
            std::vector<QSqlRecord> records;
            records.resize(0);
            if (ignore && hideVR) {
                records = selectAllFrom("SELECT unicode\n"
                                        "FROM movies\n"
                                        "WHERE prefix NOT IN (\n"
                                        "    SELECT prefix\n"
                                        "    FROM ignored_prefix\n"
                                        ") AND prefix NOT IN (\n"
                                        "    SELECT prefix\n"
                                        "    FROM vr_prefix\n"
                                        ");");
                qDebug() << "Ignored && HideVR";
            } else if (ignore && !hideVR)
                records = selectAllFrom("SELECT unicode\n"
                                        "FROM movies\n"
                                        "WHERE prefix NOT IN (\n"
                                        "    SELECT prefix\n"
                                        "    FROM ignored_prefix\n"
                                        ");");

            else {
                records = selectAllFrom("SELECT unicode FROM movies");
                qDebug() << "No Ignored";
            }

            if (records.empty() || records[0].fieldName(0) != QString("unicode"))
                return ret;

            for (auto &r: records) {
                QString unicode = r.field(0).value().toString();
//                qDebug() << unicode;
                ret.emplace_back(unicode);
            }

            // sorting
            std::sort(ret.begin(), ret.end());

            return ret;
        }

        // query movie list filtered by name from data base
        static std::vector<QString> getMovieListByActorName(const QString &actorName) {
            std::vector<QString> ret{};
            QString query = "SELECT movies.unicode\n"
                            "FROM movies\n"
                            "         JOIN movie_actors ON movies.id = movie_actors.movie_id\n"
                            "         JOIN actors ON actors.id = movie_actors.actor_id\n"
                            "WHERE actors.name = '" + actorName + "'";
            auto records = selectAllFrom(query);
            if (records.empty() || records[0].fieldName(0) != QString("unicode"))
                return ret;

            for (auto &r: records) {
                QString unicode = r.field(0).value().toString();
//                qDebug() << unicode;
                ret.emplace_back(unicode);
            }

            return ret;
        }

        // query movie list filtered by unicode from data base
        static std::vector<QString> getMovieListByUnicode(const QString &unicode) {
            std::vector<QString> ret{};
            QString query = "SELECT movies.unicode\n"
                            "FROM movies\n"
                            "WHERE movies.unicode = '" + unicode + "'";
            auto records = selectAllFrom(query);
            if (records.empty() || records[0].fieldName(0) != QString("unicode"))
                return ret;

            for (auto &r: records) {
                QString unicode = r.field(0).value().toString();
//                qDebug() << unicode;
                ret.emplace_back(unicode);
            }

            return ret;
        }

        // query movie list filtered by unicode from data base
        static std::vector<QString> getMovieListByUnicodePrefix(const QString &prefix) {
            std::vector<QString> ret{};
            QString query = "SELECT movies.unicode\n"
                            "FROM movies\n"
                            "WHERE movies.prefix = '" + prefix + "'";

            auto records = selectAllFrom(query);
            if (records.empty() || records[0].fieldName(0) != QString("unicode"))
                return ret;

            for (auto &r: records) {
                QString unicode = r.field(0).value().toString();
//                qDebug() << unicode;
                ret.emplace_back(unicode);
            }

            return ret;
        }

        static std::vector<QSqlRecord> selectAllFrom(const QString &expr, uint rows = 1000) {
            std::vector<QSqlRecord> records;
            QSqlQuery query;
            if (query.exec(expr)) {
                while (query.next() && rows > 0) {
                    QSqlRecord record = query.record();
                    records.emplace_back(std::move(record));
                    rows--;
                }
            } else {
                qDebug() << "Error executing query:" << query.lastError().text();
            }

            return records;
        }


        static QSqlRecord selectRowFromMovies(const QString &where, const QString &equals) {
            QSqlQuery query;
            QString queryString = QString("SELECT * FROM movies WHERE %1 = :param").arg(where);
            query.prepare(queryString);
            query.bindValue(":param", equals);
            if (query.exec()) {
                while (query.next()) {
                    QSqlRecord record = query.record();

                    for (int i = 0; i < record.count(); i++) {
                        QSqlField field = record.field(i);
                        qDebug() << field.name() << ":" << field.value();
                    }
                    return record;
                }
            } else {
                qDebug() << "Error executing query:" << query.lastError();
            }
            return {};
        }

        static std::vector<QSqlRecord> selectActorsFromMoviesByUnicode(const QString &equals, uint rows = 1000) {
            QSqlQuery query;
            QString queryString = QString("SELECT actors.name\n"
                                          "FROM actors\n"
                                          "         JOIN movie_actors ON actors.id = movie_actors.actor_id\n"
                                          "         JOIN movies ON movie_actors.movie_id = movies.id\n"
                                          "WHERE movies.unicode  =  '%1';").arg(equals);

            std::vector<QSqlRecord> records;
            if (query.exec(queryString)) {
                while (query.next() && rows > 0) {
                    QSqlRecord record = query.record();
                    records.emplace_back(std::move(record));
                    rows--;
                }
            } else {
                qDebug() << "Error executing query:" << query.lastError();
            }

            return records;
        }

        static std::vector<QSqlRecord> selectTagsFromMoviesByUnicode(const QString &expr_prep, uint rows = 1000) {
            QSqlQuery query;
            QString queryString = QString("SELECT tags.name FROM tags\n"
                                          "         JOIN movie_tags ON tags.id = movie_tags.tag_id\n"
                                          "         JOIN movies ON movie_tags.movie_id = movies.id\n"
                                          "WHERE movies.unicode  = '%1';").arg(expr_prep);

            std::vector<QSqlRecord> records;
            if (query.exec(queryString)) {
                while (query.next() && rows > 0) {
                    QSqlRecord record = query.record();
                    records.emplace_back(std::move(record));
                    rows--;
                }
            } else {
                qDebug() << "Error executing query:" << query.lastError();
            }

            return records;
        }
    };
}
#endif //QMULTIMEIDAMANAGER_SQILTESERVICES_H
