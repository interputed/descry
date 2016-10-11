#pragma once

#include <cvtile/base/cvTile.hpp>
#include <cvtile/base/Tiler.hpp>
//#include <cvtile/cvtile.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

// Global Constants
const char *DRIVER_NAME = "GTiff";
const int TILE_DIMS = 227;
const int NUM_BANDS = 21;
const cvt::DepthType DEPTH_T = cvt::Depth8U;


class Image
{
  public:
    Image(std::string fin, std::string fout) : input_filename(fin), output_filename(fout)
    {
        this->last_error = InitTilers();
    }



  private:
    cvt::Tiler input_tiler, output_tiler;
    std::string input_filename, output_filename;
    cv::Size2i raster_size;
    cv::Size2i tile_size;
    cvt::ErrorType last_error;
    cvt::ErrorType InitTilers(void);
    cvt::ErrorType InitInputTiler(void);
    cvt::ErrorType InitOutputTiler(void);
    cvt::ErrorType ErrorHandler(cvt::ErrorType e, const char *error_location);
};