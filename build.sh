#!/bin/bash

type=$1

if [ "$type" != "Production" ]; then
	type="Debug";
else
	echo "Unknown build type for this project";
	echo "USAGE: ./build.sh [Production|Debug]";
	exit 1;
fi;

cmake -B build -DCMAKE_BUILD_TYPE=$type
cd build;
make -j 4;
