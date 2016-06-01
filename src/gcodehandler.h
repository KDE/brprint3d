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
    Q_PROPERTY (QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_INVOKABLE void saveFile();

public:
    explicit GCodeHandler(QObject *parent = 0);
    QQuickItem *target();
    void setTarget(QQuickItem *target);

    QString fileName() const;
    QString fileContent() const;
    QUrl fileUrl() const;

    void setFileContent(const QString &content);
    void setFileName(const QString &n);
    void setFileUrl(const QUrl &name);

private:
    QString m_fileName;
    QString m_fileContent;
    QUrl m_fileUrl;

    QTextDocument *m_doc;
    QQuickItem *m_target;

signals:
    void fileContentChanged(const QString &content);
    void fileNameChanged(const QString &name);
    void fileUrlChanged(const QUrl &url);
    void targetChanged();
};

#endif // GCODEHANDLER_H
