// local project headers
// ----------------------
#include "BuildMenu.h"

// standard C/C++ headers
// ----------------------
#include <QTextStream>

int BuildMenu::displayMenuAndGetSelection()
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    QString line;
    
    while (true)
    {
        qout << "\nPlease select an option:\n";
        qout << "1. Compile file\n";
        qout << "2. Recompile file if modified\n";
        qout << "3. Build folder\n";
        qout << "4. Create library\n";
        qout << "5. Build with makefile\n";
        qout << "0. Exit\n";
        qout << "Enter your choice and press return: ";
        qout.flush();
        
        line = qin.readLine();
        bool ok;
        int selection = line.toInt(&ok);

        if (ok
                && selection >= 0 && selection < 5)
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

void BuildMenu::displayAction(int selection)
{
    // Placeholder function for executing actions.
    // This would interact with the GccHelper or similar classes/methods
    // to perform the actual work based on the user's selection.
    QTextStream qout(stdout);
    switch (selection)
    {
        case 1: // Compile
            qout << "Compiling file...\n";
            break;
        case 2: // Recompile if modified
            qout << "Recompiling file...\n";
            break;
        case 3: // Build executable
            qout << "Building folder...\n";
            break;
        case 4: // Create library
            qout << "Generating library from folder...\n";
            break;
        case 5: // Create library
            qout << "Building with makefile...\n";
            break;
        default:
            // Handle invalid selection
            break;
    }
    qout.flush();
}
