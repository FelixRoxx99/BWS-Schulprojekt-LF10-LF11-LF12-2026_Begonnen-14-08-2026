#include "statusdelegate.h"
#include <QPainter>
#include <QApplication>

void StatusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString status = index.data().toString();
    QColor color = Qt::gray;
    if(status.contains("Verfügbar", Qt::CaseInsensitive)) color = QColor("#2ecc71");
    else if(status.contains("Ausgeliehen", Qt::CaseInsensitive)) color = QColor("#f39c12");
    else if(status.contains("Defekt", Qt::CaseInsensitive)) color = QColor("#e74c3c");

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QRect r = option.rect.adjusted(6, 6, -6, -6);
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(r, 8, 8);
    painter->setPen(Qt::white);
    painter->drawText(r, Qt::AlignCenter, status);
    painter->restore();
}
