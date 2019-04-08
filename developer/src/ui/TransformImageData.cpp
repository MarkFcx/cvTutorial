//
// Created by cxfeng on 19-2-21.
//

#include "TransformImageData.h"

TransformImageData::TransformImageData(){

}

TransformImageData::~TransformImageData(){

}

/* @type: private
 * @Function: initialization data
 * @Input: std::string dataDir, vtkImageData * ptr
 * @Output: NO
 * @Note:
*/
void TransformImageData::initializationData(){

    pelDir = "/home/cxfeng/Desktop/My_Work/BinaryData/Binary2/pelVol.bin";
    leftDir = "/home/cxfeng/Desktop/My_Work/BinaryData/Binary2/leftVol.bin";
    rightDir = "/home/cxfeng/Desktop/My_Work/BinaryData/Binary2/rightVol.bin";
    dicomDir = "/home/cxfeng/Desktop/My_Work/DicomData/12";

    dicomDimension = new int [3]{512, 512, 600};
    spacings = new double [3]{0.96875, 0.96875, 1};
    independentComponents = true;

    pelRotateAngle = new double [3]{-8.19445, 0.0733765, 3.75134};
    pelRotateCenter = new double [3]{155, 211.188, 83};
    leftRotateAngle = new double [3]{10.5699, 0.484976, 18.9191};
    leftRotateCenter = new double [3]{340.088, 251.34, 157.613};
    rightRotateAngle = new double [3]{10.8356, -0.788843, -7.88475};
    rightRotateCenter = new double [3]{163.947, 255.421, 166.661};

    cameraPosition = new double [3]{};
    cameraViewUp = new double [3]{};
    cameraFocalPoint = new double [3]{};
    cameraClippingRange = new double [2]{};


    vtkUcharArray_Pel =
            vtkSmartPointer<vtkUnsignedCharArray>::New();
    vtkUcharArray_Left =
            vtkSmartPointer<vtkUnsignedCharArray>::New();
    vtkUcharArray_Right =
            vtkSmartPointer<vtkUnsignedCharArray>::New();

    // 4 imagedata
    pelImageData =
            vtkSmartPointer<vtkImageData>::New();
    leftImageData =
            vtkSmartPointer<vtkImageData>::New();
    rightImageData =
            vtkSmartPointer<vtkImageData>::New();
    dicomImageData =
            vtkSmartPointer<vtkImageData>::New();

    // 4 mapper
    pelVolumeMapper =
            vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    leftVolumeMapper =
            vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    rightVolumeMapper =
            vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    dicomVolumeMapper =
            vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    // 4 volume
    pelVolume =
            vtkSmartPointer<vtkVolume>::New();
    leftVolume =
            vtkSmartPointer<vtkVolume>::New();
    rightVolume =
            vtkSmartPointer<vtkVolume>::New();
    dicomVolume =
            vtkSmartPointer<vtkVolume>::New();

    renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    interactorStyle =
            vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    volumeProperty =
            vtkSmartPointer<vtkVolumeProperty>::New();
    volumeOpacity =
            vtkSmartPointer<vtkPiecewiseFunction>::New();
    color =
            vtkSmartPointer<vtkColorTransferFunction>::New();
    Renderer =
            vtkSmartPointer<vtkRenderer>::New();

    oriAxesActor =
            vtkSmartPointer<vtkAxesActor>::New();
    widget =
            vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    camera =
            vtkSmartPointer<vtkCamera>::New();
}

/* @type: private
 * @Function: read dicom series
 * @Input: std::string dataDir, vtkImageData * ptr
 * @Output: NO
 * @Note:
*/
void TransformImageData::readDicomSeries(std::string dataDir, vtkImageData * ptr){
    vtkSmartPointer<vtkDICOMImageReader> dicomReader =
            vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(dataDir.c_str());
    dicomReader->Update();

    ptr = dicomReader->GetOutput();
}

