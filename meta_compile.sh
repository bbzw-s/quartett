#!/bin/sh
# dumbing down the inital project
flags=" -Imeta_src"

m4 $flags main.m4 > main.cpp
gcc $flags -E main.cpp -o preproc.cpp
