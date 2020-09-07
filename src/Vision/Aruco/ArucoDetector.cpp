#include "ArucoDetector.h"

#include <QThread>
#include <opencv2/opencv.hpp>

using namespace cpq::vis;

ArucoDetector::ArucoDetector(QObject* parent)
  : CpqVideoCapture(parent)
{
  fpsTimer.start();

  timer.setTimerType(Qt::TimerType::PreciseTimer);
  timer.start(50);
  connect(&timer, &QTimer::timeout, this, &ArucoDetector::computePosition);
}

void
ArucoDetector::onJpegCaptured(QByteArray jpeg)
{}

void
ArucoDetector::onFrameCaptured(CpqMat mat)
{

  if (checkFrameSender()) {
    this->mat = mat;
    frameUpdated = true;
  }
}

void
ArucoDetector::computePosition()
{
  if (frameUpdated) {
    if (fpsTimer.elapsed() > 1e3) {
      fpsTimer.restart();
      fps = fps_count;
      fps_count = 0;
      qInfo() << "Real fps:" << fps;
    }

    cv::Mat m = cv::Mat(
      mat.size.height(), mat.size.width(), mat.type, (uchar*)mat.data.data());
    if (!m.empty()) {
      emit jpegCaptured(mat2Jpeg(CpqMat(m)));
    }
    fps_count++;
    frameUpdated = false;
  }

}
