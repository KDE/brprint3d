#include "gcodehandler.h"
#include <QTextStream>
#include <QFileInfo>

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
    if(m_fileUrl != name){
        m_fileUrl = name;
        QString path = name.toLocalFile();
        QFile gcode(path);
        if (!gcode.open(QFile::ReadOnly | QFile::Text)) {
            return;
        }
        QTextStream in(&gcode);
        QString content = in.readAll();
        setFileName(QFileInfo(path).baseName());
        setFileContent(content);
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


