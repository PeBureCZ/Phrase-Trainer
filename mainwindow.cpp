#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phrasesDataObj = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializePhraseData(phraseData* importedData)
{
    phrasesDataObj = importedData;
}

void MainWindow::initializeProgram()
{
    QString filePath = "mainLanguageData.txt";
    phrasesDataObj->createDataFile(filePath);
    filePath = "secondLanguageData.txt";
    phrasesDataObj->createDataFile(filePath);
    filePath = "savedPhrasesMain.txt";
    phrasesDataObj->createDataFile(filePath);
    filePath = "savedPhrasesSecond.txt";
    phrasesDataObj->createDataFile(filePath);
    phrasesDataObj->checkSaveFiles();
}

void MainWindow::on_AddPhraseBut_clicked()
{
    PhraseAddWindow phraseAdd;
    phraseAdd.setModal(true);
    phraseAdd.initializePhrasedata(phrasesDataObj);
    phraseAdd.exec();
}

void MainWindow::on_AcceptBut_clicked()
{
}

void MainWindow::on_NextBut_clicked()
{
    //phrasesDataObj->saveProgress(); //testOnly
    ui->PhraseText->setText(phrasesDataObj->getRandomPhrase(true)); //bool = remove phrase from data?
}