/* @type: private
 * @Function: read binary file
 * @Input: vtkImageData* imageData1, vtkImageData* imageData2
 * @Output: NO
 * @Note:
*/
void TransformImageData::readBinary(std::string dataDir, vtkUnsignedCharArray* ptr1, vtkImageData * ptr2){

    unsigned char *U_charArray_P = new unsigned char[dicomSize];
    char *binArray_P = new char[dicomSize];

    ifstream binFile(dataDir.c_str(), ios::in | ios::binary);

    binFile.read(binArray_P, dicomSize);
    binFile.close();
    U_charArray_P = reinterpret_cast<unsigned char *>(binArray_P);
    ptr1->SetArray(U_charArray_P, dicomSize, 1);

    //vtkImageData * tempImageData = vtkImageData::New();
    ptr2->GetPointData()->SetScalars(ptr1);
    ptr2->GetScalarSize();

    ptr2->SetDimensions(dicomDimension[0], dicomDimension[1],dicomDimension[2]);
    ptr2->SetSpacing(spacings[0], spacings[1], spacings[2]);
    ptr2->Modified();


}

/* @type: private
 * @Function: mask and dicom are multiplied to divide
 * @Input: vtkImageData* imageData1, vtkImageData* imageData2
 * @Output: NO
 * @Note:
*/
void TransformImageData::maskAndDicomAreMultipliedToDivideWhenYAxisMirror(vtkImageData* imageData1, vtkImageData* imageData2){
    //If the Y axis is mirror symmetrical
    unsigned char *ptr = (unsigned char *) imageData1->GetScalarPointer();
    for (int z = 0; z < dicomDimension[2]; ++z){
        for (int y = 0; y < dicomDimension[1]; ++y){
            for (int x = 0; x < dicomDimension[0]; ++x){

                double *pixel = static_cast<double *>(imageData2->GetScalarPointer(x, y, z));
                *pixel = (*pixel) * (*(ptr + x + ((dicomDimension[1]-y-1)*dicomDimension[0]) + (z*dicomDimension[1]*dicomDimension[0])));

            }
        }
    }
}

/* @type: private
 * @Function: mask and dicom are multiplied to divide
 * @Input: vtkImageData* imageData1, vtkImageData* imageData2
 * @Output: NO
 * @Note:
*/
void TransformImageData::maskAndDicomAreMultipliedToDivide(vtkImageData* imageData1, vtkImageData* imageData2){

    for (int z = 0; z < dicomDimension[2]; ++z){
        for (int y = 0; y < dicomDimension[1]; ++y){
            for (int x = 0; x < dicomDimension[0]; ++x){
                double *pixel = static_cast<double *>(imageData2->GetScalarPointer(x, y, z));
                unsigned char *ptr = (unsigned char *) imageData1->GetScalarPointer(x, y, z);
                *pixel = (*pixel) * (*ptr);
            }
        }
    }
}

/* @type: private
 * @Function: rotate volume
 * @Input: vtkVolume* volume, double rotateCenter[3], double rotateAngle[3]
 * @Output: NO
 * @Note:
*/
void TransformImageData::rotateVolume(vtkVolume* volume, double rotateCenter[3], double rotateAngle[3]){
    vtkSmartPointer<vtkTransform> transform =
            vtkSmartPointer<vtkTransform>::New();
    transform->PostMultiply();
    transform->Translate(-rotateCenter[0], -rotateCenter[1], -rotateCenter[2]);
    transform->RotateX(rotateAngle[0]);
    transform->RotateY(rotateAngle[1]);
    transform->RotateZ(rotateAngle[2]);
    transform->Translate(rotateCenter[0], rotateCenter[1], rotateCenter[2]);
    volume->SetUserTransform(transform);
}

