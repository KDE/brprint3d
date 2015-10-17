#ifndef GLWIDGET
#define GLWIDGET
#endif // GLWIDGET
#include "brprint3d.h"
#include "points.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QSettings>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include <QVector>
#include <QDebug>



class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
    void paintGL();
    void initializeGL();
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawGcode();
    void openGcode(QList<Points*> *gcodeDots);



private:
    void paintAxis();
    void paintCube();
    GLfloat xRot,yRot,zRot;
    int zoomFactor;
    QPoint lastPos;
    GLfloat angle, fAspect;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    QMatrix4x4 m_program;
    QOpenGLContext context;
    QList<Points*> *gcodeDots;
    void draw();
    float x,y,z;

};

