#include "Common.h"

#include <QFile>
#include <QRegularExpression>

#include <opencv2/aruco.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/imgproc.hpp>

ArucoMarker::ArucoMarker(quint16 id,
                         double size,
                         Eigen::Vector3d position,
                         Eigen::Quaterniond quaternion)
  : id(id)
  , size(size)
  , position(position)
  , quaternion(quaternion)
{}

ArucoMarker::ArucoMarker(quint16 id,
                         double size,
                         double x,
                         double y,
                         double z,
                         double rx,
                         double ry,
                         double rz)
  : id(id)
  , size(size)
  , position(x, y, z)
  , quaternion(Eigen::AngleAxisd(x, Eigen::Vector3d::UnitX()) *
               Eigen::AngleAxisd(y, Eigen::Vector3d::UnitY()) *
               Eigen::AngleAxisd(z, Eigen::Vector3d::UnitZ()))
{}

ArucoMarker::ArucoMarker(quint16 id, double size, double x, double y, double z)
  : id(id)
  , size(size)
  , position(x, y, z)
  , quaternion(Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX()) *
               Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY()) *
               Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ()))
{}

void
arucoMapToBoard(ArucoMarkerMap& markersMap,
                cv::Ptr<cv::aruco::Board>& emptyBoard,
                cv::Ptr<cv::aruco::Dictionary> dictionary)
{
  QMap<quint16, ArucoMarker> map;

  std::vector<std::vector<cv::Point3f>> points;
  std::vector<int> ids;

  for (auto& m : markersMap) {
    map.insert(m.indexOnMap, m);
  }

  for (auto& m : map) {
    cv::Point3f center = { float(m.position.x()),
                           float(m.position.y()),
                           float(m.position.z()) };

    float s = m.size / 2;
    cv::Point3f c1 = { -s, s, 0 };
    cv::Point3f c2 = { s, s, 0 };
    cv::Point3f c3 = { s, -s, 0 };
    cv::Point3f c4 = { -s, -s, 0 };

    points.push_back({ c1, c2, c3, c4 });
    ids.push_back(m.id);

    for (auto& p : points.back()) {
      auto r_eigen = m.quaternion.toRotationMatrix();
      cv::Mat r_cv;
      cv::eigen2cv(r_eigen, r_cv);

      cv::Mat mat(p);
      r_cv.convertTo(r_cv, 5);

      mat = r_cv * mat;
      p = cv::Point3f(mat)+center;

    }
  }

  emptyBoard = cv::aruco::Board::create(points, dictionary, ids);
}

ArucoMarker::operator QString() const
{
  cpq::CpqStringStream ss;
  ss << "cpq::vis::ArucoMarker("
     << "id: " << id << ", size: " << size
     << ", position: " << position.transpose() << ", quaternion: " << quaternion
     << ")";
  return ss;
}

ArucoMarkerMap
loadArucoMap(QString file)
{
  ArucoMarkerMap map = ArucoMarkerMap();

  QRegularExpression r1(
    R"(^([0-9]+)\s+([0-9]*\.?[0-9]+)\s+)" // id size
    R"((-?[0-9]*\.?[0-9]+)\s+(-?[0-9]*\.?[0-9]+)\s+(-?[0-9]*\.?[0-9]+)\s*$)" // x y z
  );
  // QRegularExpression r1("^([0-9]+)\s+([0-9]+\\.?[0-9]+)");

  quint16 index = 0;

  QFile f(file);
  if (f.open(QIODevice::ReadOnly)) {
    QTextStream in(&f);
    while (!in.atEnd()) {
      QString line = in.readLine();
      line = line.trimmed();
      if (!line.startsWith("#") && !line.isEmpty()) {
        QRegularExpressionMatch m = r1.match(line);
        if (m.hasMatch()) {

          quint16 id = m.captured(1).toUInt();
          double size = m.captured(2).toDouble();
          double x = m.captured(3).toDouble();
          double y = m.captured(4).toDouble();
          double z = m.captured(5).toDouble();

          map[id] = ArucoMarker(id, size, x, y, z);
          map[id].indexOnMap = index;
          index++;
        }
      }
    }
    f.close();
  }

  return map;
}

void
rotateMat(cv::Mat& src, cv::Mat& dst, double angle)
{
  // get rotation matrix for rotating the image around its center in pixel
  // coordinates
  cv::Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
  cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
  // determine bounding rectangle, center not relevant
  cv::Rect2f bbox =
    cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
  // adjust transformation matrix
  rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
  rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

  cv::warpAffine(
    src, dst, rot, bbox.size(), cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
}

void
drawArucoMarkerMap(uint pixelsPerCm,
                   cv::Mat& outImage,
                   ArucoMarkerMap& map,
                   cv::Ptr<cv::aruco::Dictionary> dictionary)
{

  uint basicBorder = 1;
  double borderCoef = 0.1;
  auto backColor = cv::Scalar(255, 255, 255, 255);

  double maxX = 0, minX = 0;
  double maxY = 0, minY = 0;

  int xOffset = 0;
  int yOffset = 0;

  QMap<quint16, ArucoMarker> mrkList;

  for (auto& m : map) {
    mrkList.insert(m.indexOnMap, m);
  }

  auto R = [=](ArucoMarker m) -> double {
    return 1 * m.size * (1 + 2 * borderCoef) / 2;
  };

  if (mrkList.size() > 0) {
    auto f = mrkList.first();
    double fr = R(f);

    maxX = f.position.x() + fr;
    minX = f.position.x() - fr;
    maxY = f.position.y() + fr;
    minY = f.position.y() - fr;

    foreach (auto& m, mrkList) {
      auto& x = m.position.x();
      auto& y = m.position.y();
      double r = R(m);

      if (x + r > maxX) {
        maxX = x + r;
      }
      if (x - r < minX) {
        minX = x - r;
      }
      if (y + r > maxY) {
        maxY = y + r;
      }
      if (y - r < minY) {
        minY = y - r;
      }
    }

    maxX *= pixelsPerCm;
    minX *= pixelsPerCm;
    maxY *= pixelsPerCm;
    minY *= pixelsPerCm;
  }

  xOffset = -minX + basicBorder;
  yOffset = -minY + basicBorder;

  outImage = cv::Mat(maxX - minX + 2 * basicBorder,
                     maxY - minY + 2 * basicBorder,
                     CV_8UC4,
                     backColor);

  foreach (auto& m, mrkList) {
    cv::Mat img;
    dictionary->drawMarker(m.id, m.size * pixelsPerCm, img);
    cv::cvtColor(img, img, cv::COLOR_GRAY2BGRA);
    int border = m.size * pixelsPerCm * borderCoef;

    cv::copyMakeBorder(img,
                       img,
                       border,
                       border,
                       border,
                       border,
                       cv::BORDER_CONSTANT,
                       cv::Scalar(255, 255, 255));

    img.copyTo(
      outImage(cv::Rect(m.position.x() * pixelsPerCm + xOffset - img.cols / 2,
                        -m.position.y() * pixelsPerCm + yOffset - img.rows / 2,
                        img.cols,
                        img.rows)));
  }
}
