//
// Created by cxfeng on 19-3-12
//

#include <QString>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QVTKOpenGLWidget.h>
#include "SavePDF.h"
struct Data{
    Data(){
        name;
        gender;
        age;
        medicalRecordNumber;
        date;
        department;
        hospital;
        diagnosis;
        planningDoctor;
        surgicalSite;
        planningSite;
        prostheticBrand;
        acetabularCupSize;
        acetabularCupAbductionAngle;
        acetabularCupAnteversion;
        acetabularCupCoverage;
        headSize;
        headLength;
        headChang;
        linerSize;
        femoralStemSize;
        femoralStemNeckAngle;
        osteotomyHeight;
        beforePlanningLegLengthDifference;
        beforePlanningLeftLegOffset;
        beforePlanningRightLegOffset;
        afterPlanningLegLengthDifference;
        afterPlanningLeftLegOffset;
        afterPlanningRightLegOffset;
    }

    QString name;
    QString gender;
    QString age;
    QString medicalRecordNumber;
    QString date;
    QString department;
    QString hospital;
    QString diagnosis;
    QString planningDoctor;
    QString surgicalSite;
    QString planningSite;
    QString prostheticBrand;
    QString cup;
    QString acetabularCupSize;
    QString acetabularCupAbductionAngle;
    QString acetabularCupAnteversion;
    QString acetabularCupCoverage;
    QString head;
    QString headSize;
    QString headLength;
    QString headChang;
    QString liner;
    QString linerSize;
    QString stem;
    QString femoralStemSize;
    QString femoralStemNeckAngle;
    QString osteotomyHeight;
    QString beforePlanningLegLengthDifference;
    QString beforePlanningLeftLegOffset;
    QString beforePlanningRightLegOffset;
    QString afterPlanningLegLengthDifference;
    QString afterPlanningLeftLegOffset;
    QString afterPlanningRightLegOffset;

}pdfData;

struct PhotoPath{
    QString photoPath_1;
    QString photoPath_2;
    QString photoPath_3;
    QString photoPath_4;

    PhotoPath(){
        photoPath_1 = "01.png";
        photoPath_2 = "02.png";
        photoPath_3 = "03.png";
        photoPath_4 = "04.png";
    }

}pdfPhoto;

void SavePDF::savePdf(QString pdfname) {
    htmlToPdf(pdfname);
}

void SavePDF::help() {
    std::cout<<""<<std::endl;
}

void SavePDF::setLogo() {

}

void SavePDF::setPhoto() {

}

void SavePDF::savePhoto(QVTKOpenGLWidget *widget, QString photoName) {
    vtkWindowToImageFilter* WindowToImageFilter =
            vtkWindowToImageFilter::New();
    vtkPNGWriter* PNGWriter =
            vtkPNGWriter::New();
    WindowToImageFilter->SetInput(widget->GetRenderWindow());
    WindowToImageFilter->Update();
    PNGWriter->SetInputConnection(WindowToImageFilter->GetOutputPort());
    PNGWriter->SetFileName(photoName.toStdString().c_str());
    PNGWriter->SetFilePattern("png");
    PNGWriter->Write();
    PNGWriter->Delete();
    WindowToImageFilter->Delete();
}

void SavePDF::saveCoronalViewPhoto(QVTKOpenGLWidget *widget, QString photoName) {
    vtkWindowToImageFilter* WindowToImageFilter =
            vtkWindowToImageFilter::New();
    vtkPNGWriter* PNGWriter =
            vtkPNGWriter::New();
    WindowToImageFilter->SetInput(widget->GetRenderWindow());
    WindowToImageFilter->Update();
    PNGWriter->SetInputConnection(WindowToImageFilter->GetOutputPort());
    PNGWriter->SetFileName(photoName.toStdString().c_str());
    PNGWriter->SetFilePattern("png");
    PNGWriter->Write();
    PNGWriter->Delete();
    WindowToImageFilter->Delete();
}

void SavePDF::saveSagittalViewPhoto(QVTKOpenGLWidget *widget, QString photoName) {
    vtkWindowToImageFilter* WindowToImageFilter =
            vtkWindowToImageFilter::New();
    vtkPNGWriter* PNGWriter =
            vtkPNGWriter::New();
    WindowToImageFilter->SetInput(widget->GetRenderWindow());
    WindowToImageFilter->Update();
    PNGWriter->SetInputConnection(WindowToImageFilter->GetOutputPort());
    PNGWriter->SetFileName(photoName.toStdString().c_str());
    PNGWriter->SetFilePattern("png");
    PNGWriter->Write();
    PNGWriter->Delete();
    WindowToImageFilter->Delete();
}

