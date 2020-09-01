#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QtDebug>

#include "../QCVTypes.h"

namespace cpq {
namespace vis {

class CpqVideoCaptureWorker_private;

class CpqVideoCapture : public QObject
{
  Q_OBJECT
public:
  explicit CpqVideoCapture(QObject* parent = nullptr);
  bool capture(int index = 0);
  bool capture(QString filename);
  void release();

signals:
  void frameCaptured(cpq::vis::CpqMat mat);

private:
  CpqVideoCaptureWorker_private* worker = nullptr;
  void clearWorker();
};
}
}

#endif // VIDEOSOURCE_H
