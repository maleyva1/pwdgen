#!/bin/bash

type="$1"

if [ "$type" != "Release" ] && [ "$type" != "Debug" ] ; then
	if [ -z "$type" ]; then
		echo "No build type specified";
		echo "Defaulting to 'Debug'";
		type="Debug";
	else
		echo "$type is an unknown build type for this project";
		echo "USAGE: ./build.sh [Release|Debug]";
		exit 1;
	fi;
fi;

cmake -B build -DCMAKE_BUILD_TYPE=$type
cd build;
make -j 4;
