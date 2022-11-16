#ifndef MUUTOSRAKENNE_H
#define MUUTOSRAKENNE_H
#include "QString"


class muutosRakenne
{


public:
    QString muutos;
    bool suunta;
    int alku;
    int loppu;
    muutosRakenne();
    muutosRakenne(QString m, bool s);
};

#endif // MUUTOSRAKENNE_H
