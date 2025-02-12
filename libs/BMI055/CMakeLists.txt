cmake_minimum_required(VERSION 3.10)
project(BMI055)

# Create a static library
add_library(BMI055 STATIC
    src/BMI055.c
)

# Specify the include directory for the library
target_include_directories(BMI055 PUBLIC
    include
)