#ifndef TIEDOSTOOHJAIN_H
#define TIEDOSTOOHJAIN_H
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class TiedostoOhjain
{
    public:
    QString tiedostoNimi {};
    QString tiedostoSisalto{};
    TiedostoOhjain();
    TiedostoOhjain(QString tNimi,QString tiedostoSisalto);
};

#endif // TIEDOSTOOHJAIN_H
