#!/bin/bash

#rot example

rm ./*.poly

./boonas polygon square -1 -1 -1 1 1 1 1 -1
./boonas extrude square cube 2
./boonas transform cube XT 5
./boonas transform cube ZT 5

./boonas rot cube cubes 0 1 0 0 0 0 10 360
./viewer cubes.poly 0 0 -20

./boonas rot cube cubes 1 0 0 0 0 0 10 360
./viewer cubes.poly 0 0 -20

./boonas rot cube cubes 0 0 1 0 0 0 10 360
./viewer cubes.poly 0 0 -20

./boonas rot cube cubes 1 1 0 0 0 0 10 360
./viewer cubes.poly 0 0 -20

./boonas rot cube cubes 0 1 1 0 0 0 10 360
./viewer cubes.poly 0 0 -20