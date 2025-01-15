void muon(TString filename = "build/data.root")
{
  gStyle->SetOptStat(0);

  //TFile* file = new TFile("build/data.root","read");
  //TFile* file = new TFile("rootfile/muon.root","read");
  //TFile* file = new TFile("rootfile/muon_vertical.root","read");
  TFile* file = new TFile(filename.Data(), "read");
  TTree* tree = (TTree*)file->Get("step");
  Int_t eventID, volumeID;
  Double_t edep, x0, y0, z0, px0, py0, pz0;
  tree->SetBranchAddress("eventID", &eventID);
  tree->SetBranchAddress("volumeID", &volumeID);
  tree->SetBranchAddress("edep", &edep);
  tree->SetBranchAddress("x0", &x0);
  tree->SetBranchAddress("y0", &y0);
  tree->SetBranchAddress("z0", &z0);
  tree->SetBranchAddress("px0", &px0);
  tree->SetBranchAddress("py0", &py0);
  tree->SetBranchAddress("pz0", &pz0);

  Double_t evtnum, dE;
  Double_t x, y, z, theta, phi;
  TFile* outfile = new TFile("rootfile/out.root", "recreate");
  TTree* data = new TTree("data", "");
  data->Branch("evtnum", &evtnum, "evtnum/I");
  data->Branch("dE", &dE, "dE/D");
  data->Branch("x", &x, "x/D");
  data->Branch("y", &y, "y/D");
  data->Branch("z", &z, "z/D");
  data->Branch("theta", &theta, "theta/D");
  data->Branch("phi", &phi, "phi/D");

  TH1D* hist = new TH1D("hist",";MeV;", 200,0,100);

  int evt=0;
  double totalE=0;

  for(int evi=0; evi<tree->GetEntries(); evi++)
  {
    tree->GetEntry(evi);
    if(evi==0 ) {
      TVector3 mom(px0, py0, pz0);
      theta = mom.Theta()*180/TMath::Pi();
      phi = mom.Phi()*180/TMath::Pi();
      x = x0;
      y = y0;
      z = z0;
      cout << volumeID << endl;
    }

    if(volumeID == 0 ) continue;
    //if(volumeID == 2 ) continue;

    if(eventID==evt) {
      totalE+=edep;
    }
    else if(eventID!=evt) {
      evtnum = evt;
      dE = totalE;
      if( dE ) {
	data->Fill();
	hist->Fill(dE);
      }
      evt++;
      totalE=edep;
      
      TVector3 mom(px0, py0, pz0);
      theta = mom.Theta()*180/TMath::Pi();
      phi = mom.Phi()*180/TMath::Pi();
      x = x0;
      y = y0;
      z = z0;
    }
  }
  evtnum = evt;
  dE = totalE;
  if( dE ) {
    data->Fill();
    hist->Fill(dE);
  }

  TCanvas* c1 = new TCanvas("c1","", 800,600);
  c1->cd()->SetLogy();
  hist->Draw();
  //data->Draw("dE>>h0(200,0,100)");
  
  TCanvas* c2 = new TCanvas("c2","", 1200,800);
  c2->Divide(3,2);
  c2->cd(1)->SetLogz();
  data->Draw("x:dE>>h1(200,0,100,200,-120,120)","","colz");
  c2->cd(2)->SetLogz();
  data->Draw("y:dE>>h2(200,0,100,200,-120,120)","","colz");
  c2->cd(3)->SetLogz();
  data->Draw("z:dE>>h3(200,0,100,200,-120,120)","","colz");
  c2->cd(4)->SetLogz();
  data->Draw("theta:dE>>h4(200,0,100,200,0,90)","","colz");
  c2->cd(5)->SetLogz();
  data->Draw("phi:dE>>h5(200,0,100,200,-90,90)","","colz");

  outfile->cd();
  data->Write();

}
