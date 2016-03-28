#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera_system.h"
#include <QTimer>
#include <QObject>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include "mat2qimage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    counter =0;
    ui->setupUi(this);
        timerId = startTimer(50);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    counter +=1;
    ui->labelCounter->setText(QString("Count is: %1").arg(QString::number(counter)));
    if (ui->pbStartCamera->isChecked())
    {
        camera.run();
        ui->labelDispImage->setPixmap(QPixmap::fromImage(Mat2QImage(camera.getDisparityImage())));
    }
}

void MainWindow::on_pbStartCamera_clicked(bool checked)
{
    if (checked)
    {
        camera.startUp();
        ui->labelResolution->setText(QString::fromStdString(camera.getResolution()));
    }
    else
    {
        camera.shutdown();
    }
}

void MainWindow::on_disp_max_sliderMoved(int position)
{
    int disp_min = ui->disp_min->value();
    int disp_max = position;

    if (disp_min > (disp_max -1)){
        ui->disp_min->setValue(disp_max -1);
    }
    else if ((disp_max - disp_min) > 240){
        ui->disp_min->setValue(disp_max -240);
    }

    ui->label_max_disp->setText(QString("Maximum Disparity: %1").arg(QString::number(ui->disp_max->value())));
    ui->label_min_disp->setText(QString("Minimum Disparity: %1").arg(QString::number(ui->disp_min->value())));
    camera.setDispMax(ui->disp_max->value());
    camera.setDispMin(ui->disp_min->value());
}

void MainWindow::on_disp_min_sliderMoved(int position)
{
    int disp_min = position;
    int disp_max = ui->disp_max->value();

    if ((disp_min + 1) > disp_max){
        ui->disp_max->setValue(disp_min + 1);
    }
    else if ((disp_max - disp_min) > 240){
        ui->disp_max->setValue(disp_min +240);
    }

    ui->label_max_disp->setText(QString("Maximum Disparity: %1").arg(QString::number(ui->disp_max->value())));
    ui->label_min_disp->setText(QString("Minimum Disparity: %1").arg(QString::number(ui->disp_min->value())));
    camera.setDispMax(ui->disp_max->value());
    camera.setDispMin(ui->disp_min->value());
}

void MainWindow::on_dispmap_max_sliderMoved(int position)
{
    int dispmap_min = ui->dispmap_min->value();
    int dispmap_max = position;

    if ((dispmap_min + 1) > dispmap_max){
        ui->dispmap_min->setValue(dispmap_max - 1);
    }
    ui->label_dispmap_max->setText(QString("Maximum Disparity Map: %1").arg(QString::number(ui->dispmap_max->value())));
    ui->label_dispmap_min->setText(QString("Minimum Disparity Map: %1").arg(QString::number(ui->dispmap_min->value())));
    camera.setDispMapMax(ui->dispmap_max->value());
    camera.setDispMapMin(ui->dispmap_min->value());
}

void MainWindow::on_dispmap_min_sliderMoved(int position)
{
    int dispmap_min = position;
    int dispmap_max = ui->dispmap_max->value();

    if ((dispmap_min + 1) > dispmap_max){
        ui->dispmap_max->setValue(dispmap_min + 1);
    }
    ui->label_dispmap_max->setText(QString("Maximum Disparity Map: %1").arg(QString::number(ui->dispmap_max->value())));
    ui->label_dispmap_min->setText(QString("Minimum Disparity Map: %1").arg(QString::number(ui->dispmap_min->value())));
    camera.setDispMapMax(ui->dispmap_max->value());
    camera.setDispMapMin(ui->dispmap_min->value());
}

void MainWindow::on_sb_stereo_mask_sliderMoved(int position)
{
    camera.setStereoMask(position);
}
