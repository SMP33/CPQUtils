#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QSharedPointer>
#include <QDebug>

#include "../QCVTypes.h"

namespace cpq {
namespace vis {

class CpqVideoCaptureWorker_private;

class CpqVideoCapture : public QObject
{
  Q_OBJECT
public:
  explicit CpqVideoCapture(QObject* parent = nullptr);
  ~CpqVideoCapture();

  bool capture(int index = 0);
  bool capture(QString file);
  void release();

public slots:
  virtual void onFrameCaptured(cpq::vis::CpqMat mat);
  virtual void onJpegCaptured(QByteArray jpeg);

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);
  void captured();
  void released();

protected:
  bool checkFrameSender();

private:
  CpqVideoCaptureWorker_private* worker = nullptr;
  void connectWorker();
};
}
}

#endif // VIDEOSOURCE_H
