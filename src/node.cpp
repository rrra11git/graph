#include <QtGui>

//#include "link.h"
#include "node.h"

Node::Node()
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
//    myBackgroundColor = Qt::white;
    myBackgroundColor = Qt::transparent;

    setFlags(ItemIsMovable | ItemIsSelectable);
}

Node::~Node()
{
//    foreach (Link *link, myLinks)
//        delete link;
}

void Node::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

QString Node::text() const
{
    return myText;
}

void Node::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor Node::textColor() const
{
    return myTextColor;
}

void Node::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor Node::outlineColor() const
{
    return myOutlineColor;
}

void Node::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor Node::backgroundColor() const
{
    return myBackgroundColor;
}

void Node::addLink(Link *link)
{
    myLinks.insert(link);
}

void Node::removeLink(Link *link)
{
    myLinks.remove(link);
}

QRectF Node::boundingRect() const
{
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()),
                      roundness(rect.height()));
    return path;
}

void Node::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
 //   QPen pen(Qt::red);

    if (option->state & QStyle::State_Selected) {
	QPen pen_tmp(Qt::red);
	pen=pen_tmp;
        pen.setStyle(Qt::DotLine);
        pen.setWidth(1);//2
 //       pen.setStyle(Qt::DotLine);
 //       pen.setWidth(1);//2



    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);

    QRectF rect = outlineRect();
//    painter->drawRoundRect(rect, roundness(rect.width()), roundness(rect.height()));
    painter->drawRoundRect(rect, 0,0);

    painter->setPen(myTextColor);
    painter->drawText(rect, Qt::AlignCenter, myText);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(event->widget(),
                           tr("Edit Text"), tr("Enter new text:"),
                           QLineEdit::Normal, myText);
    if (!text.isEmpty())
        setText(text);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
/*
    if (change == ItemPositionHasChanged) {
        foreach (Link *link, myLinks)
            link->trackNodes();
    }
*/
    return QGraphicsItem::itemChange(change, value);
}

QRectF Node::outlineRect() const
{
    const int Padding = 8;//8
    QFontMetricsF metrics = qApp->font();
    QRectF rect = metrics.boundingRect(myText);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}

int Node::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}
