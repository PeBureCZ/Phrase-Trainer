#include "phrasedata.h"

phraseData::phraseData()
{
    mainLanguageDatabase = {""}; //index 0 - nothing
    secondLanguageDatabase = {""}; //index 0 - nothing
}

void phraseData::addPhrase(QString newPhrase, int languageNum)
{
    switch (languageNum)
    {
    case 0:
        mainLanguageDatabase.push_back(newPhrase);
        break;
    case 1:
        secondLanguageDatabase.push_back(newPhrase);
        break;
    }
}

QString phraseData::getPhrase(int line, int languageNum)
{

    if (line >= 0 && line <= mainLanguageDatabase.size())
    {
        switch (languageNum)
        {
        case 0:
            return mainLanguageDatabase[line];
            break;
        case 1:
            return secondLanguageDatabase[line];
            break;
        }

    }
    return "";
}

int phraseData::getPhrasesCount()
{
    return mainLanguageDatabase.size();
}

void phraseData::checkSaveFiles()
{
    QString filePath = "savedPhrasesMain.txt"; //saved phrases data - main
    QFile dataFileSavedMain = filePath;
    QString line = "";
    if (dataFileSavedMain.open(QIODevice::ReadWrite| QIODevice::Text )) //can create new file -- | QIODevice::Append
    {
        QTextStream InSavedMain(&dataFileSavedMain);
        line = InSavedMain.readLine(); //copy first line

        //saved phrases data - second
        filePath = "savedPhrasesSecond.txt";
        QFile dataFileSavedSecond = filePath;
        QTextStream InSavedSecond(&dataFileSavedSecond);
        dataFileSavedSecond.open(QIODevice::ReadWrite| QIODevice::Text);

        if (line == "") //check if savedData-first line is empty? -> fill phrases from full-data
        {
            //full phrases data - main
            filePath = "mainLanguageData.txt";
            QFile dataFileMain = filePath;
            QTextStream inMain(&dataFileMain);
            dataFileMain.open(QIODevice::ReadOnly);

            //full phrases data - second
            filePath = "secondLanguageData.txt";
            QFile dataFileSecond = filePath;
            QTextStream inSecond(&dataFileSecond);
            dataFileSecond.open(QIODevice::ReadOnly);

            int repeatLine = 1;
            while (!inMain.atEnd() && repeatLine <= 100000)
            {
                line = inMain.readLine();
                addPhrase(line, 0); //copy data from file to phrasedata class (main)
                InSavedMain << line + "\n";

                line = inSecond.readLine();
                addPhrase(line, 1); //copy data from file to phrasedata class (second)
                InSavedSecond << line + "\n";

                repeatLine++;
            }
            dataFileMain.close();
            dataFileSecond.close();
            dataFileSavedSecond.close();
        }
        else //save files exist + filled -> fill phrases from saved files
        {
            addPhrase(line, 0); //copy data from file to phrasedata class (main)
            line = InSavedSecond.readLine();
            addPhrase(line, 1); //copy data from file to phrasedata class (second)
            while (!InSavedMain.atEnd()) // continue after readed line 1 ----> lines 2+
            {
                line = InSavedMain.readLine();
                addPhrase(line, 0); //copy data from file to phrasedata class (main)

                line = InSavedSecond.readLine();
                addPhrase(line, 1); //copy data from file to phrasedata class (second)
            }
        }
        dataFileSavedMain.close();
    }
}

void phraseData::saveProgress() //  NOT COMPLETED!!!!!!!!!!! BUG
{
    QString filePath = "savedPhrasesMain.txt"; //saved phrases data - main
    QFile dataFileSavedMain = filePath;
    QTextStream InSavedMain(&dataFileSavedMain);
    dataFileSavedMain.open(QIODevice::WriteOnly);

    filePath = "savedPhrasesSecond.txt";
    QFile dataFileSavedSecond = filePath;
    QTextStream InSavedSecond(&dataFileSavedSecond);
    dataFileSavedSecond.open(QIODevice::WriteOnly);

    QString emptyText = "";

    dataFileSavedMain.write(emptyText.toUtf8());
    dataFileSavedSecond.write(emptyText.toUtf8());

    if (mainLanguageDatabase.size() > 1) //index 0 = "" (always)
    {
        for (int i = 0; i < getPhrasesCount(); i++)
        {
            InSavedMain << getPhrase(i, 0);
            InSavedSecond << getPhrase(i, 1);
        }
    }
    dataFileSavedMain.close();
    dataFileSavedSecond.close();
}

QString phraseData::getRandomPhrase(bool removePhrase)
{
    if (mainLanguageDatabase.size() >= 2) //index 0 = "";
    {
        int minPhraseLine = 1;
        int maxPhraseLine = mainLanguageDatabase.size(); //-1 not included due to BOUNDED in random gen
        int randomLine = QRandomGenerator::global()->bounded(minPhraseLine, maxPhraseLine);
        if (removePhrase = false) return mainLanguageDatabase[randomLine];
        else
        {
            QString out = mainLanguageDatabase[randomLine];
            mainLanguageDatabase.removeAt(randomLine);
            secondLanguageDatabase.removeAt(randomLine);
            return out;
        }
    }
    else
    {
        return "LEVEL COMPLETED!\nTo improve your level, add more phrases ";
        saveProgress();
        checkSaveFiles();
    }
}


void phraseData::createDataFile(QString filePath)
{
    QFile dataFile = filePath;
    if (!dataFile.open(QIODevice::ReadOnly)) //can open? = exist
    {
        dataFile.open(QIODevice::WriteOnly); //no exist? = create
    }
    dataFile.close();
}

void phraseData::writeNewLineToDataFile(QString filePath, QString textData)
{
    QFile dataFile = filePath;
    if (dataFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Append)) //can create new file
    {
        QTextStream in(&dataFile);
        in << textData + "\n";
        dataFile.close();
    }
}

