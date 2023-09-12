#include "phraseaddwindow.h"
#include "ui_phraseaddwindow.h"

#define MAIN_LANGUAGE_PATH "mainLanguageData.txt"
#define SECOND_LANGUAGE_PATH "secondLanguageData.txt"


PhraseAddWindow::PhraseAddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhraseAddWindow)
{
    ui->setupUi(this);
    ui->WarningLabel->setStyleSheet("QLabel { background-color : red; color : black; }"); //change style sheet
    ui->WarningLabel->hide(); //hide warning message
    PhrasedataObject = nullptr;
}

PhraseAddWindow::~PhraseAddWindow()
{
    delete ui;
}

void PhraseAddWindow::initializePhrasedata (phraseData* phrasedataObj)
{
    PhrasedataObject = phrasedataObj;
}

void PhraseAddWindow::on_acceptButt_clicked()
{
    QString textMain = ui->PhraseAddTextMain->toPlainText();
    QString textSecond = ui->PhraseAddTextSecond->toPlainText();

    int sizeOfText1 = textMain.length();
    int sizeOfText2 = textSecond.length();
    if (sizeOfText1 > 0 && sizeOfText2 > 0)
    {
        PhrasedataObject->addPhrase(textMain, 0);
        PhrasedataObject->addPhrase(textSecond, 1);
        PhrasedataObject->writeNewLineToDataFile(MAIN_LANGUAGE_PATH, textMain);
        PhrasedataObject->writeNewLineToDataFile(SECOND_LANGUAGE_PATH, textSecond);
        this->close();
    }
    else
    {
        ui->WarningLabel->show();
    }
}

void PhraseAddWindow::on_CancelButt_clicked()
{
    this->close();
}

