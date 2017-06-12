#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

/**
 * @brief Klasa button.
 *
 * Klasa odpowiada za utworzenie objektu przycisku dziedziczącego po QObjekt i QGraphicsRectItem.
 * Obiekt ten posiada zdolność reagowania na QGraphicsSceneMouseEvent.
 */
class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy button
     *
     * Stworzony obiekt posiada teks na nim wyświtlany, miejsce w przestrzeni i rozmiary przycisku
     * @param name Argument ten to napis wyświetlany na przycisku.
     *
     */
    Button(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
    void doubleClicked();
private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
