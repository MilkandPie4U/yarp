/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * LGPLv2.1+ license. See the accompanying LICENSE file for details.
 */

#ifndef SOURCEPORTITEM_H
#define SOURCEPORTITEM_H


#include <QObject>
#include <QPainter>
#include <QGraphicsPolygonItem>

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "commons.h"
#include "arrow.h"
#include "itemsignalhandler.h"
#include "builderitem.h"

class ItemSignalHandler;
class Arrow;

class SourcePortItem : public BuilderItem
{
    friend class Arrow;
public:
    SourcePortItem(QString itemName, bool nestedInApp = false,
                   bool editOnStart = false, Application *app = NULL,BuilderItem * parent = 0);
    ~SourcePortItem();
    QRectF boundingRect() const override;
    QPointF connectionPoint() override;
    int type() const override;
    void setAvailable(bool);
    void editingFinished();
    bool isErrorState();

private:
    void updateConnectionsFrom(QString from);

private:
    Application *app;
    BuilderItem *parent;
    bool portAvailable;
    QGraphicsProxyWidget *lineEditWidget;
    bool errorState;

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

};

#endif // SOURCEPORTITEM_H
