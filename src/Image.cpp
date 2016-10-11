#include "inc/Image.hpp"

cvt::ErrorType Image::InitTilers(void)
{
    cv::Size2i t_size(TILE_DIMS, TILE_DIMS);
    tile_size = t_size;
    cvt::ErrorType error;
    error = InitInputTiler();
    if (error == cvt::NoError) {
        error = InitOutputTiler();
    }
    if (error != cvt::NoError) {
        return ErrorHandler(error, "Image::InitTilers()");
    }
    return error;
}

cvt::ErrorType Image::InitInputTiler(void)
{
    cvt::ErrorType error;
    error = input_tiler.open(input_filename);
    if (error != cvt::NoError) {
        return ErrorHandler(error, "Image::InitInputTiler()");
    }
    cv::Size2i r_size(input_tiler.getRasterSize());
    raster_size = r_size;
    input_tiler.setCvTileSize(tile_size);
    return error;
}

cvt::ErrorType Image::InitOutputTiler(void)
{
    cvt::ErrorType error = output_tiler.create(output_filename, DRIVER_NAME, raster_size, NUM_BANDS, DEPTH_T);
    if (error != cvt::NoError) {
        return ErrorHandler(error, "Image::InitOutputTiler()");
    }
    output_tiler.setCvTileSize(tile_size);
    return error;
}

cvt::ErrorType Image::ErrorHandler(cvt::ErrorType e, const char *error_location)
{
    switch (e) {
        case cvt::NoError:
            return e;
        case cvt::DriverError:
            std::cerr << "<ERROR> In " << error_location << ": The GDAL driver returned an unknown/unhandled error.\n";
            return e;
        case cvt::FileExists:
            std::cerr << "<ERROR> In " << error_location << ": The file already exists.\n";
            return e;
        case cvt::FileMissing:
            std::cerr << "<ERROR> In " << error_location << ": The file is missing.\n";
            return e;
        case cvt::CreateError:
            std::cerr << "<ERROR> In " << error_location << ": The GDAL driver returned a creation error.\n";
            return e;
        case cvt::OpenError:
            std::cerr << "<ERROR> In " << error_location << ": The file couldn't be opened.\n";
            return e;
        case cvt::WriteError:
            std::cerr << "<ERROR> In " << error_location << ": Couldn't write to the file.\n";
            return e;
        case cvt::ReadError:
            std::cerr << "<ERROR> In " << error_location << ": Couldn't read from the file.\n";
            return e;
        case cvt::BoundsError:
            std::cerr << "<ERROR> In " << error_location
                      << ": A tile index or band index exceeded the available bounds.\n";
            return e;
        case cvt::NullPointer:
            std::cerr << "<ERROR> In " << error_location << ": A null pointer was encountered.\n";
            return e;
        case cvt::InvalidData:
            std::cerr << "<ERROR> In " << error_location << ": Invalid data was provided.\n";
            return e;
        default:
            std::cerr << "<ERROR> In " << error_location << ": The ErrorHandler itself experienced an error.\n";
            return e;
    }
}