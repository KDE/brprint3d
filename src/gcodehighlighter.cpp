#include "gcodehighlighter.h"

GCodeHighLighter::GCodeHighLighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    setForegrounds();
    setRules();
}

void GCodeHighLighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    //I'm not sure what this do... copy from example
    //http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-highlighter-cpp.html
    setCurrentBlockState(0);
}

void GCodeHighLighter::setRules()
{
    HighlightingRule rule;
    /*M + value*/
    rule.format = mCommands;
    rule.pattern = QRegExp("\\bM(\\d+)\\b");
    highlightingRules.append(rule);
    /*G + value*/
    rule.format = gCommands;
    rule.pattern = QRegExp("\\bG(\\d+)\\b");
    highlightingRules.append(rule);
    /*X | Y | Z*/
    rule.format = xyzCommands;
    rule.pattern = QRegExp("\\bX|Y|Z\\b");
    highlightingRules.append(rule);
    /*F*/
    rule.format = fCommands;
    rule.pattern = QRegExp("\\bF.+\\b");
    highlightingRules.append(rule);
    /*E*/
    rule.format = eCommands;
    rule.pattern = QRegExp("\\bE.+\\b");
    highlightingRules.append(rule);
    /*comments*/
    rule.format = comments;
    rule.pattern = QRegExp("\\b;.+\\b");
    highlightingRules.append(rule);
    /*Numbers*/
    rule.format = numbers;
    rule.pattern = QRegExp("\\(\\d+.\\d+)\\b");
    highlightingRules.append(rule);
}

void GCodeHighLighter::setForegrounds()
{
    gCommands.setForeground(Qt::darkCyan);
    mCommands.setForeground(Qt::magenta);
    fCommands.setForeground(Qt::yellow);
    eCommands.setForeground(Qt::red);
    comments.setForeground(Qt::darkGreen);
    numbers.setForeground(Qt::darkRed);
}
