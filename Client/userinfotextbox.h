#pragma once

#include <QTextEdit>

class UserInfoTextBox : public QTextEdit
{
    Q_OBJECT
public:
    explicit UserInfoTextBox(QWidget *parent = 0);

    QSize sizeHint() const;
    
signals:
    
public slots:
    
};
