#!/bin/sh
#
# job1.sh run neutron_capture with test macro on lxplus 
# Copyright Andrés Camilo Sevilla
#
# !!!! Must be changed for each user !!! #

# Loading environmental variables 
#source /afs/cern.ch/work/a/asevilla/workspace/G4WORK/SciFW1/setup_lxplus.sh

# Defining variables
TEMPLATE_DIR=/Users/andreagiraldo/workspace/JOBS/neutron-capture
JOB_DIR=/Users/andreagiraldo/workspace/JOBS/neutron-capture/Job2

energyArray=(0.001 0.50 1 50 1 50 1 50)
energyUnitArray=(eV eV eV eV keV keV MeV MeV)

for i in ${!energyArray[*]}
do

	sed "
	
		s/%%FileName%%/${energyArray[$i]}ug_ml/g;
		
		s/%%Concentration%%/100/g;
		
		s/%%ConcentrationUnit%%/ug\/g/g;
		
		s/%%Particle%%/neutron/g;
		
		s/%%ConicalShapeBeam%%//g;
		
		s/%%BeamSpectrum%%/#/g;
		
		s/%%BeamSpectrumMacroFile%%//g;
		
		s/%%BeamMonoEnergy%%//g;
		
		s/%%BeamEnergy%%/${energyArray[$i]}/g;
		
		s/%%BeamEneryUnit%%/${energyUnitArray[$i]}/g;
		
		s/%%Histo1D0X%%/500 0 100 MeV/g;
		
		s/%%Histo1D1X%%/300 0 300 mm/g;
		
		s/%%Histo1D2X%%/300 0 300 mm/g;
		
		s/%%Histo1D3X%%/1000 1.4 1.8 MeV/g;
		
		s/%%Histo1D4X%%/1000 820 1020 keV/g;
		
		s/%%Histo1D5X%%/1000 476 480 keV/g;
		
		" $TEMPLATE_DIR/template_1.mac > $JOB_DIR/mac/${energyArray[$i]}${energyUnitArray[$i]}.mac
		
done