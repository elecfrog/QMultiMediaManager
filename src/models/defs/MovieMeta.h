//
// Created by elecfrog on 2023/7/14.
//

#ifndef QMULTIMEIDAMANAGER_MOVIEMETA_H
#define QMULTIMEIDAMANAGER_MOVIEMETA_H

#include <QString>

namespace elf {
    struct MovieMeta {
        QString unicode;
        QString title;
        QString releaseDate;
        QString duration;
        QString score;

        std::vector<QString> actors;
        std::vector<QString> tags;

        QString libLink;
        QString coverLink;
        QString torrentLink;
        QString localFile;
    };
}
#endif //QMULTIMEIDAMANAGER_MOVIEMETA_H
