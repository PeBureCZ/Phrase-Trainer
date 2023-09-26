#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEF_TEXT_NEXTBUT  "Next phrase\n(I know...)"
#define DECLINED_TEXT_NEXTBUT " Next phrase \n (incomplete) "

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phrasesDataObj = nullptr; //program functions
    trainMainLanguage = true; //constant for switch languages
    savedPhraseText = "";
    phraseAccepted = true;
    shownPhraseIndex = 0; //saved phrase index
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializePhraseData(phraseData* importedData)
{
    phrasesDataObj = importedData; //imported from main
}

void MainWindow::initializeProgram()
{
    ui->InformText->hide();
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

void MainWindow::on_AddPhraseBut_clicked() //create new window - add phrases
{
    PhraseAddWindow phraseAdd;
    phraseAdd.setModal(true);
    phraseAdd.initializePhrasedata(phrasesDataObj);
    phraseAdd.exec();
}

void MainWindow::on_NextBut_clicked() //click on next phrase
{
    if (phraseAccepted && shownPhraseIndex != 0) phrasesDataObj->deletePhrase(shownPhraseIndex); //delete both languages

    if (phrasesDataObj->getPhrasesCount() > 2) //new random index, not same, if phrases count > 2 (phrase index 0 = "")
    {
        int newIndex = 0;
        int maxCount = 0;
        do
        {
            newIndex = phrasesDataObj->getRandomPhraseIndex();
            maxCount++;
        }
        while(newIndex == shownPhraseIndex && maxCount < 20); //newIndex != shownPhraseIndex
        shownPhraseIndex = newIndex;
    }
    else shownPhraseIndex = phrasesDataObj->getRandomPhraseIndex();

    ui->InformText->hide();
    ui->NextBut->setText(DEF_TEXT_NEXTBUT);

    if (shownPhraseIndex > 0) //uncompleted or not started
    {
        ui->PhraseEditText->setText("");
        if (trainMainLanguage)
        {
            ui->PhraseText->setText(phrasesDataObj->getPhrase(shownPhraseIndex,1));
            savedPhraseText = phrasesDataObj->getPhrase(shownPhraseIndex, 0);
            //ui->PhraseEditText->setText(phrasesDataObj->getPhrase(index,0));
        }
        else
        {
            ui->PhraseText->setText(phrasesDataObj->getPhrase(shownPhraseIndex, 0));
            savedPhraseText = phrasesDataObj->getPhrase(shownPhraseIndex, 1);
            //ui->PhraseEditText->setText(phrasesDataObj->getPhrase(index,1));
        }
            phraseAccepted = true; //reset to default
    }
    else //started or completed
    {
       ui->PhraseText->setText(" LEVEL COMPLETED! \n To proceed to the next level, add more phrases and then click on the 'Next phrase' button ");
       ui->PhraseEditText->setText("");
       savedPhraseText = "";
       phraseAccepted = false;
       phrasesDataObj->saveProgress();
    }
}


void MainWindow::on_UnhideBut_clicked()
{   
   ui->PhraseEditText->setText(savedPhraseText);
   ui->NextBut->setText(" Next phrase \n (incomplete) ");
   phraseAccepted = false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   if (phraseAccepted && shownPhraseIndex != 0) phrasesDataObj->deletePhrase(shownPhraseIndex); //delete both languages
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

void MainWindow::on_AcceptBut_clicked()
{
    if (ui->PhraseEditText->toPlainText() == savedPhraseText && savedPhraseText != "")
    {
        ui->InformText->show();
        phraseAccepted = true;
        ui->InformText->setStyleSheet("QLabel { background-color : green; color : black; }"); //change style sheet
        ui->InformText->setText("Phrase accepted");
        ui->NextBut->setText(DEF_TEXT_NEXTBUT);
    }
    else if (savedPhraseText != "")
    {
        ui->InformText->show();
        phraseAccepted = false;
        ui->InformText->setStyleSheet("QLabel { background-color : red; color : black; }"); //change style sheet
        ui->InformText->setText("Phrase \" " + ui->PhraseEditText->toPlainText() + "\" rejected");
        ui->NextBut->setText(DECLINED_TEXT_NEXTBUT);
    }
}


