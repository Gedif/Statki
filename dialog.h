#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool getPickedKlient();

private slots:
    void on_pushButton_clicked();


private:
    bool pickedKlient;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
