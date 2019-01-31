#include "webcam.h"
#include <string>
#include <vector>

#include <qwidget.h>
#include <QVBoxLayout>
#include <qcamera.h>
#include <qcameraviewfinder.h>
#include <qthread.h>

bool cwComp(Point p1, Point p2) {
	return p1.x < p2.x;
}

Webcam::Webcam(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
	timer = new QTimer(parent);
	QCamera *camera = new QCamera();
	QCameraViewfinder *viewFinder = new QCameraViewfinder();
	camera->setViewfinder(viewFinder);
	camera->start();

    layout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    //viewFinder->showFullScreen();
    //layout->setAlignment(Qt::AlignRight);
    //layout->setDirection(QVBoxLayout::LeftToRight);
    layout->addWidget(viewFinder);
    this->setLayout(layout);
}

void Webcam::displayGesture(Mat frame, int feature[]) {
	std::string result = "인식 할수 없습니다.";
	int b0 = feature[0];
	int b1 = feature[1];
	int b2 = feature[2];
	int b3 = feature[3];
	int b4 = feature[4];
	if ((b0 == 1 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 0))
		result = "ㅏ";
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 1)
		result = "ㄱ";
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 0)
		result = "ㄴ";
	else if (b0 == 0 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 1)
		result = "ㄷ";
	else if (b0 == 0 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 1)
		result = "ㄹ";
	else if (b0 == 0 && b1 == 1 && b2 == 1 && b3 == 0 && b4 == 0)
		result = "ㅁ";
	else if (b0 == 0 && b1 == 1 && b2 == 1 && b3 == 1 && b4 == 0)
		result = "ㅂ";
	else if (b0 == 1 && b1 == 1 && b2 == 1 && b3 == 0 && b4 == 1)
		result = "ㅇ";
	else if ((b0 == 0 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 0) || (b0 == 0 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 1))
		result = "ㅎ";
	else if (b0 == 0 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 1)
		result = "ㅅ";
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 0 && b4 == 1)
		result = "ㅔ";
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 0 && b4 == 0)
		result = "ㅣ";
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 0 && b4 == 1)
		result = "ㅗ";
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 0 && b4 == 0)
		result = "ㅛ";
	else if ((b0 == 1 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 1) || (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 0) || (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 0) || (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 1))
		result = "ㅕ";
	else
		result = "인식 하지 못했습니다.";

	putText(frame, result, Point(frame.cols - 100, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 4);
	std::cout << " result : " << result << std::endl;
}

void Webcam::open_webcam()
{
	cap.open(0);

	if (!cap.isOpened())
		return;
	else
	{
		connect(timer, &QTimer::timeout, this, &Webcam::update_window);
		timer->start(20);
	}
}

void Webcam::update_window()
{
	cap >> frame;

	cvtColor(frame, frame, CV_BGR2RGB);
    flip(frame, frame, 1);
	qt_image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
}

Webcam::~Webcam()
{
}
