#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camera_system.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pbStartCamera_clicked(bool checked);

    void on_disp_max_sliderMoved(int position);

    void on_disp_min_sliderMoved(int position);

    void on_dispmap_max_sliderMoved(int position);

    void on_dispmap_min_sliderMoved(int position);

    void on_sb_stereo_mask_sliderMoved(int position);

private:
        int timerId;
    Ui::MainWindow *ui;
    CameraSystem camera;
    QTimer *timer;
    void timerEvent(QTimerEvent *event);
    int counter;

};

#endif // MAINWINDOW_H
