//
// Created by elecfrog on 2023/7/15.
//

#ifndef QMULTIMEIDAMANAGER_SINGLINEINPUTDIALOG_H
#define QMULTIMEIDAMANAGER_SINGLINEINPUTDIALOG_H

#include <QDialog>


namespace elf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class LineInputDialog; }
    QT_END_NAMESPACE

    class LineInputDialog : public QDialog {
    Q_OBJECT

    public:
        explicit LineInputDialog(QWidget *parent = nullptr);

        ~LineInputDialog() override;

        void accept() override;

        void reject() override;

    private slots:

        void onScriptSearch();

    private:
        Ui::LineInputDialog *ui;
    };

}

#endif //QMULTIMEIDAMANAGER_SINGLINEINPUTDIALOG_H
