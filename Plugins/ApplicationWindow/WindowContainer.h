#ifndef WINDOW_CONTAINER_H
#define WINDOW_CONTAINER_H

// local project headers
// ----------------------
#include "EditView.h"
#include "CompileView.h"
#include "ClickableLabel.h"

// standard C/C++ headers
// ----------------------
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

class WindowContainer : public QWidget
{
    Q_OBJECT

public:

    explicit WindowContainer(QWidget* parent = nullptr);

protected:
    void initializeComandEdit();

    void initializeControlButtons();

    void initializeWorkArea();

    void initializeProjectTabs();

protected:
    // Main grid
    QGridLayout* m_mainGridLayout;

    // Project tabs
    QVBoxLayout* m_projectTabLayout;
    ClickableLabel* m_editProjectTab;
    ClickableLabel* m_compileProjectTab;

    // Gcc command line edit
    QLabel* m_commandLabel;
    QLineEdit* m_gccComandEdit;
    QHBoxLayout* m_commandLayout;

    // Control buttons
    QHBoxLayout* m_controlButtonsLayout;
    QPushButton* m_functionButton0;
    QPushButton* m_functionButton1;
    QPushButton* m_functionButton2;
    QPushButton* m_functionButton3;
    QPushButton* m_functionButton4;

    // Bottom work area
    QGridLayout* m_workAreaLayout;
    QStackedWidget* m_stackedWorkArea;

    // Edit and Compile subwidgets
    EditView* m_editView;
    CompileView* m_compileView;
};

#endif // WINDOW_CONTAINER_H
