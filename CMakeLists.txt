cmake_minimum_required(VERSION 3.15)
project(pa01_sentiment)

set(CMAKE_CXX_STANDARD 17)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "data/train_dataset_20k.csv")
set (input02 "data/test_dataset_10k.csv")
set (input03 "data/test_dataset_sentiment_10k.csv")
set (input04 "data/sample_train.txt")
#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

# Create the executable for sorting
add_executable(pa01_sentiment main.cpp DSString.cpp DSString.h driverfunctions.cpp driverfunctions.h optimization.cpp optimization.h)

