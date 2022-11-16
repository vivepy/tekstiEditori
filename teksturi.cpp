#include "teksturi.h"
#include "./ui_teksturi.h"
#include "QSizePolicy"
#include "QtDebug"
#include "QTimer"


teksturi::teksturi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::teksturi)
{
    ui->setupUi(this);
    ui->tiedostoLista->clear();

    QTimer *muutosAjastin = new QTimer(this);
    muutosAjastin->setSingleShot(true);
    connect(muutosAjastin, &QTimer::timeout, this, &teksturi::muutosListaaja);

    TiedostoOhjain testi = TiedostoOhjain("testi yksi","File alavalikon alla olevat jutut toimii, muita ei ole vielä toteutettu");
    TiedostoOhjain kaksi = TiedostoOhjain("testi kaksi","testi2");
    TiedostoOhjain kolme = TiedostoOhjain("testi kolme","testi3");

    avoimetTiedostot = {testi,kaksi,kolme};
    updatetiedostoLista();

    connect(ui->tiedostoLista, &QListWidget::itemSelectionChanged, this, [=](){
        //qDebug()<< ui->tiedostoLista->currentItem()->text();
        ui->teksti->setText(avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto);
    });
    connect(ui->teksti, &QTextEdit::textChanged, this, [=](){
        muutosAjastin->start(750);
    });
    ui->tiedostoLista->setCurrentRow(0);

}

teksturi::~teksturi()
{
    delete ui;
}


void teksturi::on_actionSave_triggered()
{
    TiedostoOhjain haku = avoimetTiedostot[ui->tiedostoLista->currentRow()];
    haku.tiedostoSisalto = ui->teksti->toPlainText();
    if (QFileInfo::exists(haku.tiedostoNimi)){
        //qDebug()<< ui->tiedostoLista->currentItem()->text()+" + OLEMASSA + " +haku.tiedostoSisalto;
        QFile file(haku.tiedostoNimi);
        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            QTextStream stream(&file);
            stream << haku.tiedostoSisalto;

        }}

    else{
        //qDebug() << "ei ole";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                     "/home/untitled.txt",
                                     tr("Text files (*.txt);;"));
            QFile file(fileName);
            if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&file);
                avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoNimi = fileName;
                stream << haku.tiedostoSisalto;
                updatetiedostoLista();
            }
    }
}



void teksturi::on_actionfont_size_triggered()
{

}


void teksturi::on_actionLoad_triggered()
{
    QString sis {};
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "",
                                                      tr("Text files (*.txt);;"));
    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            sis += line;
        }
    TiedostoOhjain lataus = TiedostoOhjain(fileName, sis);
    avoimetTiedostot.append(lataus);
    ui->tiedostoLista->addItem(avoimetTiedostot.last().tiedostoNimi);
    ui->tiedostoLista->setCurrentItem(ui->tiedostoLista->item(avoimetTiedostot.count()-1));
}

void teksturi::on_actionNew_File_triggered()
{
    TiedostoOhjain uusi = TiedostoOhjain("nimetön","");
    avoimetTiedostot.append(uusi);
    ui->tiedostoLista->addItem(avoimetTiedostot.last().tiedostoNimi);
    ui->tiedostoLista->setCurrentItem(ui->tiedostoLista->item(avoimetTiedostot.count()-1));
}

void teksturi::on_actionClose_file_triggered()
{
    if(avoimetTiedostot.count() < 2){
        //qDebug()<<"vika";
        QApplication::quit();
        return;
    }
    avoimetTiedostot.removeAt(ui->tiedostoLista->currentRow());
    updatetiedostoLista();
    ui->tiedostoLista->setCurrentRow(0);

}


void teksturi::on_actionQuit_triggered()
{
    QApplication::quit();
}

void teksturi::updatetiedostoLista(){
    ui->tiedostoLista->clear();
    for(int i = 0; i <avoimetTiedostot.length(); i++){
        ui->tiedostoLista->addItem(avoimetTiedostot[i].tiedostoNimi);
    }
}
void teksturi::muutosListaaja(){
    int pituus = avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto.count();
    QString muutos;
    if( ui->teksti->toPlainText().count()-pituus > 0){
        muutos = ui->teksti->toPlainText().sliced(pituus);
    }
    else {
        muutos = avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto.sliced(ui->teksti->toPlainText().count());
    }
    muutosRakenne annettava(muutos,true);
    if(muutos.count() > 0){
        avoimetTiedostot[ui->tiedostoLista->currentRow()].muutosLista.append(annettava);
        avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto = ui->teksti->toPlainText();
    }
}

void teksturi::on_actionundo_triggered()
{
    for(int i=0; i < avoimetTiedostot[ui->tiedostoLista->currentRow()].muutosLista.count();i++){
        qDebug() << avoimetTiedostot[ui->tiedostoLista->currentRow()].muutosLista[i].muutos;
    }

}

