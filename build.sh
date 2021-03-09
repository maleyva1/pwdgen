#!/bin/bash

type="$1"
gen="$2"

if [ "$type" != "Release" ] && [ "$type" != "Debug" ] ; then
	if [ -z "$type" ]; then
		echo "No build type specified";
		echo "Defaulting to 'Debug'";
		type="Debug";
	else
		echo "$type is an unknown build type for this project";
		echo "USAGE: ./build.sh [Release|Debug] GENERATOR";
		echo "\t\tWhere GENERATOR is your CMake generator of choioce"
		exit 1;
	fi;
fi;

if [ ! -z "$gen" ]; then
	cmake -B build -DCMAKE_BUILD_TYPE=$type -G $gen && ninja -C build
else
	cmake -B build -DCMAKE_BUILD_TYPE=$type && make -C build -j 4
fi;
