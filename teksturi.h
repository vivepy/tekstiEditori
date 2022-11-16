#ifndef TEKSTURI_H
#define TEKSTURI_H

#include <QMainWindow>
#include "QListWidget"
#include "tiedostoohjain.h"
#include <QList>
#include "muutosrakenne.h"

QT_BEGIN_NAMESPACE
namespace Ui { class teksturi; }
QT_END_NAMESPACE

class teksturi : public QMainWindow
{
    Q_OBJECT

public:
    QList <TiedostoOhjain> avoimetTiedostot;
    teksturi(QWidget *parent = nullptr);
    ~teksturi();

private slots:

    void on_actionSave_triggered();

    void on_actionfont_size_triggered();

    void on_actionLoad_triggered();

    void on_actionNew_File_triggered();

    void on_actionClose_file_triggered();

    void on_actionQuit_triggered();
    void updatetiedostoLista();
    void muutosListaaja();

    void on_actionundo_triggered();

private:
    Ui::teksturi *ui;
};
#endif // TEKSTURI_H
