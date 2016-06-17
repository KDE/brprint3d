/*=====================================================================

 Br-Print3D, Open Source 3D Printing Host

 Copyright (C) 2016 Br-Print3D Authors

 This file is part of the Br-Print3D project

 Br-Print3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Br-Print3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Br-Print3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
#ifndef EXTRUDERMODEL_H
#define EXTRUDERMODEL_H
//QtIncludes
#include <QtCore/QAbstractTableModel>
#include <QtCore/QTimer>
//LocalIncludes
#include "extruderobject.h"

class ExtruderModel : public QAbstractTableModel
{
public:
    ExtruderModel(int qntExtruders, QList<ExtruderObject> list);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    int m_qntExtruders;
    QList <ExtruderObject> extruderList;
    void updateExtruderTemp();
};

#endif // EXTRUDERMODEL_H