void SavePDF::saveTransverseViewPhoto(QVTKOpenGLWidget *widget, QString photoName) {
    vtkWindowToImageFilter* WindowToImageFilter =
            vtkWindowToImageFilter::New();
    vtkPNGWriter* PNGWriter =
            vtkPNGWriter::New();
    WindowToImageFilter->SetInput(widget->GetRenderWindow());
    WindowToImageFilter->SetViewport(100, 100, 300,300);
    WindowToImageFilter->Update();
    PNGWriter->SetInputConnection(WindowToImageFilter->GetOutputPort());
    PNGWriter->SetFileName(photoName.toStdString().c_str());
    PNGWriter->SetFilePattern("png");
    PNGWriter->Write();
    PNGWriter->Delete();
    WindowToImageFilter->Delete();
}

void SavePDF::htmlToPdf(QString pdfname) {

    QPrinter printer;
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfname);
    QTextDocument document;
    QString html = htmlLayout();
    document.setHtml(html);
    document.print(&printer);

}

QString SavePDF::htmlLayout(){
    QString html = "";
    html += "<html>";
    html += "<body>";
    html += "<p align=\"center\" style=\"font-family:arial; font-size:30px; \">AIHIP 规划报告</p>";
    html += "<hr />";
    html += "<h4>基本信息：</h4>";
    html += "<table border=\"0\">";
    html += "<tr>";
        html += "<td>姓名: ";
        html += pdfData.name;
        html += " </td>";
        html += "<td>性别: ";
        html += pdfData.gender;
        html += " </td>";
        html += "<td>年龄: ";
        html += pdfData.age;
        html += " </td>";
        html += "<td>病例号: ";
        html += pdfData.medicalRecordNumber;
        html += " </td>";
    html += "</tr>";
    html += "<tr>";
        html += "<td>检查日期: ";
        html += pdfData.date;
        html += " </td>";
        html += " <td>科室: ";
        html += pdfData.department;
        html += " </td>";
        html += " <td>医院: ";
        html += pdfData.hospital;
        html += "</td>";
        //html += "<td></td>";
    html += "</tr>";
    html += "<tr>";
        html += "<td>诊断: ";
        html += pdfData.diagnosis;
        html += "</td>";
        html += "<td></td>";
        html += "<td>规划医生: ";
        html += pdfData.planningDoctor;
        html += "</td>";
        html += "<td></td>";
    html += "</tr>";
    html += "</table>";

//    html += "<br />";

    html += "<h4>规划信息：</h4>";
    html += "<table border=\"0\">";
    html += "<tr>";
    html += "<td>手术类型: " + pdfData.surgicalSite + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>规划部位: " + pdfData.planningSite + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>假体品牌: " + pdfData.prostheticBrand + "</td>";
    html += "</tr>";
    html += "</table>";

//    html += "<br />";

    html += "<p align=\"left\" height=\"60\">髋臼杯规划信息:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"5\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">类型</td>";
    html += "<td align=\"center\" height=\"60\">尺寸</td>";
    html += "<td align=\"center\" height=\"60\">外展角</td>";
    html += "<td align=\"center\" height=\"60\">前倾角</td>";
    html += "<td align=\"center\" height=\"60\">覆盖率</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.head + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.acetabularCupSize + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.acetabularCupAbductionAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.acetabularCupAnteversion + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.acetabularCupCoverage + "</td>";
    html += "</tr>";
    html += "</table>";

//    html += "<br />";

    //<表格>矫正到标准位置后参数
    html += "<p align=\"left\" height=\"60\">球头规划信息:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"6\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">类型</td>";
    html += "<td align=\"center\" height=\"60\">尺寸</td>";
    html += "<td align=\"center\" height=\"60\">长度（加减头）</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.head+ "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.headSize+ "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.headLength+ "(" + pdfData.headChang +")" + "</td>";
    html += "</tr>";
    html += "</table>";

//    html += "<br />";

    html += "<p align=\"left\" height=\"60\">内衬规划信息:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"6\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">类型</td>";
    html += "<td align=\"center\" height=\"60\">尺寸</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.liner+ "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.linerSize+ "</td>";//
    html += "</tr>";
    html += "</table>";

//    html += "<br />";

    html += "<p align=\"left\" height=\"60\">股骨柄规划信息:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"6\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">类型</td>";
    html += "<td align=\"center\" height=\"60\">尺寸</td>";
    html += "<td align=\"center\" height=\"60\">颈干角</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.stem + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.femoralStemSize + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.femoralStemNeckAngle + "</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<p align=\"left\" height=\"60\">患侧截骨高度: 距离小转子上缘 " +pdfData.osteotomyHeight + "mm</p>";
//    html += "<br />";

    html += "<p align=\"left\" height=\"60\">解剖参数:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"6\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\"></td>";
    html += "<td align=\"center\" height=\"60\">规划前</td>";
    html += "<td align=\"center\" height=\"60\">规划后</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">腿长差(患侧较健侧)(mm)/td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.beforePlanningLegLengthDifference + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.afterPlanningLegLengthDifference + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">左腿偏距(mm)</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.beforePlanningLeftLegOffset + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.afterPlanningLeftLegOffset + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">右腿偏距(mm)</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.beforePlanningRightLegOffset + "</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.afterPlanningRightLegOffset + "</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
//    html += "<br />";
//    html += "<br />";
//    html += "<br />";
//    html += "<br />";
//    html += "<br />";
//    html += "<br />";

    html += "<hr />";

    html += "<h4 align=\"center\">图像信息</h4>";
    html += "<p align=\"center\">";
    html += "<img src=\"" + pdfPhoto.photoPath_1 + "\" align=\"center\" alt=\"picture\" width=\"288\" height=\"189\">";
    html += "<img src=\"" + pdfPhoto.photoPath_2 + "\" align=\"center\" alt=\"picture\" width=\"288\" height=\"189\">";
    html += "</p>";
    html += "<p align=\"center\">";
    html += "<img src=\"" + pdfPhoto.photoPath_3 + "\" align=\"center\" alt=\"picture\" width=\"288\" height=\"229\">";
    html += "<img src=\"" + pdfPhoto.photoPath_4 + "\" align=\"center\" alt=\"picture\" width=\"288\" height=\"229\">";
    html += "</p>";
    html += "</body>";
    html += "</html>";
    return html;
}

