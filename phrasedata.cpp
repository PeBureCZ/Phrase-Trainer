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

QString phraseData::getPhrase(int line)
{
    if (line >= 0 && line <= mainLanguageDatabase.size())
    {
        return mainLanguageDatabase[line];
    }
    return "";
}

int phraseData::getPhrasesCount()
{
    return mainLanguageDatabase.size();
}

void phraseData::checkSaveFile()
{
    QString filePath = "savedPhrases.txt";
    QFile dataFileSaved = filePath;
    QString line = "";
    if (dataFileSaved.open(QIODevice::ReadWrite| QIODevice::Text | QIODevice::Append)) //can create new file


    //__________CONDITION NOT WORKING CORECTLY NOW!!!!!!!!!!!!!!!!!!!!!


    {
        QTextStream inSaved(&dataFileSaved);
        line = inSaved.readLine(); //copy first line
        if (line.length() == 0) //check if savedData-first line is empty?
        {
            inSaved << line + " - test";
            filePath = "mainLanguageData.txt";
            QFile dataFileMain = filePath;
            filePath = "secondLanguageData.txt";
            QFile dataFileSecond = filePath;
            QTextStream inMain(&dataFileMain);
            QTextStream inSecond(&dataFileSecond);
            dataFileMain.open(QIODevice::ReadOnly);
            dataFileSecond.open(QIODevice::ReadOnly);
            int repeatLine = 1;
            while (!inMain.atEnd() && repeatLine <= 100000)
            {

                if (repeatLine % 2 == 0)
                {
                    line = inMain.readLine();
                    addPhrase(line, 0); //copy data from file to phrasedata class
                    inSaved << line + "\n";
                }
                else
                {
                    line = inSecond.readLine();
                    addPhrase(line, 1); //copy data from file to phrasedata class
                    inSaved << line + "\n";
                }
                repeatLine++;
            }
            dataFileMain.close();
            dataFileSecond.close();
        }
        dataFileSaved.close();
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

