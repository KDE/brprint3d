#include "gcodehandler.h"
#include <QTextStream>
#include <QFileInfo>
#include <QRegularExpression>

GCodeHandler::GCodeHandler(QObject *parent) : QObject(parent),
    m_target(0),
    m_doc(0)
{

}

QQuickItem *GCodeHandler::target()
{
    return m_target;
}

void GCodeHandler::setTarget(QQuickItem *target)
{
    m_doc = 0;
    m_target = target;
    if (!m_target)
        return;

    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
    }
    emit targetChanged();

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

QString GCodeHandler::fileContent() const
{
    return m_fileContent;
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
        QString header = "-------------------Header of Gcode----------------------\n";
        QString footer = "-------------------Footer of Gcode-------------------------\n";
        foreach (const auto line, list) {
            _match = _cacthMov.match(line);
            if(_match.hasMatch()){
                break;
            }
            header += (line + "\n");
        }
        int last = list.lastIndexOf(_catchEnd);
        for(int i = last; i!= list.size(); ++i) {
            footer += (list.at(i) + "\n");
        }
        setFileName(QFileInfo(path).baseName());
        setFileContent(header + footer);
    }
}

void GCodeHandler::setFileContent(const QString& content)
{
        m_fileContent = content;
        emit fileContentChanged(m_fileContent);
}

void GCodeHandler::setFileName(const QString& n)
{
    if(m_fileName != n){
        m_fileName = n;
        emit fileNameChanged(m_fileName);
    }
}


