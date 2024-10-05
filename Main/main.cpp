// local project headers
// ----------------------
#include "ApplicationWindow.h"

// standard C/C++ headers
// ----------------------
#include <QApplication>
#include <QDebug>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    ApplicationWindow window;
    window.show();

    return app.exec();
}
