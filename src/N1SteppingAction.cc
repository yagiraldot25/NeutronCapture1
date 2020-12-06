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
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackingManager.hh"

// N1 Headers
#include "N1SteppingAction.hh"
#include "N1DetectorConstruction.hh"
#include "N1Analysis.hh"

using namespace std;

N1SteppingAction::N1SteppingAction():G4UserSteppingAction()
{}

N1SteppingAction::~N1SteppingAction()
{}

void N1SteppingAction::UserSteppingAction(const G4Step* aStep)
{

	G4double energyDeposit = aStep->GetTotalEnergyDeposit();
	G4String volumeName = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume(0)->GetName();

	if (volumeName!="layer_phys") return;
	if (energyDeposit == 0) return;


	// Analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4double volumeMass = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume(0)->GetLogicalVolume()->GetMass();
	G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0);

	// Total PDD
	analysisManager->FillH1(1, copyNo*mm,energyDeposit/volumeMass);

	// Boron PDD
	G4String particleName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
	G4double kineticEnergyAtVertex = aStep->GetTrack()->GetVertexKineticEnergy();

	if(particleName == "alpha"){
		if ((kineticEnergyAtVertex >= 1.775*MeV && kineticEnergyAtVertex <= 1.778*MeV)|| (kineticEnergyAtVertex >= 1.471*MeV && kineticEnergyAtVertex <= 1.474*MeV) ){
			analysisManager->FillH1(2, copyNo*mm,energyDeposit/volumeMass);
			G4TrackVector childrens = *aStep->GetSecondary();
			for( G4int i = 0 ; i < G4int(childrens.size()) ; ++i){
				analysisManager->FillH1(2, copyNo*mm,childrens[i]->GetKineticEnergy()/volumeMass);
			}
		}
	}

	if(particleName == "Li7"){
		if ((kineticEnergyAtVertex >= 820*keV && kineticEnergyAtVertex <= 860*keV)||(kineticEnergyAtVertex >= 1.0125*MeV && kineticEnergyAtVertex <= 1.0145*MeV)){
			analysisManager->FillH1(2, copyNo*mm,energyDeposit/volumeMass);
			G4TrackVector childrens = *aStep->GetSecondary();
			for( G4int i = 0 ; i < G4int(childrens.size()) ; ++i){
				analysisManager->FillH1(2, copyNo*mm,childrens[i]->GetKineticEnergy()/volumeMass);
			}
		}
	}

	if(particleName == "gamma"){
		if (kineticEnergyAtVertex >= 476*keV && kineticEnergyAtVertex <= 480*keV){
			analysisManager->FillH1(2, copyNo*mm,energyDeposit/volumeMass);
			G4TrackVector childrens = *aStep->GetSecondary();
			for( G4int i = 0 ; i < G4int(childrens.size()) ; ++i){
				analysisManager->FillH1(2, copyNo*mm,childrens[i]->GetKineticEnergy()/volumeMass);
			}
		}
	}

}

