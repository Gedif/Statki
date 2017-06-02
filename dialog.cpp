#include "Dialog.h"
#include "ui_Dialog.h"
#include "Game.h"

extern Game* game;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog){
    ui->setupUi(this);
}

Dialog::~Dialog(){
    delete ui;
}

QString Dialog::getIpAdress(){
    return ipAdress;
}

QString Dialog::getPort(){
    return port;
}

bool Dialog::getPickedKlient(){
    return pickedKlient;
}

void Dialog::on_pushButton_clicked(){
    ipAdress = ui->lineEdit->text();
    port = ui->lineEdit_2->text();
    if (ui->radioButton->isChecked()){
        pickedKlient = true;
    }
        else{
        pickedKlient = false;
        }
    game-> start();
    close();
}


