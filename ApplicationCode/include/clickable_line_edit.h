// Author : Filip Dymczyk
// Description : Clickable LineEdit class extending QLineEdit.

#pragma once

#include <QtWidgets/QLineEdit>
#include <QtGui/QMouseEvent>

class ClickableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ClickableLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}

Q_SIGNALS:
    void 
    clicked();

protected:
    void 
    mousePressEvent(QMouseEvent* event) override 
    {
        Q_EMIT clicked();
        QLineEdit::mousePressEvent(event);
    }
};