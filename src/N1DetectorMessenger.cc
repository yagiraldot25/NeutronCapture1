/*
 * Neutron Capture 1.0
 * Copyright (c) 2020
 * Universidad Nacional de Colombia
 * Servicio Geológico Colombiano
 * All Right Reserved.
 *
 * Developed by Andrea Giraldo Torres
 *              Andrés Camilo Sevilla Moreno
 *
 * Use and copying of these libraries and preparation of derivative works
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * Bogotá, Colombia.
 *
 */

// N1 Headers
#include "N1DetectorMessenger.hh"

N1DetectorMessenger::N1DetectorMessenger(N1DetectorConstruction* aN1DetectorConstruction){

	fN1DetectorConstruction = aN1DetectorConstruction ;

	fUIDirectoryCollection["N1Geometry"] = new G4UIdirectory("/N1/geometry/") ;
	fUIDirectoryCollection["N1Geometry"] -> SetGuidance("Geometry construction commands") ;

	fUIcmdWithADoubleAndUnitCollection["SetConcentration"] = new G4UIcmdWithADoubleAndUnit("/N1/geometry/SetConcentration",this) ;
	fUIcmdWithADoubleAndUnitCollection["SetConcentration"] -> SetGuidance("Set particles concentration in the medium");
	fUIcmdWithADoubleAndUnitCollection["SetConcentration"] -> SetParameterName("Concentration",false);
	fUIcmdWithADoubleAndUnitCollection["SetConcentration"] -> SetUnitCategory("Concentration");
	fUIcmdWithADoubleAndUnitCollection["SetConcentration"] -> AvailableForStates(G4State_PreInit, G4State_Idle);

}


N1DetectorMessenger::~N1DetectorMessenger(){

	// UI Directory Collection
	for(size_t i = 0; i < fUIDirectoryCollection.size(); i++){
		delete fUIDirectoryCollection[i] ;
	}

	// UI cmd With a String Collection
	for(size_t i = 0; i < fUIcmdWithAStringCollection.size(); i++){
		delete fUIcmdWithAStringCollection[i] ;
	}

	// UI cmd With a Bool Collection
	for(size_t i = 0; i < fUIcmdWithABoolCollection.size(); i++){
		delete fUIcmdWithABoolCollection[i] ;
	}

	// UI cmd With a Double and Unit Collection
	for(size_t i = 0; i < fUIcmdWithADoubleAndUnitCollection.size(); i++){
		delete fUIcmdWithADoubleAndUnitCollection[i] ;
	}

	// UI cmd With a Int Collection
	for(size_t i = 0; i < fUIcmdWithAIntCollection.size(); i++){
		delete fUIcmdWithAIntCollection[i] ;
	}
}

void N1DetectorMessenger::SetNewValue(G4UIcommand* command,G4String aValue ){

	if( command == fUIcmdWithADoubleAndUnitCollection["SetConcentration"] ) { fN1DetectorConstruction->SetConcentration(fUIcmdWithADoubleAndUnitCollection["SetConcentration"]->GetNewDoubleValue(aValue)); }

}

