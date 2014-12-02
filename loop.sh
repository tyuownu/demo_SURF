#!/bin/sh

echo "please enter the loop times: "
read times

for (( c=1; c<=${times}; c++ ))
do
	./bin/match_surf ./keypoint/k1_.txt ./keypoint/k2_.txt ./keypoint/matches_.txt yes
done
