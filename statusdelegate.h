#pragma once

#include <QStyledItemDelegate>

class StatusDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit StatusDelegate(QObject *parent=nullptr): QStyledItemDelegate(parent){}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
