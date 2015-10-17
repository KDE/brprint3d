#ifndef ARDUINOLISTENER_H
#define ARDUINOLISTENER_H
#include <QString>
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QThread>


class arduinoListener : public QThread
{
    Q_OBJECT
public:
    arduinoListener();
    virtual void run() Q_DECL_OVERRIDE;
    ~arduinoListener();
private:
    bool garbage,test;
    QString file;
signals:
    void arduinoConnect(bool b, QString word);
};

#endif // ARDUINOLISTENER_H
