#include "WindowContainer.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>

WindowContainer::WindowContainer(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Builder"));
    QWidget::resize(1600, 800);

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(m_mainLayout);
}

WindowContainer::~WindowContainer()
{
}

void WindowContainer::initializeComandEdit()
{
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
}

void WindowContainer::initializeControlButtons()
{
    m_compileButton0 = new QPushButton(this);
    m_linkButton1 = new QPushButton(this);
    m_buildButton2 = new QPushButton(this);
    m_upperButton3 = new QPushButton(this);
    m_upperButton4 = new QPushButton(this);

    m_compileButton0->setObjectName(QString("pushButton0"));
    m_compileButton0->setText("Compile");
    m_compileButton0->setGeometry(QRect(20, 30, 40, 25));

    m_linkButton1->setObjectName(QString("pushButton1"));
    m_linkButton1->setText("Link");
    m_linkButton1->setGeometry(QRect(110, 30, 40, 25));

    m_buildButton2->setObjectName(QString("pushButton2"));
    m_buildButton2->setText("Build");
    m_buildButton2->setGeometry(QRect(200, 30, 40, 25));

    m_upperButton3->setObjectName(QString("pushButton3"));
    m_upperButton3->setText("Button3");
    m_upperButton3->setGeometry(QRect(290, 30, 40, 25));

    m_upperButton4->setObjectName(QString("pushButton4"));
    m_upperButton4->setText("Button4");
    m_upperButton4->setGeometry(QRect(380, 30, 40, 25));

    // addLayout(QLayout * layout, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = 0)
    m_buttonLayout = new QHBoxLayout();
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addLayout(m_buttonLayout, 1, 0, 1, 8);

    m_buttonLayout->setObjectName(QString("verticalLayout"));
    m_buttonLayout->addWidget(m_compileButton0);
    m_buttonLayout->addWidget(m_linkButton1);
    m_buttonLayout->addWidget(m_buildButton2);
    m_buttonLayout->addWidget(m_upperButton3);
    m_buttonLayout->addWidget(m_upperButton4);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // AI RAMAS
    // 1. SPACING ul nu iti merge
    // 2. trebuie sa faci SIZE POLICY = EXPANDING pentru QIMAGE = DrawingView
    m_buttonLayout->setSpacing(20);
}

void WindowContainer::initializeBottomGrid()
{
    m_bottomGridWithoutSpacing = new QGridLayout(this);
    m_bottomGridWithoutSpacing->setObjectName(QString::fromUtf8("verticalLayout"));
    m_bottomGridWithoutSpacing->setContentsMargins(0, 0, 0, 0);
    m_bottomGridWithoutSpacing->setSpacing(0);

    m_tabsLayout = new QHBoxLayout(this);
    m_tabsLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    m_tabsLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *tab0 = new QPushButton(this);
    tab0->setObjectName(QString("Tab0"));
    tab0->setText("Untitled");
    tab0->setGeometry(QRect(20, 10, 80, 25));
    m_tabsLayout->addWidget(tab0);
    m_tabVector.append(tab0);

    m_mainLayout->addLayout(m_bottomGridWithoutSpacing, 2, 0, 6, 8);
    m_bottomGridWithoutSpacing->addLayout(m_tabsLayout, 0, 0, 1, 8);
}

void WindowContainer::initializeOutputBoardAndTreeView(QStackedWidget* stackedWorkArea)
{
    const QString resourcesPath = QDir::currentPath() + "/Resources";
    // create the file system model
    QFileSystemModel *model = new QFileSystemModel(this);
    qDebug() << "QDir::currentPath(): " << QDir::currentPath();
    model->setRootPath(resourcesPath);
    model->setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
    QStringList filter;
    filter << "*.c";
    filter << "*.h";
    filter << "*.cpp";
    model->setNameFilters(filter);

    // create the tree view associated to that model
    m_filesTreeView = new QTreeView(this);
    m_filesTreeView->setModel(model);
    m_filesTreeView->setRootIndex(model->index(resourcesPath));
    m_filesTreeView->setGeometry(0, 0, 781, 300);
    // SET SIZE POLICY
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(6);
    sizePolicy.setHeightForWidth(m_filesTreeView->sizePolicy().hasHeightForWidth());
    m_filesTreeView->setSizePolicy(sizePolicy);
    m_bottomGridWithoutSpacing->addWidget(m_filesTreeView, 1, 0, 7, 3);

    // create the board for build output
    m_outputTextEdit = new QTextEdit(this);
    m_outputTextEdit->setObjectName(QString::fromUtf8("textEdit"));
    m_outputTextEdit->setGeometry(QRect(20, 10, 80, 25));
    // SET SIZE POLICY
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(6);
    sizePolicy1.setVerticalStretch(6);
    sizePolicy1.setHeightForWidth(m_outputTextEdit->sizePolicy().hasHeightForWidth());
    m_outputTextEdit->setSizePolicy(sizePolicy1);
    m_bottomGridWithoutSpacing->addWidget(m_outputTextEdit, 1, 3, 7, 5);
}
