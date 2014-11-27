#!/bin/sh
echo "please enter Y(for recompile) or N(or others for do not recompile): "
read key
if [ $key = "Y" -o $key = "y" ];then
	make
	echo "the function compile is OVER!"
fi
if [ ! -e ./keypoint ]
then
	if [ ! -d /demo_SURF_src/keypoint ]
	then
		mkdir keypoint
	fi
fi
echo please enter the threshold: 
read threshold
./bin/extract_surf ./examples/1.png ./keypoint/k1_${threshold}.txt ${threshold}
echo "find the keypoint of 1.png"
./bin/extract_surf ./examples/2.png ./keypoint/k2_${threshold}.txt ${threshold}
echo "find the keypoint of 2.png"
./bin/match_surf ./keypoint/k1_${threshold}.txt ./keypoint/k2_${threshold}.txt ./keypoint/matches_${threshold}.txt yes
echo "matches DONE!"
./bin/display_surf ./keypoint/k1_${threshold}.txt ./keypoint/k2_${threshold}.txt ./keypoint/matches_${threshold}.txt ./examples/1.png ./examples/2.png ./keypoint/descriptor_${threshold}.png ./keypoint/matches_${threshold}.png
echo "display_${threshold} DONE!"
#./bin/extract_surf ./examples/1.png ./keypoint/k1_5000.txt 5000
#echo "find the keypoint of 1.png"
#./bin/extract_surf ./examples/2.png ./keypoint/k2_5000.txt 5000
#echo "find the keypoint of 2.png"
#./bin/match_surf ./keypoint/k1_5000.txt ./keypoint/k2_5000.txt ./keypoint/matches_5000.txt
#echo "matches_5000 DONE!"
#./bin/display_surf ./keypoint/k1_5000.txt ./keypoint/k2_5000.txt ./keypoint/matches_5000.txt ./examples/1.png ./examples/2.png ./keypoint/descriptor_5000.png ./keypoint/matches_5000.png
#echo "display_5000 DONE!"
