void test()
{
  //gStyle->SetOptStat(0);
  
  const Int_t TotalEvent = 100000;
  const Int_t NumOfEnergies = 5;
  const Double_t EnergyGap = 0.01;
  Double_t Energy[NumOfEnergies];
  for(Int_t i=0; i<NumOfEnergies; i++) Energy[i] = 6+i;

  TFile* file[NumOfEnergies];
  TTree* tree[NumOfEnergies];
  TH1D* rawHist[NumOfEnergies];
  TH1D* bgoHist[NumOfEnergies];
  TH1D* bgoHist_cut[NumOfEnergies];
  Double_t edep[NumOfEnergies], edep2[NumOfEnergies];
  Double_t efficiency[NumOfEnergies] = {0};

  for(Int_t i=0; i<NumOfEnergies; i++) {
    file[i] = new TFile(Form("rootfile/wobgo_%.0f.root", Energy[i]), "read");
    tree[i] = (TTree*)file[i]->Get("step");
    tree[i]->SetBranchAddress("edep", &edep[i]);
    tree[i]->SetBranchAddress("edep2", &edep2[i]);

    rawHist[i] = new TH1D(Form("rawHist%.0f",Energy[i]), 
			  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist[i] = new TH1D(Form("bgoHist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist_cut[i] = new TH1D(Form("bgoHist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    for(Int_t evi=0; evi<tree[i]->GetEntries(); evi++) {
      tree[i]->GetEntry(evi);
      rawHist[i]->Fill(edep[i]);
      if( edep[i]>Energy[i]-EnergyGap && edep[i]<Energy[i]+EnergyGap ) efficiency[i]++;
    }

    efficiency[i] /= (double)TotalEvent;
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

}
