#ifndef WindowContainer_H
#define WindowContainer_H

// QT
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeView>
#include <QStackedWidget>
#include <QTextEdit>

class WindowContainer : public QWidget
{
    Q_OBJECT

public:
    WindowContainer(QWidget *parent = nullptr);
    ~WindowContainer();

    void initializeComandEdit();

    void initializeControlButtons();

    void initializeBottomGrid();

    void initializeOutputBoardAndTreeView(QStackedWidget* stackedWorkArea);

protected:
    QGridLayout *m_mainLayout;
    QLineEdit * m_gccComandEdit;
    QLabel *m_label;

    // upper buttons
    QHBoxLayout *m_buttonLayout;
    QPushButton* m_compileButton0;
    QPushButton* m_linkButton1;
    QPushButton* m_buildButton2;
    QPushButton* m_upperButton3;
    QPushButton* m_upperButton4;

    // bottom layout
    QGridLayout* m_bottomGridWithoutSpacing;

    // bottom output board and tree view
    QTextEdit* m_outputTextEdit;
    QTreeView* m_filesTreeView;

    // file tabs from here
    QHBoxLayout* m_tabsLayout;
    QVector<QPushButton*> m_tabVector;
};
#endif // WindowContainer_H
