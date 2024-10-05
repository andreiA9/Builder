#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    using QLabel::QLabel; // Inherit constructors

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit clicked();
        }
    }
};

#endif // CLICKABLE_LABEL_H
