#include "GLwidget.h"
#include "ui_GLwidget.h"
#include <QtDebug>
#include <QEvent>
#include <QFileDialog>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkCamera.h>
#include <QMouseEvent>
#include <QCursor>
GLWidget::GLWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GLWidget)
{
//    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    QSurfaceFormat fmt = QVTKOpenGLWidget::defaultFormat();
    fmt.setSamples (0);
    QSurfaceFormat::setDefaultFormat (fmt);

    ui->setupUi(this);
    setMouseTracking(true);

    initUIInterface();
    initConnect();
    initUIIcon();
    imageReader_ = vtkDICOMImageReader::New();
    mapper_ = vtkFixedPointVolumeRayCastMapper::New();
    volume_ = vtkVolume::New();

    imageReader_2 = vtkDICOMImageReader::New();
    mapper_2 = vtkFixedPointVolumeRayCastMapper::New();
    volume_2 = vtkVolume::New();

    imageData_ = vtkImageData::New ();
    imageData_2 = vtkImageData::New ();

    widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New ();
    oriAxesActor = vtkSmartPointer<vtkAxesActor>::New ();
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New ();

}

GLWidget::~GLWidget()
{
    delete ui;
}

void GLWidget::initUIInterface()
{
    renderWidget_ = new QVTKOpenGLWidget;
    renderWindow_ = vtkGenericOpenGLRenderWindow::New();
    renderWidget_2 = new QVTKOpenGLWidget;
    renderWindow_2 = vtkGenericOpenGLRenderWindow::New();

    renderWidget_->SetRenderWindow(renderWindow_);
    renderWidget_2->SetRenderWindow(renderWindow_2);
    renderer_ = vtkRenderer::New();
    renderer_2 = vtkRenderer::New();

    vLayout_ = new QVBoxLayout;
    vLayout_->addWidget(renderWidget_);
    vLayout_2 = new QVBoxLayout;
    vLayout_2->addWidget(renderWidget_2);
    ui->showWidget->setLayout(vLayout_);
    ui->showWidget_2->setLayout(vLayout_2);

}

void GLWidget::initConnect()
{
    connect(ui->setDistance_2, SIGNAL(valueChanged(int)), this, SLOT(testSetDistance()));
    connect(ui->setPosition_x, SIGNAL(valueChanged(int)), this, SLOT(testSetPosition()));
    connect(ui->setPosition_y, SIGNAL(valueChanged(int)), this, SLOT(testSetPosition()));
    connect(ui->setPosition_z, SIGNAL(valueChanged(int)), this, SLOT(testSetPosition()));
    connect(ui->setFocalPoint_x, SIGNAL(valueChanged(int)), this, SLOT(testSetFocalPoint()));
    connect(ui->setFocalPoint_y, SIGNAL(valueChanged(int)), this, SLOT(testSetFocalPoint()));
    connect(ui->setFocalPoint_z, SIGNAL(valueChanged(int)), this, SLOT(testSetFocalPoint()));
    connect(ui->setViewAngle, SIGNAL(valueChanged(int)), this, SLOT(testSetViewAngle()));

    connect(ui->setClippingRange_f, SIGNAL(valueChanged(int)), this, SLOT(testSetClippingRange()));
    connect(ui->setClippingRange_b, SIGNAL(valueChanged(int)), this, SLOT(testSetClippingRange()));
//TODO:
    connect(ui->SetWindowCenter_2, SIGNAL(valueChanged(int)), this, SLOT(testSetWindowCenter()));
    connect(ui->SetWindowCenter_3, SIGNAL(valueChanged(int)), this, SLOT(testSetWindowCenter()));

    connect(ui->setFocalDisk, SIGNAL(valueChanged(int)), this, SLOT(testSetFocalDisk()));

    connect(ui->SetScreenBottomLeft, SIGNAL(valueChanged(int)), this, SLOT(TestSetScreenBottomLeft()));
    connect(ui->SetScreenBottomLeft_2, SIGNAL(valueChanged(int)), this, SLOT(TestSetScreenBottomLeft()));
    connect(ui->SetScreenBottomLeft_3, SIGNAL(valueChanged(int)), this, SLOT(TestSetScreenBottomLeft()));

    connect(ui->SetEyeSeparation_2, SIGNAL(valueChanged(int)), this, SLOT(TestSetEyeSeparation()));
//
    connect(ui->setParallelScale, SIGNAL(valueChanged(int)), this, SLOT(setParallelScale()));

    connect(ui->setEyePosition_x, SIGNAL(valueChanged(int)), this, SLOT(testSetEyePosition()));
    connect(ui->setEyePosition_y, SIGNAL(valueChanged(int)), this, SLOT(testSetEyePosition()));
    connect(ui->setEyePosition_z, SIGNAL(valueChanged(int)), this, SLOT(testSetEyePosition()));

    connect(ui->SetViewShear, SIGNAL(valueChanged(int)), this, SLOT(testSetViewShear()));
    connect(ui->SetViewShear_2, SIGNAL(valueChanged(int)), this, SLOT(testSetViewShear()));
    connect(ui->SetViewShear_3, SIGNAL(valueChanged(int)), this, SLOT(testSetViewShear()));

    connect(ui->setEyeAngle, SIGNAL(valueChanged(int)), this, SLOT(testSetEyeAngle()));
    connect(ui->setUseHorizontalViewAngle_2, SIGNAL(valueChanged(int)), this, SLOT(testSetUseHorizontalViewAngle()));
}

