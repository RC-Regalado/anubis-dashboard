cmake_minimum_required(VERSION 3.0)

project(control)

# Agregar las bibliotecas UNO y CPPU del SDK de LibreOffice a tu proyecto
set(UNO_INCLUDE_PATH /usr/include/libreoffice)
set(UNO_LIB_PATH /usr/lib/libreoffice/sdk/lib)
set(UNO_LIBRARIES uno_cppuhelpergcc3 uno_cppu uno_salhelpergcc3 uno_sal)
include_directories(${UNO_INCLUDE_PATH})
link_directories(${UNO_LIB_PATH})

# Agregar tu archivo de código fuente
add_executable(officectl uno.cpp)

target_link_libraries(officectl ${UNO_LIBRARIES})