/* @type: private
 * @Function: rotate imageData
 * @Input: vtkImageData *inputImagedata, double *rotateCenter, double *rotateAngle, int *dims
 * @Output: NO
 * @Note:
*/
void TransformImageData::rotateImageData(vtkImageData *inputImagedata, double *rotateCenter, double *rotateAngle){
    vtkImageData* outputImagedata =
            vtkImageData::New ();
    int dims[3];
    inputImagedata->GetDimensions(dims);
    outputImagedata->SetDimensions(inputImagedata->GetDimensions());
    outputImagedata->SetSpacing(inputImagedata->GetSpacing());
    outputImagedata->AllocateScalars(VTK_UNSIGNED_CHAR, 0);

    unsigned char *pTemp = (unsigned char *) outputImagedata->GetScalarPointer();
    unsigned char *ptr = (unsigned char *) inputImagedata->GetScalarPointer();

    vtkSmartPointer<vtkTransform> transform =
            vtkSmartPointer<vtkTransform>::New();
    transform->PostMultiply();
    transform->Translate(-rotateCenter[0], -rotateCenter[1], -rotateCenter[2]);
    transform->RotateX(rotateAngle[0]);
    transform->RotateY(rotateAngle[1]);
    transform->RotateZ(rotateAngle[2]);
    transform->Translate(rotateCenter[0], rotateCenter[1], rotateCenter[2]);

    vtkSmartPointer<vtkMatrix4x4> matrix = transform->GetMatrix();

    int w = 1;
    float inputVector[4]{0};
    float outputVector[4]{0};
    int count = 0;
    for (int z = 0; z < dims[2]; ++z){
        for (int y = 0; y < dims[1]; ++y){
            for (int x = 0; x < dims[0]; ++x){
                int data = (int)(*(ptr + x + (y*dims[0]) + (z*dims[1]*dims[0])));

                if(data){
                    inputVector[0] = x;
                    inputVector[1] = y;
                    inputVector[2] = z;
                    inputVector[3] = w;
                    matrix->MultiplyPoint(matrix->GetData(), inputVector, outputVector);
                    int outsize = (int)outputVector[0] + ((int)outputVector[1]*dims[0]) + ((int)outputVector[2]*dims[1]*dims[0]);

                    if(outsize >= 0 && outsize < dims[0]*dims[1]*dims[2] ){
                        *(pTemp + (int)outputVector[0] + ((int)outputVector[1]*dims[0]) + ((int)(outputVector[2])*dims[1]*dims[0])) =
                                *(ptr + x + (y*dims[0]) + (z*dims[1]*dims[0]));
                    count++;
                    }
                }
            }
        }
    }
    inputImagedata->ShallowCopy (outputImagedata);
    outputImagedata->Delete ();
}

