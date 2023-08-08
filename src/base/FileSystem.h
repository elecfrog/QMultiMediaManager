#pragma once

#include <QDebug>
#include <QFile>

namespace elf::base {
    class FileSystem {
    public:
        static bool WriteQByteArrayToFile(const QByteArray &data, const QString &filePath) {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Cannot open file for writing: " << file.errorString();
                return false;
            }

            file.write(data);
            file.close();
            return true;
        }

        static bool ReadQByteArrayFromFile(QByteArray &data, const QString &filePath) {
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << "Cannot open file for writing: " << file.errorString();
                return false;
            }

            data = file.readAll();
            file.close();
            return true;
        }
    };
}

