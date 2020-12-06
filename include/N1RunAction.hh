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

#ifndef N1RunAction_h
#define N1RunAction_h 1

// Geant4 Headers
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

// N1 Headers
#include "N1DetectorConstruction.hh"

using namespace std;

/// Run action class
///

class N1RunAction : public G4UserRunAction
{

public:
	N1RunAction();
	virtual ~N1RunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

	void CreateHistos();
	void CreateNTuples();
};

#endif // N1RunAction_h
