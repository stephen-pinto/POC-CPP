#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QWidget>
#include <QPlainTextEdit>
#include "syntaxhighlighter.h"

//class QPaintEvent;
//class QResizeEvent;
//class QSize;
//class QWidget;

class CodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEdit(QWidget *parent = 0);

    void setFontPointSize(int size);
    void setDefaultFontProperties();

    void lineNumMarginPaintEvent(QPaintEvent *event);
    int  lineNumMarginWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumMarginWidth(int newBlockCount);
    void updateLineNumMargin(const QRect&, int);
    void highlightCurrentLine();

private:
    void connectSignalsToSlots();

    QWidget *m_Parent;
    QWidget *m_LineNumberMargin;
    SyntaxHighlighter *highlighter;
};

#endif // CODEEDIT_H
