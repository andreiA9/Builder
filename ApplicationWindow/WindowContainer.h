#ifndef WindowContainer_H
#define WindowContainer_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeView>
#include <QStackedWidget>

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
    // main layout
    QGridLayout* m_mainLayout;

    // upper widgets
    QLineEdit* m_gccComandEdit;
    QLabel* m_commandLabel;

    // upper buttons
    QHBoxLayout* m_buttonLayout;
    QPushButton* m_compileButton0;
    QPushButton* m_linkButton1;
    QPushButton* m_buildButton2;
    QPushButton* m_upperButton3;
    QPushButton* m_upperButton4;

    // bottom grid layout
    QGridLayout* m_bottomGridWithoutSpacing;

    // bottom output board and tree view
    QTreeView* m_filesTreeView;
    QTreeView* m_projectTreeView;

    // file tabs from here
    QHBoxLayout* m_tabsLayout;
    QVector<QLabel*> m_tabVector;
};
#endif // WindowContainer_H
