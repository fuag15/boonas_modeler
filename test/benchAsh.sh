#!/bin/bash

rm ./*.poly

./boonas polygonC lowback 1 0 0 10 -2 1 -2 1 0 10 0
./boonas polygonC hiback 1 0 0 1 -2 -10 -4 -11 -3.5 -11 -2.5 -10 -2 1 0
./boonas assemble lowback hiback back
./boonas extrude back back 2
./boonas transform back ZD -90
./boonas transform back YD 90

./boonas polygonC frontback 0 1 0 10 -2 -2 -2 -2 0 10 0
./boonas extrude frontback frontback 2
./boonas transform frontback ZD -90
./boonas transform frontback ZT 10

./boonas polygonC low 0 0 1 5 -2 -5 -2 -5 0 5 0
./boonas extrude low low 2
./boonas transform low YD 90
./boonas create high low YT 6
./boonas assemble high low sideSup

./boonas polygonC armS 1 2 1 5 -2 2 -2 2 0 5 0
./boonas polygonC armW 1 2 1 2 -2 1 -3 -4 -3 -4.5 -2 -4.5 -1 -4 0 2 0
./boonas assemble armS armW arm
./boonas extrude arm arm 1
./boonas transform arm XD 90
./boonas transform arm YD -90

./boonas polygonC finnessArm 2 1 1 -2 -1 1 -1 1 0 -2 0
./boonas extrude finnessArm finnessArm 1
./boonas transform finnessArm ZD 90

# put the left part of the bench together! heres where i mod it
./boonas transform back ZT 4
./boonas transform sideSup YT -10 XS .9 YS .7
./boonas transform arm YT 3 XT -1 ZT -1 XS .99 ZS 1.5
./boonas transform frontback ZT -15 XT 1
./boonas transform finnessArm ZT -6.5 XT 1 YT 1

# heres where we put it together
./boonas assemble finnessArm arm sideSup frontback back benchRside

#lets make the Right side
./boonas transform finnessArm XT -3
./boonas transform arm YD 180 XD 180 YT 5

./boonas assemble finnessArm arm sideSup frontback back benchLside

./boonas transform benchRside XT 20
./boonas transform benchLside XT -20

./boonas assemble benchLside benchRside benchSides

#start the back portion

./boonas polygonC backPlankA 2 2 1 -20 -2 20 -2 20 0 -20 0
./boonas extrude backPlankA backPlankA 1
./boonas transform backPlankA ZT 3.7 YT 1
./boonas create backPlankB backPlankA ZT -10
./boonas create backPlankC backPlankA YT 15 XD 15
./boonas transform backPlankC YT -2 ZT -2

./boonas assemble backPlankB backPlankA backPlankC backPlanks
./boonas transform backPlanks YT -3

./boonas assemble backPlanks benchSides benchAlmost

./boonas polygonC backSupPlank 3 2 1 -5 -2 5 -2 5 0 -5 0
./boonas extrude backSupPlank backSupPlank 1
./boonas transform backSupPlank ZD 90 YS 1.14 YT 2
./boonas transform backSupPlank XD 10 ZT 4.4 YT 1
./boonas transform backSupPlank XT 16 
./boonas create backSupPlankA backSupPlank XT -4
./boonas create backSupPlankB backSupPlankA XT -4
./boonas create backSupPlankC backSupPlankB XT -4
./boonas create backSupPlankD backSupPlankC XT -4
./boonas create backSupPlankE backSupPlankD XT -4
./boonas create backSupPlankF backSupPlankE XT -4
./boonas create backSupPlankG backSupPlankF XT -4
./boonas create backSupPlankH backSupPlankG XT -4
./boonas create backSupPlankI backSupPlankH XT -4

./boonas assemble backSupPlank backSupPlankA backSupPlankB backSupPlankC backSupPlankD backSupPlankE backSupPlankF backSupPlankG backSupPlankH backSupPlanks

./boonas transform backSupPlanks XT -1

./boonas assemble benchAlmost backSupPlanks benchAlmostA

# make the center lowest bench piece eh?

./boonas polygonC midSeat 4 3 4 -20 -1 20 -1 20 0 -20 0
./boonas extrude midSeat midSeat .5
./boonas transform midSeat XD 90 YT -2
./boonas transform midSeat ZD -90 XT 20

# rot infile outfile vectorx, y, z pointx, y, z, divisions, degrees

./boonas rot midSeat midSeatS 0 1 0 0 0 0 6 30
./boonas transform midSeatS ZD 90 ZD 180 YT 14
./boonas transform midSeatS XD -15 ZT 3.5 YT 0.2

./boonas assemble midSeatS benchAlmostA bench

#got a bench, time to make a freakin ash tray man!

./boonas polygonC rimEdge 1 0 1 -5 -.5 -5.25 -1 -5.75 -1 -6 -.5 -6 .5 -5.75 1 -5.25 1 -5 .5
./boonas transform rimEdge XS 1.5
./boonas extrude rimEdge rimEdge 2
./boonas rot rimEdge rimEdgeR 0 1 0 0 0 0 50 360

./boonas polygonC rimIn 1 0 1 -8 -.5 -8 .5 -5 .5 -5 -.5
./boonas extrude rimIn rimIn 2
./boonas transform rimEdge XS 1.5
./boonas rot rimIn rimInR 0 1 0 0 0 0 50 360

./boonas assemble rimInR rimEdgeR rimTop
./boonas create rimBottom rimTop YT -20
./boonas assemble rimBottom rimTop rims

#./boonas polygonC rimCenter 0 0 1 -6 -.4 -6 .4 -.1 .1 -.1 -.4
#./boonas extrude rimCenter rimCenter 3
#./boonas transform rimCenter ZT -20
#./boonas rot rimCenter rimCenterR 0 1 0 0 0 0 40 360

./boonas polygonC rimOut 1 0 0 1 -1 1 -20 -1 -20 -1 -1
./boonas extrude rimOut rimOut 1
./boonas transform rimOut ZT 7.4
./boonas rot rimOut rimOutR 0 1 0 0 0 0 15 360

./boonas transform rimOut ZT -3
./boonas rot rimOut rimInR 0 1 0 0 0 0 50 360

./boonas assemble rimOutR rimInR rims ash

./boonas transform ash XS .6 ZS .6 YS .9 XT -30 ZT -5 YT 8

./boonas assemble bench ash benchAsh

./viewer benchAsh.poly 0 0 -20