void GLWidget::initUIIcon()
{
    ui->loadBtn->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/load.png);}"
                               "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/load_.png);}"
                               "QPushButton:pressed{border-image:url(:/home/cxfeng/Documents/AIBone/AIBone/icon/load.png);}");

    ui->save3DPhoto->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/photo.png);}"
                                                "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/photo_.png);}"
                                                "QPushButton:pressed{border-image:url(:/home/cxfeng/Documents/AIBone/AIBone/icon/photo.png);}");
    ui->savePDF->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/pdf.png);}"
                                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/pdf_.png);}"
                                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/pdf.png);}");
    ui->resetCamera->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/resetCamera.png);}"
                               "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/resetCamera_.png);}"
                               "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/resetCamera.png);}");

    ui->setParallelProjection_on->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/on.png);}"
                               "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/on_.png);}"
                               "QPushButton:pressed{border-image:url(:/home/cxfeng/Documents/AIBone/AIBone/icon/on.png);}");
    ui->setParallelProjection_off->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/off.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/off_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/off.png);}");
    ui->Azimuth->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                               "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                               "QPushButton:pressed{border-image:url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Azimuth_2->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                            "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                            "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Roll->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Roll_2->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Elevation->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Elevation_2->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Dolly->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Dolly_2->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                                 "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                                 "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Zoom->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                             "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                             "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Zoom_2->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                               "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                               "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Yaw_l->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                            "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                            "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Yaw_r->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                              "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                              "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
    ui->Pitch_l->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}"
                            "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2_.png);}"
                            "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/less2.png);}");
    ui->Pitch_r->setStyleSheet("QPushButton{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}"
                              "QPushButton:hover{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2_.png);}"
                              "QPushButton:pressed{border-image: url(:/home/cxfeng/Documents/AIBone/AIBone/icon/plus2.png);}");
}

void GLWidget::on_loadBtn_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, QString("Open Directory"), QString("./"));
//    QString path = "/home/cxfeng/Documents/AIBone/AIBone/cmake-build-debug/12";
    if (path.isEmpty())
    {
        qDebug() << " open the DICOM file Failed,the path is empty!!" << endl;
        return;
    }
    imageReader_->SetDirectoryName(path.toStdString().c_str());
    imageReader_->Update();

    imageData_ = imageReader_->GetOutput ();
    imageData_2 = imageReader_->GetOutput ();
    mapper_->SetInputData (imageData_);
    mapper_2->SetInputData (imageData_2);
