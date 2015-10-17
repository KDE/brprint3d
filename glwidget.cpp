/* This file manage the openglwidget
*/
#include "glwidget.h"
#include <unistd.h>
#include <GL/freeglut.h>

QSettings setting(QDir::currentPath()+"/br.ini",QSettings::IniFormat); //Arquivo INI

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent),xRot(-10),yRot(-10),zRot(-90.0f),angle(70)
{
    this->gcodeDots = NULL;
}
//Inicializa o widget
void GLWidget::initializeGL()
{     initializeOpenGLFunctions();
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);
      glEnable(GL_DEPTH_TEST);
      glShadeModel(GL_SMOOTH);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(angle,(GLfloat)width()/(GLfloat)height(),0.1f,600.0f);	// Calculate The Aspect Ratio Of The Window
}


//Faz a pintura da tela
void GLWidget::paintGL()
{
        float x,y,z;
        QString pathx=QVariant (setting.value("tablex")).toString();
        QString pathy=QVariant (setting.value("tabley")).toString();
        QString pathz=QVariant (setting.value("tablez")).toString();
            if(pathx.isEmpty() && pathy.isEmpty() && pathz.isEmpty())
            {
                x=40.0;
                y=40.0;
                z=40.0;

            }
            else
            {
                x=QVariant (setting.value("tablex")).toFloat();
                y=QVariant (setting.value("tabley")).toFloat();
                z=QVariant (setting.value("tablez")).toFloat();

            }


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glTranslatef(xRot,yRot,zRot);
        glScalef(x,y,z);

        this->paintAxis();
        this->paintCube();
        this->drawGcode();

        glFlush();
}

//Resize Window
void GLWidget::resizeGL(int w, int h)
{
    if(h==0)
        h=1;
      glViewport(0, 0, w, h);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(angle,(GLfloat)w/(GLfloat)h,0.5,500);
      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();
      glFlush();
}
//Desenha os eixos
void GLWidget::paintAxis()
{   glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
        glColor3f(0,0,1);//X -> Azul
        glVertex3d(0,0,0);
        glVertex3d(1,0,0);
        glColor3f(1,0,0);//Y -> Vermelho
        glVertex3d(0,0,0);
        glVertex3d(0,1,0);

        glColor3f(0,1,0);//z -> Verde
        glVertex3d(0,0,0);
        glVertex3d(0,0,1);

    glEnd();
    glPopMatrix();
}
//Desenha o cubo
void GLWidget::paintCube()
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);

    //Frente
    glColor3f(0.0f,0.0f,0.0f);
    //glNormal3f();
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,0,1);
    glVertex3f(0,0,1);
    glEnd();
    //Esquerda
   glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0,1,1);
    glVertex3f(0,0,1);
   glEnd();
    glBegin(GL_QUADS);
    //chao DO CUBO
    glColor3f(0.7f,0.7f,0.7f);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(1,1,0);
    glVertex3f(1,0,0);
    glEnd();
  // Trás
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(0,1,0);
    glVertex3f(0,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,1,0);
    glEnd();
    // Direita
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(1,1,1);
    glVertex3f(1,0,1);
    glEnd();
    glPopMatrix();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {/*
        qDebug() <<"HERE!";
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle+10,(GLfloat)width()/(GLfloat)height(),0.5,500);
        glFlush();*/



    }
    if(event->buttons() == Qt::LeftButton)
    {   /*glMatrixMode(GL_PROJECTION);
        gluPerspective(angle-10,(GLfloat)width()/(GLfloat)height(),0.5,500);
        glFlush();*/

    }
    //update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint p = event->angleDelta();//pega o y que diz se foi positivo ou negativo
    //QPoint actpos= event->pos();//pega a posição do mouse na tela


    //Zoom out
    if(p.y() > 0 )
    {
        zRot -=2;
    }
    //Zoom in
    if(p.y() < 0)
    {
        zRot +=2;
    }

    update();
   // qDebug() << QPoint(m);
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}
//Recebe a lista dos pontos
void GLWidget::openGcode(QList<Points*> *gcodeDots){
    this->gcodeDots = gcodeDots;

}

//desenha o gcode na tela
void GLWidget::drawGcode()
{
    GLfloat x=0,y=0,z=0,xx=0,yy=0,zz=0;
    Points *ant=NULL, *act=NULL;
    if(this->gcodeDots == NULL) {
       // qDebug() << "glWidget: Não desenhei GCode.";
        return;
    }
   // qDebug() << "glWidget: Desenhei GCode.";
    glPushMatrix();
    for(int i=1/*((this->gcodeDots->size()-1)/2)*/;i < this->gcodeDots->size();i++)
    {
        try{
            act = this->gcodeDots->takeAt(i);
            ant = this->gcodeDots->takeAt(i-1);
            //qDebug() << float(x) <<float(y) <<float(z) <<"\n";
        }
        catch(QString str)
        {
            qDebug() << i << ' ' <<QString(str);
        }
        //qDebug() << "glWidget: Got point " << i << '\n';
        act->getPoint(&x, &y, &z);
        x/=200.0;
        y/=200.0;
        z/=200.0;
        //qDebug() << float(x) <<float(y) <<float(z) <<"\n";
        ant->getPoint(&xx, &yy, &zz);
        xx/=200.0;
        yy/=200.0;
        zz/=200.0;
        glBegin(GL_POINTS);
        //glLineWidth(2);
        glColor3f(0.0f,0.0f,255.0f);
        glVertex3f(x,y,z);
        glVertex3f(xx,yy,zz);
        glEnd();
    }
    glPopMatrix();
    //qDebug() << "HERE!";
}
