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
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// N1 Headers
#include "N1RunAction.hh"
#include "N1Analysis.hh"

class G4AccumulableManager;

using namespace std;

N1RunAction::N1RunAction(): G4UserRunAction()
{

	// add new units for dose
	//
	const G4double milligray = 1.e-3*gray;
	const G4double microgray = 1.e-6*gray;
	const G4double nanogray  = 1.e-9*gray;
	const G4double picogray  = 1.e-12*gray;

	new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
	new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
	new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
	new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetActivation(true);
	G4cout << "Using " << analysisManager->GetType() << G4endl;
	analysisManager->SetVerboseLevel(0);
	analysisManager->SetFileName("data/N1");

	// Create Histograms an n-Tuples
	CreateNTuples();
	CreateHistos();

}

N1RunAction::~N1RunAction()
{
	delete G4AnalysisManager::Instance();
}

void N1RunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	if(analysisManager->IsActive()){
		// Open an output file
		analysisManager->OpenFile();
	}
}

void N1RunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	if(analysisManager->IsActive()){
		// Save histograms and ntuples
		analysisManager->Write();
		analysisManager->CloseFile();
	}

	// Print
	//
	if (IsMaster()) {
		G4cout
		<< G4endl
		<< "--------------------End of Global Run-----------------------";
		G4cout
		<< G4endl
		<< " Total events per run : "
		<< nofEvents
		<< G4endl;
	}

}

void N1RunAction::CreateNTuples(){

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetNtupleMerging(true);

	// Creating ntuples
	analysisManager->SetFirstNtupleId(0);

	// id = 0
	analysisManager->CreateNtuple("SecondariesProduction", "Variables related to secondaries production");
	analysisManager->SetNtupleActivation(0,true);
	analysisManager->CreateNtupleDColumn(0,"KineticEnergyAtVertex");
	analysisManager->CreateNtupleDColumn(0,"RAtVertex");
	analysisManager->CreateNtupleSColumn(0,"CreatorProcessName");
	analysisManager->CreateNtupleSColumn(0,"CreatorModelName");
	analysisManager->CreateNtupleSColumn(0,"ParticleName");
	analysisManager->CreateNtupleDColumn(0,"TrackLength");
	analysisManager->CreateNtupleDColumn(0,"R");
	analysisManager->FinishNtuple();


	// id = 1
	analysisManager->CreateNtuple("Source", "Variables related to source");
	analysisManager->SetNtupleActivation(1,false);
	analysisManager->CreateNtupleDColumn(1,"KineticEnergyAtVertex");
	analysisManager->CreateNtupleSColumn(1,"ParticleName");
	analysisManager->CreateNtupleDColumn(1,"XAtVertex");
	analysisManager->CreateNtupleDColumn(1,"YAtVertex");
	analysisManager->CreateNtupleDColumn(1,"ZAtVertex");
	analysisManager->FinishNtuple();

}

void N1RunAction::CreateHistos(){

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	// Creating histos
	analysisManager->SetFirstHistoId(0);

	// id = 0
	analysisManager->CreateH1("KineticEnergyAtVertex","Kinetic energy at vertex", 100, 0, 50*MeV,"MeV");
	analysisManager->SetH1Activation(0,true);
	analysisManager->SetH1XAxisTitle(0,"Energy [MeV]");
	analysisManager->SetH1YAxisTitle(0,"Relative Number of Neutrons");

	// id = 1
	analysisManager->CreateH1("TotalPDD","Total percentage depth dose", 300, 0, 300*mm,"mm");
	analysisManager->SetH1Activation(1,true);
	analysisManager->SetH1XAxisTitle(1,"copyNo");
	analysisManager->SetH1YAxisTitle(1,"Total Deposit Energy [keV]");

	// id = 2
	analysisManager->CreateH1("BoronPDD","Boron percentage depth dose", 300, 0, 300*mm,"mm");
	analysisManager->SetH1Activation(2,true);
	analysisManager->SetH1XAxisTitle(2,"copyNo");
	analysisManager->SetH1YAxisTitle(2,"Boron Deposit Energy [keV]");

	// id = 3
	analysisManager->CreateH1("AlphaKineticEnergyAtVertex","Kinetic energy at vertex for alpha particles", 1000 , 1.4*MeV, 1.8*MeV,"keV");
	analysisManager->SetH1Activation(3,true);
	analysisManager->SetH1XAxisTitle(3,"Energy [keV]");
	analysisManager->SetH1YAxisTitle(3,"Counts");

	// id = 4
	analysisManager->CreateH1("Li7KineticEnergyAtVertex","Kinetic energy at vertex for Li7 particles",1000 , 820*keV, 1020*keV,"keV");
	analysisManager->SetH1Activation(4,true);
	analysisManager->SetH1XAxisTitle(4,"Energy [keV]");
	analysisManager->SetH1YAxisTitle(4,"Counts");

	// id = 5
	analysisManager->CreateH1("GammaKineticEnergyAtVertex","Kinetic energy at vertex for gamma particles",1000 , 476*keV, 480*keV,"keV");
	analysisManager->SetH1Activation(5,true);
	analysisManager->SetH1XAxisTitle(5,"Energy [keV]");
	analysisManager->SetH1YAxisTitle(5,"Counts");

}



