#ifndef PHRASEDATA_H
#define PHRASEDATA_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication> // "modulo"
#include <QRandomGenerator> //random num generator

class phraseData
{
public:
    phraseData();
    QVector<QString> mainLanguageDatabase;
    QVector<QString> secondLanguageDatabase;

    void checkSaveFiles();
    void addPhrase(QString newPhrase, int languageNum);

    void createDataFile(QString filePath);
    void writeNewLineToDataFile(QString filePath, QString textData);

    QString getPhrase(int line, int languageNum);
    QString getRandomPhrase(bool removePhrase);
    void saveProgress();
    int getPhrasesCount();


};

#endif // PHRASEDATA_H































