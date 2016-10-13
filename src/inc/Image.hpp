#pragma once

#include <cvtile/base/cvTile.hpp>
#include <cvtile/base/Tiler.hpp>
#include <string>

// GDAL driver type used. TODO: Provide further explanation and/or alternate options.
#define GDAL_DRIVER_NAME "GTiff"
// Caffe supports a max of 227x227 image.
const int TILE_DIMS = 227;
// Band count requested as 21. TODO: Explain why.
const int NUM_BANDS = 21;
// Data type for cvtile.
const cvt::DepthType DEPTH_T = cvt::Depth8U;



///
/// \brief Abstraction class for Tiler/CVtile which provides only needed functionality.
/// Probably ending up just as complicated, if not moreso than using tiler directly.
///
class Image
{
  public:
    Image(std::string fin, std::string fout) : input_filename(fin), output_filename(fout)
    {
        this->last_error = InitTilers();
    }
    cvt::ErrorType getLastError() {
        return this->last_error;
    }
    cv::Size2i getRasterSize() {
        return this->raster_size;
    }
    cv::Size2i getTileSize() {
        return this->tile_size;
    }
    // The following get functions take "INPUT" or "OUTPUT" as an argument to specify which value
    // to provide.
    int getCvTileCount(const char *);
    int getRowCount(const char *);
    int getColumnCount(const char *);
    int getBandCount(const char *);

    // Testing function that just initializes all 21 bands of output, to the same values as input.
    void InputToOutput(void);

  private:
    cvt::Tiler input_tiler, output_tiler;
    std::string input_filename, output_filename;
    cv::Size2i raster_size;
    cv::Size2i tile_size;
    cvt::ErrorType last_error;
    cvt::ErrorType InitTilers(void);
    cvt::ErrorType InitInputTiler(void);
    cvt::ErrorType InitOutputTiler(void);
    cvt::ErrorType ErrorHandler(cvt::ErrorType, const char *);
};
