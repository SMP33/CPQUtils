#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QDebug>
#include <QObject>
#include <QSharedPointer>

#include "../QCVTypes.h"

namespace cpq {
namespace vis {

class CpqVideoCaptureWorker_private;

/// @brief cv::VideoCapture wrapper for Qt
class CpqVideoCapture : public QObject
{
  Q_OBJECT
public:
  explicit CpqVideoCapture(QObject* parent = nullptr);
  ~CpqVideoCapture();

  /// @brief See cv::VideoCapture::capture(int)
  bool capture(int index = 0);

  /// @brief See cv::VideoCapture::capture(string)
  bool capture(QString file);
  /// @brief See cv::VideoCapture::release()
  void release();
  /// @brief See cv::VideoCapture::set()
  void set(int propId, double value);

  int getRealSourceFps();

public slots:
  virtual void onFrameCaptured(cpq::vis::CpqMat mat);
  virtual void onJpegCaptured(QByteArray jpeg);

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);
  void bmpCaptured(QByteArray bmp);
  void captureStarted();
  void captureReleased();
  void setSignal(int propId, double value);

protected:
  bool checkFrameSender();

private:
  CpqVideoCaptureWorker_private* worker = nullptr;
  void connectWorker();
};
}
}

#endif // VIDEOSOURCE_H
