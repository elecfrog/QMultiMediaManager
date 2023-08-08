//
// Created by elecfrog on 2023/7/15.
//

#include "LineInputDialog.h"
#include "ui_LineInputDialog.h"
#include "../../script_service/RunPythonScript.h"

namespace elf {
    LineInputDialog::LineInputDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::LineInputDialog) {
        ui->setupUi(this);

        connect(ui->ConfirmBut, &QPushButton::clicked, this, &QDialog::accept);
        connect(ui->CancelBut, &QPushButton::clicked, this, &QDialog::reject);
    }

    LineInputDialog::~LineInputDialog() {
        delete ui;
    }

    void LineInputDialog::onScriptSearch() {
        qDebug() << ui->InputLineEdit->text();
        if (runLinkCrawler(ui->InputLineEdit->text().toStdString()) == 1)
            qDebug() << "Script Run Successfully!";
    }

    void LineInputDialog::accept() {
        onScriptSearch();
        QDialog::accept();
    }

    void LineInputDialog::reject() {
        QDialog::reject();
    }
}
