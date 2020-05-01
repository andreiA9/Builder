#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

// QT
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>

// USER-DEFINED
#include "GccInterpreter.h"



class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void initializeConnects();
    void interpretCommand();

private:
    QLineEdit * m_gccComandEdit;
    QLabel *m_label;
    GccInterpreter *m_interpreter;
    QTableView *m_outputBoard;
};
#endif // APPLICATIONWINDOW_H
