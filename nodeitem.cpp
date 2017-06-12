#include "nodeitem.h"

NodeItem::NodeItem(const QString &name,
                   QGraphicsItem *parent) :
    QGraphicsItem(parent),
    _name(name) {
    this->setPos(qrand() % 640 - 320,
                 qrand() % 640 - 320);
    _rect  = QRectF(-_radius, -_radius,
                    2*_radius, 2*_radius);
    _color = QColor(qrand() % 256,
                    qrand() % 256,
                    qrand() % 256);
}

NodeItem::~NodeItem() {}

QRectF NodeItem::boundingRect() const {
    return _rect;
}

void NodeItem::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
    painter->setBrush(_color);
    painter->drawEllipse(_rect);
    painter->drawText(10, 10, _name);
}

void NodeItem::advance(int phase) {
    if (phase == 0) {

    } else {
        update();
    }
}
