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

private:
  CpqVideoCaptureWorker_private* worker;
};
}
}

#endif // VIDEOSOURCE_H
