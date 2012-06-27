#!/bin/bash

#clip example

rm ./*.poly

./boonas polygonC square 1 0 0 -1 -1 -1 1 1 1 1 -1
./boonas extrude square cube 2
./boonas transform cube XT 10
./boonas rot cube cubes 0 1 0 0 0 0 5 360

#// clip, file, inpolies, outpolies, normalx normaly normalz, pointx, pointy, pointz

./boonas clip cubes clippedCubes 0 1 0 0 0 0

./viewer cubes.poly 0 0 -10
#./viewer clippedCubes.poly 0 0 -10