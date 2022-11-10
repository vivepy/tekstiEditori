#include "teksturi.h"
#include "./ui_teksturi.h"
#include "QSizePolicy"
#include "QtDebug"

teksturi::teksturi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::teksturi)
{
    ui->setupUi(this);
    ui->tiedostoLista->clear();
    TiedostoOhjain testi = TiedostoOhjain("testi yksi","testi1");
    TiedostoOhjain kaksi = TiedostoOhjain("testi kaksi","testi2");
    TiedostoOhjain kolme = TiedostoOhjain("testi kolme","testi3");

    avoimetTiedostot = {testi,kaksi,kolme};
    updatetiedostoLista();
    connect(ui->tiedostoLista, &QListWidget::itemSelectionChanged, this, [=](){
        //qDebug()<< ui->tiedostoLista->currentItem()->text();
        ui->teksti->setText(avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto);
    });
    connect(ui->teksti, &QTextEdit::textChanged, this, [=](){
        avoimetTiedostot[ui->tiedostoLista->currentRow()].tiedostoSisalto = ui->teksti->toPlainText();
    });
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
        QApplication::quit();
    }
    avoimetTiedostot.removeAt(ui->tiedostoLista->currentRow());
    ui->tiedostoLista->setCurrentRow(0);
    updatetiedostoLista();
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
