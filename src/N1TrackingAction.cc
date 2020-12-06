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

// Geant4 Headers
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

// N1 Headers
#include "N1TrackingAction.hh"
#include "N1Analysis.hh"

using namespace std;

N1TrackingAction::N1TrackingAction():G4UserTrackingAction()
{}

N1TrackingAction::~N1TrackingAction()
{}

void N1TrackingAction::PreUserTrackingAction (const G4Track* aTrack){

	G4String particleName = aTrack->GetParticleDefinition()->GetParticleName();

	if(particleName != "alpha" && particleName != "Li7" && particleName != "gamma") return;

	G4double kineticEnergyAtVertex = aTrack->GetKineticEnergy();
	G4String creatorProcessName;
	G4String creatorModelName ;

	if(aTrack -> GetCreatorProcess ()!=0){
		creatorProcessName = aTrack -> GetCreatorProcess() -> GetProcessName() ;
		creatorModelName = aTrack ->GetCreatorModelName();
		if(creatorModelName=="Undefined"){
			creatorModelName="u_"+creatorProcessName;
		}
	}else{
		creatorProcessName = "gun" ;
		creatorModelName = "gun";
	}

	// Analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	if(particleName == "alpha")
		if ((kineticEnergyAtVertex >= 1.775*MeV && kineticEnergyAtVertex <= 1.778*MeV)|| (kineticEnergyAtVertex >= 1.471*MeV && kineticEnergyAtVertex <= 1.474*MeV) )
			analysisManager->FillH1(3, kineticEnergyAtVertex);

	if(particleName == "Li7")
		if ((kineticEnergyAtVertex >= 820*keV && kineticEnergyAtVertex <= 860*keV)||(kineticEnergyAtVertex >= 1.0125*MeV && kineticEnergyAtVertex <= 1.0145*MeV))
			analysisManager->FillH1(4, kineticEnergyAtVertex);

	if(particleName == "gamma")
		if (kineticEnergyAtVertex >= 476*keV && kineticEnergyAtVertex <= 480*keV)
			analysisManager->FillH1(5, kineticEnergyAtVertex);

}

void N1TrackingAction::PostUserTrackingAction (const G4Track* aTrack){

	G4String particleName = aTrack->GetParticleDefinition()->GetParticleName();

	// Analysis analysisManagerager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	if(analysisManager->GetNtupleActivation(0)==true){

		G4String creatorProcessName;
		G4String creatorModelName ;

		if(aTrack -> GetCreatorProcess ()!=0){
			creatorProcessName = aTrack -> GetCreatorProcess() -> GetProcessName() ;
			creatorModelName = aTrack ->GetCreatorModelName();
			if(creatorModelName=="Undefined"){
				creatorModelName="u_"+creatorProcessName;
			}
		}else{
			creatorProcessName = "gun" ;
			creatorModelName = "gun";
		}

		G4double KineticEnergyAtVertex 		= aTrack->GetVertexKineticEnergy();
		G4double RAtVertex 					= aTrack->GetVertexPosition().getR();
		G4String ParticleName 				= aTrack->GetParticleDefinition()-> GetParticleName();
		G4double TrackLength		 		= aTrack->GetTrackLength();
		G4double R		 					= aTrack->GetPosition().getR();


		analysisManager->FillNtupleDColumn(0,0,KineticEnergyAtVertex);
		analysisManager->FillNtupleDColumn(0,1,RAtVertex);
		analysisManager->FillNtupleSColumn(0,2,creatorProcessName);
		analysisManager->FillNtupleSColumn(0,3,creatorModelName);
		analysisManager->FillNtupleSColumn(0,4,ParticleName);
		analysisManager->FillNtupleDColumn(0,5,TrackLength);
		analysisManager->FillNtupleDColumn(0,6,R);
		analysisManager->AddNtupleRow(0);

	}

}
