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
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVReplica.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4PhysicalConstants.hh"
#include "globals.hh"
#include "G4UserLimits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"

// N1 Headers
#include "N1DetectorConstruction.hh"

#include "N1Material.hh"

N1DetectorConstruction::N1DetectorConstruction(): G4VUserDetectorConstruction(),
fShell_log(0),
fPhantom_phys(0),
fShell_phys(0),
fLayer_phys(0)
{

	const G4double ug = 1.e-6*g;
	const G4double ppm = ug/g;
	new G4UnitDefinition("microgram", "ug" , "Mass", ug);
	new G4UnitDefinition("ppm", "ppm","Concentration", ppm);
	new G4UnitDefinition("miligram/gram", "mg/g","Concentration", mg/g);
	new G4UnitDefinition("microgram/gram", "ug/g","Concentration", ug/g);

	fN1DetectorMessenger = new N1DetectorMessenger(this) ;

	fConcentration = 200*ug/g;

}

N1DetectorConstruction::~N1DetectorConstruction()
{}

G4VPhysicalVolume* N1DetectorConstruction::Construct()
{  

	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// Define materials
	G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

	// General Attributes
	G4VisAttributes* simpleInvisibleSVisAtt;
	simpleInvisibleSVisAtt= new G4VisAttributes(G4Colour(0.,0.5,0.5,0.1));
	simpleInvisibleSVisAtt->SetVisibility(false);

	// Geometrical Volume =========================================================================================

	// World
	G4double world_size_X = (10/2.)*m;
	G4VSolid* world_geo = new G4Box("world_geo", world_size_X, world_size_X, world_size_X);


	//Logical Volume ==============================================================================================

	// World
	G4LogicalVolume* world_log = new G4LogicalVolume(world_geo,vacuum,"world_log");
	world_log -> SetVisAttributes(simpleInvisibleSVisAtt);

	//Physics Volume  =============================================================================================

	G4VPhysicalVolume* world_phys =
			new G4PVPlacement(0,                     	//no rotation
					G4ThreeVector(),       				//at (0,0,0)
					world_log,      					//its logical volume
					"world_phys",   					//its name
					0,                     				//its mother  volume
					false,                 				//no boolean operation
					0,                     				//copy number
					0);      			    			//overlaps checking

	SetupGeometry(world_log);

	//always return the physical World
	//
	return world_phys;

}

