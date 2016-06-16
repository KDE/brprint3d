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

    Q_PROPERTY (QQuickItem *header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY (QQuickItem *footer READ footer WRITE setFooter NOTIFY footerChanged)
    Q_PROPERTY (QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY (QString fileContentHeader READ fileContentHeader WRITE setFileContentHeader NOTIFY fileContentHeaderChanged)
    Q_PROPERTY (QString fileContentFooter READ fileContentFooter WRITE setFileContentFooter NOTIFY fileContentFooterChanged)
    Q_PROPERTY (QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_INVOKABLE void saveFile();

public:
    explicit GCodeHandler(QObject *parent = 0);
    QQuickItem *header();
    QQuickItem *footer();
    void setHeader(QQuickItem *target);
    void setFooter(QQuickItem *target);

    QString fileName() const;
    QString fileContentHeader() const;
    QString fileContentFooter() const;
    QUrl fileUrl() const;

    void setFileContentHeader(const QString &content);
    void setFileContentFooter(const QString &content);
    void setFileName(const QString &n);
    void setFileUrl(const QUrl &name);

private:
    QString m_fileName;
    QString m_fileContentHeader;
    QString m_fileContentFooter;
    QUrl m_fileUrl;
    QTextDocument *m_doc;
    QQuickItem *m_header;
    QQuickItem *m_footer;

signals:
    void fileContentHeaderChanged(const QString &content);
    void fileContentFooterChanged(const QString &content);
    void fileNameChanged(const QString &name);
    void fileUrlChanged(const QUrl &url);
    void headerChanged();
    void footerChanged();
};

#endif // GCODEHANDLER_H
