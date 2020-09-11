#ifndef CPQVIDEOCAPTUREWORKER_PRIVATE_H
#define CPQVIDEOCAPTUREWORKER_PRIVATE_H

#include <QElapsedTimer>
#include <QMap>
#include <QMutex>
#include <QObject>
#include <QTimer>

#include <opencv2/opencv.hpp>

#include "../QCVTypes.h"

namespace cpq {
namespace vis {

class CpqVideoCaptureWorker_private : public QObject
{
  Q_OBJECT
public:
  bool isOpened() const;
  bool clientsCount() const;
  void clientRemove();
  int getRealFps();

  explicit CpqVideoCaptureWorker_private(QString url);
  static CpqVideoCaptureWorker_private* getWorker(int index);

public slots:
  void onGrabbed();
  void set(int propId, double value);

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);

private:
  void start();
  enum Type
  {
    URL,
    INDEX
  };

  Type captureType;
  QTimer timer;
  QElapsedTimer fpsTimer;

  explicit CpqVideoCaptureWorker_private(int index);
  void release();
  void clientAdd();
  bool m_isOpened = false;

  unsigned int m_count = 0;
  int m_fps = 0;
  int fps_count=0;

  QString m_url;
  int m_index;

  cv::VideoCapture capture;

  static QMutex* static_mutex;
  static QMap<int, CpqVideoCaptureWorker_private*>* static_cameras;
};
}
}
#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
