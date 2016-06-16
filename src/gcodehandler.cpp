#include "gcodehandler.h"
#include <QTextStream>
#include <QFileInfo>
#include <QRegularExpression>

GCodeHandler::GCodeHandler(QObject *parent) : QObject(parent),
    m_header(nullptr),
    m_footer(nullptr),
    m_doc(nullptr)
{

}

QQuickItem *GCodeHandler::header()
{
    return m_header;
}

QQuickItem *GCodeHandler::footer()
{
    return m_footer;
}

void GCodeHandler::setHeader(QQuickItem *target)
{
    m_doc = 0;
    m_header = target;
    if (!m_header)
        return;

    QVariant doc = m_header->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
    }
    emit headerChanged();

}

void GCodeHandler::setFooter(QQuickItem *target)
{
    m_doc = 0;
    m_footer = target;
    if (!m_footer)
        return;

    QVariant doc = m_footer->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
    }
    emit footerChanged();

}

/*
 * Save edit file - overrite
*/
void GCodeHandler::saveFile() //Default pattern .gcode - Needs handle it?
{
    QFile gcode(m_fileUrl.toLocalFile());
    if(!gcode.open(QFile::WriteOnly | QFile::Text)){
        gcode.write(m_doc->toPlainText().toUtf8());
        gcode.close();
    }

}

QString GCodeHandler::fileName() const
{
    return m_fileName;
}

QString GCodeHandler::fileContentHeader() const
{
    return m_fileContentHeader;
}

QString GCodeHandler::fileContentFooter() const
{
    return m_fileContentFooter;
}

QUrl GCodeHandler::fileUrl() const
{
    return m_fileUrl;
}

void GCodeHandler::setFileUrl(const QUrl &name)
{
    QRegularExpression _cacthMov("G(?<command>.) .*\\bX(?<axisX>[0-9.-]+) Y(?<axisY>[0-9.-]+) Z(?<axisZ>[0-9].+)");
    QRegularExpression _catchEnd(";End GCode");
    QRegularExpressionMatch _match;
    if(m_fileUrl != name){
        m_fileUrl = name;
        QString path = name.toLocalFile();
        QFile gcode(path);
        if (!gcode.open(QFile::ReadOnly | QFile::Text)) {
            return;
        }
        QTextStream in(&gcode);
        QString content = in.readAll();
        //TODO: Send this content to 3DView
        QStringList list = content.split('\n', QString::SkipEmptyParts);
        QString header;
        QString footer;
        foreach (const auto line, list) {
            _match = _cacthMov.match(line);
            if(_match.hasMatch()){
                break;
            }
            header += (line + "\n");
        }
        int last = list.lastIndexOf(_catchEnd);
        for(int i = last; i!= list.size() -1; ++i) {
            footer += (list.at(i) + "\n");
        }
        setFileName(QFileInfo(path).baseName());
        setFileContentHeader(header);
        setFileContentFooter(footer);
    }
}

void GCodeHandler::setFileContentHeader(const QString& content)
{
        m_fileContentHeader = content;
        emit fileContentHeaderChanged(m_fileContentHeader);
}

void GCodeHandler::setFileContentFooter(const QString& content)
{
        m_fileContentFooter = content;
        emit fileContentFooterChanged(m_fileContentFooter);
}

void GCodeHandler::setFileName(const QString& n)
{
    if(m_fileName != n){
        m_fileName = n;
        emit fileNameChanged(m_fileName);
    }
}


