#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phrasesData = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializePhraseData(phraseData* importedData)
{
    phrasesData = importedData;
}

void MainWindow::initializeProgram()
{
    QString filePath = "mainLanguageData.txt";
    phrasesData->createDataFile(filePath);
    filePath = "secondLanguageData.txt";
    phrasesData->createDataFile(filePath);
    filePath = "savedPhrases.txt";
    phrasesData->createDataFile(filePath);
    phrasesData->checkSaveFile();
}

void MainWindow::on_AddPhraseBut_clicked()
{
    PhraseAddWindow phraseAdd;
    phraseAdd.setModal(true);
    phraseAdd.initializePhrasedata(phrasesData);
    phraseAdd.exec();
}

void MainWindow::on_AcceptBut_clicked()
{
}

