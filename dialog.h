#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog;
}

/**
 * @brief Klasa dialog.
 *
 * Klasa odpowiada za utworzenie okna dialogowego w celu wybrania chęci połączenia się do gry jako klient albo srever
 *
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    /**
     * @brief Getter wyboru uzyskanego z dialogu
     *
     * Funkcja ta zwraca wartość logiczną true jeśli gracz wybrał klienta i false jeśli wybrał serwer
     *
     */
    bool getPickedKlient();

private slots:
    /**
     * @brief Prywanty slot
     *
     * Zczytuje wartości wybrane na RadioButton-ach i zapisuje co zostało wybrane
     *
     */
    void on_pushButton_clicked();


private:
    bool pickedKlient;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
