//
// Created by cxfeng on 19-4-2.
//

#ifndef AIBONE_TESTVTKCAMERA_H
#define AIBONE_TESTVTKCAMERA_H

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>

class TestVTKCamera {
public:
    void testAzimuth(vtkRenderer * renderer_, int value);

    void testRoll(vtkRenderer * renderer_, int value);

    void testElevation(vtkRenderer * renderer_, int value);

    void testDolly(vtkRenderer * renderer_, double value);

    void testZoom(vtkRenderer * renderer_, double value);

    void testYaw(vtkRenderer * renderer_, double value);

    void testPitch(vtkRenderer * renderer_, double value);

    void testSetDistance(vtkRenderer * renderer_);

    void testSetPosition(vtkRenderer * renderer_);

    void testSetFocalPoint(vtkRenderer * renderer_);

    void testSetViewUp(vtkRenderer *renderer_, int x, int y, int z);

    void testSetRoll(vtkRenderer * renderer_);

    void testSetParallelProjection(vtkRenderer * renderer_, int flag);

    void testSetUseHorizontalViewAngle(vtkRenderer * renderer_, int value);

    void testSetViewAngle(vtkRenderer * renderer_, double value);

    void testSetParallelScale(vtkRenderer * renderer_, double value);

    void testSetClippingRange(vtkRenderer * renderer_, double dNear, double dFar);

private:

};


#endif //AIBONE_TESTVTKCAMERA_H
