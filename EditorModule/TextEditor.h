#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QString>

// !!!!
// THIS contains the QTextEdit where the source file is loaded
class TextEditor
{
public:
    int currentLine() const {};
    int currentColumn() const {};
    void gotoLine(int line, int column = 0);

    /*! Returns the amount of visible columns (in characters) in the editor */
    int columnCount() const {};

    /*! Returns the amount of visible lines (in characters) in the editor */
    int rowCount() const {};

    QString selectedText() const {};

    /*! Removes \a length characters to the right of the cursor. */
    virtual void remove(int length) {};
    /*! Inserts the given string to the right of the cursor. */
    virtual void insert(const QString &string) {};
    /*! Replaces \a length characters to the right of the cursor with the given string. */
    virtual void replace(int length, const QString &string) {};
    /*! Sets current cursor position to \a pos. */
    virtual void setCursorPosition(int pos) {};
    /*! Selects text between current cursor position and \a toPos. */
    virtual void select(int toPos) {};
};

#endif // TEXT_EDITOR_H
