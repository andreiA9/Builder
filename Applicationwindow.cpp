#include "Applicationwindow.h"


ApplicationWindow::ApplicationWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Builder"));
    QWidget::resize(800, 600);

    QGridLayout *m_mainLayout = new QGridLayout(this);
    m_mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_label = new QLabel(this);
    m_label->setGeometry(10, 10, 70, 30);
    m_label->setFrameStyle(QFrame::Panel);
    m_label->setText("Command:");
    m_label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    m_mainLayout->addWidget(m_label, 0, 0, 1, 1);

    m_gccComandEdit = new QLineEdit(this);
    m_gccComandEdit->setGeometry(90, 10, 227, 30);
    m_gccComandEdit->setPlaceholderText("Placeholder Text");
    m_mainLayout->addWidget(m_gccComandEdit, 0, 1, 1, 7);

    QTableView *m_outputBoard = new QTableView(this);
    m_outputBoard->setGeometry(10, 40, 781, 20);
    m_outputBoard->setObjectName(QString::fromUtf8("canView"));
    m_outputBoard->setStyleSheet(QString::fromUtf8(""));
    m_outputBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_outputBoard->horizontalHeader()->setStretchLastSection(true);
    m_outputBoard->verticalHeader()->setDefaultSectionSize(22);

    m_mainLayout->addWidget(m_outputBoard, 1, 0, 3, 8);
    QWidget::setLayout(m_mainLayout);

    initializeConnects();
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::initializeConnects()
{
    connect(m_gccComandEdit, &QLineEdit::textEdited, this, &ApplicationWindow::interpretCommand);
}

void ApplicationWindow::interpretCommand()
{
    ::system("gcc -Wunused .\\Resources\\0-unused-variable.c > output.txt");
    ::system("gcc -Wall -o hello.o  .\\Resources\\1-hello.c");
}
