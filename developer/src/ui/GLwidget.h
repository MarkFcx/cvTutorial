
#ifndef GLWIDGET_H
#define GLWIDGET_H
/*
* Qt lib
*/
#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTimer>
/*
* VTK read lib
*/
#include <vtkDICOMImageReader.h>

/*
* VTK pipline
*/
#include <vtkVolume.h>

/*
* VTK Render
*/

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVBoxLayout>
#include <vtkDICOMImageReader.h>
#include <vtkRenderer.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolume.h>

/*
* OpenCV Lib
*/
#include <opencv2/opencv.hpp>

/*
* self Head
*/
#include "SavePDF.h"
#include "CVwidget.h"
#include "TestVTKCamera.h"
#include "TransformImageData.h"

namespace Ui {
class GLWidget;
}

class GLWidget : public QWidget
{
Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();
    void initUIInterface();

    void initConnect();

    void initUIIcon();
public slots:
    void on_loadBtn_clicked();

    void on_loadBinary_clicked();

    void on_save3DPhoto_clicked();

    void on_savePDF_clicked();

    void on_resetCamera_clicked();

    // test camera
    void on_Azimuth_clicked();
    void on_Azimuth_2_clicked();

    void on_Roll_clicked();
    void on_Roll_2_clicked();

    void on_Elevation_clicked();
    void on_Elevation_2_clicked();

    void on_Dolly_clicked();
    void on_Dolly_2_clicked();

    void on_Zoom_clicked();
    void on_Zoom_2_clicked();

    void on_Yaw_l_clicked();
    void on_Yaw_r_clicked();

    void on_Pitch_l_clicked();
    void on_Pitch_r_clicked();

    void testSetDistance();

    void testSetPosition();

    void testSetFocalPoint();

    void testSetViewUp(int x, int y, int z);

    void on_setRoll_clicked();

    void on_setParallelProjection_on_clicked();

    void on_setParallelProjection_off_clicked();

    void testSetViewAngle();

    void testSetClippingRange();

    void testSetWindowCenter();

    void testSetFocalDisk();

    void TestSetScreenBottomLeft();

    void on_useOffAxisProjectionOn_clicked();

    void on_useOffAxisProjectionOff_clicked();

    void setParallelScale();

    void TestSetEyeSeparation();

    void testSetEyePosition();

    void testSetViewShear();

    void testSetEyeAngle();

    void testSetUseHorizontalViewAngle();

protected:

    void getCameraPrame();

    void showCameraPrame();

public:

    void get3DWindow();

    void orienntationMarkerWidget();

    void coordinateMarkerWidget();

    void markFocalPoint(double *focalPoint);

private:
    Ui::GLWidget *ui;
    SavePDF *savePDF;
    TestVTKCamera *testVtkCamera;

    TransformImageData *transformImageData;

    QVTKOpenGLWidget * renderWidget_;
    QVTKOpenGLWidget * renderWidget_2;
    vtkGenericOpenGLRenderWindow * renderWindow_;
    vtkGenericOpenGLRenderWindow * renderWindow_2;
    QVBoxLayout * vLayout_;
    QVBoxLayout * vLayout_2;
    vtkDICOMImageReader * imageReader_;
    vtkDICOMImageReader * imageReader_2;
    vtkImageData * imageData_;
    vtkImageData * imageData_2;
    vtkRenderer * renderer_;
    vtkRenderer * renderer_2;
    vtkFixedPointVolumeRayCastMapper * mapper_;
    vtkFixedPointVolumeRayCastMapper * mapper_2;
    vtkVolume * volume_;
    vtkVolume * volume_2;

    vtkNew<vtkCamera> camera_;
    double distance;
    double position[3];
    double viewUp[3];
    double focalPoint[3];
    double clippingRange[2];
    double viewAngle;
    double thickness;
    double windowCenter[2];
    double focalDisk;
    double parallelScale;
    double eyeSeparation;
    double eyePosition[3];
    double eyeAngle;
    double ScreenBottomLeft[3];
    double viewShear[3];
    double useHorizontalViewAngle;


    vtkSmartPointer<vtkOrientationMarkerWidget> widget;
    vtkSmartPointer<vtkAxesActor> oriAxesActor;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};
#endif // GLWIDGET_H

