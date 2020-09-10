#include "ArucoDetector.h"

#include <QThread>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

using namespace cpq::vis;

ArucoDetector::ArucoDetector(QObject* parent)
  : CpqVideoCapture(parent)
  , frame(new cv::Mat())
{
  fpsTimer.start();

  connect(this,
          &CpqVideoCapture::captureStarted,
          this,
          &ArucoDetector::onCaptureStarted);
  connect(this,
          &CpqVideoCapture::captureReleased,
          this,
          &ArucoDetector::onCaptureReleased);

  computeTimer.setTimerType(Qt::TimerType::PreciseTimer);
  connect(
    &computeTimer, &QTimer::timeout, this, &ArucoDetector::computePosition);
}

ArucoDetector::~ArucoDetector()
{
  delete frame;
}

void
ArucoDetector::onJpegCaptured(QByteArray jpeg)
{}

uint
ArucoDetector::getComputePeriod()
{
  return m_computePeriod;
}

void
ArucoDetector::onFrameCaptured(CpqMat frame)
{

  if (checkFrameSender()) {
    this->lastFrame = frame;
    frameUpdated = true;
  }
}

void
ArucoDetector::setComputePeriod(uint ms)
{
  computeTimer.setInterval(m_computePeriod);
}

void
ArucoDetector::setSettings(DetectorSettings settings)
{
  QMutexLocker lock(&mutex);
  this->settings = settings;
}

void
ArucoDetector::onCaptureStarted()
{
  computeTimer.start(m_computePeriod);
}

void
ArucoDetector::onCaptureReleased()
{
  computeTimer.stop();
}

void
ArucoDetector::computePosition()
{
  QMutexLocker lock(&mutex);

  // Calc fps
  if (frameUpdated) {
    if (fpsTimer.elapsed() > 1e3) {
      fpsTimer.restart();
      fps = fps_count;
      fps_count = 0;
      qDebug() << "Real fps:" << fps;
    }
    fps_count++;

    // Update frame
    *frame = cv::Mat(lastFrame.size.height(),
                     lastFrame.size.width(),
                     lastFrame.type,
                     (uchar*)lastFrame.data.data());
    // Compute frame
    if (settings.isOk()) {
      std::vector<int> markerIds;
      std::vector<std::vector<cv::Point2f>> markerCorners;
      cv::aruco::detectMarkers(
        *frame, settings.board->dictionary, markerCorners, markerIds);

      if (markerIds.size() > 0) {
        cv::Vec3d rvec, tvec;
        int valid = cv::aruco::estimatePoseBoard(markerCorners,
                                                 markerIds,
                                                 settings.board,
                                                 *settings.camera_matrix,
                                                 *settings.distorsion_array,
                                                 rvec,
                                                 tvec);

        cv::aruco::drawDetectedMarkers(*frame, markerCorners, markerIds);
        if (valid > 0) {
          cv::aruco::drawAxis(*frame,
                              *settings.camera_matrix,
                              *settings.distorsion_array,
                              rvec,
                              tvec,
                              10);
        }
      }
    }

    if (!frame->empty()) {
      emit jpegCaptured(mat2Jpeg(CpqMat(*frame)));
    }
    frameUpdated = false;
  }
}

ArucoDetector::DetectorSettings::DetectorSettings(cv::aruco::Board* board,
                                                  cv::Mat* camera_matrix,
                                                  cv::Mat* dist_coeffs)
  : board(board)
  , camera_matrix(camera_matrix)
  , distorsion_array(dist_coeffs)

{}
bool
ArucoDetector::DetectorSettings::isOk()
{
  return (board && camera_matrix && distorsion_array);
}