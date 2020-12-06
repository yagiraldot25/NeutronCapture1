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

#ifndef N1SteppingAction_h
#define N1SteppingAction_h 1


// Geant4 Headers
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"

using namespace std;

/// Stepping action class
///

class N1SteppingAction : public G4UserSteppingAction
{

public:
	N1SteppingAction();
	virtual ~N1SteppingAction();

	// method from the base class
	virtual void UserSteppingAction(const G4Step*);

};

#endif // N1SteppingAction_h
