/*****************************************************************************
 * Copyright(C): changmugu.com
 * Author: FengChenXuan
 * Version: (CFDA) 1.0
 * Date: 19-3-12
 * Description:
 *
 * Function List:
 *
 * History:
 *
 *****************************************************************************/

#ifndef AIBONE_SAVEPDF_H
#define AIBONE_SAVEPDF_H
#include <iostream>
#include <QString>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>


/*
 * @brief: Used to save PDF report.
 *
 */
class SavePDF {
public:
    SavePDF();
    ~SavePDF();


    void savePdf(QString pdfname);

    void savePhoto(QVTKOpenGLWidget *widget, QString photoName);

    void saveCoronalViewPhoto(QVTKOpenGLWidget *widget, QString photoName);

    void saveSagittalViewPhoto(QVTKOpenGLWidget *widget, QString photoName);

    void saveTransverseViewPhoto(QVTKOpenGLWidget *widget, QString photoName);

    void help();

    void setLogo();

    void setPhoto();

private:

    QString htmlLayout();

    void htmlToPdf(QString pdfname);


//    Data data;
//    PhotoPath photoPath;

};


#endif //AIBONE_SAVEPDF_H
