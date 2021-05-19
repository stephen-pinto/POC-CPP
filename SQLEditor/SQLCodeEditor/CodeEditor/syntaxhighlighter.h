#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QTextCharFormat>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

class QTextDocument;

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SyntaxHighlighter(QTextDocument *document);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    void setRule(QRegularExpression matchExprn, QBrush brushForeground);
    void setRule(QRegularExpression matchExprn, QBrush brushForeground, QFont font);

    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    //QTextCharFormat keywordFormat;
    //QTextCharFormat classFormat;
    //QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    //QTextCharFormat quotationFormat;
    //QTextCharFormat functionFormat;

    void addDefualtRules();
};

#endif // SYNTAXHIGHLIGHTER_H
