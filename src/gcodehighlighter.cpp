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
