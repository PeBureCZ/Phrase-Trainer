#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    phraseData phrases;
    w.initializePhraseData(&phrases);
    w.initializeProgram();
    w.show();
    return a.exec();
}
