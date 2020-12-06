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

	TString key_name("thermal/2");

	// Draw histos filled by Geant4 simulation

	TString file_dir="data/"+key_name+"/N1.root";
	TFile* F1 = new TFile(file_dir.Data());

	// ======================================================

	TCanvas* c1 = new TCanvas("c1", "c1", 600, 400);
	c1->cd()->SetLeftMargin(0.15);
	c1->cd()->SetLogy(false);
	c1->cd()->SetGrid(true,true);
	c1->cd()->SetTicks(true,true);

	// --- KineticEnergyAtVertex ---

	// Gun neutron spectrum

	TH1* h1_1 = static_cast<TH1D*>(F1->Get("histograms/KineticEnergyAtVertex"));
	h1_1->SetLineColor(kGreen);
	h1_1->SetLineWidth(2);
	h1_1->GetXaxis()->SetTitleOffset(1.2);
	h1_1->GetYaxis()->SetTitleOffset(1.8);
	//h1_1->SetTitle("Neutron Spectrum");
	h1_1->SetXTitle("Energy [MeV]");
	h1_1->SetYTitle("Relative Number of Neutrons");
	h1_1->Scale(1/h1_1->GetBinContent(h1_1->GetMaximumBin()));
	h1_1->Draw("HIST");

	// --- End KineticEnergyAtVertex ---

	TLegend* l1 = new TLegend(0.55, 0.70, 0.85, 0.85) ;
	l1->AddEntry(h1_1, "Standard Target", "L") ;
	l1->Draw() ;

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

	TH1* h2_1 = static_cast<TH1D*>(F1->Get("histograms/TotalPDD"));
	h2_1->Rebin(10);
	Double_t norm_factor2_1=1/h2_1->GetBinContent(h2_1->GetMaximumBin());
	//h2_1->Scale(norm_factor2_1);
	TGraph* gr2_1 = new TGraph(h2_1);
	gr2_1->SetLineColor(kGreen);
	gr2_1->SetLineWidth(2);
	gr2_1->SetMarkerStyle(2);
	gr2_1->SetMarkerColor(kGreen);
	gr2_1->SetFillColorAlpha(kGreen,0.2);
	gr2_1->SetFillStyle(1001);

	// Measured data

	Int_t rows_count2_2 = 26; // 26

	ifstream in_file2_2("analysis/data/total-dose-mesuared-2.dat");

	Double_t x2_2[rows_count2_2], y2_2[rows_count2_2];

	Double_t norm_factor2_2=0;

	for(Int_t i=0; !in_file2_2.eof();i++){
		in_file2_2 >> x2_2[i] >> y2_2[i];
		if(y2_2[i]>norm_factor2_2) norm_factor2_2=y2_2[i];
	}


	for(Int_t i=0; i<rows_count2_2;i++){
		y2_2[i]/=norm_factor2_2;
	}

	TGraph* gr2_2 = new TGraph(rows_count2_2,x2_2,y2_2);
	gr2_2->SetMarkerStyle(23);
	gr2_2->SetMarkerColor(kRed);

	// --- End Total PDD ---

	TMultiGraph* mg2_1 = new TMultiGraph();
	mg2_1->Add(gr2_1,"ABP");
	//mg2_1->Add(gr2_2,"P");
	mg2_1->Draw("ABLP");
	mg2_1->GetXaxis()->SetTitle("Depth in Phantom [mm]");
	mg2_1->GetYaxis()->SetTitle("Relative Total Absorbed Dose");

	TLegend* l2 = new TLegend(0.35, 0.70, 0.85, 0.85);
	l2->AddEntry(gr2_1, "Calculated Dose (H2O_B10 100um/ml)", "L");
	l2->AddEntry(gr2_2, "Measured Dose", "P");
	l2->Draw();

	TString output2 ="data/"+key_name+"/TotalPDD.png";
	c2->Print(output2.Data());

	// ======================================================

	TCanvas* c3 = new TCanvas("c3", "c3", 600, 400);
	c3->cd()->SetLeftMargin(0.15);
	c3->cd()->SetLogy(false);
	c3->cd()->SetGrid(true,true);
	c3->cd()->SetTicks(true,true);

	// --- Boron PDD ---

	// Calculation using sensitive volume

	TH1* h3_1 = static_cast<TH1D*>(F1->Get("histograms/BoronPDD"));
	h3_1->Rebin(10);
	Double_t norm_factor3_1=1/h3_1->GetBinContent(h3_1->GetMaximumBin());
	h3_1->Scale(norm_factor3_1);
	TGraph* gr3_1 = new TGraph(h3_1);
	gr3_1->SetLineColor(kGreen);
	gr3_1->SetLineWidth(2);
	gr3_1->SetMarkerStyle(2);
	gr3_1->SetMarkerColor(kGreen);
	gr3_1->SetFillColorAlpha(kGreen,0.2);
	gr3_1->SetFillStyle(1001);

	// Measured data

	Int_t rows_count3_2 = 18; // 18

	ifstream in_file3_2("analysis/data/boron-dose-mesuared-2.dat");

	Double_t x3_2[rows_count3_2], y3_2[rows_count3_2];

	Double_t norm_factor3_2=0;

	for(Int_t i=0; !in_file3_2.eof();i++){
		in_file3_2 >> x3_2[i] >> y3_2[i];
		if(y3_2[i]>norm_factor3_2) norm_factor3_2=y3_2[i];
	}


	for(Int_t i=0; i<rows_count3_2;i++){
		y3_2[i]/=norm_factor3_2;
	}

	TGraph* gr3_2 = new TGraph(rows_count3_2,x3_2,y3_2);
	gr3_2->SetMarkerStyle(23);
	gr3_2->SetMarkerColor(kRed);

	// --- End Boron PDD ---

	TMultiGraph* mg3_1 = new TMultiGraph();
	mg3_1->Add(gr3_1,"ABP");
	mg3_1->Add(gr3_2,"P");
	mg3_1->Draw("ABLP");
	mg3_1->GetXaxis()->SetTitle("Depth in Phantom [mm]");
	mg3_1->GetYaxis()->SetTitle("Relative Boron Absorbed Dose");

	TLegend* l3 = new TLegend(0.35, 0.70, 0.85, 0.85) ;
	l3->AddEntry(gr3_1, "Calculated Dose (H2O_B10) SV", "LAB") ;
	l3->AddEntry(gr3_2, "Measured Dose", "P") ;
	l3->Draw() ;

	TString output3 ="data/"+key_name+"/BoronPDD.png";
	c3->Print(output3.Data());

	// ======================================================

	TCanvas* c4 = new TCanvas("c4", "c4", 600, 400);
	c4->cd()->SetLeftMargin(0.15);
	c4->cd()->SetLogy(false);
	c4->cd()->SetGrid(true,true);
	c4->cd()->SetTicks(true,true);

	// --- BNC Boost Ratio ---

	// Calculation using sensitive volume

	Int_t rows_count4_1 = 30; // 26

	Double_t x4_1[rows_count4_1], y4_1[rows_count4_1];

	for(Int_t i=0; i<rows_count4_1;i++){
		x4_1[i]=gr2_1->GetX()[i];
		y4_1[i]=gr3_1->GetY()[i]/gr2_1->GetY()[i];
	}

	TGraph* gr4_1 = new TGraph(rows_count4_1,x4_1,y4_1);
	gr4_1->SetLineColor(kGreen);
	gr4_1->SetLineWidth(2);
	gr4_1->SetMarkerStyle(2);
	gr4_1->SetMarkerColor(kGreen);
	gr4_1->SetFillColorAlpha(kGreen,0.2);

	// Measured data

	Int_t rows_count4_2 = 17; // 17

	ifstream in_file4("analysis/data/boron-boost-ratio-2.dat");

	Double_t x4_2[rows_count4_2], y4_2[rows_count4_2];

	for(Int_t i=0; !in_file4.eof();i++){
		in_file4 >> x4_2[i] >> y4_2[i];
	}

	for(Int_t i=0; i<rows_count4_2;i++){
		y4_2[i]*=100;
	}

	TGraph* gr4_2 = new TGraph(rows_count4_2,x4_2,y4_2);
	gr4_2->SetMarkerStyle(23);
	gr4_2->SetMarkerColor(kRed);

	// --- End BNC Boost Ratio ---

	TMultiGraph* mg4_1 = new TMultiGraph();
	mg4_1->Add(gr4_1,"ABP");
	mg4_1->Add(gr4_2,"P");
	mg4_1->Draw("ABLP");
	mg4_1->GetXaxis()->SetTitle("Depth in Phantom [mm]");
	mg4_1->GetYaxis()->SetTitle("BNC Boost Ratio");

	TLegend* l4 = new TLegend(0.35, 0.70, 0.85, 0.85) ;
	l4->AddEntry(gr4_1, "Calculated Boost Ratio (H2O_B10) SV", "LAB") ;
	l4->AddEntry(gr4_2, "Measured Dose", "P") ;
	l4->Draw() ;

	TString output4 ="data/"+key_name+"/BNCBoostRatio.png";
	c4->Print(output4.Data());

	// ======================================================


}
