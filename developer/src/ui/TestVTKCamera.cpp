//
// Created by cxfeng on 19-4-2.
//
#include "ui_GLwidget.h"
#include "TestVTKCamera.h"

void TestVTKCamera::testAzimuth(vtkRenderer * renderer_, int value) {
    renderer_->GetActiveCamera()->Azimuth(value);
}

void TestVTKCamera::testRoll(vtkRenderer *renderer_, int value) {
    renderer_->GetActiveCamera()->Roll(value);
}

void TestVTKCamera::testElevation(vtkRenderer *renderer_, int value) {
    renderer_->GetActiveCamera()->Elevation(value);
    renderer_->GetActiveCamera()->OrthogonalizeViewUp();
}

void TestVTKCamera::testDolly(vtkRenderer *renderer_, double value) {
    renderer_->GetActiveCamera()->Dolly(value);
}

void TestVTKCamera::testZoom(vtkRenderer *renderer_, double value) {
    renderer_->GetActiveCamera()->Zoom(value);
}

void TestVTKCamera::testYaw(vtkRenderer * renderer_, double value) {
    renderer_->GetActiveCamera()->Yaw(value);
}

void TestVTKCamera::testPitch(vtkRenderer * renderer_, double value) {
    renderer_->GetActiveCamera()->Pitch(value);
}

void TestVTKCamera::testSetDistance(vtkRenderer * renderer_) {

}

void TestVTKCamera::testSetPosition(vtkRenderer *renderer_) {
    renderer_->GetActiveCamera()->SetPosition(100, 100, 100);
}

void TestVTKCamera::testSetFocalPoint(vtkRenderer *renderer_) {
    renderer_->GetActiveCamera()->SetFocalPoint(1,1,1);
}

void TestVTKCamera::testSetViewUp(vtkRenderer *renderer_, int x, int y, int z) {
    renderer_->GetActiveCamera()->SetViewUp(x, y, z);
}

void TestVTKCamera::testSetRoll(vtkRenderer *renderer_) {
    renderer_->GetActiveCamera()->SetRoll(45);
}

void TestVTKCamera::testSetParallelProjection(vtkRenderer *renderer_, int flag) {
    renderer_->GetActiveCamera()->SetParallelProjection(flag);
}

void TestVTKCamera::testSetUseHorizontalViewAngle(vtkRenderer *renderer_, int value) {
    renderer_->GetActiveCamera()->SetUseHorizontalViewAngle(value);
}

void TestVTKCamera::testSetViewAngle(vtkRenderer *renderer_, double value) {
    renderer_->GetActiveCamera()->SetViewAngle(value);
}

void TestVTKCamera::testSetParallelScale(vtkRenderer *renderer_, double value) {
    renderer_->GetActiveCamera()->SetParallelScale(value);
}

void TestVTKCamera::testSetClippingRange(vtkRenderer *renderer_, double dNear, double dFar) {
    renderer_->GetActiveCamera()->SetClippingRange(dNear+0.01, dFar);
}
