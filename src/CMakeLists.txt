# Add additional class files as libraries, as below.
add_library (Image Image.cpp inc/Image.hpp)

# Builds the program.
add_executable (descry Main.cpp)

# Add added libraries here as well.
target_link_libraries(descry
    Image
    boost_system-mt
    boost_filesystem-mt
)