//    mapper_->SetInputConnection(imageReader_->GetOutputPort());

    vtkNew<vtkColorTransferFunction> volumeColor;
    volumeColor->AddRGBPoint(0, 0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(500, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

    vtkNew<vtkPiecewiseFunction> volumeScalarOpacity;
    volumeScalarOpacity->AddPoint(0, 0.00);
    volumeScalarOpacity->AddPoint(500, 0.15);
    volumeScalarOpacity->AddPoint(1000, 0.15);
    volumeScalarOpacity->AddPoint(1150, 0.85);

    vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;
    volumeGradientOpacity->AddPoint(0, 0.0);
    volumeGradientOpacity->AddPoint(90, 0.5);
    volumeGradientOpacity->AddPoint(100, 0.6);

    vtkNew<vtkVolumeProperty> volumeProperty;
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    volume_->SetMapper(mapper_);
    volume_2->SetMapper(mapper_2);
    volume_->SetProperty(volumeProperty);
    volume_2->SetProperty(volumeProperty);
    renderer_->AddVolume(volume_);
    renderer_2->AddVolume(volume_2);

    renderWindow_->AddRenderer(renderer_);
    renderWindow_2->AddRenderer(renderer_2);

//    coordinateMarkerWidget();
    renderWindow_->Render ();
    renderWindow_2->Render ();
    orienntationMarkerWidget();

    renderer_->GetActiveCamera()->GetPosition(position);
    renderer_->GetActiveCamera()->GetViewUp(viewUp);
    renderer_->GetActiveCamera()->GetFocalPoint(focalPoint);
    renderer_->GetActiveCamera()->GetClippingRange(clippingRange);
    distance = renderer_->GetActiveCamera()->GetDistance();
    viewAngle = renderer_->GetActiveCamera()->GetViewAngle();
    renderer_->GetActiveCamera()->GetEyePosition(eyePosition);
    eyeAngle = renderer_->GetActiveCamera()->GetEyeAngle();
    useHorizontalViewAngle = renderer_->GetActiveCamera()->GetUseHorizontalViewAngle();
    thickness = renderer_->GetActiveCamera()->GetThickness();
    focalDisk = renderer_->GetActiveCamera ()->GetFocalDisk ();
    parallelScale = renderer_->GetActiveCamera ()->GetParallelScale ();
    eyeSeparation = renderer_->GetActiveCamera ()->GetEyeSeparation ();
    renderer_->GetActiveCamera ()->GetWindowCenter (windowCenter);
    renderer_->GetActiveCamera ()->GetScreenBottomLeft (ScreenBottomLeft);
    renderer_->GetActiveCamera ()->GetViewShear (viewShear);
}

void GLWidget::on_loadBinary_clicked()
{

    QString path = QFileDialog::getExistingDirectory(this, QString("Open Directory"), QString("./"));
    if (path.isEmpty())
    {
        qDebug() << " open the Binary file Failed,the path is empty!!" << endl;
        return;
    }
    imageReader_2->SetDirectoryName(path.toStdString().c_str());
    imageReader_2->Update();


    mapper_2->SetInputConnection(imageReader_2->GetOutputPort());

    vtkNew<vtkColorTransferFunction> volumeColor;
    volumeColor->AddRGBPoint(0, 0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(500, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

    vtkNew<vtkPiecewiseFunction> volumeScalarOpacity;
    volumeScalarOpacity->AddPoint(0, 0.00);
    volumeScalarOpacity->AddPoint(500, 0.15);
    volumeScalarOpacity->AddPoint(1000, 0.15);
    volumeScalarOpacity->AddPoint(1150, 0.85);

    vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;
    volumeGradientOpacity->AddPoint(0, 0.0);
    volumeGradientOpacity->AddPoint(90, 0.5);
    volumeGradientOpacity->AddPoint(100, 0.6);

    vtkNew<vtkVolumeProperty> volumeProperty;
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    volume_2->SetMapper(mapper_2);
    volume_2->SetProperty(volumeProperty);
    renderer_2->AddVolume(volume_2);

    renderWindow_2->AddRenderer(renderer_2);
    renderWindow_2->Render();
}

void GLWidget::orienntationMarkerWidget(){

    double rgba[4]{0.6, 0.0, 0.5, 0.0};
    widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    widget->SetOrientationMarker( oriAxesActor );
    widget->SetInteractor(renderer_->GetRenderWindow()->GetInteractor());
    widget->SetViewport( 0, 0, 0.2, 0.2 );
    widget->SetEnabled( 1 );
    widget->InteractiveOn();
}

void GLWidget::coordinateMarkerWidget(){

    oriAxesActor->SetPosition(0, 0, 0);
    oriAxesActor->SetTotalLength(512, 512, 600);
    oriAxesActor->SetShaftType(0);
    oriAxesActor->SetAxisLabels(1);
    oriAxesActor->SetCylinderRadius(0.002);
    renderer_->AddActor(oriAxesActor);
}

/* @type: puble
 * @Function: use there polydata mark FocalPoint
 * @Input: double *focalPoint
 * @Output: NO
 * @Note:
*/
void GLWidget::markFocalPoint(double *focalPoint){
    vtkSphereSource* Sphere =
            vtkSphereSource::New();
    Sphere->SetRadius( 10 );
    Sphere->Update ();

    vtkPolyDataMapper* SphereMapper =
            vtkPolyDataMapper::New();
    SphereMapper->SetInputConnection( Sphere->GetOutputPort() );


    vtkActor *SphereActor =
            vtkActor::New();
    SphereActor->SetMapper( SphereMapper );
    SphereActor->GetProperty ()->SetColor (0, 255, 255);

    SphereActor->SetPosition(focalPoint[0], focalPoint[1], focalPoint[2]);

    renderer_->AddActor(SphereActor);
    renderWindow_->Render ();

    Sphere->Delete ();
    SphereMapper->Delete ();
    SphereActor->Delete ();
}


void GLWidget::on_savePDF_clicked() {
    QString photoName1 = "01.png";
    savePDF->savePhoto(renderWidget_, photoName1);
    QString photoName2 = "02.png";
    savePDF->savePhoto(renderWidget_2, photoName2);
    QString photoName3 = "03.png";
    savePDF->savePhoto(renderWidget_, photoName3);
    QString photoName4 = "04.png";
    savePDF->savePhoto(renderWidget_, photoName4);

    QString pdfname = "01.pdf";
    savePDF->savePdf(pdfname);
}

void GLWidget::on_resetCamera_clicked()
{
    renderer_->GetActiveCamera()->SetPosition(position);
    renderer_->GetActiveCamera()->SetViewUp(viewUp);
    renderer_->GetActiveCamera()->SetFocalPoint(focalPoint);
    renderer_->GetActiveCamera()->SetClippingRange(clippingRange);
    renderer_->GetActiveCamera()->SetDistance(distance);
    renderer_->GetActiveCamera()->SetViewAngle(viewAngle);
    renderer_->GetActiveCamera()->SetEyePosition(eyePosition);
    renderer_->GetActiveCamera()->SetEyeAngle(eyeAngle);
    renderer_->GetActiveCamera()->SetUseHorizontalViewAngle(useHorizontalViewAngle);
    renderer_->GetActiveCamera()->SetThickness(thickness);
    renderer_->GetActiveCamera ()->SetFocalDisk (focalDisk);
    renderer_->GetActiveCamera ()->SetParallelScale (parallelScale);
    renderer_->GetActiveCamera ()->SetEyeSeparation (eyeSeparation);
    renderer_->GetActiveCamera ()->SetWindowCenter (windowCenter[0], windowCenter[1]);
    renderer_->GetActiveCamera ()->SetScreenBottomLeft (ScreenBottomLeft);
    renderer_->GetActiveCamera ()->SetViewShear (viewShear);

    QString str_distance = QString("%1").arg(distance);
    QString str_viewAngle = QString("%1").arg(viewAngle);
    QString str_position_x = QString("%1").arg(position[0]);
    QString str_position_y = QString("%1").arg(position[1]);
    QString str_position_z = QString("%1").arg(position[2]);
    QString str_viewUp_x = QString("%1").arg(viewUp[0]);
    QString str_viewUp_y = QString("%1").arg(viewUp[1]);
    QString str_viewUp_z = QString("%1").arg(viewUp[2]);
    QString str_focalPoint_x = QString("%1").arg(focalPoint[0]);
    QString str_focalPoint_y = QString("%1").arg(focalPoint[1]);
    QString str_focalPoint_z = QString("%1").arg(focalPoint[2]);
    QString str_clippingRange_f = QString("%1").arg(clippingRange[0]);
    QString str_clippingRange_b = QString("%1").arg(clippingRange[1]);

    QString str_thickness_ = QString("%1").arg(thickness);
    QString str_focalDisk_ = QString("%1").arg(focalDisk);
    QString str_setParallelScale_ = QString("%1").arg(parallelScale);
    QString str_eyeSeparation_ = QString("%1").arg(eyeSeparation);

    QString str_windowCenter_x = QString("%1").arg(windowCenter[0]);
    QString str_windowCenter_y = QString("%1").arg(windowCenter[1]);

    QString str_ScreenBottomLeft_x = QString("%1").arg(ScreenBottomLeft[0]);
    QString str_ScreenBottomLeft_y = QString("%1").arg(ScreenBottomLeft[1]);
    QString str_ScreenBottomLeft_z = QString("%1").arg(ScreenBottomLeft[2]);

    QString str_viewShear_x = QString("%1").arg(viewShear[0]);
    QString str_viewShear_y = QString("%1").arg(viewShear[1]);
    QString str_viewShear_z = QString("%1").arg(viewShear[2]);

    QString str_eyePosition_x = QString("%1").arg(eyePosition[0]);
    QString str_eyePosition_y = QString("%1").arg(eyePosition[1]);
    QString str_eyePosition_z = QString("%1").arg(eyePosition[2]);
    QString str_eyeAngle = QString("%1").arg(eyeAngle);
    QString str_useHorizontalViewAngle = QString("%1").arg(useHorizontalViewAngle);



    ui->textEdit->setHtml("<b>Distance: (" + str_distance + ")</b>");
    ui->textEdit_2->setHtml("<b>camera position: (" + str_position_x+", "+str_position_y+", "+str_position_z+ ")</b>");
    ui->textEdit_3->setHtml("<b>View Up: (" + str_viewUp_x+", "+str_viewUp_y+", "+str_viewUp_z+ ")</b>");
    ui->textEdit_4->setHtml("<b>FocalPoint: (" + str_focalPoint_x+", "+str_focalPoint_y+", "+str_focalPoint_z+ ")</b>");
    ui->textEdit_5->setHtml("<b>clipping Range: (" + str_clippingRange_f+", "+str_clippingRange_b+ ")</b>");
    ui->textEdit_6->setHtml("<b>View Angle: (" + str_viewAngle + ")</b>");

    ui->textEdit_7->setHtml("<b>Thickness: (" + str_thickness_ + ")</b>");
    ui->textEdit_8->setHtml("<b>FocalDisk: (" + str_focalDisk_ + ")</b>");
    ui->textEdit_9->setHtml("<b>ParallelScale: (" + str_setParallelScale_ + ")</b>");
    ui->textEdit_10->setHtml("<b>eyeSeparation: (" + str_eyeSeparation_ + ")</b>");

    ui->textEdit_11->setHtml("<b>windowCenter: (" + str_windowCenter_x+", "+str_windowCenter_y + ")</b>");
    ui->textEdit_12->setHtml("<b>Screen Bottom Left: (" + str_ScreenBottomLeft_x+", "+str_ScreenBottomLeft_y+", "+str_ScreenBottomLeft_z+ ")</b>");
    ui->textEdit_13->setHtml("<b>viewShear: (" + str_viewShear_x+", "+str_viewShear_y+", "+str_viewShear_z+ ")</b>");

    ui->textEdit_14->setHtml("<b>eye position: (" + str_eyePosition_x+", "+str_eyePosition_y+", "+str_eyePosition_z+ ")</b>");
    ui->textEdit_15->setHtml("<b>eye angle: (" + str_eyeAngle + ")</b>");
    ui->textEdit_16->setHtml("<b>useHorizontalViewAngle: (" + str_useHorizontalViewAngle + ")</b>");
    renderWindow_->Render();
}

void GLWidget::on_save3DPhoto_clicked()
{
    QString photoName = "01.png";
    savePDF->savePhoto(renderWidget_, photoName);
}

void GLWidget::on_Azimuth_clicked()
{
    testVtkCamera->testAzimuth(renderer_, -10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Azimuth_2_clicked() {
    testVtkCamera->testAzimuth(renderer_, 10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Roll_clicked() {
    testVtkCamera->testRoll(renderer_, -10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Roll_2_clicked() {
    testVtkCamera->testRoll(renderer_, 10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Elevation_clicked() {
    testVtkCamera->testElevation(renderer_, -10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Elevation_2_clicked() {
    testVtkCamera->testElevation(renderer_, 10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::get3DWindow() {
    renderer_->GetActiveCamera()->Elevation(10);
    renderer_->GetActiveCamera()->OrthogonalizeViewUp();
    renderer_->GetActiveCamera()->Azimuth(10);
    renderer_->GetActiveCamera()->Roll(10);
}

void GLWidget::on_Dolly_clicked() {
    testVtkCamera->testDolly(renderer_, 0.5);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Dolly_2_clicked() {
    testVtkCamera->testDolly(renderer_, 1.5);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Zoom_clicked() {
    testVtkCamera->testZoom(renderer_, 0.75);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Zoom_2_clicked() {
    testVtkCamera->testZoom(renderer_, 1.25);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Yaw_l_clicked() {
    testVtkCamera->testYaw(renderer_, -10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Yaw_r_clicked() {
    testVtkCamera->testYaw (renderer_, 10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Pitch_l_clicked() {
    testVtkCamera->testPitch (renderer_, -10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_Pitch_r_clicked() {
    testVtkCamera->testPitch(renderer_, 10);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::testSetDistance(){
    int pos = ui->setDistance_2->value();
    renderer_->GetActiveCamera()->SetDistance(pos);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetPosition(){
    int x = ui->setPosition_x->value();
    int y = ui->setPosition_y->value();
    int z = ui->setPosition_z->value();
    renderer_->GetActiveCamera()->SetPosition(x, y, z);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetFocalPoint(){
    int x = ui->setFocalPoint_x->value();
    int y = ui->setFocalPoint_y->value();
    int z = ui->setFocalPoint_z->value();
    renderer_->GetActiveCamera()->SetFocalPoint(x, y, z);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetViewUp(int x, int y, int z) {
    testVtkCamera->testSetViewUp(renderer_, x, y, z);
    renderWindow_->Render();
}

void GLWidget::on_setRoll_clicked() {

    renderWindow_->Render();
}

void GLWidget::on_setParallelProjection_on_clicked() {
    testVtkCamera->testSetParallelProjection(renderer_, 1);
//    renderer_->GetActiveCamera()->ParallelProjectionOn();
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::on_setParallelProjection_off_clicked() {
    testVtkCamera->testSetParallelProjection(renderer_, 0);
//    renderer_->GetActiveCamera()->ParallelProjectionOff();
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::testSetClippingRange() {
    double clippingRange_[2];
    clippingRange_[0] = ui->setClippingRange_f->value();
    clippingRange_[1] = ui->setClippingRange_b->value();
    testVtkCamera->testSetClippingRange(renderer_, clippingRange_[0], clippingRange_[1]);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::testSetViewAngle() {
    int pos = ui->setViewAngle->value();
    testVtkCamera->testSetViewAngle(renderer_, pos);
    renderWindow_->Render();
    getCameraPrame();
}

//TODO:
void GLWidget::testSetWindowCenter(){
    double windowCenter[2];
    windowCenter[0] = ui->SetWindowCenter_2->value();
    windowCenter[1] = ui->SetWindowCenter_3->value();
    renderer_->GetActiveCamera()->SetWindowCenter(windowCenter[0], windowCenter[1]);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetFocalDisk(){
    double focalDisk = ui->setFocalDisk->value();
    renderer_->GetActiveCamera()->SetFocalDisk(focalDisk);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::TestSetScreenBottomLeft(){
    double screenBottomLeft[3];
    screenBottomLeft[0] = ui->SetScreenBottomLeft->value();
    screenBottomLeft[1] = ui->SetScreenBottomLeft_2->value();
    screenBottomLeft[2] = ui->SetScreenBottomLeft_3->value();
    renderer_->GetActiveCamera()->SetScreenBottomLeft(screenBottomLeft);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::on_useOffAxisProjectionOn_clicked()
{
    renderer_->GetActiveCamera()->UseOffAxisProjectionOn ();
    getCameraPrame();
}

void GLWidget::on_useOffAxisProjectionOff_clicked()
{
    renderer_->GetActiveCamera()->UseOffAxisProjectionOff ();
    getCameraPrame();
}

void GLWidget::setParallelScale() {
    int pos = ui->setParallelScale->value();
    testVtkCamera->testSetParallelScale(renderer_, pos);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::TestSetEyeSeparation() {
    int eyeSeparation = ui->SetEyeSeparation_2->value();
    renderer_->GetActiveCamera()->SetEyeSeparation (eyeSeparation);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::testSetEyePosition() {
    double eyePosition[3];
    eyePosition[0] = ui->setEyePosition_x->value();
    eyePosition[1] = ui->setEyePosition_y->value();
    eyePosition[2] = ui->setEyePosition_z->value();
    renderer_->GetActiveCamera()->SetEyePosition(eyePosition);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetViewShear() {
    double viewShear[3];
    viewShear[0] = ui->SetViewShear->value();
    viewShear[1] = ui->SetViewShear_2->value();
    viewShear[2] = ui->SetViewShear_3->value();
    renderer_->GetActiveCamera()->SetViewShear(viewShear);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetEyeAngle() {
    int eyeAngle;
    eyeAngle = ui->setEyeAngle->value();
    renderer_->GetActiveCamera()->SetEyeAngle(eyeAngle);
    renderWindow_->Render();

    getCameraPrame();
}

void GLWidget::testSetUseHorizontalViewAngle() {
    int pos = ui->setUseHorizontalViewAngle_2->value();
    testVtkCamera->testSetUseHorizontalViewAngle(renderer_, pos);
    renderWindow_->Render();
    getCameraPrame();
}

void GLWidget::getCameraPrame() {
    double distance_;
    double position_[3];
    double viewUp_[3];
    double focalPoint_[3];
    double clippingRange_[2];
    double viewAngle_;
    double thickness_;
    double windowCenter_[2];
    double focalDisk_;
    double setParallelScale_;
    double eyeSeparation_;
    double eyePosition_[3];
    double eyeAngle_;
    double ScreenBottomLeft_[3];
    double viewShear_[3];
    double useHorizontalViewAngle_;

    renderer_->GetActiveCamera()->GetPosition(position_);
    renderer_->GetActiveCamera()->GetViewUp(viewUp_);
    renderer_->GetActiveCamera()->GetFocalPoint(focalPoint_);
    renderer_->GetActiveCamera()->GetClippingRange(clippingRange_);
    distance_ = renderer_->GetActiveCamera()->GetDistance();
    viewAngle_ = renderer_->GetActiveCamera()->GetViewAngle();
    renderer_->GetActiveCamera()->GetEyePosition(eyePosition_);
    eyeAngle_ = renderer_->GetActiveCamera()->GetEyeAngle();
    useHorizontalViewAngle_ = renderer_->GetActiveCamera()->GetUseHorizontalViewAngle();
    thickness_ = renderer_->GetActiveCamera()->GetThickness();
    focalDisk_ = renderer_->GetActiveCamera ()->GetFocalDisk ();
    setParallelScale_ = renderer_->GetActiveCamera ()->GetParallelScale ();
    eyeSeparation_ = renderer_->GetActiveCamera ()->GetEyeSeparation ();
    renderer_->GetActiveCamera ()->GetWindowCenter (windowCenter_);
    renderer_->GetActiveCamera ()->GetScreenBottomLeft (ScreenBottomLeft_);
    renderer_->GetActiveCamera ()->GetViewShear (viewShear_);

    QString str_distance = QString("%1").arg(distance_);
    QString str_viewAngle = QString("%1").arg(viewAngle_);
    QString str_position_x = QString("%1").arg(position_[0]);
    QString str_position_y = QString("%1").arg(position_[1]);
    QString str_position_z = QString("%1").arg(position_[2]);
    QString str_viewUp_x = QString("%1").arg(viewUp_[0]);
    QString str_viewUp_y = QString("%1").arg(viewUp_[1]);
    QString str_viewUp_z = QString("%1").arg(viewUp_[2]);
    QString str_focalPoint_x = QString("%1").arg(focalPoint_[0]);
    QString str_focalPoint_y = QString("%1").arg(focalPoint_[1]);
    QString str_focalPoint_z = QString("%1").arg(focalPoint_[2]);
    QString str_clippingRange_f = QString("%1").arg(clippingRange_[0]);
    QString str_clippingRange_b = QString("%1").arg(clippingRange_[1]);

    QString str_thickness_ = QString("%1").arg(thickness_);
    QString str_focalDisk_ = QString("%1").arg(focalDisk_);
    QString str_setParallelScale_ = QString("%1").arg(setParallelScale_);
    QString str_eyeSeparation_ = QString("%1").arg(eyeSeparation_);

    QString str_windowCenter_x = QString("%1").arg(windowCenter_[0]);
    QString str_windowCenter_y = QString("%1").arg(windowCenter_[1]);

    QString str_ScreenBottomLeft_x = QString("%1").arg(ScreenBottomLeft_[0]);
    QString str_ScreenBottomLeft_y = QString("%1").arg(ScreenBottomLeft_[1]);
    QString str_ScreenBottomLeft_z = QString("%1").arg(ScreenBottomLeft_[2]);

    QString str_viewShear_x = QString("%1").arg(viewShear_[0]);
    QString str_viewShear_y = QString("%1").arg(viewShear_[1]);
    QString str_viewShear_z = QString("%1").arg(viewShear_[2]);

    QString str_eyePosition_x = QString("%1").arg(eyePosition_[0]);
    QString str_eyePosition_y = QString("%1").arg(eyePosition_[1]);
    QString str_eyePosition_z = QString("%1").arg(eyePosition_[2]);
    QString str_eyeAngle = QString("%1").arg(eyeAngle_);
    QString str_useHorizontalViewAngle = QString("%1").arg(useHorizontalViewAngle_);



    ui->textEdit->setHtml("<b>Distance: (" + str_distance + ")</b>");
    ui->textEdit_2->setHtml("<b>camera position: (" + str_position_x+", "+str_position_y+", "+str_position_z+ ")</b>");
    ui->textEdit_3->setHtml("<b>View Up: (" + str_viewUp_x+", "+str_viewUp_y+", "+str_viewUp_z+ ")</b>");
    ui->textEdit_4->setHtml("<b>FocalPoint: (" + str_focalPoint_x+", "+str_focalPoint_y+", "+str_focalPoint_z+ ")</b>");
    ui->textEdit_5->setHtml("<b>clipping Range: (" + str_clippingRange_f+", "+str_clippingRange_b+ ")</b>");
    ui->textEdit_6->setHtml("<b>View Angle: (" + str_viewAngle + ")</b>");

    ui->textEdit_7->setHtml("<b>Thickness: (" + str_thickness_ + ")</b>");
    ui->textEdit_8->setHtml("<b>FocalDisk: (" + str_focalDisk_ + ")</b>");
    ui->textEdit_9->setHtml("<b>ParallelScale: (" + str_setParallelScale_ + ")</b>");
    ui->textEdit_10->setHtml("<b>eyeSeparation: (" + str_eyeSeparation_ + ")</b>");

    ui->textEdit_11->setHtml("<b>windowCenter: (" + str_windowCenter_x+", "+str_windowCenter_y + ")</b>");
    ui->textEdit_12->setHtml("<b>Screen Bottom Left: (" + str_ScreenBottomLeft_x+", "+str_ScreenBottomLeft_y+", "+str_ScreenBottomLeft_z+ ")</b>");
    ui->textEdit_13->setHtml("<b>viewShear: (" + str_viewShear_x+", "+str_viewShear_y+", "+str_viewShear_z+ ")</b>");

    ui->textEdit_14->setHtml("<b>eye position: (" + str_eyePosition_x+", "+str_eyePosition_y+", "+str_eyePosition_z+ ")</b>");
    ui->textEdit_15->setHtml("<b>eye angle: (" + str_eyeAngle + ")</b>");
    ui->textEdit_16->setHtml("<b>useHorizontalViewAngle: (" + str_useHorizontalViewAngle + ")</b>");

//    markFocalPoint(focalPoint);
}

void GLWidget::showCameraPrame()
{

}