#if 0
QString SavePDF::htmlLayout(){
    QString html = "";
    html += "<html>";
    html += "<head>";
    html += "<title></title>";
    html += "<head>";
    html += "<body>";
#if 0
    html += "<br />";
        html += "<p align=\"center\"><img src=\"";
            html += pdfData.logo;
        html += "\" style=\"float:center\" alt=\"picture\" width=\"300\" height=\"300\"></p>";
    html += "<br />";

    html += "<table frame=\"box\">";
    html += "<tr>";
    html += "<p align=\"center\" style=\"font-family:arial; font-size:80px; \">" + pdfData.title + "</p>";
    html += "<br />";
    html += "<p align=\"center\" style=\"font-family:arial; font-size:20px; \">版本: 1.0</p>";
#endif
    html += "<br />";
    html += "<p align=\"center\" style=\"font-family:arial; font-size:40px; \">AIHIP 规划报告</p>";
    html += "<br />";
#if 0
    html += "<p align=\"center\">报告编号：" + pdfData.reportNumber +"</p>";
    html += "<br />";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<hr>";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
//    html += "<br />";
#endif
    //第二页开始
    //病人基本信息
    html += "<h4>基本信息：</h4>";
    html += "<table border=\"0\">";
    html += "<tr>";
        html += "<td>病例号: ";
        html += pdfData.medicalRecordNumber;
        html += "</td>";
        html += "<td>医院: ";
        html += pdfData.hospital;
        html += "</td>";
    html += "</tr>";
    html += "<tr>";
        html += "<td>姓名: ";
        html += pdfData.name;
        html += "</td>";
        html += "<td>性别: ";
        html += pdfData.gender;
        html += "</td>";
    html += "</tr>";
    html += "<tr>";
        html += "<td>检查日期: ";
        html += pdfData.date;
        html += "</td>";
        html += "<td>患侧: ";
        html += pdfData.illSide;
        html += "</td>";
    html += "</tr>";
    html += "<tr>";
        html += "<td>病种: ";
        html += pdfData.diseases;
        html += "</td>";
        html += "<td></td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";

    //手术基本信息
    html += "<h4>手术基本信息：</h4>";
    html += "<table border=\"0\">";
    html += "<tr>";
    html += "<td>规划医生: " + pdfData.planningDoctor + "</td>";
    html += "<td>手术医生: " + pdfData.surgeryDoctor + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>术侧: " + pdfData.surgicalSide + "</td>";
    html += "<td>手术类型: " + pdfData.typeOfSurgery + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>假体厂商: " + pdfData.prosthesisManufacturer + "</td>";
    html += "<td></td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>股骨柄系列: " + pdfData.stemSeries + "</td>";
    html += "<td></td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>髋臼杯系列: " + pdfData.cupSeries + "</td>";
    html += "<td></td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>球头: " + pdfData.head + "</td>";
    html += "<td></td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>内衬: " + pdfData.liner + "</td>";
    html += "<td></td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";

    //解剖参数
    //<表格>矫正前解剖参数:
    html += "<h4>解剖参数：</h4>";
    html += "<p align=\"left\" height=\"60\">矫正前解剖参数:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"5\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">骨盆</td>";
    html += "<td align=\"center\" height=\"60\">矢状面前倾 " + pdfData.sagittalAnteversion + "</td>";
    html += "<td align=\"center\" height=\"60\">冠状面侧倾 " + pdfData.coronalRollAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">横断面侧倾 " + pdfData.axialRollAngle + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">左股骨</td>";
    html += "<td align=\"center\" height=\"60\">内收 " + pdfData.leftFemurAdductionAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">屈曲 " + pdfData.leftFemurBucklingAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">外旋 " + pdfData.leftFemurExternalRotationAngle + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">右股骨</td>";
    html += "<td align=\"center\" height=\"60\">内收 " + pdfData.rightFemurAdductionAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">屈曲 " + pdfData.rightFemurBucklingAngle + "</td>";
    html += "<td align=\"center\" height=\"60\">外旋 " + pdfData.rightFemurExternalRotationAngle + "</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";

    //<表格>矫正到标准位置后参数
    html += "<p align=\"left\" height=\"60\">矫正到标准位置后参数:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"6\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">股骨前倾角</td>";
    html += "<td align=\"center\" height=\"60\">左: " + pdfData.leftFemoralAnteversion + "</td>";
    html += "<td align=\"center\" height=\"60\">右: " + pdfData.rightFemoralAnteversion + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">髋臼前倾角</td>";
    html += "<td align=\"center\" height=\"60\">左: " + pdfData.leftAcetabularAnteversion + "</td>";
    html += "<td align=\"center\" height=\"60\">右: " + pdfData.rightAcetabularAnteversion + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">股骨偏距</td>";
    html += "<td align=\"center\" height=\"60\">左: " + pdfData.leftFemoralOffset + "</td>";
    html += "<td align=\"center\" height=\"60\">右: " + pdfData.rightFemoralOffset + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">腿长差</td>";
    html += "<td align=\"center\" height=\"60\"> " + pdfData.lesserTrochanter + "(小转子)</td>";
    html += "<td align=\"center\" height=\"60\"> " + pdfData.rearCondyle + "(股骨后髁)</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";


    //第三页开始
    html += "<h4>假体安放信息：</h4>";
    html += "<p align=\"left\" height=\"60\">髋臼杯:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"5\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">臼杯大小</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.cupSize + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">外展角</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.outreachAngle + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">前倾角</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.anteriorAngle + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">距髋臼内壁</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.distanceToAcetabularWall + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">距髋臼切迹</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.distanceToAcetabularCuttingTrace + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">覆盖率</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.coverage + "</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";

    html += "<p align=\"left\" height=\"60\">股骨柄:</p>";
    html += "<table align=\"left\" width=\"100%\" border=\"0.5\" cellspacing=\"0.1\" cellpadding=\"5\">";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">股骨柄型号</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.femoralStemModel + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">股骨柄前倾角</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.femoralAnteversion + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">截骨高度</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.osteotomyHeight + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">LOC</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.loc + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td align=\"center\" height=\"60\">球头大小(加减头)</td>";
    html += "<td align=\"center\" height=\"60\">" + pdfData.headSize + "(" + pdfData.headSizeChange +")</td>";
    html += "</tr>";
    html += "</table>";

    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";

    html += "<hr />";

    //第4页开始
    //put photo in pdf
    //TODO: photo size need to change
    html += "<h4 align=\"center\">三维可视化</h4>";
    html += "<p  align=\"center\" height=\"60\">整体正面观:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.thereDPhotoPath_1 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "<p  align=\"center\" height=\"60\">整体左面观:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.thereDPhotoPath_2 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "<p  align=\"center\" height=\"60\">整体左面观:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.thereDPhotoPath_3 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "<br />";


    html += "<h4 align=\"center\">断层观察</h4>";
    html += "<p  align=\"center\" height=\"60\">冠状视图:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.coronalPhotoPath_1 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "<p  align=\"center\" height=\"60\">矢状视图:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.sagittalPhotoPath_1 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "<p  align=\"center\" height=\"60\">横断视图:</p>";
    html += "<p align=\"center\"><img src=\"" + pdfPhoto.axialPhotoPath_1 + "\" alt=\"picture\" width=\"290\" height=\"290\"></p>";

    html += "</body>";
    html += "</html>";
    return html;
}
#endif



