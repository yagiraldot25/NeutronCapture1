/*
 * P-P Rad 1.0
 * Copyright (c) 2019 Instituto Nacional de Cancerología - INC
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

// ROOT Headers
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TGaxis.h"

#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Plot_01(){

	gStyle->SetOptStat(0);

	TString key_name("data");

	// Draw histos filled by Geant4 simulation
	//
	map<TString,TFile*> FileCollection;
	map<TString,TFile*>::iterator FileCollectionIt;

	FileCollection["0"] 		= new TFile("./"+key_name+"/data/0ug_ml.root");
	FileCollection["1"]		= new TFile("./"+key_name+"/data/1ug_ml.root");
	FileCollection["5"]		= new TFile("./"+key_name+"/data/5ug_ml.root");
	FileCollection["10"]		= new TFile("./"+key_name+"/data/10ug_ml.root");
	FileCollection["20"]		= new TFile("./"+key_name+"/data/20ug_ml.root");
	FileCollection["50"]		= new TFile("./"+key_name+"/data/50ug_ml.root");
	FileCollection["100"]		= new TFile("./"+key_name+"/data/100ug_ml.root");

	map<TString,Int_t> ColorCollection;

	ColorCollection["0"] 		= kBlue;
	ColorCollection["1"] 		= kRed;
	ColorCollection["5"] 		= kMagenta;
	ColorCollection["10"] 		= kCyan;
	ColorCollection["20"] 		= kGreen;
	ColorCollection["50"] 		= kYellow;
	ColorCollection["100"] 		= kViolet;

	// ======================================================

	TCanvas* c1 = new TCanvas("c1", "c1", 600, 400);
	c1->cd()->SetLeftMargin(0.15);
	c1->cd()->SetLogy(false);
	c1->cd()->SetGrid(true,true);
	c1->cd()->SetTicks(true,true);

	// --- KineticEnergyAtVertex ---

	// Gun neutron spectrum


	map<TString,TH1D*> h1;
	map<TString,TGraph*> gr1;
	TMultiGraph* mg1 = new TMultiGraph();
	TLegend* l1 = new TLegend(0.35, 0.70, 0.85, 0.85);

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){

		h1[FileCollectionIt->first] = static_cast<TH1D*>(FileCollectionIt->second->Get("histograms/KineticEnergyAtVertex"));
		h1[FileCollectionIt->first]->Rebin(20);
		Double_t norm_factor1 = 1/h1[FileCollectionIt->first]->GetBinContent(h1[FileCollectionIt->first]->GetMaximumBin());
		h1[FileCollectionIt->first]->Scale(norm_factor1);
		gr1[FileCollectionIt->first] = new TGraph(h1[FileCollectionIt->first]);
		gr1[FileCollectionIt->first]->SetLineColor(ColorCollection[FileCollectionIt->first]);
		gr1[FileCollectionIt->first]->SetLineWidth(2);
		gr1[FileCollectionIt->first]->SetMarkerStyle(1);
		gr1[FileCollectionIt->first]->SetMarkerColor(ColorCollection[FileCollectionIt->first]);
		gr1[FileCollectionIt->first]->SetFillColorAlpha(ColorCollection[FileCollectionIt->first],0.2);
		gr1[FileCollectionIt->first]->SetFillStyle(1001);

		mg1->Add(gr1[FileCollectionIt->first],"L");
		l1->AddEntry(gr1[FileCollectionIt->first], "Total ("+FileCollectionIt->first+"ug/ml)", "L");

	}

	mg1->Draw("ABCLP");
	mg1->GetXaxis()->SetTitle("Energy [MeV]");
	mg1->GetYaxis()->SetTitle("Relative Number of Neutrons");
	l1->Draw();

	// --- End KineticEnergyAtVertex ---

	TString output1 ="data/"+key_name+"/neutron-spectrum.png";;
	c1->Print(output1.Data());

	// ======================================================

	TCanvas* c2 = new TCanvas("c2", "c2", 600, 400);
	c2->cd()->SetLeftMargin(0.15);
	c2->cd()->SetLogy(false);
	c2->cd()->SetGrid(true,true);
	c2->cd()->SetTicks(true,true);

	// --- Total PDD ---

	// Calculation using sensitive volume

	map<TString,TH1D*> h2;
	map<TString,TGraph*> gr2;
	TMultiGraph* mg2 = new TMultiGraph();
	TLegend* l2 = new TLegend(0.35, 0.70, 0.85, 0.85);

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){

		h2[FileCollectionIt->first] = static_cast<TH1D*>(FileCollectionIt->second->Get("histograms/TotalPDD"));
		h2[FileCollectionIt->first]->Rebin(20);
		Double_t norm_factor2_1=1E21/1E6;
		h2[FileCollectionIt->first]->Scale(norm_factor2_1);
		gr2[FileCollectionIt->first] = new TGraph(h2[FileCollectionIt->first]);
		gr2[FileCollectionIt->first]->SetLineColor(ColorCollection[FileCollectionIt->first]);
		gr2[FileCollectionIt->first]->SetLineWidth(2);
		gr2[FileCollectionIt->first]->SetMarkerStyle(2);
		gr2[FileCollectionIt->first]->SetMarkerColor(ColorCollection[FileCollectionIt->first]);
		gr2[FileCollectionIt->first]->SetFillColorAlpha(ColorCollection[FileCollectionIt->first],0.2);
		gr2[FileCollectionIt->first]->SetFillStyle(1001);

		mg2->Add(gr2[FileCollectionIt->first],"CP");
		l2->AddEntry(gr2[FileCollectionIt->first], "Total ("+FileCollectionIt->first+"ug/ml)", "L");

	}

	map<TString,TH1D*> h3;
	map<TString,TGraph*> gr3;

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){

		h3[FileCollectionIt->first] = static_cast<TH1D*>(FileCollectionIt->second->Get("histograms/BoronPDD"));
		h3[FileCollectionIt->first]->Rebin(20);
		Double_t norm_factor2_2=1E21/1E6;
		h3[FileCollectionIt->first]->Scale(norm_factor2_2);
		gr3[FileCollectionIt->first] = new TGraph(h3[FileCollectionIt->first]);
		gr3[FileCollectionIt->first]->SetLineColor(ColorCollection[FileCollectionIt->first]);
		gr3[FileCollectionIt->first]->SetLineWidth(2);
		gr3[FileCollectionIt->first]->SetLineStyle(2);
		gr3[FileCollectionIt->first]->SetMarkerStyle(2);
		gr3[FileCollectionIt->first]->SetMarkerColor(ColorCollection[FileCollectionIt->first]);
		gr3[FileCollectionIt->first]->SetFillColorAlpha(ColorCollection[FileCollectionIt->first],0.2);
		gr3[FileCollectionIt->first]->SetFillStyle(1001);

		mg2->Add(gr3[FileCollectionIt->first],"CP");
		l2->AddEntry(gr3[FileCollectionIt->first], "n+10B (Neutron Capture) ("+FileCollectionIt->first+"ug/ml)", "L");

	}

	mg2->Draw("ABCLP");
	mg2->GetXaxis()->SetTitle("Depth in Phantom [mm]");
	mg2->GetYaxis()->SetTitle("Absorbed Dose per incident neutron [nGy]");
	l2->Draw();

	// --- End Total PDD ---

	TString output2 ="Job1/"+key_name+"/TotalPDD.png";
	c2->Print(output2.Data());

}
