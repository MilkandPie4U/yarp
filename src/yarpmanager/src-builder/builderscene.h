/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * LGPLv2.1+ license. See the accompanying LICENSE file for details.
 */

#ifndef BUILDERSCENE_H
#define BUILDERSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <yarp/conf/compiler.h>

class CustomView;
class BuilderWindow;

class BuilderScene : public QGraphicsScene
{
    friend class CustomView;
    friend class BuilderWindow;
    Q_OBJECT
public:
    explicit BuilderScene(QObject *parent = 0);


private:
    QGraphicsLineItem *currentLine;
    QPointF startingPoint;
    QGraphicsItem *startConnectionItem;
    QGraphicsItem *endConnectionItem;

protected:
    bool snap;
    bool editingMode;


protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //void wheelEvent(QGraphicsSceneWheelEvent *event) override;

signals:
    void addedApplication(void *app,QPointF);
    void addedModule(void *mod,QPointF);
    void addNewConnection(void *start, void *end);

public slots:
    void snapToGrid(bool snap);
    void onNewConnectionRequested(QPointF, QGraphicsItem *item);
    void onNewConnectionAdded(QPointF, QGraphicsItem *item);
    void onSceneChanged(QList<QRectF> rects);

};

#endif // BUILDERSCENE_H

