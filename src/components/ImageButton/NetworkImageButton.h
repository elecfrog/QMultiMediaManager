#ifndef QMULTIMEIDAMANAGER_NETWORKIMAGEBUTTON_H
#define QMULTIMEIDAMANAGER_NETWORKIMAGEBUTTON_H

#include <QApplication>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QPushButton>
#include <QBuffer>
#include <QSslSocket>
#include <QUrl>

namespace elf {
    class NetworkImageButton : public QPushButton {
    public:
        NetworkImageButton(QWidget *parent = nullptr)
                : QPushButton(parent) {
            // Create a network access manager
            manager = new QNetworkAccessManager(this);
        }

        void changePic(const QString &imageUrl) {
            url = imageUrl;
            // Disconnect previous connections
            disconnect(manager, &QNetworkAccessManager::finished, this, &NetworkImageButton::showImage);

            // Call the showImage method when the image is loaded
            connect(manager, &QNetworkAccessManager::finished, this, &NetworkImageButton::showImage);

            // Load the image from the network
            manager->get(QNetworkRequest(QUrl(url)));
        }

    private slots:
        void showImage(QNetworkReply *reply) {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray jpegData = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(jpegData);
                pixmap = pixmap.scaled((int) ((float) pixmap.width() / 1.5f), (int) ((float) pixmap.height() / 1.5f),
                                       Qt::KeepAspectRatio, Qt::SmoothTransformation);

                setIcon(QIcon(pixmap));
                setIconSize(pixmap.size());
                setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                setMinimumSize(pixmap.size());
                setMaximumSize(pixmap.size());
                setText("");
            } else {
                qDebug() << "Network error: " << reply->errorString();
            }

            reply->deleteLater();
        }

    private:
        QNetworkAccessManager *manager;
        QString url;
    };
}
#endif //QMULTIMEIDAMANAGER_NETWORKIMAGEBUTTON_H
