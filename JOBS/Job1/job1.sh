#!/bin/sh
#
# job1.sh run neutron_capture with test macro on lxplus 
# Copyright Andrés Camilo Sevilla
#
# !!!! Must be changed for each user !!! #

# Loading environmental variables 
#source /afs/cern.ch/work/a/asevilla/workspace/G4WORK/SciFW1/setup_lxplus.sh

# Defining variables
neutron_capture_DIR=/Users/andreagiraldo/workspace/G4WORK/neutron-capture-build
JOB_DIR=/Users/andreagiraldo/workspace/JOBS/neutron-capture/Job1
DataNo=1
i=0

# Creating DataNo directory

while [ $i -lt 1 ]
do
	if [ -d "./${DataNo}" ]
	then
		echo " “./${DataNo}” has been created"
		DataNo=$(($DataNo+1))
		i=0
	else
		mkdir ./${DataNo}
		i=1
fi
done

# Creating log directory

if [ -d "./${DataNo}/log" ]
then
	echo " “./${DataNo}/log” has been created"
else
	mkdir ./${DataNo}/log
fi

# Creating data directory

if [ -d "./${DataNo}/data" ]
then
	echo " “./${DataNo}/data” has been created"
else
	mkdir ./${DataNo}/data
fi

# Running neutron_capture

cp -R $neutron_capture_DIR/beam $JOB_DIR/${DataNo}/beam
cp -R $neutron_capture_DIR/mac $JOB_DIR/${DataNo}/mac
cp -R $JOB_DIR/mac/* $JOB_DIR/${DataNo}/mac/.

cd $JOB_DIR/${DataNo}

concentrationArray=(0 50 100 150 200)

for i in ${!concentrationArray[*]}
do
echo " ${concentrationArray[$i]}ug/ml is running"
time $neutron_capture_DIR/neutron_capture -m $JOB_DIR/mac/${concentrationArray[$i]}ug_ml.mac -v off -n 10000000 > $JOB_DIR/${DataNo}/log/${concentrationArray[$i]}ug_ml.log &
sleep 10
done

cd $JOB_DIR/