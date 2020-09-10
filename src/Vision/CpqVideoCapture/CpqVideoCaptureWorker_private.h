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
  bool set(int propId, double value);

  explicit CpqVideoCaptureWorker_private(QString url);
  static CpqVideoCaptureWorker_private* getWorker(int index);

public slots:
  void onGrabbed();

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

  explicit CpqVideoCaptureWorker_private(int index);
  void release();
  bool m_isOpened = false;

  void clientAdd();

  unsigned int m_count = 0;

  QString m_url;
  int m_index;

  cv::VideoCapture capture;

  static QMutex* static_mutex;
  static QMap<int, CpqVideoCaptureWorker_private*>* static_cameras;
};
}
}
#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
