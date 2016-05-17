#ifndef GCODEHIGHLIGHTER_H
#define GCODEHIGHLIGHTER_H
#include <QSyntaxHighlighter>


class GCodeHighLighter : public QSyntaxHighlighter
{
public:
    GCodeHighLighter(QTextDocument *parent);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
            QRegExp pattern;
            QTextCharFormat format;
    };

    QList <HighlightingRule> highlightingRules;
    QTextCharFormat gCommands;
    QTextCharFormat mCommands;
    QTextCharFormat fCommands;
    QTextCharFormat eCommands;
    QTextCharFormat comments;
    QTextCharFormat numbers;
    QTextCharFormat xyzCommands;
    void setForegrounds();
    void setRules();

};

#endif // GCODEHIGHLIGHTER_H
