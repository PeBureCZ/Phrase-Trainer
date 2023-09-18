#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phrasesDataObj = nullptr;
    trainMainLanguage = true;
    savedPhraseText = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializePhraseData(phraseData* importedData)
{
    phrasesDataObj = importedData;
//    Phrase
//    phrasesDataObj->getRandomPhraseIndex()
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
    int actualPhraseIndex = phrasesDataObj->getRandomPhraseIndex();
    if (actualPhraseIndex > 0)
    {
        ui->PhraseEditText->setText("");
        if (trainMainLanguage)
        {
            ui->PhraseText->setText(phrasesDataObj->getPhrase(actualPhraseIndex,1));
            savedPhraseText = phrasesDataObj->getPhrase(actualPhraseIndex, 0);
            //ui->PhraseEditText->setText(phrasesDataObj->getPhrase(index,0));
            phrasesDataObj->deletePhrase(actualPhraseIndex); //delete both languages
        }
        else
        {
            ui->PhraseText->setText(phrasesDataObj->getPhrase(actualPhraseIndex, 0));
            savedPhraseText = phrasesDataObj->getPhrase(actualPhraseIndex, 1);
            //ui->PhraseEditText->setText(phrasesDataObj->getPhrase(index,1));
            phrasesDataObj->deletePhrase(actualPhraseIndex); //delete both languages
        }

    }
    else
    {
       ui->PhraseText->setText("LEVEL COMPLETED!\nTo improve your level, add more phrases ");
       ui->PhraseEditText->setText("");
       savedPhraseText = "";
       phrasesDataObj->saveProgress();
    }

}


void MainWindow::on_UnhideBut_clicked()
{   
   ui->PhraseEditText->setText(savedPhraseText);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    phrasesDataObj->saveProgress(); //close = save from loaded data
}


void MainWindow::on_SwitchButt_clicked()
{
    if (trainMainLanguage)
    {
        ui->SwitchButt->setText("Phrases language (actual: česky)");
        trainMainLanguage = false;
    }
    else
    {
        ui->SwitchButt->setText("Phrases language (actual: english)");
        trainMainLanguage = true;
    }
}

