/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include "glwidget.h"
#include <QWidget>
#include <QtWidgets>
#include <string>

class QAction;
class QMenu;
class QLineEdit;

enum class Transform
{
    SCF,        ///< scale factor
    XTRS,       ///< translation in x
    YTRS,       ///< translation in y
    ZTRS,       ///< translation in z
    XROT,       ///< rotation in x
    YROT,       ///< rotation in y
    ZROT,       ///< rotation in z
};

class Window : public QMainWindow
{
    Q_OBJECT

public:

    /// constructor
    Window();

    /// destructor
    ~Window(){};

    /// provides ideal size for window
    QSize sizeHint() const;

    /// getter for currently active camera
    View &getCamera() { return *perspectiveView->getView(); }

     /// constant version of getter for currently active camera
    const View &getCamera() const { return *perspectiveView->getView(); }

    /// Getter for perspective view
    GLWidget * getGL() { return perspectiveView; }

public slots:

    /// force re-rendering of scene
    void repaintAllGL();

    /// new file menu item
    // void newFile();

    /// open intersection file menu item
    // void open();

    /// save tesselation file menu item
    void saveFile();

    /// save tesselation file under user-inputted name
    void saveAs();

    /// toggle visibility of geometry
    void showModel(int show);

    /// toggle visibility of ffd lattice
    void showLat(int show);

    /// make parameter panel visible
    void showParamOptions();

    /// handle change in line-edit parameters values
    void lineEditChange();

    /// handle change in slider position
    void sliderChange(int value);

    /// voxelise csg tree
    void voxPress();

    /// apply marching cubes
    void marchPress();

    /// smooth isosurface
    void smoothPress();

    /// deform isosurface
    void defPress();

    /// load model
    void loadPress();

    /// load voxel grids
    void loadGridPress();

    /// shrink model
    void shrinkPress();

    // display demo label
    void demoMode();

    void loadModelDemo(string filename, string txtDisplay);

    void resetView();

protected:

    /// Handle key press event
    void keyPressEvent(QKeyEvent *event);

    /// Handle mouse movement event
    void mouseMoveEvent(QMouseEvent *event);

    /// Handle changes in parameter settings
    void optionsChanged();

private:
    GLWidget * perspectiveView; ///< openGL render view
    QWidget * paramPanel;       ///< side panel for user access to parameters

    // param panel sub components
    QCheckBox * checkModel; ///< determine whether loaded model should be displayed or not
    QCheckBox * checkLat; ///< determine whether ffd lattice should be displayed or not
    QPushButton * voxButton; ///< button to activate voxelisation
    QPushButton * marchButton; ///< button to activate marching cubes
    QPushButton * smoothButton; ///< button to activate smoothing
    QPushButton * defButton; ///< button to activate deformation
    QPushButton * loadButton; ///< button to load model
    QPushButton * loadGridButton; ///< button to voxel grid
    QPushButton * demoButton; ///< button to voxel grid
    QPushButton * shrinkButton; ///< button to shrink mesh
    QLabel * demoLabel;

    // active control point
    int cpi, cpj, cpk;    ///< coordinates of currently active ffd control point
    int latdx, latdy, latdz; ///< order of the ffd lattice in each dimension
    float sliderange;       ///< bound on extent of cp shifting in each dimension


    // menu widgets and actions
    QMenu *fileMenu;        ///< file menu response
    QAction *saveAct;       ///< save menu response
    QAction *saveAsAct;     ///< save as menu response
    QMenu *viewMenu;        ///< view menu response
    QAction *showParamAct;  ///< toggle param panel menu response

    QString tessfilename; ///< name of tesselation file for output

    QSlider * xtrslider, * ytrslider, * ztrslider; ///< sliders for intersector positioning
    QLineEdit * iEdit, * jEdit, * kEdit; ///< text entry fields for parameters

    /// init reponses
    void createActions();

    /// init menu
    void createMenus();
};

#endif
