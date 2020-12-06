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

#ifndef N1DetectorMessenger_hh
#define N1DetectorMessenger_hh 1

// C++ Headers
#include <vector>
#include <map>

// Geant4 Headers
#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

// N1 Headers
#include "N1DetectorConstruction.hh"

using namespace std;

typedef map <G4String,G4UIdirectory*>         			UIDirectoryCollection ;
typedef map <G4String,G4UIcmdWithAString*>    			UIcmdWithAStringCollection ;
typedef map <G4String,G4UIcmdWithABool*>    			UIcmdWithABoolCollection ;
typedef map <G4String,G4UIcmdWithADoubleAndUnit*>    	UIcmdWithADoubleAndUnitCollection ;
typedef map <G4String,G4UIcmdWithAnInteger*>    		UIcmdWithAIntCollection ;
typedef map <G4String,G4UIcmdWithoutParameter*>    		UIcmdWithoutParameter ;

class N1DetectorConstruction ;
class G4UIdirectory ;
class G4UIcmdWithAString ;
class G4UIcmdWithABool ;
class G4UIcmdWithADoubleAndUnit ;
class G4UIcmdWithAnInteger ;
class G4UIcmdWithoutParameter ;

class N1DetectorMessenger: public G4UImessenger{

public:

	N1DetectorMessenger(N1DetectorConstruction* aN1DetectorConstruction ) ;
	~N1DetectorMessenger() ;

	void SetNewValue(G4UIcommand* command, G4String aValue) ;

private:

	N1DetectorConstruction*				fN1DetectorConstruction ;

	UIDirectoryCollection					fUIDirectoryCollection ;
	UIcmdWithAStringCollection				fUIcmdWithAStringCollection ;
	UIcmdWithABoolCollection				fUIcmdWithABoolCollection ;
	UIcmdWithADoubleAndUnitCollection		fUIcmdWithADoubleAndUnitCollection;
	UIcmdWithAIntCollection					fUIcmdWithAIntCollection;
	UIcmdWithoutParameter					fUIcmdWithoutParameter;


} ;

#endif // N1DetectorMessenger_hh
