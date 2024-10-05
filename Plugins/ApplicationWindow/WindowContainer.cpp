// local project headers
// ----------------------
#include "WindowContainer.h"

// standard C/C++ headers
// ----------------------

WindowContainer::WindowContainer(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Builder"));
    // DOAR pentru DIMENSIUNEA.asta iti va da BINE
    QWidget::resize(1600, 800);

    m_mainGridLayout = new QGridLayout(this);
    // this will set the margin from html, outside the layout
    m_mainGridLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(m_mainGridLayout);
}

void WindowContainer::initializeComandEdit()
{
    m_commandLabel = new QLabel("Command");
    m_gccComandEdit = new QLineEdit;
    m_gccComandEdit->setPlaceholderText("Enter command here");

    m_commandLayout = new QHBoxLayout;
    m_commandLayout->addWidget(m_commandLabel, 10);
    m_commandLayout->addWidget(m_gccComandEdit, 90);
    // the buttons need to be pushed to the right
    m_commandLayout->setContentsMargins(9, 0, 9, 0);

    m_mainGridLayout->addLayout(m_commandLayout, 0, 0);
    m_mainGridLayout->setRowStretch(0, 1); // Top layout 10% height
}

void WindowContainer::initializeControlButtons()
{
    m_functionButton0 = new QPushButton("Compile");
    m_functionButton1 = new QPushButton("Recompile");
    m_functionButton2 = new QPushButton("Build");
    m_functionButton3 = new QPushButton("Generate lib");
    m_functionButton4 = new QPushButton("Undefined");

    QHBoxLayout* m_controlButtonsLayout = new QHBoxLayout;
    m_controlButtonsLayout->addWidget(m_functionButton0);
    m_controlButtonsLayout->addWidget(m_functionButton1);
    m_controlButtonsLayout->addWidget(m_functionButton2);
    m_controlButtonsLayout->addWidget(m_functionButton3);
    m_controlButtonsLayout->addWidget(m_functionButton4);
    m_controlButtonsLayout->setSpacing(40);
    // the buttons need to be pushed to the right
    m_controlButtonsLayout->setContentsMargins(9, 0, 9, 0);

    m_mainGridLayout->addLayout(m_controlButtonsLayout, 1, 0);
    m_mainGridLayout->setRowStretch(1, 1); // Button layout 10% height
}

void WindowContainer::initializeWorkArea()
{
    m_stackedWorkArea = new QStackedWidget;
    m_stackedWorkArea->addWidget(m_editView);
    m_stackedWorkArea->addWidget(m_compileView);
    m_stackedWorkArea->setCurrentWidget(m_compileView);

    initializeProjectTabs();

    m_workAreaLayout = new QGridLayout;
    m_workAreaLayout->addLayout(m_projectTabLayout, 0, 0); // Added to row 0, column 0
    m_workAreaLayout->addWidget(m_stackedWorkArea, 0, 1); // Added to row 0, column 1

    m_workAreaLayout->setColumnStretch(0, 10); // Tree view gets 30% of width
    m_workAreaLayout->setColumnStretch(1, 90); // Text edit gets 70% of width
    m_workAreaLayout->setSpacing(0);

    m_mainGridLayout->addLayout(m_workAreaLayout, 2, 0);
    m_mainGridLayout->setRowStretch(2, 8); // Assigning stretch factor of 7
}

void WindowContainer::initializeProjectTabs()
{
    m_editProjectTab = new ClickableLabel("Edit");
    m_editProjectTab->setFrameShape(QFrame::Box);
    m_editProjectTab->setStyleSheet("QLabel { background-color: darkgray; color: white }");

    m_compileProjectTab = new ClickableLabel("Compile");
    m_compileProjectTab->setFrameShape(QFrame::Box);
    m_compileProjectTab->setStyleSheet("QLabel { background-color: darkgray; color: white }");

    m_projectTabLayout = new QVBoxLayout;
    m_projectTabLayout->addWidget(m_editProjectTab);
    m_projectTabLayout->addWidget(m_compileProjectTab);
    m_projectTabLayout->setContentsMargins(9, 0, 0, 0);
}