/* @type: private
 * @Function: There dimensional reconstruction
 * @Input: NO
 * @Output: NO
 * @Note:
*/
void TransformImageData::ThereDimensionalReconstruction(){

    readBinary(pelDir, vtkUcharArray_Pel, pelImageData);
    readBinary(leftDir, vtkUcharArray_Left, leftImageData);
    readBinary(rightDir, vtkUcharArray_Right, rightImageData);

#if 0
    clock_t time1 = clock ();
    rotateImageData(pelImageData, pelRotateCenter, pelRotateAngle, dicomDimension);
    time1 = clock () - time1;
    std::cout<<"rotateImageData time :"<<(double)time1 / CLOCKS_PER_SEC<<endl;

    clock_t time2 = clock ();
    rotateImageData(leftImageData, leftRotateCenter, leftRotateAngle, dicomDimension);
    time2 = clock () - time2;
    std::cout<<"rotateImageData time :"<<(double)time2 / CLOCKS_PER_SEC<<endl;

    clock_t time3 = clock ();
    rotateImageData(rightImageData, rightRotateCenter, rightRotateAngle, dicomDimension);
    time3 = clock () - time3;
    std::cout<<"rotateImageData time :"<<(double)time3 / CLOCKS_PER_SEC<<endl;
#endif
    for(int i = 0; i < 30; i+=5)
    {
        translateImageData (pelImageData, i, BACK);
        translateImageData (leftImageData, i, UP);
        translateImageData (rightImageData, i, FRONT);


        pelVolumeMapper->SetInputData (pelImageData);
        leftVolumeMapper->SetInputData (leftImageData);
        rightVolumeMapper->SetInputData (rightImageData);
        readDicomSeries (dicomDir, dicomImageData);
        dicomVolumeMapper->SetInputData (dicomImageData);

        pelVolume->SetMapper (pelVolumeMapper);
        leftVolume->SetMapper (leftVolumeMapper);
        rightVolume->SetMapper (rightVolumeMapper);
        dicomVolume->SetMapper (dicomVolumeMapper);

#if 0
        clock_t time1 = clock ();
        rotateVolume(pelVolume, pelRotateCenter, pelRotateAngle);
        time1 = clock () - time1;
        std::cout<<"rotateVolume time :"<<(double)time1 / CLOCKS_PER_SEC<<endl;

        clock_t time2 = clock ();
        rotateVolume(leftVolume, leftRotateCenter, leftRotateAngle);
        time2 = clock () - time2;
        std::cout<<"rotateVolume time :"<<(double)time2 / CLOCKS_PER_SEC<<endl;

        clock_t time3 = clock ();
        rotateVolume(rightVolume, rightRotateCenter, rightRotateAngle);
        time3 = clock () - time3;
        std::cout<<"rotateVolume time :"<<(double)time3 / CLOCKS_PER_SEC<<endl;

#endif
        Renderer->AddVolume (pelVolume);
        Renderer->AddVolume (leftVolume);
        Renderer->AddVolume (rightVolume);
        //    Renderer->AddVolume(dicomVolume);
        Renderer->SetBackground (0, 0, 0);
        renderWindowInteractor->SetRenderWindow (renderWindow);
        volumeProperty->SetIndependentComponents (independentComponents);
        volumeOpacity->AddSegment (3, 0, 1000, 1);
        color->AddRGBSegment (0.0, 1.0, 1.0, 1.0, 3.0, 1.0, 1.0, 1.0);
        volumeProperty->SetColor (color);
        volumeProperty->SetScalarOpacity (volumeOpacity);
        volumeProperty->SetInterpolationTypeToLinear ();

        pelVolume->SetProperty (volumeProperty);
        leftVolume->SetProperty (volumeProperty);
        rightVolume->SetProperty (volumeProperty);
        dicomVolume->SetProperty (volumeProperty);

        renderWindow->SetSize (1600, 1000);
        renderWindow->AddRenderer (Renderer);
        renderWindowInteractor->SetRenderWindow (renderWindow);

        coordinateMarkerWidget ();
        markRotateCenter (leftRotateCenter);

        renderWindow->Render ();
    }

//    putPicturesInPdfFile();
    renderWindowInteractor->Start();

    for(int i = 0; i < 40; i+=5)
    {
        translateImageData (pelImageData, i, BACK);
        translateImageData (leftImageData, i, DOWN);
        translateImageData (rightImageData, i, FRONT);


        pelVolumeMapper->SetInputData (pelImageData);
        leftVolumeMapper->SetInputData (leftImageData);
        rightVolumeMapper->SetInputData (rightImageData);
        readDicomSeries (dicomDir, dicomImageData);
        dicomVolumeMapper->SetInputData (dicomImageData);

        pelVolume->SetMapper (pelVolumeMapper);
        leftVolume->SetMapper (leftVolumeMapper);
        rightVolume->SetMapper (rightVolumeMapper);
        dicomVolume->SetMapper (dicomVolumeMapper);

#if 0
        clock_t time1 = clock ();
        rotateVolume(pelVolume, pelRotateCenter, pelRotateAngle);
        time1 = clock () - time1;
        std::cout<<"rotateVolume time :"<<(double)time1 / CLOCKS_PER_SEC<<endl;

        clock_t time2 = clock ();
        rotateVolume(leftVolume, leftRotateCenter, leftRotateAngle);
        time2 = clock () - time2;
        std::cout<<"rotateVolume time :"<<(double)time2 / CLOCKS_PER_SEC<<endl;

        clock_t time3 = clock ();
        rotateVolume(rightVolume, rightRotateCenter, rightRotateAngle);
        time3 = clock () - time3;
        std::cout<<"rotateVolume time :"<<(double)time3 / CLOCKS_PER_SEC<<endl;

#endif
        Renderer->AddVolume (pelVolume);
        Renderer->AddVolume (leftVolume);
        Renderer->AddVolume (rightVolume);
        //    Renderer->AddVolume(dicomVolume);
        Renderer->SetBackground (0, 0, 0);
        renderWindowInteractor->SetRenderWindow (renderWindow);
        volumeProperty->SetIndependentComponents (independentComponents);
        volumeOpacity->AddSegment (3, 0, 1000, 1);
        color->AddRGBSegment (0.0, 1.0, 1.0, 1.0, 3.0, 1.0, 1.0, 1.0);
        volumeProperty->SetColor (color);
        volumeProperty->SetScalarOpacity (volumeOpacity);
        volumeProperty->SetInterpolationTypeToLinear ();

        pelVolume->SetProperty (volumeProperty);
        leftVolume->SetProperty (volumeProperty);
        rightVolume->SetProperty (volumeProperty);
        dicomVolume->SetProperty (volumeProperty);

        renderWindow->SetSize (1600, 1000);
        renderWindow->AddRenderer (Renderer);
        renderWindowInteractor->SetRenderWindow (renderWindow);

        coordinateMarkerWidget ();
        markRotateCenter (leftRotateCenter);

        renderWindow->Render ();
    }


}

