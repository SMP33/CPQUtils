#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QtDebug>
#include <QSharedPointer>

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

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);

private:
  QSharedPointer<CpqVideoCaptureWorker_private> worker = nullptr;
  void clearWorker();
};
}
}

#endif // VIDEOSOURCE_H
