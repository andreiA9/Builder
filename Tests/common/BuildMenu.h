#ifndef BUILD_MENU_H
#define BUILD_MENU_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------

class BuildMenu
{
public:
    // Displays menu and gets the user selection.
    int displayMenuAndGetSelection();

    // Executes an action based on user selection.
    void displayAction(int selection);
};

#endif // BUILD_MENU_H
