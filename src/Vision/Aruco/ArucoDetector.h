#pragma once

#include <QElapsedTimer>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTimer>

#include "../../Core.h"
#include "../CpqVideoCapture/CpqVideoCapture.h"
#include "Common.h"

cpq_start_namespace(vis)

  class ArucoDetector : public CpqVideoCapture
{
  Q_OBJECT
public:
  struct DetectorSettings
  {
    DetectorSettings(
      cv::aruco::Board* board = nullptr,
      cv::Mat* camera_matrix = nullptr,
      cv::Mat* dist_coeffs = nullptr,
      cv::aruco::DetectorParameters* params = nullptr);

    bool isOk();

    cv::Ptr<cv::aruco::Board> board;
    cv::Ptr<cv::Mat> camera_matrix;
    cv::Ptr<cv::Mat> distorsion_array;
    cv::Ptr<cv::aruco::DetectorParameters> params;
  };

  ArucoDetector(QObject* parent = nullptr);
  ~ArucoDetector();

  uint getComputePeriod();

public slots:
  virtual void onJpegCaptured(QByteArray jpeg) override;
  virtual void onFrameCaptured(CpqMat frame) override;
  void setComputePeriod(uint ms);
  void setSettings(DetectorSettings settings);

  void onCaptureStarted();
  void onCaptureReleased();

private:
  void computePosition();

  QMutex mutex;
  DetectorSettings settings;
  bool frameUpdated = false;
  CpqMat lastFrame;
  cv::Mat* frame;

  uint fps = 1000;
  uint fps_count = 0;
  uint m_computePeriod = 1e3 / 30;

  QTimer computeTimer;
  QElapsedTimer fpsTimer;
  QElapsedTimer outTimer;
};

cpq_end_namespace
