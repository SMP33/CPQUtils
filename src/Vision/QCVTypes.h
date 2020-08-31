#ifndef QCVTYPES_H
#define QCVTYPES_H

#include <QDebug>
#include <QMetaType>
#include <QSize>

//#define NO_OPENCV

#define NO_CV_WARNING()                                                        \
  qWarning().noquote()                                                         \
    << "QCPUtils was built without OpenCV. This method does nothing: " +       \
         QString(__FUNCTION__);

#define CPQ_ADD_METATYPE(T)                                                    \
  Q_DECLARE_METATYPE(T)                                                        \
  static int T##_CPQ_MetaType_id = qRegisterMetaType<T>(#T);

namespace cv {
class Mat;
}

namespace cpq {
namespace vis {

struct CpqMat
{
  CpqMat() = default;
  CpqMat(QSize size, int type, uchar* data);
  CpqMat(uint16_t width, uint16_t heigth, int type, uchar* data);
  CpqMat(cv::Mat& mat);
  QSize size;
  int type;
  QByteArray data;
};
}
}
#endif // QCVTYPES_H
