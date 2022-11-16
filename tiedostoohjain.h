#ifndef TIEDOSTOOHJAIN_H
#define TIEDOSTOOHJAIN_H
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>
#include "muutosrakenne.h"

class TiedostoOhjain
{
    public:
    QString tiedostoNimi {};
    QString tiedostoSisalto{};
    QList<muutosRakenne> muutosLista{};
    TiedostoOhjain();
    TiedostoOhjain(QString tNimi,QString tiedostoSisalto);
};

#endif // TIEDOSTOOHJAIN_H
