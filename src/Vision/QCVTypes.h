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

Q_DECLARE_METATYPE(cpq::vis::CpqMat);
static int cpq_vis_CpqMat_id =
  qRegisterMetaType<cpq::vis::CpqMat>("cpq::vis::CpqMat");

#endif // QCVTYPES_H
