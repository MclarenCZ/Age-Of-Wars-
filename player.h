#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>

class Player : public QGraphicsItem
{
public:
    Player();
    QRectF boundingRect() const;
    int speed = 2;

protected:
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int sirka = 20;
    int vyska = 30;
};

#endif // PLAYER_H
