#!/bin/sh
echo "please enter Y(for recompile) or N(or others for do not recompile): "
read key
if [ $key = "Y" -o $key = "y" ];then
	make
	echo "the function compile is OVER!"
fi
echo please enter the threshold: 
read threshold
if [ ! -e ./keypoint/rpy_${threshold} ]
then
	if [ ! -d /demo_SURF_src/keypoint/rpy_${threshold} ]
	then
		mkdir -p keypoint/rpy_${threshold}
	fi
fi
./bin/extract_surf ./examples/rpy1.png ./keypoint/rpy_${threshold}/rpy_k1_${threshold}.txt ${threshold}
echo "find the keypoint/rpy_${threshold} of rpy1.png"
./bin/extract_surf ./examples/rpy2.png ./keypoint/rpy_${threshold}/rpy_k2_${threshold}.txt ${threshold}
echo "find the keypoint/rpy_${threshold} of rpy2.png"
echo with or without orsa?
read orsa
if [ $orsa = "Y" -o $orsa = "y" ];then
	./bin/match_surf ./keypoint/rpy_${threshold}/rpy_k1_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_k2_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_matches_${threshold}.txt orsa
else
	./bin/match_surf ./keypoint/rpy_${threshold}/rpy_k1_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_k2_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_matches_${threshold}.txt
fi
echo "matches DONE!"
./bin/display_surf ./keypoint/rpy_${threshold}/rpy_k1_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_k2_${threshold}.txt ./keypoint/rpy_${threshold}/rpy_matches_${threshold}.txt ./examples/rpy1.png ./examples/rpy2.png ./keypoint/rpy_${threshold}/rpy_descriptor_${threshold}.png ./keypoint/rpy_${threshold}/rpy_matches_${threshold}.png
echo "display_${threshold} DONE!"

sort < ./keypoint/rpy_${threshold}/rpy_matches_${threshold}.txt > ./keypoint/rpy_${threshold}/rpy${threshold}.txt



#echo please enter the threshold: 
#read threshold
#./bin/extract_surf ./examples/image2.png ./keypoint/Kk1_${threshold}.txt ${threshold}
#echo "find the keypoint of 1.png"
#./bin/extract_surf ./examples/image3.png ./keypoint/Kk2_${threshold}.txt ${threshold}
#echo "find the keypoint of 2.png"
#echo with or without orsa?
#read orsa
#if [ $orsa = "Y" -o $orsa = "y" ];then
	#./bin/match_surf ./keypoint/Kk1_${threshold}.txt ./keypoint/Kk2_${threshold}.txt ./keypoint/Kmatches_${threshold}.txt orsa
#else
	#./bin/match_surf ./keypoint/Kk1_${threshold}.txt ./keypoint/Kk2_${threshold}.txt ./keypoint/Kmatches_${threshold}.txt
#fi
#echo "matches DONE!"
#./bin/display_surf ./keypoint/Kk1_${threshold}.txt ./keypoint/Kk2_${threshold}.txt ./keypoint/Kmatches_${threshold}.txt ./examples/image2.png ./examples/image3.png ./keypoint/Kdescriptor_${threshold}.png ./keypoint/Kmatches_${threshold}.png
#echo "display_${threshold} DONE!"
