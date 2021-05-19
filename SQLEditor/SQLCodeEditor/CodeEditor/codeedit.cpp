#include "codeedit.h"
#include "linenumberarea.h"
#include <QPainter>
#include <QTextBlock>
#include <QApplication>

CodeEdit::CodeEdit(QWidget *parent)
{
    this->m_Parent = parent;
    this->setParent(parent);

    m_LineNumberMargin = new LineNumberArea(this);

    connectSignalsToSlots();
    updateLineNumMarginWidth(0);
    highlightCurrentLine();

    setDefaultFontProperties();

    QFont tempFont = font();
    highlighter = new SyntaxHighlighter(document());
}

void CodeEdit::setDefaultFontProperties()
{
    QFont newFont;
    newFont.setFamily("Source code pro");
    newFont.setPointSize(11);
    setFont(newFont);
}

void CodeEdit::setFontPointSize(int size)
{
    auto curr_font = font();
    curr_font.setPointSize(size);
    setFont(curr_font);
}

void CodeEdit::connectSignalsToSlots()
{
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumMarginWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumMargin(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

void CodeEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    m_LineNumberMargin->setGeometry(QRect(cr.left(), cr.top(), lineNumMarginWidth(), cr.height()));
}

void CodeEdit::updateLineNumMarginWidth(int)
{
    setViewportMargins(lineNumMarginWidth(), 0, 0, 0);
}

int  CodeEdit::lineNumMarginWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());

    //Find number of digits in line max
    while(max >= 10)
    {
        max /= 10;
        digits++;
    }

    //For margin
    digits += 2;

    //Find exact space needed based on font currently applied here
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEdit::updateLineNumMargin(const QRect &rect, int dy)
{
    if(dy)
        m_LineNumberMargin->scroll(0, dy);
    else
        m_LineNumberMargin->update(0, rect.y(), m_LineNumberMargin->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumMarginWidth(0);
}

void CodeEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> lineSelections;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selectn;
        QColor lineColor = QColor(Qt::yellow).lighter(180);

        selectn.format.setBackground(lineColor);
        selectn.format.setProperty(QTextFormat::FullWidthSelection, true);
        selectn.cursor = textCursor();
        selectn.cursor.clearSelection();
        lineSelections.append(selectn);
    }

    setExtraSelections(lineSelections);

    //Repaint to apply changes for line number margin
    repaint();
}

void CodeEdit::lineNumMarginPaintEvent(QPaintEvent *event)
{
    //Get necessary co-ordinates
    QTextBlock textBlock = firstVisibleBlock();
    int blockNum = textBlock.blockNumber();
    int pointX   = (int)blockBoundingGeometry(textBlock).translated(contentOffset()).top();
    int pointY   = pointX + (int) blockBoundingRect(textBlock).height();

    //Prepare painter for line number margin
    QPainter painter(m_LineNumberMargin);

    //Fill line number margin
    painter.fillRect(event->rect(), QColor(Qt::lightGray).lighter(110));

    //Make current line rectangle a bit darker
    painter.fillRect(0, blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top(),
                     m_LineNumberMargin->width(), fontMetrics().height(), QColor(Qt::gray).darker(100));

    //Set painter's pen to black for upcoming draws
    painter.setPen(Qt::black);

    //Fill all edited lines with appropriate line numbers
    while(textBlock.isValid() && textBlock.isVisible() && pointX <= event->rect().bottom())
    {
        if(textBlock.isVisible() && pointY >= event->rect().top())
        {
            painter.drawText(0, pointX, m_LineNumberMargin->width(),
                             fontMetrics().height(), Qt::AlignCenter,
                             QString::number(blockNum + 1));
        }

        //Move on to next position in block
        textBlock = textBlock.next();
        pointX = pointY;
        pointY = pointX + (int)blockBoundingRect(textBlock).height();
        ++blockNum;
    }
}

