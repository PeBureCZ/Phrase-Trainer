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

void checkSaveFile()
{
    //openDataFile IT MUST BE COMPLETED  (CREATE OR USE -> FILL PHRASEDATA CLASS)
    QString filePath = "saveFile";
    QFile dataFile = filePath;
    if (!dataFile.exists())
    {
        //CREATE FILE

        //USE CLASS PHRASEDATA => FILL...
        //.....LOOP
        //CREATE NEW LINE - MAIN
        //CREATE NEW LINE - SECOND
        //.....LOOP
    }
    else
    {
        //nothing - delete?
    }
    dataFile.close();

}

void phraseData::openDataFile(QString filePath)
{
    QFile dataFile = filePath;
    QString line = "";
    if (dataFile.open(QIODevice::ReadWrite)) //can create new file
    {
        QTextStream in(&dataFile);
        int maxRepeatLine = 0;
        while (!in.atEnd() && maxRepeatLine <= 100000)
        {
            line = in.readLine();

            addPhrase(line, 0); //copy data from file to phrasedata class
            maxRepeatLine++;

        }
        dataFile.close();
    }
    else
    {
        //file not created?!
    }
}

void phraseData::writeNewLineToDataFile(QString filePath, QString textData)
{
    QFile dataFile = filePath;
    QString line = "";
    if (dataFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Append)) //can create new file
    {
        QTextStream in(&dataFile);
        in << textData + "\n";
        dataFile.close();
    }
    else
    {
        //file not created?!
    }
}