/* @type: private
 * @Function: Set up report photos and put them in PDF
 * @Input: NO
 * @Output: NO
 * @Note:
*/
void TransformImageData::putPicturesInPdfFile(){
    changeCameraFieldOfView(0, 1, 0);
    savePngPictures("1");
    changeCameraFieldOfView(0, 4, 0);
    savePngPictures("2");
    changeCameraFieldOfView(0, 6, 0);
    savePngPictures("3");

    std::cout<<"Here is save PDF file function"<<endl;
}

/* @type: private
 * @Function: change camera field of view
 * @Input: double AzimuthDegree, double RollDegree, double ElevationDegree
 * @Output: NO
 * @Note:
*/
void TransformImageData::changeCameraFieldOfView(double AzimuthDegree, double RollDegree, double ElevationDegree){
    Renderer->GetActiveCamera()->Elevation(ElevationDegree);
    Renderer->GetActiveCamera()->Roll(RollDegree);
    Renderer->GetActiveCamera()->Azimuth(AzimuthDegree);
}

/* @type: private
 * @Function: save png pictures
 * @Input: std::string pngSaveNam
 * @Output: NO
 * @Note:
*/
void TransformImageData::savePngPictures(std::string pngSaveName){
    vtkWindowToImageFilter* WindowToImageFilter =
            vtkWindowToImageFilter::New();
    vtkPNGWriter* PNGWriter =
            vtkPNGWriter::New();
    WindowToImageFilter->SetInput(renderWindow);
    WindowToImageFilter->Update();
    PNGWriter->SetInputConnection(WindowToImageFilter->GetOutputPort());
    PNGWriter->SetFileName(pngSaveName.c_str());
    PNGWriter->SetFilePattern("png");
    PNGWriter->Write();
    PNGWriter->Delete();
    WindowToImageFilter->Delete();
}

