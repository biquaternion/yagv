#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class NodeItem : public QGraphicsItem
{
public:
    explicit NodeItem(const QString &name,
                      QGraphicsItem *parent = 0);
    virtual ~NodeItem() override;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    qreal radius() const { return _radius; }
private:
    virtual void advance(int phase) override;
    QRectF     _rect;
    QColor     _color;
    QString    _name;
    qreal      _radius{5};

};

#endif // NODEITEM_H
