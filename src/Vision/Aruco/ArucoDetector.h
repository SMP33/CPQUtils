#pragma once

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>

#include "../../Core.h"
#include "../CpqVideoCapture/CpqVideoCapture.h"

cpq_start_namespace(vis)

  class ArucoDetector : public CpqVideoCapture
{
  Q_OBJECT
public:
  ArucoDetector(QObject* parent = nullptr);

public slots:
  virtual void onJpegCaptured(QByteArray jpeg) override;
  virtual void onFrameCaptured(CpqMat mat) override;

private:
  void computePosition();

  CpqMat mat;
  bool frameUpdated = false;

  QTimer timer;

  QElapsedTimer fpsTimer;

  uint fps = 1000;
  uint fps_count = 0;
  uint nsec = 1;

};

cpq_end_namespace
