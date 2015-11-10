/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

#ifndef GLWIDGET
#define GLWIDGET

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
    GLfloat xRot, yRot, zRot;
    int zoomFactor;
    QPoint lastPos;
    GLfloat angle, fAspect;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    QMatrix4x4 m_program;
    QOpenGLContext context;
    QList<Points*> *gcodeDots;
    void draw();
    float x, y, z;

};

#endif