#pragma once
#include <iostream>
#include <qwidget.h>

#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class Webcam : public QWidget
{
	Q_OBJECT

public:
	Webcam(QWidget *parent = nullptr);
	void displayGesture(Mat frame, int feature[]);
	~Webcam();
public slots:
	void open_webcam();
	void update_window();
private:
	QTimer *timer;
	VideoCapture cap;
	Mat frame;
	QImage qt_image;
	int threshold_val;
};