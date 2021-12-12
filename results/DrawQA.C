#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"

void DrawQA() {
  gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetOptStat(0);

  int ci[4];
  TColor* color[4];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);//blue
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);//red
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);//yellow
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);//light blue

  TFile* inputFile = TFile::Open("AnalysisResults.root");
  TDirectory* inputDir = inputFile->GetDirectory("Results");
  TList* inputList = nullptr;
  inputDir->GetObject("SimpleTask_",inputList);

  TH1D*      fHistLambdaPt[2];
  TH1D*      fHistLambdaEta[2];
  TH1D*      fHistLambdaPhi[2];
  TH1D*      fHistLambdaDcaToPrimVertex[2];
  TH1D*      fHistLambdaCPA[2];
  TH1D*      fHistLambdaDecayLength[2];
  TH1D*      fHistLambdaMass[2];
  TH1D*      fHistAntiLambdaPt[2];
  TH1D*      fHistAntiLambdaEta[2];
  TH1D*      fHistAntiLambdaPhi[2];
  TH1D*      fHistAntiLambdaDcaToPrimVertex[2];
  TH1D*      fHistAntiLambdaCPA[2];
  TH1D*      fHistAntiLambdaDecayLength[2];
  TH1D*      fHistAntiLambdaMass[2];
  TProfile*  fProfileLambdaMassVsPt[2];
  TProfile*  fProfileAntiLambdaMassVsPt[2];

  for (size_t i = 0; i < 2; i++)
  {
    fHistLambdaPt[i]                  = nullptr;
    fHistLambdaEta[i]                 = nullptr;
    fHistLambdaPhi[i]                 = nullptr;
    fHistLambdaDcaToPrimVertex[i]     = nullptr;
    fHistLambdaCPA[i]                 = nullptr;
    fHistLambdaDecayLength[i]         = nullptr;
    fHistLambdaMass[i]                = nullptr;
    fHistAntiLambdaPt[i]              = nullptr;
    fHistAntiLambdaEta[i]             = nullptr;
    fHistAntiLambdaPhi[i]             = nullptr;
    fHistAntiLambdaDcaToPrimVertex[i] = nullptr;
    fHistAntiLambdaCPA[i]             = nullptr;
    fHistAntiLambdaDecayLength[i]     = nullptr;
    fHistAntiLambdaMass[i]            = nullptr;
    fProfileLambdaMassVsPt[i]         = nullptr;
    fProfileAntiLambdaMassVsPt[i]     = nullptr;
  }

  fHistLambdaPt[0]                  = (TH1D*)inputList->FindObject("hLambdaPt_BeforeMassCut");
  fHistLambdaEta[0]                 = (TH1D*)inputList->FindObject("hLambdaEta_BeforeMassCut");
  fHistLambdaPhi[0]                 = (TH1D*)inputList->FindObject("hLambdaPhi_BeforeMassCut");
  fHistLambdaDcaToPrimVertex[0]     = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_BeforeMassCut");
  fHistLambdaCPA[0]                 = (TH1D*)inputList->FindObject("hLambdaCPA_BeforeMassCut");
  fHistLambdaDecayLength[0]         = (TH1D*)inputList->FindObject("hLambdaDecayLength_BeforeMassCut");
  fHistLambdaMass[0]                = (TH1D*)inputList->FindObject("hLambdaMass_BeforeMassCut");
  fHistAntiLambdaPt[0]              = (TH1D*)inputList->FindObject("hAntiLambdaPt_BeforeMassCut");
  fHistAntiLambdaEta[0]             = (TH1D*)inputList->FindObject("hAntiLambdaEta_BeforeMassCut");
  fHistAntiLambdaPhi[0]             = (TH1D*)inputList->FindObject("hAntiLambdaPhi_BeforeMassCut");
  fHistAntiLambdaDcaToPrimVertex[0] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_BeforeMassCut");
  fHistAntiLambdaCPA[0]             = (TH1D*)inputList->FindObject("hAntiLambdaCPA_BeforeMassCut");
  fHistAntiLambdaDecayLength[0]     = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_BeforeMassCut");
  fHistAntiLambdaMass[0]            = (TH1D*)inputList->FindObject("hAntiLambdaMass_BeforeMassCut");
  fProfileLambdaMassVsPt[0]         = (TProfile*)inputList->FindObject("pLambdaMassVsPt_BeforeMassCut");
  fProfileAntiLambdaMassVsPt[0]     = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_BeforeMassCut");

  fHistLambdaPt[1]                  = (TH1D*)inputList->FindObject("hLambdaPt_AfterMassCut");
  fHistLambdaEta[1]                 = (TH1D*)inputList->FindObject("hLambdaEta_AfterMassCut");
  fHistLambdaPhi[1]                 = (TH1D*)inputList->FindObject("hLambdaPhi_AfterMassCut");
  fHistLambdaDcaToPrimVertex[1]     = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_AfterMassCut");
  fHistLambdaCPA[1]                 = (TH1D*)inputList->FindObject("hLambdaCPA_AfterMassCut");
  fHistLambdaDecayLength[1]         = (TH1D*)inputList->FindObject("hLambdaDecayLength_AfterMassCut");
  fHistLambdaMass[1]                = (TH1D*)inputList->FindObject("hLambdaMass_AfterMassCut");
  fHistAntiLambdaPt[1]              = (TH1D*)inputList->FindObject("hAntiLambdaPt_AfterMassCut");
  fHistAntiLambdaEta[1]             = (TH1D*)inputList->FindObject("hAntiLambdaEta_AfterMassCut");
  fHistAntiLambdaPhi[1]             = (TH1D*)inputList->FindObject("hAntiLambdaPhi_AfterMassCut");
  fHistAntiLambdaDcaToPrimVertex[1] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_AfterMassCut");
  fHistAntiLambdaCPA[1]             = (TH1D*)inputList->FindObject("hAntiLambdaCPA_AfterMassCut");
  fHistAntiLambdaDecayLength[1]     = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_AfterMassCut");
  fHistAntiLambdaMass[1]            = (TH1D*)inputList->FindObject("hAntiLambdaMass_AfterMassCut");
  fProfileLambdaMassVsPt[1]         = (TProfile*)inputList->FindObject("pLambdaMassVsPt_AfterMassCut");
  fProfileAntiLambdaMassVsPt[1]     = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_AfterMassCut");

  //Set Mass Style
  fHistLambdaMass[0]     -> SetMarkerColor(ci[0]);
  fHistLambdaMass[0]     -> SetLineColor(ci[0]);
  fHistAntiLambdaMass[0] -> SetMarkerColor(ci[1]);
  fHistAntiLambdaMass[0] -> SetLineColor(ci[1]);
  fHistLambdaMass[1]     -> SetMarkerColor(ci[3]);
  fHistLambdaMass[1]     -> SetLineColor(ci[3]);
  fHistAntiLambdaMass[1] -> SetMarkerColor(ci[2]);
  fHistAntiLambdaMass[1] -> SetLineColor(ci[2]);

  //Set Mass vs pT style
  fProfileLambdaMassVsPt[0]     -> SetMarkerColor(ci[0]);
  fProfileLambdaMassVsPt[0]     -> SetLineColor(ci[0]);
  fProfileAntiLambdaMassVsPt[0] -> SetMarkerColor(ci[1]);
  fProfileAntiLambdaMassVsPt[0] -> SetLineColor(ci[1]);
  fProfileLambdaMassVsPt[1]     -> SetMarkerColor(ci[3]);
  fProfileLambdaMassVsPt[1]     -> SetLineColor(ci[3]);
  fProfileAntiLambdaMassVsPt[1] -> SetMarkerColor(ci[2]);
  fProfileAntiLambdaMassVsPt[1] -> SetLineColor(ci[2]);

  //Set pT style
  fHistLambdaPt[0]->SetMarkerColor(ci[0]);
  fHistLambdaPt[0]->SetLineColor(ci[0]);
  fHistAntiLambdaPt[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaPt[0]->SetLineColor(ci[1]);
  fHistLambdaPt[1]->SetMarkerColor(ci[3]);
  fHistLambdaPt[1]->SetLineColor(ci[3]);
  fHistAntiLambdaPt[1]->SetMarkerColor(ci[2]);
  fHistAntiLambdaPt[1]->SetLineColor(ci[2]);

  //Set eta style
  fHistLambdaEta[0]->SetLineColor(ci[0]);
  fHistAntiLambdaEta[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaEta[0]->SetLineColor(ci[1]);
  fHistLambdaEta[1]->SetMarkerColor(ci[3]);
  fHistLambdaEta[1]->SetLineColor(ci[3]);
  fHistAntiLambdaEta[1]->SetMarkerColor(ci[2]);
  fHistAntiLambdaEta[1]->SetLineColor(ci[2]);

  //Set phi style
  fHistLambdaPhi[0]->SetLineColor(ci[0]);
  fHistAntiLambdaPhi[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaPhi[0]->SetLineColor(ci[1]);
  fHistLambdaPhi[1]->SetMarkerColor(ci[3]);
  fHistLambdaPhi[1]->SetLineColor(ci[3]);
  fHistAntiLambdaPhi[1]->SetMarkerColor(ci[2]);
  fHistAntiLambdaPhi[1]->SetLineColor(ci[2]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TLegend* legend = new TLegend(0.15,0.55,0.45,0.85);
  legend->AddEntry(fHistLambdaMass[0],"#Lambda(Before mass cut)","lp");
  legend->AddEntry(fHistLambdaMass[1],"#Lambda(After mass cut)","lp");
  legend->AddEntry(fHistAntiLambdaMass[0],"#bar{#Lambda}(Before mass cut)","lp");
  legend->AddEntry(fHistAntiLambdaMass[1],"#bar{#Lambda}(After mass cut)","lp");

  TCanvas* cLambdaQA = new TCanvas("LambdaQA","LambdaQA",1000,800);
  cLambdaQA->Divide(3,2);

  cLambdaQA->cd(1);
  gPad->SetLogy(1);
  TH2D* dummyInvMass = new TH2D("","",1,1.1,1.13,1,15.e5,15.e6);
  dummyInvMass -> GetXaxis() -> SetTitle("M_{inv}");
  dummyInvMass -> GetYaxis() -> SetTitle("Counts");
  dummyInvMass -> SetTitle("Inv. Mass distribution of #Lambda(#bar{#Lambda})");
  dummyInvMass           -> Draw("same");
  fHistLambdaMass[0]     -> Draw("same");
  fHistAntiLambdaMass[0] -> Draw("same");
  fHistLambdaMass[1]     -> Draw("same");
  fHistAntiLambdaMass[1] -> Draw("same");
  legend->Draw("same");

  cLambdaQA->cd(2);
  TH2D* dummyRawMassVsPt = new TH2D("","",1,0.,10.,1,1.,3.);
  dummyRawMassVsPt -> GetXaxis() -> SetTitle("p_{T}");
  dummyRawMassVsPt -> GetYaxis() -> SetTitle("M_{inv}");
  dummyRawMassVsPt -> SetTitle("Inv. Mass vs. p_{T} of #Lambda(#bar{#Lambda}) before Mass Cut");
  dummyRawMassVsPt -> Draw("same");
  fProfileLambdaMassVsPt[0]     -> Draw("same");
  fProfileAntiLambdaMassVsPt[0] -> Draw("same");

  cLambdaQA->cd(3);
  TH2D* dummyMassVsPt = new TH2D("","",1,0,10.,1,1.11,1.12);
  dummyMassVsPt ->GetXaxis() ->SetTitle("p_{T}");
  dummyMassVsPt ->GetYaxis() ->SetTitle("M_{inv}");
  dummyMassVsPt -> SetTitle("Inv. Mass vs. p_{T} of #Lambda(#bar{#Lambda}) after Mass Cut");
  dummyMassVsPt ->Draw();
  fProfileLambdaMassVsPt[1]     -> Draw("same");
  fProfileAntiLambdaMassVsPt[1] -> Draw("same");

  cLambdaQA->cd(4);
  gPad->SetLogy(1);
  fHistLambdaPt[0] -> SetTitle("p_{T} distribution of #Lambda(#bar{#Lambda})");
  fHistLambdaPt[0] -> GetXaxis()->SetTitle("p_{T}");
  fHistLambdaPt[0] -> GetXaxis()->SetRangeUser(0.,10.);
  fHistLambdaPt[0]     -> Draw("same");
  fHistAntiLambdaPt[0] -> Draw("same");
  fHistLambdaPt[1]     -> Draw("same");
  fHistAntiLambdaPt[1] -> Draw("same");

  cLambdaQA->cd(5);
  gPad->SetLogy(1);
  fHistLambdaEta[0] -> SetTitle("#eta distribution of #Lambda(#bar{#Lambda})");
  fHistLambdaEta[0] -> GetXaxis()->SetTitle("#eta");
  fHistLambdaEta[0] -> GetXaxis()->SetRangeUser(-2.,2.);
  fHistLambdaEta[0]     -> Draw("same");
  fHistAntiLambdaEta[0] -> Draw("same");
  fHistLambdaEta[1]     -> Draw("same");
  fHistAntiLambdaEta[1] -> Draw("same");

  cLambdaQA->cd(6);
  gPad->SetLogy(1);
  fHistLambdaPhi[0] -> SetTitle("#phi distribution of #Lambda(#bar{#Lambda})");
  fHistLambdaPhi[0]->GetXaxis()->SetTitle("#phi");
  fHistLambdaPhi[0]->GetYaxis()->SetRangeUser(1.e5,15.e6);
  fHistLambdaPhi[0]     -> Draw("same");
  fHistAntiLambdaPhi[0] -> Draw("same");
  fHistLambdaPhi[1]     -> Draw("same");
  //fHistAntiLambdaPhi[1] -> Draw("same");

  cLambdaQA->SaveAs("LambdaQA.pdf");  
}

