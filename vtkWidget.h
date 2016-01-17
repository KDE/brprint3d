/*
 * This class use a deprecated library!
 * QVTKWidget is disused, so this class will not be used for long.
 * Only I'm working with her because I'm learning VTK and many Qt + VTK tutorials still use this library,
 * with time I will be carrying to the new class.
 * Thank you for your understanding.
 * Lays Rodrigues November 7,2015
 * */
/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

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
#ifndef VTKWIDGET_H
#define VTKWIDGET_H

#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkCubeSource.h>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

class vtkWidget : public QVTKWidget
{
    Q_OBJECT
public:
explicit vtkWidget(QWidget *parent = 0);
~vtkWidget();
    void renderSTL(const QString& path);
    void renderGcode(const QString& text);
public slots:
    void updateCube(int v, QChar axis);
    void showCarTravels(bool b);

signals:
    void layersCount(int l);

private:
    void drawCube();
    void cleanup();
    void drawFloor();
    double areaX, areaY, areaZ;
    //Vtk Variables
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkPolyDataMapper> mapperStl;
    vtkSmartPointer<vtkPolyDataMapper> mapperGcode;
    vtkSmartPointer<vtkPolyDataMapper> mapperGcodeCar;
    vtkSmartPointer<vtkPolyDataMapper> mapperCube;
    vtkSmartPointer<vtkPolyDataMapper> mapperFloor;
    vtkSmartPointer<vtkActor> actorStl;
    vtkSmartPointer<vtkActor> actorGcode;
    vtkSmartPointer<vtkActor> actorGcodeCar;
    vtkSmartPointer<vtkActor> actorCube;
    vtkSmartPointer<vtkActor> actorFloor;
    vtkSmartPointer <vtkCubeSource> cube;

};

#endif // VTKWIDGET_H