/* @type: public
 * @Function: first entrance
 * @Input: NO
 * @Output: NO
 * @Note:
*/
void TransformImageData::show(){
    initializationData();
    ThereDimensionalReconstruction();
//    savePNGPictures();
    return;
}

/* @type: private
 * @Function: orienntation marker widget
 * @Input: NO
 * @Output: NO
 * @Note:
*/
void TransformImageData::orienntationMarkerWidget(){

        double rgba[4]{0.0, 0.0, 0.0, 0.0};
        widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
        widget->SetOrientationMarker( oriAxesActor );
        widget->SetInteractor( renderWindowInteractor );
        widget->SetViewport( 0, 0, 0.3, 0.3 );
        widget->SetEnabled( 1 );
        widget->InteractiveOn();
}

/* @type: private
 * @Function: coordinate marker widget
 * @Input: NO
 * @Output: NO
 * @Note:
*/
void TransformImageData::coordinateMarkerWidget(){

    oriAxesActor->SetPosition(0, 0, 0);
    oriAxesActor->SetTotalLength(512, 512, 600);
    oriAxesActor->SetShaftType(0);
    oriAxesActor->SetAxisLabels(1);
    oriAxesActor->SetCylinderRadius(0.002);
    Renderer->AddActor(oriAxesActor);
}

/* @type: private
 * @Function: write out binary files
 * @Input: vtkImageData *inputImagedata, std::string filename
 * @Output: NO
 * @Note:
*/
void TransformImageData::writeOutBinaryFiles(vtkImageData *inputImagedata, std::string filename){
    char *buffer = new char[dicomSize]{0};
    ofstream myFile(filename.c_str(), ios::out | ios::binary);
    if(!myFile){cout<<"false!!!"<<endl;}
    myFile.write(buffer, dicomSize);
    myFile.close();
}

/* @type: private
 * @Function: use there polydata mark rotate center
 * @Input: double *rotateCenter
 * @Output: NO
 * @Note:
*/
void TransformImageData::markRotateCenter(double *rotateCenter){
    vtkSmartPointer<vtkSphereSource> pelSphere =
            vtkSmartPointer<vtkSphereSource>::New();
    pelSphere->SetRadius( 10 );
    vtkSmartPointer<vtkSphereSource> leftSphere =
            vtkSmartPointer<vtkSphereSource>::New();
    leftSphere->SetRadius( 10 );
    vtkSmartPointer<vtkSphereSource> rightSphere =
            vtkSmartPointer<vtkSphereSource>::New();
    rightSphere->SetRadius( 10 );

    vtkSmartPointer<vtkPolyDataMapper> pelSphereMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    pelSphereMapper->SetInputConnection( pelSphere->GetOutputPort() );
    vtkSmartPointer<vtkPolyDataMapper> leftSphereMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    leftSphereMapper->SetInputConnection( leftSphere->GetOutputPort() );
    vtkSmartPointer<vtkPolyDataMapper> rightSphereMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    rightSphereMapper->SetInputConnection( rightSphere->GetOutputPort() );

    vtkSmartPointer<vtkActor> pelSphereActor =
            vtkSmartPointer<vtkActor>::New();
    pelSphereActor->SetMapper( pelSphereMapper );
    pelSphereActor->GetProperty ()->SetColor (255, 0 ,0);
    vtkSmartPointer<vtkActor> leftSphereActor =
            vtkSmartPointer<vtkActor>::New();
    leftSphereActor->SetMapper( leftSphereMapper );
    leftSphereActor->GetProperty ()->SetColor (0, 255 ,0);
    vtkSmartPointer<vtkActor> rightSphereActor =
            vtkSmartPointer<vtkActor>::New();
    rightSphereActor->SetMapper( rightSphereMapper );
    rightSphereActor->GetProperty ()->SetColor (0, 0 ,255);

    pelSphereActor->SetPosition(155, 211.188, 83);
    leftSphereActor->SetPosition(340.088, 251.34, 157.613);
    rightSphereActor->SetPosition(163.947, 255.421, 166.661);

    Renderer->AddActor(pelSphereActor);
    Renderer->AddActor(leftSphereActor);
    Renderer->AddActor(rightSphereActor);

}

