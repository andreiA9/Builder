#ifndef PRJ_MENU_H
#define PRJ_MENU_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------

class PrjMenu
{
public:
    // Displays menu and gets the user selection.
    int displayMenuAndGetSelection();

    // Executes an action based on user selection.
    void displayAction(int selection);
};

#endif // PRJ_MENU_H
