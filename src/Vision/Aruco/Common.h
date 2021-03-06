#pragma once

#include "../../Core.h"
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

namespace cv {
class Mat;
namespace aruco {
//class Dictionary;
//class DetectorParameters;
//class Board;
}
}

struct ArucoMarker
{
  ArucoMarker() = default;
  /// @brief
  /// @param id marker id
  /// @param size marker size in mm
  /// @param marker coordinates in m
  /// @param quaternion marker rotation quaternion
  ArucoMarker(quint16 id,
              double size,
              Eigen::Vector3d position,
              Eigen::Quaterniond quaternion);

  /// @brief
  /// @param id marker id
  /// @param size marker size in mm
  /// @param x position.x in m
  /// @param y position.y in m
  /// @param z position.z in m
  /// @param rx rotation around the X axis (rad)
  /// @param ry rotation around the Y' axis (rad)
  /// @param rz rotation around the Z'' axis (rad)
  ArucoMarker(quint16 id,
              double size,
              double x,
              double y,
              double z,
              double rx,
              double ry,
              double rz);

  /// @param id marker id
  /// @param size marker size in mm
  /// @param x position.x in m
  /// @param y position.y in m
  /// @param z position.z in m
  ArucoMarker(quint16 id, double size, double x, double y, double z);

  quint16 id = 0;  ///< Marker id
  double size = 0; ///< Marker size in mm
  Eigen::Vector3d position =
    Eigen::Vector3d(0, 0, 0); ///< Marker position in meters
  Eigen::Quaterniond quaternion =
    Eigen::Quaterniond(1, 0, 0, 0); ///< Marker rotation

  quint16 indexOnMap = 0;

  operator QString() const;
};

typedef QMap<quint16, ArucoMarker> ArucoMarkerMap;

ArucoMarkerMap
loadArucoMap(QString file);

void
arucoMapToBoard(ArucoMarkerMap& markersMap,
                cv::Ptr<cv::aruco::Board>& emptyBoard,
                cv::Ptr<cv::aruco::Dictionary> dictionary);

void
drawArucoMarkerMap(uint pixelsPerCm,
                   cv::Mat& outImage,
                   ArucoMarkerMap& map,
                   cv::Ptr<cv::aruco::Dictionary> dictionary);