/* @type: private
 * @Function: translate imageData
 * @Input: vtkImageData * img, int offset, int mode
 * @Output: NO
 * @Note:
*/
void TransformImageData::translateImageData(vtkImageData * img, int offset, int mode)
{
    vtkImageData* outputImagedata =
            vtkImageData::New ();
    int dims[3];
    img->GetDimensions(dims);
    outputImagedata->SetDimensions(img->GetDimensions());
    outputImagedata->SetSpacing(img->GetSpacing());
    outputImagedata->AllocateScalars(VTK_UNSIGNED_CHAR, 0);

    unsigned char *pTemp = (unsigned char *) outputImagedata->GetScalarPointer();
    unsigned char *ptr = (unsigned char *) img->GetScalarPointer();

    vtkSmartPointer<vtkTransform> transform =
            vtkSmartPointer<vtkTransform>::New();
    transform->PostMultiply();

    int data = 0;

    if(mode == UP)
    {
        for (int z = 0; z < 1; ++z)
        {
            for (int y = 0; y < dims[1]; ++ y)
            {
                for (int x = 0; x < dims[0]; ++ x)
                {
                    data = (int) (*(ptr + x + (y * dims[0]) + (z * dims[1] * dims[0])));

                    if (data)
                    {
                        return;
                    }
                }
            }
        }
        if(data == 0)
        {
            transform->Translate(0, 0, -offset);
        }

    }
    else if(mode == BACK)
    {
        transform->Translate(0, offset, 0);
    }
    else if(mode == LEFT)
    {
        transform->Translate(-offset, 0, 0);
    }
    else if(mode == RIGHT)
    {
        transform->Translate(offset, 0, 0);
    }
    else if(mode == FRONT)
    {
        transform->Translate(0, -offset, 0);
    }
    else if(mode == DOWN)
    {
        for (int z = dims[2]-1; z > dims[2]-2; --z)
        {
            for (int y = dims[1]; y > 0; --y)
            {
                for (int x = dims[0]; x > 0; --x)
                {
                    int data = (int) (*(ptr + x + (y * dims[0]) + (z * dims[1] * dims[0])));

                    if (data)
                    {
                        return;
                    }
                }
            }
        }
        if(data == 0)
        {
            transform->Translate(0, 0, offset);
        }
    }
    vtkSmartPointer<vtkMatrix4x4> matrix = transform->GetMatrix();

    int w = 1;
    float inputVector[4]{0};
    float outputVector[4]{0};
    for (int z = 0; z < dims[2]; ++z)
    {
        for (int y = 0; y < dims[1]; ++y)
        {
            for (int x = 0; x < dims[0]; ++x)
            {
                int data = (int)(*(ptr + x + (y*dims[0]) + (z*dims[1]*dims[0])));

                if(data)
                {
                    inputVector[0] = x;
                    inputVector[1] = y;
                    inputVector[2] = z;
                    inputVector[3] = w;
                    matrix->MultiplyPoint(matrix->GetData(), inputVector, outputVector);
                    int outsize = (int)outputVector[0] + ((int)outputVector[1]*dims[0]) + ((int)outputVector[2]*dims[1]*dims[0]);

                    if(outsize >= 0 && outsize < dims[0]*dims[1]*dims[2] )
                    {
                        *(pTemp + (int)outputVector[0] + ((int)outputVector[1]*dims[0]) + ((int)(outputVector[2])*dims[1]*dims[0])) =
                                *(ptr + x + (y*dims[0]) + (z*dims[1]*dims[0]));
                    }
                }
            }
        }
    }
    img->ShallowCopy (outputImagedata);
    outputImagedata->Delete ();
}








