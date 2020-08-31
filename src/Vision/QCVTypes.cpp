#include "QCVTypes.h"

#ifndef NO_OPENCV
#include <opencv2/opencv.hpp>
#endif

using namespace cpq::vis;

CpqMat::CpqMat(QSize size, int type, uchar* data)
  : size(size)
  , type(type)
  , data((char*)data, size.width() * size.height())
{}

CpqMat::CpqMat(uint16_t width, uint16_t height, int type, uchar* data)
  : size(width, height)
  , type(type)
  , data((char*)data, width * height)
{}

#ifdef NO_OPENCV
CpqMat::CpqMat(cv::Mat& mat) {}
#else
CpqMat::CpqMat(cv::Mat& mat)
{
  auto s = mat.size();
  size = QSize(s.width, s.height);
  type = mat.type();
  data = QByteArray((char*)mat.data, size.width() * size.height());
}
#endif
