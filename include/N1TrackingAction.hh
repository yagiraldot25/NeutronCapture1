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

#ifndef N1TrackingAction_h
#define N1TrackingAction_h 1

// Geant4 Headers
#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

/// Tracking action class
///

class N1TrackingAction : public G4UserTrackingAction{

public :

	N1TrackingAction();
	virtual ~N1TrackingAction();

	// method from the base class
	virtual void PreUserTrackingAction (const G4Track* aTrack);
	virtual void PostUserTrackingAction (const G4Track* aTrack);


private:
	vector<G4int> fNCParticlesVector;


};

#endif // N1TrackingAction_h

