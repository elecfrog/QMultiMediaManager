//
// Created by ml212fz on 7/18/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_NavigatorBar.h" resolved

#include "NavigatorBar.h"
#include "ui_NavigatorBar.h"
#include "../models/defs/SearchKeyword.h"

namespace elf {
    NavigatorBar::NavigatorBar(QWidget *parent) :
            QWidget(parent), ui(new Ui::NavigatorBar) {
        ui->setupUi(this);

        ui->comboBox->addItem("All", QVariant(0));
        ui->comboBox->addItem("Actor", QVariant(1));
        ui->comboBox->addItem("Studio", QVariant(2));
        ui->comboBox->addItem("Unicode", QVariant(3));
        ui->comboBox->setCurrentIndex(0);

        ui->ignoredCheckBox->setChecked(true);
        ui->hideVRCheckBox->setChecked(true);
        isIgnoredChecked = ui->ignoredCheckBox->isChecked();
        ishideVRCheckd = ui->hideVRCheckBox->isChecked();
        
        connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &NavigatorBar::onComboBoxIndexChanged);

        connect(ui->ignoredCheckBox, &QCheckBox::stateChanged,
                [=](int state){         isIgnoredChecked = ui->ignoredCheckBox->isChecked();
                    qDebug() << "isIgnoredChecked " << isIgnoredChecked;        
            qDebug() << "Checkbox state changed to " << state; });

        connect(ui->hideVRCheckBox, &QCheckBox::stateChanged,
                [=](int state){         isIgnoredChecked = ui->hideVRCheckBox->isChecked();
                    qDebug() << "hideVRCheckBox " << ishideVRCheckd;        
            qDebug() << "Checkbox state changed to " << state; });
    }

    NavigatorBar::~NavigatorBar() {
        delete ui;
    }


    void NavigatorBar::onComboBoxIndexChanged(int index) {
        QComboBox *comboBox = qobject_cast<QComboBox *>(sender());

        int currentIndex = comboBox->currentIndex();
        QVariant userData = comboBox->itemData(currentIndex);
        int selectedRoleId = userData.toInt();

        SearchKeyword keyword = SearchKeyword::All;
        if (selectedRoleId == 0) { keyword = SearchKeyword::All; }
        else if (selectedRoleId == 1) { keyword = SearchKeyword::Actor; }
        else if (selectedRoleId == 2) { keyword = SearchKeyword::Studio; }
        else if (selectedRoleId == 3) { keyword = SearchKeyword::Unicode; }

        connect(ui->searchBut, &QPushButton::clicked, [this, keyword] {
            emit updateListBySearch(keyword, ui->searchLineEdit->text());
        });

        connect(ui->searchLineEdit, &QLineEdit::returnPressed, [this, keyword] {
            emit updateListBySearch(keyword, ui->searchLineEdit->text());
        });

    }

    QPushButton *NavigatorBar::getSearchBut() { return ui->searchBut; }

    QLineEdit *NavigatorBar::getSearchLineEdit() { return ui->searchLineEdit; }

    MovieListView *NavigatorBar::getMovieListView() {
        return ui->movieList;
    }

    QCheckBox *NavigatorBar::getIgnoredCheckBox() {
        return ui->ignoredCheckBox;
    }


    QCheckBox *NavigatorBar::getHidVRCheckBox() {
        return ui->hideVRCheckBox;
    }

} // elf
