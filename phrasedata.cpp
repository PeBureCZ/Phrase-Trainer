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

QString phraseData::getPhrase(int index, int languageNum)
{

    if (index >= 0 && index < mainLanguageDatabase.size())
    {
        switch (languageNum)
        {
        case 0:
            return mainLanguageDatabase[index];
            break;
        case 1:
            return secondLanguageDatabase[index];
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
    }
    dataFileSavedMain.close();
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

void phraseData::saveProgress()
{
    if (mainLanguageDatabase.size() == 1)
    {
        //CLEAR FILE START
        QString emptyText = "";

        QString filePath = "savedPhrasesMain.txt";
        QFile dataFileSavedMain = filePath;
        QTextStream InSavedMain(&dataFileSavedMain);
        dataFileSavedMain.open(QIODevice::WriteOnly);
        dataFileSavedMain.write(emptyText.toUtf8());
        dataFileSavedMain.close();

        filePath = "savedPhrasesSecond.txt";
        QFile dataFileSavedSecond = filePath;
        QTextStream InSavedSecond(&dataFileSavedSecond);
        dataFileSavedSecond.open(QIODevice::WriteOnly);
        dataFileSavedSecond.write(emptyText.toUtf8());
        dataFileSavedSecond.close();
        //CLEAR FILE END

        checkSaveFiles();
    }
    else
    {
        QString line = "";

        //saved phrases data - main
        QString filePath = "savedPhrasesMain.txt"; //saved phrases data - main
        QFile dataFileSavedMain = filePath;
        dataFileSavedMain.open(QIODevice::WriteOnly);
        QTextStream InSavedMain(&dataFileSavedMain);
        dataFileSavedMain.write(line.toUtf8());

        //saved phrases data - second
        filePath = "savedPhrasesSecond.txt";
        QFile dataFileSavedSecond = filePath;
        QTextStream InSavedSecond(&dataFileSavedSecond);
        dataFileSavedSecond.open(QIODevice::WriteOnly);
        dataFileSavedSecond.write(line.toUtf8());

        for (int i = 1; i < getPhrasesCount(); i++)
        {
            line = getPhrase(i, 0);
            writeNewLineToDataFile("savedPhrasesMain.txt", line);

            line = getPhrase(i, 1);
            writeNewLineToDataFile("savedPhrasesSecond.txt", line);
        }

        dataFileSavedMain.close();
        dataFileSavedSecond.close();
    }
}

int phraseData::getRandomPhraseIndex()
{
    if (mainLanguageDatabase.size() >= 2) //index 0 = "";
    {
        int minPhraseLine = 1;
        int maxPhraseLine = mainLanguageDatabase.size(); //-1 not included due to BOUNDED in random gen
        return QRandomGenerator::global()->bounded(minPhraseLine, maxPhraseLine);
    }
    else return 0;
}

void phraseData::deletePhrase(int indexToRemove)
{
    if (mainLanguageDatabase.size() > 1) //index 0 = "";
    {
        mainLanguageDatabase.removeAt(indexToRemove);
        secondLanguageDatabase.removeAt(indexToRemove);
    }
}



