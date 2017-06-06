#include "dialog.h"
#include "ui_Dialog.h"
#include "game.h"

extern Game* game;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog){
    ui->setupUi(this);
}

Dialog::~Dialog(){
    delete ui;
}

bool Dialog::getPickedKlient(){
    return pickedKlient;
}

void Dialog::on_pushButton_clicked(){
    if (ui->radioButton->isChecked()){
        pickedKlient = true;
    }
        else{
        pickedKlient = false;
        }
    game-> start();
    close();
}


