#ifndef CPQVIDEOCAPTUREWORKER_PRIVATE_H
#define CPQVIDEOCAPTUREWORKER_PRIVATE_H

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QThread>

#include <opencv2/opencv.hpp>

#include "../QCVTypes.h"

class CpqVideoCaptureWorker_private : public QThread
{
  Q_OBJECT
public:
  explicit CpqVideoCaptureWorker_private(int index, QObject* parent);
  explicit CpqVideoCaptureWorker_private(QString file, QObject* parent);

protected:
  void run();

private:
  cv::VideoCapture capture;
};

#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
