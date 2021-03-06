
// System Libraries
#include <boost/filesystem.hpp>

// C++ Libraries
#include <iostream>
#include <sstream>
#include <stdexcept>

// Local Headers
#include "inc/descryConfig.h" // For version number passing from CMake.
#include "inc/Image.hpp"

// Declared Constants
const int NUM_ARGS(2);
const char OUTPUT_APPEND[] = {"_output"};

///
/// Simple helper function to return a string containing the version number.
///
std::string Version(void);

///
/// Verifies correct number of arguments are passed to the program, as well as
/// verifying the given input filename is a valid file.
///
/// \param argc - int containing the number of program arguments.
/// \returns input_file.string() - Verified path of input image.
///
std::string InputValidation(const int argc, const char **argv);

///
/// Re-uses the input filename for the output file, but simply appends an output
/// label to it. This way you only need to pass in a single filename. Will
/// overwrite any existing file with the same name.
///
/// \param input_file - A verified string with the path of the input file.
/// \returns output_path.string() - The path of the output file.
///
std::string OutputValidation(const std::string input_file);

int main(int argc, char **argv)
{
    std::cout << "\nExecuting descry - Version " << Version() << "." << std::endl;

    std::string temp_file;
    try {
        temp_file = InputValidation(argc, (const char **)argv);
    } catch (const std::invalid_argument &e) {
        std::cerr << "InputValidation ERROR: " << e.what() << std::endl;
        std::cerr << "Correct Usage: " << argv[0] << "<full input image path>" << std::endl;
        return 1;
    }
    const std::string INPUT_FILENAME = temp_file;

    try {
        temp_file = OutputValidation(INPUT_FILENAME);
    } catch (const std::invalid_argument &e) {
        std::cerr << "OutputValidation ERROR: " << e.what() << std::endl;
        return 2;
    }
    const std::string OUTPUT_FILENAME = temp_file;

    // The main data handling object.
    Image img(INPUT_FILENAME, OUTPUT_FILENAME);
    // Used to specify between the input and output files for some Image class methods.
    const char in[]  = "INPUT";
    const char out[] = "OUTPUT";

// Displaying format data, mainly for debugging. Set to 0 if undesired.
// A value of -1 for any property indicates an error.
#if 1
    // Input section
    std::cout << "\n\tImage path: " << INPUT_FILENAME << std::endl;
    std::cout << "\t\tInput Image Dimensions: " << img.getRasterSize().height << " x "
            << img.getRasterSize().width << std::endl;
    std::cout << "\t\tInput Tile Dimensions: " << img.getRowCount(in) << " x "
            << img.getColumnCount(in) << std::endl;
    std::cout << "\t\tInput Band Count: " << img.getBandCount(in) << std::endl;
    // Output section
    std::cout << "\n\tOutput image path: " << OUTPUT_FILENAME << std::endl;
    std::cout << "\t\tOutput Image Dimensions: " << img.getRasterSize().height << " x "
            << img.getRasterSize().width << std::endl;
    std::cout << "\t\tOutput Tile Dimensions: " << img.getRowCount(out) << " x "
            << img.getColumnCount(out) << std::endl;
    std::cout << "\t\tOutput Band Count: " << img.getBandCount(out) << std::endl;
#endif

    img.InputToOutput();

    std::cout << "\nExecution finished." << std::endl;
    return 0;
}

std::string Version(void)
{
    std::stringstream ss;
    ss << descry_VERSION_MAJOR << '.' << descry_VERSION_MINOR;
    std::string version = ss.str();
    return version;
}

std::string InputValidation(const int argc, const char **argv)
{
    if (argc != NUM_ARGS) {
        throw std::invalid_argument(std::string("Invalid number of arguments."));
    }
    boost::filesystem::path input_path(argv[1]);
    if (!boost::filesystem::exists(input_path)) {
        throw std::invalid_argument(std::string("Invalid image path."));
    }
    return input_path.string();
}

std::string OutputValidation(const std::string input_file)
{
    boost::filesystem::path input_path(input_file);
    std::string output_file_mod = input_path.string();
    output_file_mod.insert(output_file_mod.length() - input_path.extension().string().length(), OUTPUT_APPEND);
    boost::filesystem::path output_path(output_file_mod);
    // If output_path is a file that already exists, deletes it.
    if (boost::filesystem::exists(output_path)) {
        // If could not delete already existing file.
        if (!boost::filesystem::remove(output_path)) {
            throw std::invalid_argument(std::string("Failed to remove existing output file."));
        }
    }
    return output_path.string();
}
