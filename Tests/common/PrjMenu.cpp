// local project headers
// ----------------------
#include "PrjMenu.h"

// standard C/C++ headers
// ----------------------
#include <QTextStream>

int PrjMenu::displayMenuAndGetSelection()
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    QString line;

    while (true)
    {
        qout << "\nPlease select an option:\n";
        qout << "1. Parse project prj\n";
        qout << "2. Parse binary prj\n";
        qout << "3. Parse library prj\n";
        qout << "4. Parse subdirs prj\n";
        qout << "5. Recompile if modified\n";
        qout << "0. Exit\n";
        qout << "Enter your choice and press return: ";
        qout.flush();

        line = qin.readLine();
        bool ok;
        int selection = line.toInt(&ok);

        if (ok
                && selection >= 0 && selection < 6)
        {
            return selection; // Valid choice, return it.
        }
        else
        {
            qout << "Invalid choice, please try again.\n";
            qout.flush();
        }
    }
}

void PrjMenu::displayAction(int selection)
{
    // Placeholder function for executing actions.
    // This would interact with the GccHelper or similar classes/methods
    // to perform the actual work based on the user's selection.
    QTextStream qout(stdout);
    switch (selection)
    {
        case 1: // Compile
            qout << "Parsing project prj...\n";
            break;
        case 2: // Recompile if modified
            qout << "Parsing binary prj...\n";
            break;
        case 3: // Build executable
            qout << "Parsing library prj...\n";
            break;
        case 4: // Create library
            qout << "Parsing subdirs prj...\n";
            break;
        case 5: // Create library
            qout << "Recompiling sources...\n";
            break;
        default:
            // Handle invalid selection
            break;
    }
    qout.flush();
}
