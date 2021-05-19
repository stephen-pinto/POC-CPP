#include "linenumberarea.h"

LineNumberArea::LineNumberArea(CodeEdit *parent) : QWidget(parent)
{
    parentEditor = parent;
}

LineNumberArea::~LineNumberArea()
{

}

QSize LineNumberArea::sizeHint() const
{
    return QSize(parentEditor->lineNumMarginWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    parentEditor->lineNumMarginPaintEvent(event);
}
