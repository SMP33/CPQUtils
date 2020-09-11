#include "ArucoDetector.h"

#include <QDateTime>
#include <QThread>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

using namespace cpq::vis;

ArucoDetector::ArucoDetector(QObject* parent)
  : CpqVideoCapture(parent)
  , frame(new cv::Mat())
{
  fpsTimer.start();
  outTimer.start();

  connect(this,
          &CpqVideoCapture::captureStarted,
          this,
          &ArucoDetector::onCaptureStarted);
  connect(this,
          &CpqVideoCapture::captureReleased,
          this,
          &ArucoDetector::onCaptureReleased);

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
    QMutexLocker lock(&mutex);
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
  computeTimer.setTimerType(Qt::TimerType::PreciseTimer);
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
      qDebug() << "Detector fps:" << fps;
      qDebug() << "Source fps:" << getRealSourceFps();
    }
    fps_count++;

    // Update frame
    *frame = cv::Mat(lastFrame.size.height(),
                     lastFrame.size.width(),
                     lastFrame.type,
                     (uchar*)lastFrame.data.data());
    // Compute frame
    if (settings.isOk()) {
      std::vector<int> markerIds(20);
      std::vector<std::vector<cv::Point2f>> markerCorners(20);
      cv::Vec3d rvec, tvec;

      cv::aruco::detectMarkers(*frame,
                               settings.board->dictionary,
                               markerCorners,
                               markerIds,
                               settings.params,
                               cv::noArray(),
                               *settings.camera_matrix,
                               *settings.distorsion_array);

      if (markerIds.size() > 0) {

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

    if (!frame->empty() && outTimer.elapsed() > 1e3 / 10) {
      outTimer.restart();

      std::vector<uchar> buff;
      std::vector<int> param(2);
      param[0] = cv::IMWRITE_JPEG_QUALITY;
      param[1] = 100;

      cv::imencode(".jpeg", *frame, buff, param);
      QByteArray* arr =
        new QByteArray(reinterpret_cast<const char*>(buff.data()), buff.size());
      emit jpegCaptured(*arr);

      delete arr;
    }
    frameUpdated = false;
  }
}

ArucoDetector::DetectorSettings::DetectorSettings(
  cv::aruco::Board* board,
  cv::Mat* camera_matrix,
  cv::Mat* dist_coeffs,
  cv::aruco::DetectorParameters* params)
  : board(board)
  , camera_matrix(camera_matrix)
  , distorsion_array(dist_coeffs)
  , params(params)

{}
bool
ArucoDetector::DetectorSettings::isOk()
{
  return (board && camera_matrix && distorsion_array && params);
}