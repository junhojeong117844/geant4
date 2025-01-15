void LaBr3EnergySpectrum()
{
  //gStyle->SetOptStat(0);
  
  const Int_t TotalEvent = 100000;
  const Int_t NumOfEnergies = 5;
  const Double_t EnergyGap = 0.01;

  Double_t Energy[NumOfEnergies];
  for(Int_t i=0; i<NumOfEnergies; i++) Energy[i] = 6+i;

  TFile* file;
  TTree* tree;
  TH1D* rawHist[NumOfEnergies];
  TH1D* bgoHist[NumOfEnergies];
  TH1D* bgoHist_bgo[NumOfEnergies];
  TH1D* bgoHist_cut[NumOfEnergies];
  Double_t edep, edep2;
  Double_t efficiency[NumOfEnergies] = {0};

  for(Int_t i=0; i<NumOfEnergies; i++) {
    file = new TFile(Form("rootfile/wobgo_%.0f.root", Energy[i]), "read");
    tree = (TTree*)file->Get("step");
    tree->SetBranchAddress("edep", &edep);
    tree->SetBranchAddress("edep2", &edep2);

    rawHist[i] = new TH1D(Form("rawHist%.0f",Energy[i]), 
			  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    for(Int_t evi=0; evi<tree->GetEntries(); evi++) {
      tree->GetEntry(evi);
      rawHist[i]->Fill(edep);
      if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) efficiency[i]++;
    }

    efficiency[i] /= (double)TotalEvent;
  }
  
  for(Int_t i=0; i<NumOfEnergies; i++) {
    file = new TFile(Form("rootfile/wbgo_%.0f.root", Energy[i]), "read");
    tree = (TTree*)file->Get("step");
    tree->SetBranchAddress("edep", &edep);
    tree->SetBranchAddress("edep2", &edep2);

    bgoHist[i] = new TH1D(Form("bgoHist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist_bgo[i] = new TH1D(Form("bgoHist_bgo%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist_cut[i] = new TH1D(Form("bgoHist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    for(Int_t evi=0; evi<tree->GetEntries(); evi++) {
      tree->GetEntry(evi);
      bgoHist[i]->Fill(edep);
      bgoHist_bgo[i]->Fill(edep2);
      if( edep2 < 0.1 ) bgoHist_cut[i]->Fill(edep);
    }
  }

  TGraph* graph = new TGraph(NumOfEnergies, Energy, efficiency);
  graph->SetMarkerStyle(21);
  graph->SetMarkerSize(1.0);

  TCanvas* c1 = new TCanvas("c1","c1", 1200, 600);
  c1->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    c1->cd(i+1)->SetLogy();
    rawHist[i]->Draw();
  }

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
  c2->cd();
  graph->Draw("AP");

  TCanvas* c3 = new TCanvas("c3","c3", 1200, 600);
  c3->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    c3->cd(i+1)->SetLogy();
    bgoHist[i]->Draw();
    bgoHist_cut[i]->SetLineColor(kRed);
    bgoHist_cut[i]->Draw("same");
  }
  TCanvas* c4 = new TCanvas("c4","c4", 1200, 600);
  c4->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    c4->cd(i+1)->SetLogy();
    bgoHist_bgo[i]->Draw();
  }
}
