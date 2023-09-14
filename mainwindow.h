#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "phraseaddwindow.h"
#include "phrasedata.h"
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    Ui::MainWindow *ui;
    phraseData* phrasesDataObj;

public:
    MainWindow(QWidget *parent = nullptr);
    void initializePhraseData(phraseData* importedData);
    void initializeProgram();
    ~MainWindow();

private slots:
    void on_AddPhraseBut_clicked();
    void on_AcceptBut_clicked();


    void on_NextBut_clicked();
};
#endif // MAINWINDOW_H
