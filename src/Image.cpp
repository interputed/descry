#include "inc/Image.hpp"

///
/// \brief  Helper function to convert C-style strings to all uppercase.
/// \param  A C-style string to be converted to uppercase.
/// \return The converted C-style string.
///
const char *UpperCase(const char *);

void Image::InputToOutput(void)
{
    for (auto i = 0; i < input_tiler.getRowCount(); ++i) {
        for (auto j = 0; j < input_tiler.getColumnCount(); ++j) {
            auto idx = input_tiler.getColumnCount() * i + j;
            cvt::cvTile<unsigned char> inTile = input_tiler.getCvTile<unsigned char>(idx, 0);
            cvt::cvTile<unsigned char> band_data(tile_size, NUM_BANDS);
            for (auto band_idx = 0; band_idx < output_tiler.getBandCount(); ++band_idx) {
                band_data[band_idx] = inTile[0];
            }
            output_tiler.putCvTile(band_data, idx);
        }
    }

}

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
    cvt::ErrorType error = output_tiler.create(output_filename, GDAL_DRIVER_NAME, raster_size, NUM_BANDS, DEPTH_T);
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

int Image::getCvTileCount(const char *IO)
{
    const char *new_IO = UpperCase(IO);
    if (strcmp(new_IO, "INPUT") == 0) {
        return input_tiler.getCvTileCount();
    } else if (strcmp(new_IO, "OUTPUT") == 0) {
        return output_tiler.getCvTileCount();
    } else {
        if (input_tiler.getCvTileCount() == output_tiler.getCvTileCount()) {
            return input_tiler.getCvTileCount();
        } else {
            return -1;
        }
    }
}

int Image::getRowCount(const char *IO)
{
    const char *new_IO = UpperCase(IO);
    if (strcmp(new_IO, "INPUT") == 0) {
        return input_tiler.getRowCount();
    } else if (strcmp(new_IO, "OUTPUT") == 0) {
        return output_tiler.getRowCount();
    } else {
        if (input_tiler.getRowCount() == output_tiler.getRowCount()) {
            return input_tiler.getRowCount();
        } else {
            return -1;
        }
    }
}

int Image::getColumnCount(const char *IO) {
     const char *new_IO = UpperCase(IO);
    if (strcmp(new_IO, "INPUT") == 0) {
        return input_tiler.getColumnCount();
    } else if (strcmp(new_IO, "OUTPUT") == 0) {
        return output_tiler.getColumnCount();
    } else {
        if (input_tiler.getColumnCount() == output_tiler.getColumnCount()) {
            return input_tiler.getColumnCount();
        } else {
            return -1;
        }
    }
}

int Image::getBandCount(const char *IO) {
     const char *new_IO = UpperCase(IO);
    if (strcmp(new_IO, "INPUT") == 0) {
        return input_tiler.getBandCount();
    } else if (strcmp(new_IO, "OUTPUT") == 0) {
        return output_tiler.getBandCount();
    } else {
        if (input_tiler.getBandCount() == output_tiler.getBandCount()) {
            return input_tiler.getBandCount();
        } else {
            return -1;
        }
    }
}

const char *UpperCase(const char *IO)
{
    std::string str = IO;
    for (auto &c: str) {
        c = toupper(c);
    }
    return str.c_str();
}