void N1DetectorConstruction::SetupGeometry(G4LogicalVolume* motherVolume){

	G4Material* material;
	if(fConcentration>0){
		material = N1Material::GetInstance()->GetMaterial("H2O+B10",fConcentration);
	}else{
		material = N1Material::GetInstance()->GetMaterial("G4_WATER");

	}

	// Visualization attributes
	G4VisAttributes* simplePhantomVisAtt;
	simplePhantomVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.1));
	simplePhantomVisAtt->SetVisibility(true);

	G4VisAttributes* simpleLayerVisAtt;
	simpleLayerVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0,1.0));
	simpleLayerVisAtt->SetVisibility(true);

	// Geometrical Volume =========================================================================================


	G4cout<<"============================ Geometry Description ============================"<<G4endl;

	// phantom
	G4double phantom_rmax =10*cm, phantom_dz=(30./2.)*cm;
	G4VSolid* phantom_geo =new G4Tubs("phantom_geo",0,phantom_rmax,phantom_dz,0*deg,360*deg);

	// Shells frame
	G4double shellsFrame_rmin = (60/2.)*mm, shellsFrame_rmax =10*cm, shellsFrame_dz=(30./2.)*cm;
	G4VSolid* shellsFrame_geo =new G4Tubs("shellsFrame_geo",shellsFrame_rmin,shellsFrame_rmax,shellsFrame_dz,0*deg,360*deg);

	G4cout<<"Diameter to outer sensitive volume: "<<G4BestUnit(shellsFrame_rmin*2,"Length")<<G4endl;

	// Shells
	G4int nShells = 9;
	G4double shell_rmax = shellsFrame_rmax/nShells, shell_dz=shellsFrame_dz;
	G4VSolid* shell_geo = new G4Tubs("div_phantom_geo",0,shell_rmax, shell_dz,0*deg,360*deg);

	G4cout<<"No of shells to bias: "<<nShells<<G4endl;

	// Layers frame
	G4double layersFrame_rmin=0, layersFrame_rmax=shellsFrame_rmin,layersFrame_dz=(30./2.)*cm;
	G4VSolid* layersFrame_geo = new G4Tubs("layersFrame_geo",layersFrame_rmin,layersFrame_rmax,layersFrame_dz,0*deg,360*deg);

	// Layer
	G4int nLayers = 300;
	G4double layer_rmin = layersFrame_rmin, layer_rmax = layersFrame_rmax,layer_dz=layersFrame_dz/nLayers;
	G4VSolid* layer_geo = new G4Tubs("layer_geo",layer_rmin,layer_rmax,layer_dz,0*deg,360*deg);

	// Layers core frame
	G4double layersCoreFrame_rmax=(60/2.)*mm,layersCoreFrame_dz=layersFrame_dz;
	G4VSolid* layersCoreFrame_geo = new G4Tubs("layersFrame_geo",0,layersCoreFrame_rmax,layersCoreFrame_dz,0*deg,360*deg);

	//Logical Volume ==============================================================================================

	// phantom
	G4LogicalVolume* phantom_log = new G4LogicalVolume(phantom_geo, material,"phantom_log");
	phantom_log -> SetVisAttributes(simplePhantomVisAtt);

	// Shells frame
	G4LogicalVolume* shellsFrame_log = new G4LogicalVolume(shellsFrame_geo, material,"shellsFrame_log");
	shellsFrame_log -> SetVisAttributes(simplePhantomVisAtt);

	// Shell
	G4LogicalVolume* shell_log = new G4LogicalVolume(shell_geo, material,"shell_log");
	shell_log -> SetVisAttributes(simplePhantomVisAtt);
	fShell_log=shell_log;

	// Layers frame
	G4LogicalVolume* layersFrame_log = new G4LogicalVolume(layersFrame_geo, material,"layersFrame_log");
	layersFrame_log -> SetVisAttributes(simpleLayerVisAtt);

	// Layer
	G4LogicalVolume* layer_log = new G4LogicalVolume(layer_geo, material,"layer_log");
	layer_log -> SetVisAttributes(simpleLayerVisAtt);

	// Layers core frame
	G4LogicalVolume* layersCoreFrame_log = new G4LogicalVolume(layersCoreFrame_geo, material,"layersCoreFrame_log");
	layersCoreFrame_log -> SetVisAttributes(simpleLayerVisAtt);

	G4UserLimits *l = new G4UserLimits();
	// Sets a max Step length in the layer and layer frame :
	G4double maxStep = 4*um;
	l->SetMaxAllowedStep(maxStep);
	layersFrame_log->SetUserLimits(l);
	layer_log->SetUserLimits(l);

	//Physics Volume  =============================================================================================

	// phantom
	fPhantom_phys = new G4PVPlacement(0,
			G4ThreeVector(0,0,phantom_dz),      //at (0,0,0)
			phantom_log,     					//its logical volume
			"phantom_phys", 	 				//its name
			motherVolume, 						//its mother  volume
			false,                 				//no boolean operation
			0,                     				//copy number
			true);      			     		//overlaps checking

	// Shells frame
	new G4PVPlacement(0,
			G4ThreeVector(0,0,0),               //at (0,0,0)
			shellsFrame_log,     				//its logical volume
			"shellsFrame_phys", 	 			//its name
			phantom_log, 						//its mother  volume
			false,                 				//no boolean operation
			0,                     				//copy number
			true);      			     		//overlaps checking

	// Shell
	fShell_phys = new G4PVReplica("shells_phys",
			shell_log,
			shellsFrame_log,
			kRho,
			nShells,
			(shellsFrame_rmax-shellsFrame_rmin)/nShells,
			shellsFrame_rmin);

	// Layers frame
	new G4PVPlacement(0,                     	//no rotation
			G4ThreeVector(),       				//at (0,0,0)
			layersFrame_log,     	 			//its logical volume
			"layerFrame_phys", 	 				//its name
			phantom_log, 						//its mother  volume
			false,                 				//no boolean operation
			0,                     				//copy number
			true);      			     		//overlaps checking

	// Replica
	fLayer_phys = new G4PVReplica("layer_phys",
			layer_log,
			layersFrame_log,
			kZAxis,
			nLayers,
			layersFrame_dz*2/nLayers);

}

void N1DetectorConstruction::ConstructSDandField()
{}

void N1DetectorConstruction::SetConcentration(G4double aConcentration){


	G4GeometryManager* geoman = G4GeometryManager::GetInstance() ;

	// Open geometry for the physical volume to be modified ...
	//
	geoman->OpenGeometry(fPhantom_phys);

	fConcentration=aConcentration;
	G4Material* material;
	if(fConcentration>0){
		material = N1Material::GetInstance()->GetMaterial("H2O+B10",fConcentration);
	}else{
		material = N1Material::GetInstance()->GetMaterial("G4_WATER");

	}
	this->fPhantom_phys->GetLogicalVolume()->SetMaterial(material);
	this->fShell_phys->GetLogicalVolume()->SetMaterial(material);
	this->fLayer_phys->GetLogicalVolume()->SetMaterial(material);


	G4cout<<"================================================================================"<<fConcentration<<G4endl;

	// Close geometry for the portion modified ...
	//
	geoman->CloseGeometry(fPhantom_phys);

	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4RunManager::GetRunManager()->ReinitializeGeometry();

}
