#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"


Double_t GetResolutionErr(Double_t A, Double_t AErr, Double_t B, Double_t BErr, Double_t C, Double_t CErr);
//For fit
Double_t dNdDeltaPhi(Double_t *x, Double_t *par) {
  return par[0] * (1.+2.*par[1]*TMath::Cos(2*x[0]));
}

Double_t GetFlowParameter(TH1D* hist, Double_t &v2Err) {
  v2Err = -999;
  TF1 *fitFcn = new TF1("fitFcn", dNdDeltaPhi, 0., TMath::Pi(), 2);
  fitFcn->SetParameters(100,1);
  hist->Fit(fitFcn,"QNER");
  Double_t v2 = fitFcn->GetParameter(1);
  v2Err = fitFcn->GetParError(1);
  delete fitFcn;
  return v2;
}


void DrawFlow() {
  Bool_t bDrawIntegral = kFALSE;
  Bool_t bDrawDiff = kTRUE;

  gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetOptStat(0);

  TFile* pubedFile = TFile::Open("HEPData-ins1672822-v1-root.root");

  TDirectory* pubedProton1020Dir = pubedFile->GetDirectory("Table 49");
  TDirectory* pubedProton2030Dir = pubedFile->GetDirectory("Table 50");
  TDirectory* pubedProton3040Dir = pubedFile->GetDirectory("Table 51");
  TDirectory* pubedProton4050Dir = pubedFile->GetDirectory("Table 52");
  TDirectory* pubedProton5060Dir = pubedFile->GetDirectory("Table 53");
  TDirectory* pubedProton6070Dir = pubedFile->GetDirectory("Table 53");
  TDirectory* pubedlambda1020Dir = pubedFile->GetDirectory("Table 85");
  TDirectory* pubedlambda2030Dir = pubedFile->GetDirectory("Table 86");
  TDirectory* pubedlambda3040Dir = pubedFile->GetDirectory("Table 87");
  TDirectory* pubedlambda4050Dir = pubedFile->GetDirectory("Table 88");  
  TDirectory* pubedlambda5060Dir = pubedFile->GetDirectory("Table 89");
  TDirectory* pubedlambda6070Dir = pubedFile->GetDirectory("Table 90");

  TGraphAsymmErrors* pubedProton1020 = nullptr;
  TGraphAsymmErrors* pubedProton2030 = nullptr;
  TGraphAsymmErrors* pubedProton3040 = nullptr;
  TGraphAsymmErrors* pubedProton4050 = nullptr;
  TGraphAsymmErrors* pubedProton5060 = nullptr;
  TGraphAsymmErrors* pubedProton6070 = nullptr;
  TGraphAsymmErrors* pubedLambda1020 = nullptr;
  TGraphAsymmErrors* pubedLambda2030 = nullptr;
  TGraphAsymmErrors* pubedLambda3040 = nullptr;
  TGraphAsymmErrors* pubedLambda4050 = nullptr;
  TGraphAsymmErrors* pubedLambda5060 = nullptr;
  TGraphAsymmErrors* pubedLambda6070 = nullptr;

  pubedProton1020Dir->GetObject("Graph1D_y1",pubedProton1020);
  pubedProton2030Dir->GetObject("Graph1D_y1",pubedProton2030);
  pubedProton3040Dir->GetObject("Graph1D_y1",pubedProton3040);
  pubedProton4050Dir->GetObject("Graph1D_y1",pubedProton4050);
  pubedProton5060Dir->GetObject("Graph1D_y1",pubedProton5060);
  pubedProton6070Dir->GetObject("Graph1D_y1",pubedProton6070);
  pubedlambda1020Dir->GetObject("Graph1D_y1",pubedLambda1020);
  pubedlambda2030Dir->GetObject("Graph1D_y1",pubedLambda2030);
  pubedlambda3040Dir->GetObject("Graph1D_y1",pubedLambda3040);
  pubedlambda4050Dir->GetObject("Graph1D_y1",pubedLambda4050);
  pubedlambda5060Dir->GetObject("Graph1D_y1",pubedLambda5060);
  pubedlambda6070Dir->GetObject("Graph1D_y1",pubedLambda6070);

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






  //////////////////////////////
  ///////Plane Resolution///////
  //////////////////////////////

  ///Resolution
  TProfile* pV0CV0APsiNCorrelation = (TProfile*)inputList->FindObject("hV0CV0APsiNCorrelation");
  TProfile* pV0CTPCPsiNCorrelation = (TProfile*)inputList->FindObject("hV0CTPCPsiNCorrelation");
  TProfile* pV0ATPCPsiNCorrelation = (TProfile*)inputList->FindObject("hV0ATPCPsiNCorrelation");
  TProfile* pTPCPsiNCorrelation    = (TProfile*)inputList->FindObject("hTPCPsiNCorrelation");
  pV0CV0APsiNCorrelation -> Rebin(10);
  pV0CTPCPsiNCorrelation -> Rebin(10);
  pV0ATPCPsiNCorrelation -> Rebin(10);
  pTPCPsiNCorrelation    -> Rebin(10);
  TH1D* hV0CV0APsiNCorrelation = pV0CV0APsiNCorrelation->ProjectionX();
  TH1D* hV0CTPCPsiNCorrelation = pV0CTPCPsiNCorrelation->ProjectionX();
  TH1D* hV0ATPCPsiNCorrelation = pV0ATPCPsiNCorrelation->ProjectionX();
  TH1D* hTPCPsiNCorrelation    = pTPCPsiNCorrelation   ->ProjectionX();
  TH1D* hV0CRes_TPC_V0C_V0A = new TH1D("hV0CRes_TPC_V0C_V0A", "Res", 9, 0., 90.);
  TH1D* hV0ARes_TPC_V0A_V0C = new TH1D("hV0ARes_TPC_V0A_V0C", "Res", 9, 0., 90.);
  TH1D* hTPCRes_V0C_TPC_V0A = new TH1D("hTPCRes_V0C_TPC_V0A", "Res", 9, 0., 90.);

  for (int iCent = 1; iCent <= 9; iCent++) {
    Double_t A    = hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B    = hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t C    = hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);

    Double_t resV0C    = TMath::Sqrt(A*B/C);
    Double_t resV0CErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hV0CRes_TPC_V0C_V0A -> SetBinContent(iCent,resV0C);
    hV0CRes_TPC_V0C_V0A -> SetBinError(iCent,resV0CErr);
  }
  for (int iCent = 1; iCent <= 9; iCent++) {
    Double_t A =    hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B =    hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t C =    hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);

    Double_t resV0A    = TMath::Sqrt(A*B/C);
    Double_t resV0AErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hV0ARes_TPC_V0A_V0C -> SetBinContent(iCent,resV0A);
    hV0ARes_TPC_V0A_V0C -> SetBinError(iCent,resV0AErr);
  }
  for (int iCent = 1; iCent <= 9; iCent++) {
    Double_t A    = hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B    = hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t C    = hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);

    Double_t resTPC    = TMath::Sqrt(A*B/C);
    Double_t resTPCErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hTPCRes_V0C_TPC_V0A -> SetBinContent(iCent,resTPC);
    hTPCRes_V0C_TPC_V0A -> SetBinError(iCent,resTPCErr);
  }

  TH1D* hRes[3];
  hRes[0] = (TH1D*)hTPCRes_V0C_TPC_V0A->Clone();
  hRes[1] = (TH1D*)hV0CRes_TPC_V0C_V0A->Clone();
  hRes[2] = (TH1D*)hV0ARes_TPC_V0A_V0C->Clone();
  TH1D* hResLambda[4];
  hResLambda[0] = (TH1D*)hTPCRes_V0C_TPC_V0A->Clone();
  hResLambda[1] = (TH1D*)hTPCRes_V0C_TPC_V0A->Clone();
  hResLambda[2] = (TH1D*)hV0CRes_TPC_V0C_V0A->Clone();
  hResLambda[3] = (TH1D*)hV0ARes_TPC_V0A_V0C->Clone();

  TLegend* legendRes = new TLegend(0.7,0.7,0.88,0.85);
  legendRes->AddEntry(hTPCRes_V0C_TPC_V0A,"TPC","pl");
  legendRes->AddEntry(hV0CRes_TPC_V0C_V0A,"V0C","pl");
  legendRes->AddEntry(hV0ARes_TPC_V0A_V0C,"V0A","pl");

  TCanvas* cRes = new TCanvas();
  cRes->cd();
  hTPCRes_V0C_TPC_V0A->SetLineColor(ci[0]);
  hTPCRes_V0C_TPC_V0A->SetMarkerStyle(kFullCircle);
  hTPCRes_V0C_TPC_V0A->SetMarkerColor(ci[0]);
  hTPCRes_V0C_TPC_V0A->SetMarkerSize(1);
  hTPCRes_V0C_TPC_V0A->Draw("same");

  hV0CRes_TPC_V0C_V0A->SetLineColor(ci[1]);
  hV0CRes_TPC_V0C_V0A->SetMarkerStyle(kFullCircle);
  hV0CRes_TPC_V0C_V0A->SetMarkerColor(ci[1]);
  hV0CRes_TPC_V0C_V0A->SetMarkerSize(1);
  hV0CRes_TPC_V0C_V0A->Draw("same");

  hV0ARes_TPC_V0A_V0C->SetLineColor(ci[2]);
  hV0ARes_TPC_V0A_V0C->SetMarkerStyle(kFullCircle);
  hV0ARes_TPC_V0A_V0C->SetMarkerColor(ci[2]);
  hV0ARes_TPC_V0A_V0C->SetMarkerSize(1);
  hV0ARes_TPC_V0A_V0C->Draw("same");

  legendRes->Draw("same");
  //cRes->SaveAs("Res.png");

  ///////////////////////
  ///////PID Flow////////
  ///////////////////////

  // Get hists from file
  //[plane]
  TH3D* fHist3DdNdPhiCentPthPos[3];
  TH3D* fHist3DdNdPhiCentPthNeg[3];  
  TH3D* fHist3DdNdPhiCentPtProton[3];
  TH3D* fHist3DdNdPhiCentPtAntiProton[3];
  TH3D* fHist3DdNdPhiCentPtLambda[4];
  TH3D* fHist3DdNdPhiCentPtAntiLambda[4];
  Char_t name1[20];
  for (Int_t i = 0; i < 3; i++) {
    if(i==0) sprintf(name1,"TPC");
    if(i==1) sprintf(name1,"V0C");
    if(i==2) sprintf(name1,"V0A");
    fHist3DdNdPhiCentPthPos[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPthPos_%s",name1));
    fHist3DdNdPhiCentPthNeg[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPthNeg_%s",name1));
    fHist3DdNdPhiCentPtProton[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPtProton_%s",name1));
    fHist3DdNdPhiCentPtAntiProton[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPtAntiProton_%s",name1));
  }
  Char_t name2[20];
  for (Int_t i = 0; i < 4; i++) {
    if(i==0) sprintf(name2,"TPCPos");
    if(i==1) sprintf(name2,"TPCNeg");
    if(i==2) sprintf(name2,"V0C");
    if(i==3) sprintf(name2,"V0A");
    fHist3DdNdPhiCentPtLambda[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPtLambda_%s",name2));
    fHist3DdNdPhiCentPtAntiLambda[i] = (TH3D*)inputList->FindObject(Form("fHist3DdNdPhiCentPtLambda_%s",name2));
  }

// if(bDrawIntegral)  
// {
//   //////////////////////////
//   ////PID Integral Flow/////
//   //////////////////////////

//   //Integral Flow (v2 vs. cent)
//   //[plane]
//   TH2D* fHist2DdNdPhiCenthPos[3];
//   TH2D* fHist2DdNdPhiCenthNeg[3];  
//   TH2D* fHist2DdNdPhiCentProton[3];
//   TH2D* fHist2DdNdPhiCentAntiProton[3];
//   TH2D* fHist2DdNdPhiCentLambda[4];
//   TH2D* fHist2DdNdPhiCentAntiLambda[4];
//   for (Int_t i = 0; i < 3; i++) {
//     fHist2DdNdPhiCenthPos[i] = (TH2D*)fHist3DdNdPhiCentPthPos[i] -> Project3D("xz");
//     fHist2DdNdPhiCenthNeg[i] = (TH2D*)fHist3DdNdPhiCentPthNeg[i] -> Project3D("xz");
//     fHist2DdNdPhiCentProton[i] = (TH2D*)fHist3DdNdPhiCentPtProton[i] -> Project3D("xz");
//     fHist2DdNdPhiCentAntiProton[i] = (TH2D*)fHist3DdNdPhiCentPtAntiProton[i] -> Project3D("xz");
//   }
//   for (Int_t i = 0; i < 4; i++) {
//     fHist2DdNdPhiCentLambda[i] = (TH2D*)fHist3DdNdPhiCentPtLambda[i] -> Project3D("xz");
//     fHist2DdNdPhiCentAntiLambda[i] = (TH2D*)fHist3DdNdPhiCentPtLambda[i] -> Project3D("xz");
//   }

//   //[cent][plane]
//   TH1D* hdNdPhiCenthPos[9][3];
//   TH1D* hdNdPhiCenthNeg[9][3];
//   TH1D* hdNdPhiCentProton[9][3];
//   TH1D* hdNdPhiCentAntiProton[9][3];
//   TH1D* hdNdPhiCentLambda[9][4];
//   TH1D* hdNdPhiCentAntiLambda[9][4];
//   for (int i = 0; i < 3; i++) {
//     for (int iCent = 0; iCent < 9; iCent++) {
//       hdNdPhiCenthPos[iCent][i]        = fHist2DdNdPhiCenthPos[i]       -> ProjectionX(Form("fHist2DdNdPhiCent%dhPos_%d",iCent,i),iCent + 1, iCent + 1);
//       hdNdPhiCenthNeg[iCent][i]        = fHist2DdNdPhiCenthNeg[i]       -> ProjectionX(Form("fHist2DdNdPhiCent%dhNeg_%d",iCent,i),iCent + 1, iCent + 1);
//       hdNdPhiCentProton[iCent][i]      = fHist2DdNdPhiCentProton[i]     -> ProjectionX(Form("fHist2DdNdPhiCent%dProton_%d",iCent,i),iCent + 1, iCent + 1);
//       hdNdPhiCentAntiProton[iCent][i]  = fHist2DdNdPhiCentAntiProton[i] -> ProjectionX(Form("fHist2DdNdPhiCent%dAntiProton_%d",iCent,i),iCent + 1, iCent + 1);
//     }
//   }
//   for (int i = 0; i < 4; i++) {
//     for (int iCent = 0; iCent < 9; iCent++) {
//       hdNdPhiCentLambda[iCent][i]     = fHist2DdNdPhiCentLambda[i]     -> ProjectionX(Form("fHist2DdNdPhiCent%dLambda_%d",iCent,i),iCent + 1, iCent + 1);
//       hdNdPhiCentAntiLambda[iCent][i] = fHist2DdNdPhiCentAntiLambda[i] -> ProjectionX(Form("fHist2DdNdPhiCent%dAntiLambda_%d",iCent,i),iCent + 1, iCent + 1);
//     }
//   }

//   //// TODO
//   //[plane]
//   TH1D* hRawFlowVsCenthPos[3];
//   TH1D* hRawFlowVsCenthNeg[3];
//   TH1D* hRawFlowVsCentProton[3];
//   TH1D* hRawFlowVsCentAntiProton[3];
//   TH1D* hRawFlowVsCentLambda[4];
//   TH1D* hRawFlowVsCentAntiLambda[4];

//   for (int i = 0; i < 3; i++) {
//       hRawFlowVsCenthPos[i]       = new TH1D(Form("hRawFlowVsCenthPos_%d",i), Form("hPos Raw Flow Vs Cent %d",i), 9, 0., 90.);
//       hRawFlowVsCenthNeg[i]       = new TH1D(Form("hRawFlowVsCenthNeg_%d",i), Form("hNeg Raw Flow Vs Cent %d",i), 9, 0., 90.);
//       hRawFlowVsCentProton[i]     = new TH1D(Form("hRawFlowVsCentProton_%d",i), Form("Proton Raw Flow Vs Cent %d",i), 9, 0., 90.);
//       hRawFlowVsCentAntiProton[i] = new TH1D(Form("hRawFlowVsCentAntiProton_%d",i), Form("AntiProton Raw Flow Vs Cent %d",i), 9, 0., 90.);
//   }
//   for (int i = 0; i < 4; i++) {
//       hRawFlowVsCentLambda[i]     = new TH1D(Form("hRawFlowVsCentLambda_%d",i), Form("Lambda Raw Flow Vs Cent %d",i), 9, 0., 90.);
//       hRawFlowVsCentAntiLambda[i] = new TH1D(Form("hRawFlowVsCentAntiLambda_%d",i), Form("AntiLambda Raw Flow Vs Cent %d",i), 9, 0., 90.);
//   }
//   //Draw dNdPhi
//   TCanvas* cInclusiveProtonVsCent = new TCanvas();
//   cInclusiveProtonVsCent->cd();
//   cInclusiveProtonVsCent->Divide(3,3);
//   for (int iCent = 0; iCent < 9; iCent++) {
//     cInclusiveProtonVsCent->cd(iCent+1);
//     for (int i = 0; i < 3; i++) {
//       hdNdPhiCenthPos[iCent][i]       -> Draw("same");
//       hdNdPhiCenthNeg[iCent][i]       -> Draw("same");
//       hdNdPhiCentProton[iCent][i]     -> Draw("same");
//       hdNdPhiCentAntiProton[iCent][i] -> Draw("same");
//     }
//   }
//   TCanvas* cLambdaVsCent = new TCanvas();
//   cLambdaVsCent->cd();
//   cLambdaVsCent->Divide(3,3);
//   for (int iCent = 0; iCent < 9; iCent++) {
//     cLambdaVsCent->cd(iCent+1);
//     for (int i = 0; i < 4; i++) {
//       hdNdPhiCentLambda[iCent][i] -> Draw("same");
//       hdNdPhiCentLambda[iCent][i] -> Draw("same");
//     }
//   }

//   for (int i = 0; i < 3; i++) {
//     for (int iCent = 0; iCent < 9; iCent++) {
//       Double_t v2Err = -999;
//       hRawFlowVsCenthPos[i]       -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCenthPos[iCent][i],v2Err));
//       hRawFlowVsCenthPos[i]       -> SetBinError(iCent+1, v2Err);
//       hRawFlowVsCenthNeg[i]       -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCenthNeg[iCent][i],v2Err)); 
//       hRawFlowVsCenthNeg[i]       -> SetBinError(iCent+1, v2Err);
//       hRawFlowVsCentProton[i]     -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCentProton[iCent][i],v2Err)); 
//       hRawFlowVsCentProton[i]     -> SetBinError(iCent+1, v2Err);
//       hRawFlowVsCentAntiProton[i] -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCentAntiProton[iCent][i],v2Err)); 
//       hRawFlowVsCentAntiProton[i] -> SetBinError(iCent+1, v2Err);
//     }
//   }
//   for (int i = 0; i < 4; i++) {
//     for (int iCent = 0; iCent < 9; iCent++) {
//       Double_t v2Err = -999;
//       hRawFlowVsCentLambda[i]     -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCentLambda[iCent][i],v2Err));
//       hRawFlowVsCentLambda[i]     -> SetBinError(iCent+1, v2Err);
//       hRawFlowVsCentAntiLambda[i] -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCentAntiLambda[iCent][i],v2Err));
//       hRawFlowVsCentAntiLambda[i] -> SetBinError(iCent+1, v2Err);
//     }
//   }

//   TH1D* hFlowVsCenthPos[3];
//   TH1D* hFlowVsCenthNeg[3]; 
//   TH1D* hFlowVsCentProton[3];
//   TH1D* hFlowVsCentAntiProton[3];
//   TH1D* hFlowVsCentLambda[4];
//   TH1D* hFlowVsCentAntiLambda[4];
//   for (int i = 0; i < 3; i++) {
//     hFlowVsCenthPos[i]       = new TH1D(Form("hFlowVsCenthPos_%d",i), Form("hPos Raw Flow Vs Cent %d",i), 9, 0., 90.);
//     hFlowVsCenthNeg[i]       = new TH1D(Form("hFlowVsCenthNeg_%d",i), Form("hNeg Raw Flow Vs Cent %d",i), 9, 0., 90.);
//     hFlowVsCentProton[i]     = new TH1D(Form("hFlowVsCentProton_%d",i), Form("Proton Raw Flow Vs Cent %d",i), 9, 0., 90.);
//     hFlowVsCentAntiProton[i] = new TH1D(Form("hFlowVsCentAntiProton_%d",i), Form("AntiProton Raw Flow Vs Cent %d",i), 9, 0., 90.);
//   }
//   for (int i = 0; i < 4; i++) {
//     hFlowVsCentLambda[i]     = new TH1D(Form("hFlowVsCentLambda_%d",i), Form("Lambda Raw Flow Vs Cent %d",i), 9, 0., 90.);
//     hFlowVsCentAntiLambda[i] = new TH1D(Form("hFlowVsCentAntiLambda_%d",i), Form("AntiLambda Raw Flow Vs Cent %d",i), 9, 0., 90.);
//   }  
//   for (int i = 0; i < 3; i++) {
//     hFlowVsCenthPos[i]       -> Divide(hRawFlowVsCenthPos[i], hRes[i]);
//     hFlowVsCenthNeg[i]       -> Divide(hRawFlowVsCenthNeg[i], hRes[i]);
//     hFlowVsCentProton[i]     -> Divide(hRawFlowVsCentProton[i], hRes[i]);
//     hFlowVsCentAntiProton[i] -> Divide(hRawFlowVsCentAntiProton[i], hRes[i]);
//   }
//   for (int i = 0; i < 4; i++) {
//     hFlowVsCentLambda[i]     -> Divide(hRawFlowVsCentLambda[i], hResLambda[i]);
//     hFlowVsCentAntiLambda[i] -> Divide(hRawFlowVsCentAntiLambda[i], hResLambda[i]);
//   }

//   TLegend* legend = new TLegend(0.2,0.7,0.48,0.85);
//   legend->AddEntry(hFlowVsCenthPos[0],"TPC","pl");
//   legend->AddEntry(hFlowVsCenthPos[1],"V0C","pl");
//   legend->AddEntry(hFlowVsCenthPos[2],"V0A","pl");

//   TLegend* legendLambda = new TLegend(0.2,0.7,0.48,0.85);
//   legendLambda->AddEntry(hFlowVsCentLambda[0],"TPCPos","pl");
//   legendLambda->AddEntry(hFlowVsCentLambda[1],"TPCNeg","pl");
//   legendLambda->AddEntry(hFlowVsCentLambda[2],"V0C","pl");
//   legendLambda->AddEntry(hFlowVsCentLambda[3],"V0A","pl");

//   for (int i = 0; i < 3; i++) {
//     hFlowVsCenthPos[i]       -> SetMarkerColor(ci[i]);
//     hFlowVsCenthPos[i]       -> SetMarkerStyle(kFullCircle);
//     hFlowVsCenthPos[i]       -> SetLineColor(ci[i]);
//     hFlowVsCenthNeg[i]       -> SetMarkerColor(ci[i]);
//     hFlowVsCenthNeg[i]       -> SetMarkerStyle(kFullCircle);
//     hFlowVsCenthNeg[i]       -> SetLineColor(ci[i]);
//     hFlowVsCentProton[i]     -> SetMarkerColor(ci[i]);
//     hFlowVsCentProton[i]     -> SetMarkerStyle(kFullCircle);
//     hFlowVsCentProton[i]     -> SetLineColor(ci[i]);
//     hFlowVsCentAntiProton[i] -> SetMarkerColor(ci[i]);
//     hFlowVsCentAntiProton[i] -> SetMarkerStyle(kFullCircle);
//     hFlowVsCentAntiProton[i] -> SetLineColor(ci[i]);

//     hRawFlowVsCenthPos[i]       -> SetMarkerColor(ci[i]);
//     hRawFlowVsCenthPos[i]       -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCenthPos[i]       -> SetLineColor(ci[i]);
//     hRawFlowVsCenthNeg[i]       -> SetMarkerColor(ci[i]);
//     hRawFlowVsCenthNeg[i]       -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCenthNeg[i]       -> SetLineColor(ci[i]);
//     hRawFlowVsCentProton[i]     -> SetMarkerColor(ci[i]);
//     hRawFlowVsCentProton[i]     -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCentProton[i]     -> SetLineColor(ci[i]);
//     hRawFlowVsCentAntiProton[i] -> SetMarkerColor(ci[i]);
//     hRawFlowVsCentAntiProton[i] -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCentAntiProton[i] -> SetLineColor(ci[i]);
//   }
//   for (int i = 0; i < 4; i++) {
//     hFlowVsCentLambda[i] -> SetMarkerColor(ci[i]);
//     hFlowVsCentLambda[i] -> SetMarkerStyle(kFullCircle);
//     hFlowVsCentLambda[i] -> SetLineColor(ci[i]);
//     hFlowVsCentAntiLambda[i] -> SetMarkerColor(ci[i]);
//     hFlowVsCentAntiLambda[i] -> SetMarkerStyle(kFullCircle);
//     hFlowVsCentAntiLambda[i] -> SetLineColor(ci[i]);

//     hRawFlowVsCentLambda[i] -> SetMarkerColor(ci[i]);
//     hRawFlowVsCentLambda[i] -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCentLambda[i] -> SetLineColor(ci[i]);
//     hRawFlowVsCentAntiLambda[i] -> SetMarkerColor(ci[i]);
//     hRawFlowVsCentAntiLambda[i] -> SetMarkerStyle(kFullCircle);
//     hRawFlowVsCentAntiLambda[i] -> SetLineColor(ci[i]);
//   }


//   //Draw Flow
//   TCanvas* cV2VsCent = new TCanvas("v2 vs. centrality","v2 vs. centrality",600,800);
//   TH2D* dummyV2VsCent = new TH2D("","",1,0,90,1,0.,0.2);
//   cV2VsCent->Divide(2,3);
//   cV2VsCent->cd(1);
//   dummyV2VsCent->Draw("same");
//   legend->Draw("same");
//   for (int i = 0; i < 3; i++) hFlowVsCenthPos[i]->Draw("same");
//   cV2VsCent->cd(2);
//   dummyV2VsCent->Draw("same");
//   legend->Draw("same");
//   for (int i = 0; i < 3; i++) hFlowVsCenthNeg[i]->Draw("same");
//   cV2VsCent->cd(3);
//   dummyV2VsCent->Draw("same");
//   legend->Draw("same");
//   for (int i = 0; i < 3; i++) hFlowVsCentProton[i]->Draw("same");
//   cV2VsCent->cd(4);
//   dummyV2VsCent->Draw("same");
//   legend->Draw("same");
//   for (int i = 0; i < 3; i++) hFlowVsCentAntiProton[i]->Draw("same");
//   cV2VsCent->cd(5);
//   dummyV2VsCent->Draw("same");
//   legendLambda->Draw("same");
//   for (int i = 0; i < 4; i++) hFlowVsCentLambda[i]->Draw("same");
//   cV2VsCent->cd(6);
//   dummyV2VsCent->Draw("same");
//   legendLambda->Draw("same");
//   for (int i = 0; i < 4; i++) hFlowVsCentAntiLambda[i]->Draw("same");

//   //cV2VsCent->SaveAs("V2VsCent.png");
// }


if(bDrawDiff)
{
  /////////////////////////////
  ////PID Differential Flow////
  /////////////////////////////


  //[cent][pT][plane]
  TH1D* hdNdPhiCentPthPos[9][12][3];
  TH1D* hdNdPhiCentPthNeg[9][12][3];
  TH1D* hdNdPhiCentPtProton[9][12][3];
  TH1D* hdNdPhiCentPtAntiProton[9][12][3];
  TH1D* hdNdPhiCentPtLambda[9][12][4];
  TH1D* hdNdPhiCentPtAntiLambda[9][12][4];

  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 1; iCent <= 9; iCent++) {
      for (int iPt = 1; iPt <= 12 ; iPt++) {
        hdNdPhiCentPthPos[iCent-1][iPt-1][iPlane]       = fHist3DdNdPhiCentPthPos[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt);
        hdNdPhiCentPthPos[iCent-1][iPt-1][iPlane]       ->SetName(Form("hdNdPhiCentPthPos_%d_%d_%d",iCent,iPt,iPlane));
        hdNdPhiCentPthNeg[iCent-1][iPt-1][iPlane]       = fHist3DdNdPhiCentPthNeg[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt);
        hdNdPhiCentPthNeg[iCent-1][iPt-1][iPlane]       ->SetName(Form("hdNdPhiCentPthNeg_%d_%d_%d",iCent,iPt,iPlane));
        hdNdPhiCentPtProton[iCent-1][iPt-1][iPlane]     = fHist3DdNdPhiCentPtProton[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt); 
        hdNdPhiCentPtProton[iCent-1][iPt-1][iPlane]     ->SetName(Form("hdNdPhiCentPtProton_%d_%d_%d",iCent,iPt,iPlane));
        hdNdPhiCentPtAntiProton[iCent-1][iPt-1][iPlane] = fHist3DdNdPhiCentPtAntiProton[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt);
        hdNdPhiCentPtAntiProton[iCent-1][iPt-1][iPlane] ->SetName(Form("hdNdPhiCentPtAntiProton_%d_%d_%d",iCent,iPt,iPlane));
      }
    }
  }

  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 1; iCent <= 9; iCent++) {
      for (int iPt = 1; iPt <= 12 ; iPt++) {
        hdNdPhiCentPtLambda[iCent-1][iPt-1][iPlane]     = fHist3DdNdPhiCentPtLambda[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt);
        hdNdPhiCentPtLambda[iCent-1][iPt-1][iPlane]     ->SetName(Form("hdNdPhiCentPtLambda_%d_%d_%d",iCent,iPt,iPlane));
        hdNdPhiCentPtAntiLambda[iCent-1][iPt-1][iPlane] = fHist3DdNdPhiCentPtAntiLambda[iPlane]->ProjectionZ("",iCent,iCent,iPt,iPt);
        hdNdPhiCentPtAntiLambda[iCent-1][iPt-1][iPlane] ->SetName(Form("hdNdPhiCentPtAntiLambda_%d_%d_%d",iCent,iPt,iPlane));
      }
    }
  }
  
  //// TODO
  Double_t pTbins[13]   = {0.0, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.4, 3.8, 4.2, 5.0};
  TH1D* hRawFlowVsPtCenthPos[9][3];
  TH1D* hRawFlowVsPtCenthNeg[9][3];
  TH1D* hRawFlowVsPtCentProton[9][3];
  TH1D* hRawFlowVsPtCentAntiProton[9][3];
  TH1D* hRawFlowVsPtCentLambda[9][4];
  TH1D* hRawFlowVsPtCentAntiLambda[9][4];
  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hRawFlowVsPtCenthPos[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCenthPos_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hRawFlowVsPtCenthNeg[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCenthNeg_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hRawFlowVsPtCentProton[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCentProton_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hRawFlowVsPtCentAntiProton[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCentAntiProton_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
    }
  }
  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hRawFlowVsPtCentLambda[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCentLambda_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hRawFlowVsPtCentAntiLambda[iCent][iPlane] = new TH1D(Form("hRawFlowVsPtCentAntiLambda_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
    }
  }
  TH1D* hFlowVsPtCenthPos[9][3];
  TH1D* hFlowVsPtCenthNeg[9][3];
  TH1D* hFlowVsPtCentProton[9][3];
  TH1D* hFlowVsPtCentAntiProton[9][3];
  TH1D* hFlowVsPtCentLambda[9][4];
  TH1D* hFlowVsPtCentAntiLambda[9][4];
  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCenthPos[iCent][iPlane] = new TH1D(Form("hFlowVsPtCenthPos_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hFlowVsPtCenthNeg[iCent][iPlane] = new TH1D(Form("hFlowVsPtCenthNeg_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hFlowVsPtCentProton[iCent][iPlane] = new TH1D(Form("hFlowVsPtCentProton_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hFlowVsPtCentAntiProton[iCent][iPlane] = new TH1D(Form("hFlowVsPtCentAntiProton_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
    }
  }
  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCentLambda[iCent][iPlane] = new TH1D(Form("hFlowVsPtCentLambda_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
      hFlowVsPtCentAntiLambda[iCent][iPlane] = new TH1D(Form("hFlowVsPtCentAntiLambda_cent%d_plane%d",iCent,iPlane), "", 12, pTbins);
    }
  }

  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      for (int iPt = 1; iPt < 12 ; iPt++) {
        Double_t v2Err = -999;
        hRawFlowVsPtCenthPos[iCent][iPlane]       -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPthPos[iCent][iPt][iPlane], v2Err));
        hRawFlowVsPtCenthPos[iCent][iPlane]       -> SetBinError(iPt+1, v2Err);
        hRawFlowVsPtCenthNeg[iCent][iPlane]       -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPthNeg[iCent][iPt][iPlane], v2Err)); 
        hRawFlowVsPtCenthNeg[iCent][iPlane]       -> SetBinError(iPt+1, v2Err);
        hRawFlowVsPtCentProton[iCent][iPlane]     -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPtProton[iCent][iPt][iPlane], v2Err)); 
        hRawFlowVsPtCentProton[iCent][iPlane]     -> SetBinError(iPt+1, v2Err);
        hRawFlowVsPtCentAntiProton[iCent][iPlane] -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPtAntiProton[iCent][iPt][iPlane], v2Err)); 
        hRawFlowVsPtCentAntiProton[iCent][iPlane] -> SetBinError(iPt+1, v2Err);
      }
    }
  }

  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      for (int iPt = 1; iPt < 12 ; iPt++) {
        Double_t v2Err = -999;
        hRawFlowVsPtCentLambda[iCent][iPlane]     -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPtLambda[iCent][iPt][iPlane], v2Err)); 
        hRawFlowVsPtCentLambda[iCent][iPlane]     -> SetBinError(iPt+1, v2Err);
        hRawFlowVsPtCentAntiLambda[iCent][iPlane] -> SetBinContent(iPt+1, GetFlowParameter(hdNdPhiCentPtAntiLambda[iCent][iPt][iPlane], v2Err)); 
        hRawFlowVsPtCentAntiLambda[iCent][iPlane] -> SetBinError(iPt+1, v2Err);
      }
    }
  }

  // TODO
  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      for (int iPt = 0; iPt < 12; iPt++) {
        hFlowVsPtCenthPos[iCent][iPlane]       ->SetBinContent(iPt+1, hRawFlowVsPtCenthPos[iCent][iPlane]       ->GetBinContent(iPt+1)/hRes[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCenthPos[iCent][iPlane]       ->SetBinError(iPt+1,   hRawFlowVsPtCenthPos[iCent][iPlane]       ->GetBinError(iPt+1)  /sqrt(hRes[iPlane]->GetBinContent(iCent+1)));
        hFlowVsPtCenthNeg[iCent][iPlane]       ->SetBinContent(iPt+1, hRawFlowVsPtCenthNeg[iCent][iPlane]       ->GetBinContent(iPt+1)/hRes[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCenthNeg[iCent][iPlane]       ->SetBinError(iPt+1,   hRawFlowVsPtCenthNeg[iCent][iPlane]       ->GetBinError(iPt+1)  /sqrt(hRes[iPlane]->GetBinContent(iCent+1)));
        hFlowVsPtCentProton[iCent][iPlane]     ->SetBinContent(iPt+1, hRawFlowVsPtCentProton[iCent][iPlane]     ->GetBinContent(iPt+1)/hRes[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCentProton[iCent][iPlane]     ->SetBinError(iPt+1,   hRawFlowVsPtCentProton[iCent][iPlane]     ->GetBinError(iPt+1)  /sqrt(hRes[iPlane]->GetBinContent(iCent+1)));
        hFlowVsPtCentAntiProton[iCent][iPlane] ->SetBinContent(iPt+1, hRawFlowVsPtCentAntiProton[iCent][iPlane] ->GetBinContent(iPt+1)/hRes[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCentAntiProton[iCent][iPlane] ->SetBinError(iPt+1,   hRawFlowVsPtCentAntiProton[iCent][iPlane] ->GetBinError(iPt+1)  /sqrt(hRes[iPlane]->GetBinContent(iCent+1)));
      }
    }
  }
  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      for (int iPt = 1; iPt < 12; iPt++) {
        hFlowVsPtCentLambda[iCent][iPlane]     ->SetBinContent(iPt+1, hRawFlowVsPtCentLambda[iCent][iPlane]     ->GetBinContent(iPt+1)/hResLambda[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCentLambda[iCent][iPlane]     ->SetBinError(iPt+1,   hRawFlowVsPtCentLambda[iCent][iPlane]     ->GetBinError(iPt+1)  /sqrt(hResLambda[iPlane]->GetBinContent(iCent+1)));
        hFlowVsPtCentAntiLambda[iCent][iPlane] ->SetBinContent(iPt+1, hRawFlowVsPtCentAntiLambda[iCent][iPlane] ->GetBinContent(iPt+1)/hResLambda[iPlane]->GetBinContent(iCent+1));
        hFlowVsPtCentAntiLambda[iCent][iPlane] ->SetBinError(iPt+1,   hRawFlowVsPtCentAntiLambda[iCent][iPlane] ->GetBinError(iPt+1)  /sqrt(hResLambda[iPlane]->GetBinContent(iCent+1)));
      }
    }
  }


  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerStyle(kFullCircle);
      hFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerSize(1);
      hFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerStyle(kFullCircle);
      hFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerSize(1);

      hRawFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerStyle(kFullCircle);
      hRawFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerSize(1);
      hRawFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerStyle(kFullCircle);
      hRawFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerSize(1);
    }
  }
  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerStyle(kOpenCircle);
      hFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerSize(1.2);
      hFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerStyle(kOpenCircle);
      hFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerSize(1.2);

      hRawFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerStyle(kOpenCircle);
      hRawFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerSize(1.2);
      hRawFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerStyle(kOpenCircle);
      hRawFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerSize(1.2);
    }
  }
  for (int iPlane = 0; iPlane < 3; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerColor(ci[iPlane]);
      hFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerColor(ci[iPlane]);
      hFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerColor(ci[iPlane]);
      hFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerColor(ci[iPlane]);

      hRawFlowVsPtCenthPos[iCent][iPlane]      ->SetMarkerColor(ci[iPlane]);
      hRawFlowVsPtCenthNeg[iCent][iPlane]      ->SetMarkerColor(ci[iPlane]);
      hRawFlowVsPtCentProton[iCent][iPlane]    ->SetMarkerColor(ci[iPlane]);
      hRawFlowVsPtCentAntiProton[iCent][iPlane]->SetMarkerColor(ci[iPlane]);
    }
  }


  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerStyle(kFullCircle);
      hFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerSize(1);

      hRawFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerStyle(kFullCircle);
      hRawFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerSize(1);
    }
  }
  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerStyle(kOpenCircle);
      hFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerSize(1.2);

      hRawFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerStyle(kOpenCircle);
      hRawFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerSize(1.2);
    }
  }
  for (int iPlane = 0; iPlane < 4; iPlane++) {
    for (int iCent = 0; iCent < 9; iCent++) {
      hFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerColor(ci[iPlane]);
      hFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerColor(ci[iPlane]);

      hRawFlowVsPtCentLambda[iCent][iPlane]    ->SetMarkerColor(ci[iPlane]);
      hRawFlowVsPtCentAntiLambda[iCent][iPlane]->SetMarkerColor(ci[iPlane]);
    }
  }
  
  TH2D* dummyV2VsPt = new TH2D("","",1,0.,5.,1,0,0.35);
  dummyV2VsPt->SetXTitle("p_{T}");
  dummyV2VsPt->GetXaxis()->SetTitleSize(0.05);
  dummyV2VsPt->SetYTitle("v_{2EP}");
  dummyV2VsPt->GetYaxis()->SetTitleSize(0.05);

  TCanvas* cV2VsPtCenth = new TCanvas("hPos & hNeg v2 vs pT","hPos & hNeg v2 vs pT",900,600);
  cV2VsPtCenth->Divide(3,3);
  for (int iCent = 0; iCent < 9; iCent++) {
    cV2VsPtCenth->cd(iCent+1);
    dummyV2VsPt->Draw("same");
    for (size_t iPlane = 0; iPlane < 3; iPlane++) {
      hFlowVsPtCenthPos[iCent][iPlane]->Draw("same");
      hFlowVsPtCenthNeg[iCent][iPlane]->Draw("same");
    }
  }
  cV2VsPtCenth->SaveAs("V2VsPtInclucive.png");


  TCanvas* cV2VsPtCentProton = new TCanvas("Proton & AntiProton v2 vs pT","Proton & AntiProton v2 vs pT",900,600);
  cV2VsPtCentProton->Divide(3,3);
  for (int iCent = 0; iCent < 9; iCent++) {
    cV2VsPtCentProton->cd(iCent+1);
    dummyV2VsPt->Draw("same");
    for (size_t iPlane = 0; iPlane < 3; iPlane++) {
      hFlowVsPtCentProton[iCent][iPlane]->Draw("same");
      hFlowVsPtCentAntiProton[iCent][iPlane]->Draw("same");
    }
  }

  cV2VsPtCentProton->cd(2);
  pubedProton1020->Draw("same");
  cV2VsPtCentProton->cd(3);
  pubedProton2030->Draw("same");
  cV2VsPtCentProton->cd(4);
  pubedProton3040->Draw("same");
  cV2VsPtCentProton->cd(5);
  pubedProton4050->Draw("same");
  cV2VsPtCentProton->cd(6);
  pubedProton5060->Draw("same");
  cV2VsPtCentProton->cd(7);
  pubedProton6070->Draw("same");
  cV2VsPtCentProton->SaveAs("V2VsPtProcV2VsPtCentProton.png");
  

  TCanvas* cV2VsPtCentLambda = new TCanvas("Lambda & AntiLambda v2 vs pT","Lambda & AntiLambda v2 vs pT",900,600);
  cV2VsPtCentLambda->Divide(3,3);
  for (int iCent = 0; iCent < 9; iCent++) {
    cV2VsPtCentLambda->cd(iCent+1);
    dummyV2VsPt->Draw("same");
    for (size_t iPlane = 0; iPlane < 4; iPlane++) {
      hFlowVsPtCentLambda[iCent][iPlane]->Draw("same");
      hFlowVsPtCentAntiLambda[iCent][iPlane]->Draw("same");
    }
  }
  cV2VsPtCentLambda->cd(2);
  pubedLambda1020->Draw("same");
  cV2VsPtCentLambda->cd(3);
  pubedLambda2030->Draw("same");
  cV2VsPtCentLambda->cd(4);
  pubedLambda3040->Draw("same");
  cV2VsPtCentLambda->cd(5);
  pubedLambda4050->Draw("same");
  cV2VsPtCentLambda->cd(6);
  pubedLambda5060->Draw("same");
  cV2VsPtCentLambda->cd(7);
  pubedLambda6070->Draw("same");
  cV2VsPtCentLambda->SaveAs("V2VsPtLambda.png");

  }
}



Double_t GetResolutionErr(Double_t A, Double_t AErr, Double_t B, Double_t BErr, Double_t C, Double_t CErr) {
  Double_t rootA = TMath::Power(A, 0.5);
  Double_t invRootA = TMath::Power(A, -0.5);
  Double_t rootB = TMath::Power(B, 0.5);
  Double_t invRootB = TMath::Power(B, -0.5);
  Double_t rootC = TMath::Power(C, 0.5);
  Double_t invRootC = TMath::Power(C, -0.5);

  Double_t Err = -999;
  Err = 0.5 * rootB * invRootA * invRootC * TMath::Power(AErr,2)
      + 0.5 * rootA * invRootB * invRootC * TMath::Power(BErr,2)
      - 0.5 * rootA * rootB * TMath::Power(C,-1.5) * TMath::Power(CErr,2);
  Err = TMath::Sqrt(Err);

  return Err;
}