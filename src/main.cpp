#include <QApplication>
#include "views/MainWindow.h"
#include "io/SqliteDriver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    elf::SqliteDriver::instance()->connect("");
    
    elf::MainWindow window;
    window.show();
    
    return QApplication::exec();
}
