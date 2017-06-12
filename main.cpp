#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector2D>
#include <QFile>
#include <QHash>
#include "nodeitem.h"

static const QString __defaultFileName = ":/test/test_001.txt";

using Nodes = QList<QString>;
using Graph = QHash<QString, Nodes>;

int main(int argc, char *argv[])
{
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
    QApplication a(argc, argv);
    QString fn(__defaultFileName);
    if (argc == 2) {
        const char *t = argv[1];
        fn = QString(t);
    }

    Graph g;
    QFile f(fn);
    if (!f.open(QIODevice::ReadOnly)) {
        return -1;
    }
    while (!f.atEnd()) {
        QString line = QString(f.readLine());
        line = line.simplified();
        QStringList parts = line.split(" ");
        if (parts.size() >= 2) {
            QString first  = parts[0];
            QString second = parts[1];
            g[first].push_back(second);
        } else {} // ignore
    }

    QSet<QString> l;
    const QList<QString> &keys = g.keys();
    for (auto it = keys.begin();
         it != keys.end();
         ++it) {
        for (auto i = g[*it].begin();
             i != g[*it].end();
             ++i) {
            if (!l.contains(*i)) {
                l.insert(*i);
            }
        }
        if (!l.contains(*it)) {
            l.insert(*it);
        }
    }

    QGraphicsScene *scene = new QGraphicsScene();

    QHash<QString, NodeItem*> items;
    for (auto it = l.begin();
         it != l.end();
         ++it) {
        NodeItem *t = new NodeItem(*it);
        items[*it] = t;
        scene->addItem(t);
    }

    for (auto it = keys.begin();
         it != keys.end();
         ++it) {
        QPointF ptStart = items[*it]->pos();
        for (auto i = g[*it].begin();
             i != g[*it].end();
             ++i) {
            QPointF ptEnd = items[*i]->pos();
            qreal r = items[*i]->radius();
            QVector2D v = QVector2D(ptEnd) -
                          QVector2D(ptStart);
            QVector2D ov = v.normalized();
            QVector2D on(v.y(), -v.x());
            on.normalize();
            QPointF s = ptStart +
                    (ov * r).toPointF();
            QPointF e = ptEnd -
                    (ov * r).toPointF();
            QPointF p1 = e +
                    (- ov * 9 + on * 3).toPointF();
            QPointF p2 = e +
                    (- ov * 9 - on * 3).toPointF();
                    QVector2D(ov.y(), ov.x());
            scene->addLine(QLine(s.toPoint(),
                                 e.toPoint()));
            QPolygonF p;
            p << p1 << p2 << e;
            scene->addPolygon(p, QPen(),
                              QBrush(Qt::SolidPattern));
        }
    }

    QGraphicsView  view;
    view.setScene(scene);
    view.show();

    return a.exec();
}
