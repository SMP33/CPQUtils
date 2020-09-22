#pragma once

#include <opencv2/opencv.hpp>

#include "../../Core.h"
#include "../QCVTypes.h"

cpq_start_namespace(vis) class ChessboardCameraCalibrator
{
public:
  ChessboardCameraCalibrator();
  //static void createChessboard(cv::Mat* out, int cols, int rows);
};

cpq_end_namespace