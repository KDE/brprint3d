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
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkTransform.h>
#include <vtkTriangleFilter.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#define DEFAULTX 200
#define DEFAULTY 200
#define DEFAULTZ 200

class vtkWidget : public QVTKWidget
{
    Q_OBJECT
public:
vtkWidget();
~vtkWidget();
    void renderSTL(QString path);
    void renderGcode(QString text);
public slots:
    void updateCube(QString v, QChar axis);


private:
    void drawCube();
    void cleanup();
    double areaX, areaY, areaZ;

    //Vtk Variables
    vtkSmartPointer<vtkRenderer> renderer;
    vtkRenderWindow* renderWindow;
    vtkSmartPointer<vtkPolyDataMapper> mapperStl;
    vtkSmartPointer<vtkPolyDataMapper> mapperGcode;
     vtkSmartPointer<vtkPolyDataMapper> mapperCube;
    vtkSmartPointer<vtkActor> actorStl;
    vtkSmartPointer<vtkActor> actorGcode;
    vtkSmartPointer<vtkActor> actorCube;
    vtkSmartPointer <vtkCubeSource> cube;

};

#endif // VTKWIDGET_H
