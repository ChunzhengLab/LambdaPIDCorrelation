//Delta
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
void main(){
  TCanvas* cDeltaLambdaP = new TCanvas("DeltaLambdaP","DeltaLambdaP",1200,600);
  cDeltaLambdaP->Divide(2);
  TH2D* dummyDeltaLambdaP = new TH2D("","",1,0.,80.,1,-5e-3,5.e-3);
  dummyDeltaLambdaP->GetXaxis()->SetTitle("centrality");
  dummyDeltaLambdaP->GetYaxis()->SetTitle("#LTcos(#phi_{#Lambda}+phi_{p}-2#Psi)");

  TProfile* pDeltaLambdaP_SS = (TProfile*) fProfileDelta_Lambda_Proton->Clone();
  pDeltaLambdaP_SS ->Add(fProfileDelta_AntiLambda_AntiProton, 1);
  TH1D* hDeltaLambdaP_SS = pDeltaLambdaP_SS->ProjectionX();
  hDeltaLambdaP_SS->SetName("hDelta_SS");

  TProfile* pDeltaLambdaP_OS = (TProfile*) fProfileDelta_Lambda_AntiProton->Clone();
  pDeltaLambdaP_OS ->Add(fProfileDelta_AntiLambda_Proton, 1);
  TH1D* hDeltaLambdaP_OS = pDeltaLambdaP_OS->ProjectionX();
  hDeltaLambdaP_OS->SetName("hDelta_OS");

  TH1D* hDeltaDeltaLambdaP = (TH1D*)hDeltaLambdaP_OS->Clone();
  hDeltaDeltaLambdaP ->Add(hDeltaLambdaP_SS, -1);
  hDeltaDeltaLambdaP->SetName("hDeltaDeltaLambdaP");

  hDeltaLambdaP_SS->SetMarkerColor(kAzure);
  hDeltaLambdaP_SS->SetLineColor(kAzure);
  hDeltaLambdaP_SS->SetMarkerStyle(kFullCircle);
  hDeltaLambdaP_SS->SetMarkerSize(1.5);
  hDeltaLambdaP_SS->SetLineWidth(2);
  hDeltaLambdaP_OS->SetMarkerColor(kOrange+10);
  hDeltaLambdaP_OS->SetLineColor(kOrange+10);
  hDeltaLambdaP_OS->SetMarkerStyle(kFullCircle);
  hDeltaLambdaP_OS->SetMarkerSize(1.5);
  hDeltaLambdaP_OS->SetLineWidth(2);

  hDeltaDeltaLambdaP->SetLineColor(kBlack);
  hDeltaDeltaLambdaP->SetMarkerColor(kBlack);
  hDeltaDeltaLambdaP->SetMarkerStyle(kFullCircle);
  hDeltaDeltaLambdaP->SetMarkerSize(1);
  hDeltaDeltaLambdaP->SetLineWidth(2);

  TLegend* legendDelta = new TLegend(0.2,0.75,0.45,0.85);
  legendDelta->AddEntry(hDeltaLambdaP_SS,"#Lambda-h^{+} + #bar{#Lambda}-h^{-}","lp");
  legendDelta->AddEntry(hDeltaLambdaP_OS,"#Lambda-h^{-} + #bar{#Lambda}-h^{+}","lp");

  TLegend* legendDeltaDelta = new TLegend(0.2,0.75,0.45,0.85);
  legendDeltaDelta->AddEntry(hDeltaDeltaLambdaP,"OS-SS","lp");
  
  gStyle->SetErrorX(0.0001);
  cDeltaLambdaP->cd(1);
  dummyDeltaLambdaP->Draw("same");
  hDeltaLambdaP_OS->Draw("sameP");
  hDeltaLambdaP_SS->Draw("sameP");
  legendDelta->Draw("same");
  cDeltaLambdaP->cd(2);
  hDeltaDeltaLambdaP->Draw("sameP");
  legendDeltaDelta->Draw("same");

  //Lambda-p
  //Gamma
  TCanvas* cGammaLambdaP = new TCanvas("GammaLambdaP","GammaLambdaP",1200,600);
  cGammaLambdaP->Divide(2);
  TH2D* dummyGamma = new TH2D("","",1,0.,80.,1,-3e-3,3e-3);

  TProfile* pGammaTPCLambdaP_SS = (TProfile*) fProfileGammaTPC_Lambda_Proton->Clone();
  pGammaTPCLambdaP_SS ->Add(fProfileGammaTPC_AntiLambda_AntiProton, 1);
  TH1D* hGammaTPCLambdaP_SS = pGammaTPCLambdaP_SS->ProjectionX();
  hGammaTPCLambdaP_SS->SetName("hGammaTPCLambdaP_SS");

  TProfile* pGammaV0CLambdaP_SS = (TProfile*) fProfileGammaV0C_Lambda_Proton->Clone();
  pGammaV0CLambdaP_SS ->Add(fProfileGammaV0C_AntiLambda_AntiProton, 1);
  TH1D* hGammaV0CLambdaP_SS = pGammaV0CLambdaP_SS->ProjectionX();
  hGammaV0CLambdaP_SS->SetName("hGammaV0CLambdaP_SS");

  TProfile* pGammaV0ALambdaP_SS = (TProfile*) fProfileGammaV0A_Lambda_Proton->Clone();
  pGammaV0ALambdaP_SS ->Add(fProfileGammaV0A_AntiLambda_AntiProton, 1);
  TH1D* hGammaV0ALambdaP_SS = pGammaV0ALambdaP_SS->ProjectionX();
  hGammaV0ALambdaP_SS->SetName("hGammaV0ALambdaP_SS");

  TProfile* pGammaTPCLambdaP_OS = (TProfile*) fProfileGammaTPC_Lambda_AntiProton->Clone();
  pGammaTPCLambdaP_OS ->Add(fProfileGammaTPC_AntiLambda_Proton, 1);
  TH1D* hGammaTPCLambdaP_OS = pGammaTPCLambdaP_OS->ProjectionX();
  hGammaTPCLambdaP_OS->SetName("hGammaTPCLambdaP_OS");

  TProfile* pGammaV0CLambdaP_OS = (TProfile*) fProfileGammaV0C_Lambda_AntiProton->Clone();
  pGammaV0CLambdaP_OS ->Add(fProfileGammaV0C_AntiLambda_Proton, 1);
  TH1D* hGammaV0CLambdaP_OS = pGammaV0CLambdaP_OS->ProjectionX();
  hGammaV0CLambdaP_OS->SetName("hGammaV0CLambdaP_OS");

  TProfile* pGammaV0ALambdaP_OS = (TProfile*) fProfileGammaV0A_Lambda_AntiProton->Clone();
  pGammaV0ALambdaP_OS ->Add(fProfileGammaV0A_AntiLambda_Proton, 1);
  TH1D* hGammaV0ALambdaP_OS = pGammaV0ALambdaP_OS->ProjectionX();
  hGammaV0ALambdaP_OS->SetName("hGammaV0ALambdaP_OS");

  TH1D* hDeltaGammaTPCLambdaP = (TH1D*)hGammaTPCLambdaP_OS->Clone();
  hDeltaGammaTPCLambdaP ->Add(hGammaTPCLambdaP_SS, -1);
  hDeltaGammaTPCLambdaP->SetName("hDeltaGammaTPCLambdaP");

  TH1D* hDeltaGammaV0CLambdaP = (TH1D*)hGammaV0CLambdaP_OS->Clone();
  hDeltaGammaV0CLambdaP ->Add(hGammaV0CLambdaP_SS, -1);
  hDeltaGammaV0CLambdaP->SetName("hDeltaGammaV0CLambdaP");

  TH1D* hDeltaGammaV0ALambdaP = (TH1D*)hGammaV0ALambdaP_OS->Clone();
  hDeltaGammaV0ALambdaP ->Add(hGammaV0ALambdaP_SS, -1);
  hDeltaGammaV0ALambdaP->SetName("hDeltaGammaV0ALambdaP");

  hGammaTPCLambdaP_SS->SetMarkerColor(kAzure);
  hGammaTPCLambdaP_SS->SetLineColor(kAzure);
  hGammaTPCLambdaP_SS->SetMarkerStyle(kOpenCircle);
  hGammaTPCLambdaP_SS->SetMarkerSize(1.5);
  hGammaTPCLambdaP_SS->SetLineWidth(2);
  hGammaTPCLambdaP_OS->SetMarkerColor(kOrange+10);
  hGammaTPCLambdaP_OS->SetLineColor(kOrange+10);
  hGammaTPCLambdaP_OS->SetMarkerStyle(kOpenCircle);
  hGammaTPCLambdaP_OS->SetMarkerSize(1.5);
  hGammaTPCLambdaP_OS->SetLineWidth(2);

  hGammaV0CLambdaP_SS->SetMarkerColor(kAzure-1);
  hGammaV0CLambdaP_SS->SetLineColor(kAzure-1);
  hGammaV0CLambdaP_SS->SetMarkerStyle(kOpenSquare);
  hGammaV0CLambdaP_SS->SetMarkerSize(1.5);
  hGammaV0CLambdaP_SS->SetLineWidth(2);
  hGammaV0CLambdaP_OS->SetMarkerColor(kOrange+9);
  hGammaV0CLambdaP_OS->SetLineColor(kOrange+9);
  hGammaV0CLambdaP_OS->SetMarkerStyle(kOpenSquare);
  hGammaV0CLambdaP_OS->SetMarkerSize(1.5);
  hGammaV0CLambdaP_OS->SetLineWidth(2);

  hGammaV0ALambdaP_SS->SetMarkerColor(kAzure-2);
  hGammaV0ALambdaP_SS->SetLineColor(kAzure-2);
  hGammaV0ALambdaP_SS->SetMarkerStyle(kOpenStar);
  hGammaV0ALambdaP_SS->SetMarkerSize(1.5);
  hGammaV0ALambdaP_SS->SetLineWidth(2);
  hGammaV0ALambdaP_OS->SetMarkerColor(kOrange+8);
  hGammaV0ALambdaP_OS->SetLineColor(kOrange+8);
  hGammaV0ALambdaP_OS->SetMarkerStyle(kOpenStar);
  hGammaV0ALambdaP_OS->SetMarkerSize(1.5);
  hGammaV0ALambdaP_OS->SetLineWidth(2);

  hDeltaGammaTPCLambdaP->SetLineColor(ci[0]);
  hDeltaGammaTPCLambdaP->SetMarkerColor(ci[0]);
  hDeltaGammaTPCLambdaP->SetMarkerStyle(kOpenCircle);
  hDeltaGammaTPCLambdaP->SetMarkerSize(1.5);
  hDeltaGammaTPCLambdaP->SetLineWidth(2);

  hDeltaGammaV0CLambdaP->SetLineColor(ci[1]);
  hDeltaGammaV0CLambdaP->SetMarkerColor(ci[1]);
  hDeltaGammaV0CLambdaP->SetMarkerStyle(kOpenSquare);
  hDeltaGammaV0CLambdaP->SetMarkerSize(1.5);
  hDeltaGammaV0CLambdaP->SetLineWidth(2);

  hDeltaGammaV0ALambdaP->SetLineColor(ci[2]);
  hDeltaGammaV0ALambdaP->SetMarkerColor(ci[2]);
  hDeltaGammaV0ALambdaP->SetMarkerStyle(kOpenStar);
  hDeltaGammaV0ALambdaP->SetMarkerSize(1.5);
  hDeltaGammaV0ALambdaP->SetLineWidth(2);


  TLegend* legendGammaLambdaP = new TLegend(0.2,0.65,0.4,0.85);
  legendGammaLambdaP->AddEntry(hGammaTPCLambdaP_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} TPC","lp");
  legendGammaLambdaP->AddEntry(hGammaTPCLambdaP_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} TPC","lp");
  legendGammaLambdaP->AddEntry(hGammaV0CLambdaP_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} V0C","lp");
  legendGammaLambdaP->AddEntry(hGammaV0CLambdaP_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} V0C","lp");
  legendGammaLambdaP->AddEntry(hGammaV0ALambdaP_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} V0A","lp");
  legendGammaLambdaP->AddEntry(hGammaV0ALambdaP_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} V0A","lp");

  TLegend* legendDeltaGammaLambdaP = new TLegend(0.2,0.65,0.4,0.85);
  legendDeltaGammaLambdaP->AddEntry(hDeltaGammaTPCLambdaP,"OS-SS TPC","lp");
  legendDeltaGammaLambdaP->AddEntry(hDeltaGammaV0ALambdaP,"OS-SS TPC","lp");
  legendDeltaGammaLambdaP->AddEntry(hDeltaGammaV0CLambdaP,"OS-SS V0C","lp");
  

  cGammaLambdaP->cd(1);
  dummyGamma->Draw("same");
  hGammaTPCLambdaP_OS->Draw("sameP");
  hGammaTPCLambdaP_SS->Draw("sameP");
  hGammaV0ALambdaP_OS->Draw("sameP");
  hGammaV0ALambdaP_SS->Draw("sameP");
  hGammaV0CLambdaP_OS->Draw("sameP");
  hGammaV0CLambdaP_SS->Draw("sameP");
  legendGammaLambdaP->Draw("same");

  cGammaLambdaP->cd(2);
  hDeltaGammaTPCLambdaP->Draw("sameP");
  hDeltaGammaV0ALambdaP->Draw("sameP");
  hDeltaGammaV0CLambdaP->Draw("sameP");
  legendDeltaGammaLambdaP->Draw("same");

}