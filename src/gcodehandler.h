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

    Q_PROPERTY (QQuickItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY (QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY (QString fileContent READ fileContent WRITE setFileContent NOTIFY fileContentChanged)
    Q_INVOKABLE void saveFile();

public:
    explicit GCodeHandler(QObject *parent = 0);
    QQuickItem *target();
    void setTarget(QQuickItem *target);

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
    QQuickItem *m_target;

signals:
    void fileContentChanged(const QString &content);
    void fileNameChanged(const QString &name);
    void targetChanged();
};

#endif // GCODEHANDLER_H
