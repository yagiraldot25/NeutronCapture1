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
#include "G4EventManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"

// N1 Headers
#include "N1EventAction.hh"
#include "N1Analysis.hh"
#include "N1RunAction.hh"

N1EventAction::N1EventAction():G4UserEventAction()
{}

N1EventAction::~N1EventAction()
{}

void N1EventAction::BeginOfEventAction(const G4Event* anEvent)
{

	G4int nEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed() ;
	if(nEvents>10){
		G4int 	fraction 	= G4int(nEvents/100) ;
		if(anEvent->GetEventID()%fraction == 0)
			G4cout<<"("<<(anEvent->GetEventID()/(nEvents*1.0)*100)<<" %)"<<G4endl ;

	}else {
		G4int 	fraction 	= G4int(nEvents/1) ;
		if(anEvent->GetEventID()%fraction == 0)
			G4cout<<"("<<(anEvent->GetEventID()/(nEvents*1.0)*100)<<" %)"<<G4endl ;
	}

}

void N1EventAction::EndOfEventAction(const G4Event* anEvent)
{

	// Analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4double KineticEnergyAtVertex = anEvent->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();

	analysisManager->FillH1(0, KineticEnergyAtVertex);

	if(analysisManager->GetNtupleActivation(1)==true){

		G4String ParticleName		 		= anEvent->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName();
		G4double XAtVertex 					= anEvent->GetPrimaryVertex()->GetPosition().x();
		G4double YAtVertex 					= anEvent->GetPrimaryVertex()->GetPosition().y();
		G4double ZAtVertex 					= anEvent->GetPrimaryVertex()->GetPosition().z();

		analysisManager->FillNtupleDColumn(1,0,KineticEnergyAtVertex);
		analysisManager->FillNtupleSColumn(1,1,ParticleName);
		analysisManager->FillNtupleDColumn(1,2,XAtVertex);
		analysisManager->FillNtupleDColumn(1,3,YAtVertex);
		analysisManager->FillNtupleDColumn(1,4,ZAtVertex);
		analysisManager->AddNtupleRow(1);

	}
}





