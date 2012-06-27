#!/bin/bash

rm ./*.poly

./boonas polygonC mainBuildA 0 0 1 50 -30 -50 -30 -50 30 50 30
./boonas extrude mainBuildA mainBuildA 30
./boonas transform mainBuildA ZT 40

./boonas polygonC mainBuildB 0 1 0 30 0 -30 0 -30 30 30 30
./boonas extrude mainBuildB mainBuildB 30
./boonas transform mainBuildB ZT 10

./boonas polygonC mainEntrance 1 0 0 25 0 -25 0 -25 -15 25 -15
./boonas extrude mainEntrance mainEntrance 30
./boonas transform mainEntrance ZT -5

./boonas polygonC mainEntranceF 0 2 2 15 0 -15 0 -15 -15 15 -15
./boonas extrude mainEntranceF mainEntranceF 30
./boonas transform mainEntranceF ZT -10

./boonas polygonC planters 2 2 0 25 -15 50 -15 50 -30 25 -30
./boonas extrude planters planters 25
./boonas transform planters XT 30 ZT 16 XS .6 ZS .5
./boonas create plantersB planters XT -80
./boonas create plantersC planters ZT -23 ZS 1.5
./boonas create plantersD plantersC XT -80

./boonas create plantersE planters ZT -30 XT -19 YT 5 US 1.3
./boonas create plantersF plantersE XT -55

./boonas polygonC piller 2 0 2 -3 -3 -3 3 3 3 3 -3
./boonas extrude piller piller 30
./boonas transform piller ZT -60 XD -90 YD 90 XT 24 YT 60 ZT -15

./boonas create pB piller XT -15
./boonas create pC pB XT -15
./boonas create pD pC XT -15

./boonas polygonC stairbase 2 4 4 -1 -1 -1 1 1 1 1 -1
./boonas transform stairbase XS 30
./boonas extrude stairbase stairbase 30
./boonas transform stairbase XS 1.4 ZS 1.5 ZT 10 US .95 YT -16.3
./boonas create sA stairbase US 1.025 YT -0.9
./boonas create sB sA US 1.025 YT -0.9
./boonas create sC sB US 1.025 YT -0.9
./boonas create sD sC US 1.025 YT -0.9
./boonas create sE sD US 1.025 YT -0.9
./boonas create sF sE US 1.025 YT -0.9
./boonas create sG sF US 3 YT 45

./boonas polygonC mbTopA 4 4 1 50 -5 -50 -5 -50 5 50 5
./boonas extrude mbTopA mbTopA 30
./boonas transform mbTopA ZT 40 US 1.2 ZT -5 YT 26

./boonas polygonC mbTopB 4 4 1 30 -5 -30 -5 -30 5 30 5
./boonas extrude mbTopB mbTopB 30
./boonas transform mbTopB ZT 10 US 1.2 ZT -3 YT 26

./boonas assemble mainBuildA mainBuildB mainEntrance mainEntranceF mainBuild
./boonas assemble mainBuild planters plantersB plantersC plantersD plantersE plantersF mainBuildB
./boonas assemble piller pB pC pD mainBuildB stairbase sA sB sC sD sE sF sG mainBuildC
./boonas assemble mbTopA mbTopB mainBuildC mainBuildD

#make doors

./boonas polygonC doorF 8 2 4 -4 -4 -4 4 4 4 4 -4
./boonas transform doorF YS 1.5
./boonas extrude doorF doorF 2
./boonas polygonC doorH 2 8 15 -1 -1 -1 1 1 1 1 -1
./boonas transform doorH YS 1.3 XS .3
./boonas extrude doorH doorH 1
./boonas transform doorH ZT -2
./boonas transform doorH XT 2

./boonas assemble doorH doorF doorR
./boonas transform doorH XT -4
./boonas assemble doorH doorF doorL

#door r and door l are made, time to put them in the scene i know thier in the wrong place

./boonas create doorRR doorR ZT -4 YT -9 XT -20.5
./boonas create doorLL doorL ZT -4 YT -9 XT 20.5
./boonas transform doorR ZT -8.5 YT -9 XT -5
./boonas transform doorL YD -45 ZT -10.5 YT -9 XT 5 

./boonas assemble doorRR doorLL doorR doorL mainBuildD mainBuildE

./viewer mainBuildE.poly 0 0 -30