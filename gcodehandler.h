#ifndef GCODEHANDLER_H
#define GCODEHANDLER_H
//QtIncludes
#include <QString>
#include <QQuickTextDocument>
#include <qqmlfile.h>
#include <QTextCodec>

class GCodeHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY (QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY (QString fileContent READ fileContent WRITE setFileContent NOTIFY fileContentChanged)
    Q_INVOKABLE void saveFile();

public:
    explicit GCodeHandler(QObject *parent = 0);
    QString fileName() const;
    QString fileContent() const;
    void setFileContent(QString path);
    void setFileName(QString n);
    void setFilePath(QUrl &name);

private:
    QString m_fileName;
    QString m_fileContent;
    QUrl m_filePath;
    QTextDocument *m_doc;

signals:
    void fileContentChanged(const QString &content);
    void fileNameChanged(const QString &name);
};

#endif // GCODEHANDLER_H
