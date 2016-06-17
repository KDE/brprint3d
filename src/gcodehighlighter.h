/*=====================================================================

 Br-Print3D, Open Source 3D Printing Host

 Copyright (C) 2016 Br-Print3D Authors

 This file is part of the Br-Print3D project

 Br-Print3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Br-Print3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Br-Print3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

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
