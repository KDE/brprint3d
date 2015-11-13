/*
 * This class has a deprecated library!
 * QVTKWidget is disused, so this class will not be used for long.
 * Only I'm working with her because I'm learning VTK and many Qt + VTK tutorials still use this library,
 * with time I will be carrying to the new class.
 * Thank you for your understanding.
 * Lays Rodrigues November 7,2015
 * */

#include "vtkWidget.h"

vtkWidget::vtkWidget()
{

}
void vtkWidget::renderSTL(QString pathStl)
{
    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(pathStl.toStdString().c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkRenderWindow* renderWindow = this->GetRenderWindow();

    renderWindow->AddRenderer(renderer);

    renderer->AddActor(actor);
    renderer->SetBackground(0, .5, 1); // Background color blue

    renderer->ResetCamera();
    renderWindow->Render();
}

void vtkWidget::renderGcode(QString text)
{   vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    QStringList list = text.split("\n",QString::SkipEmptyParts);
    double x=0,y=0,z=0,count=0;
    for(int i=0; i!=list.size(); i++)
    {
        if(list[i].startsWith(";")==false)
        {
            QStringList aux = list[i].split(" ");
            for(int j=1;j!=aux.size();j++)
            {
                if(aux[j].startsWith("X") && aux[j+1].startsWith("Y"))
                {
                    //ler ponto
                    QString x_str = aux[j].section("X",1);
                     x = x_str.toDouble();
                    QString y_str = aux[j+1].section("Y",1);
                     y = y_str.toDouble();
                     points->InsertPoint(count,x,y,z);
                     count++;

                }
               else if(aux[j].startsWith("Z"))
                {
                  //ler ponto
                    QString z_str = aux[j].section("Z",1);
                    z = z_str.toDouble();
                    points->InsertPoint(count,x,y,z);
                    count++;

                }
            }
        }
    }
    vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
     polyLine->GetPointIds()->SetNumberOfIds(count);
     for(unsigned int i = 0; i < count; i++)
       polyLine->GetPointIds()->SetId(i,i);


     // Create a cell array to store the lines in and add the lines to it
     vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
     cells->InsertNextCell(polyLine);

     // Create a polydata to store everything in
     vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

     // Add the points to the dataset
     polyData->SetPoints(points);

     // Add the lines to the dataset
     polyData->SetLines(cells);

     // Setup actor and mapper
     vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
     mapper->SetInputData(polyData);


     vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
     actor->SetMapper(mapper);

     vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
     vtkRenderWindow* renderWindow = this->GetRenderWindow();

     renderWindow->AddRenderer(renderer);

     renderer->AddActor(actor);
     renderer->SetBackground(0, .5, 1); // Background color blue

     renderer->ResetCamera();
     renderWindow->Render();
}
