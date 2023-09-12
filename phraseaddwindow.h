#ifndef PHRASEADDWINDOW_H
#define PHRASEADDWINDOW_H

#include <QDialog>
#include <QString>
#include "phrasedata.h"

namespace Ui {
class PhraseAddWindow;
}

class PhraseAddWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::PhraseAddWindow *ui;
    phraseData* PhrasedataObject;

public:
    explicit PhraseAddWindow(QWidget *parent = nullptr);
    ~PhraseAddWindow();
    void initializePhrasedata (phraseData* phrasedataObj);



private slots:

    void on_acceptButt_clicked();
    void on_CancelButt_clicked();
};

#endif // PHRASEADDWINDOW_H
