#include "syntaxhighlighter.h"
#include <QTextDocument>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *document) : QSyntaxHighlighter(document)
{
    addDefualtRules();    
}

void SyntaxHighlighter::addDefualtRules()
{

    HighlightingRule rule;
    QFont boldFont(this->document()->defaultFont());
    boldFont.setBold(true);

    QStringList keywordPatterns;

    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";

    foreach (const QString &pattern, keywordPatterns)
        setRule(QRegularExpression(pattern), QColor(0, 0, 255), boldFont);

    multiLineCommentFormat.setForeground(Qt::red);

    setRule(QRegularExpression("\\bQ[A-Za-z]+\\b"), QColor(139,0,139), boldFont); //classes
    setRule(QRegularExpression("//[^\n]*"), QColor(255, 0, 0)); //single line comments
    setRule(QRegularExpression("\".*\""), QColor(0, 100, 0));   //quotes
    setRule(QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()"), QColor(0, 0, 255)); //functions

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void SyntaxHighlighter::setRule(QRegularExpression matchExprn, QBrush brushForeground)
{
    static HighlightingRule rule;
    QTextCharFormat format;

    format.setForeground(brushForeground);
    rule.format = format;

    //Set match expression for the rule
    rule.pattern = matchExprn;

    //Add new rule
    highlightingRules.append(rule);
}

void SyntaxHighlighter::setRule(QRegularExpression matchExprn, QBrush brushForeground, QFont font)
{
    static HighlightingRule rule;
    QTextCharFormat format;

    format.setFontWeight(font.weight());
    format.setFontItalic(font.italic());
    format.setFontCapitalization(font.capitalization());
    format.setFontOverline(font.overline());
    format.setFontUnderline(font.underline());
    format.setFontLetterSpacing(font.letterSpacing());
    format.setFontWordSpacing(font.wordSpacing());
    format.setFontStretch(font.stretch());
    format.setFontStrikeOut(font.strikeOut());

    format.setForeground(brushForeground);
    rule.format = format;

    //Set match expression for the rule
    rule.pattern = matchExprn;

    //Add new rule
    highlightingRules.append(rule);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0)
    {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
