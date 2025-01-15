//code for histo edep

int histo(){
    gROOT->Reset();
    TStyle* hjbStyle = new TStyle("hjbStyle","");
	gStyle->SetOptFit(1111);
	gStyle->SetOptStat(1111);
	
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
        
        gStyle->SetTitleH(0.06);
        gStyle->SetTitleSize(0.03);

        TFile *f = new TFile("data.root");
        TTree* step = (TTree*)f->Get("step");
        step->Print();
	
	TFile *hst = new TFile("edep_histo.root","recreate");

	TH1F* hEvt = new TH1F("hEvt", "hEvt", 100, 0, 1000);
	TH1F* hedep = new TH1F("hedep", "hedep", 200, 0, 70);
	TH1F* hedep0 = new TH1F("hedep0","hedep0", 200, 0, 70);
	
	step->Draw("eventID>>hEvt");
	step->Draw("edep>>hedep");
	
	Double_t edep;
 	step->SetBranchAddress("edep",&edep);

	for(int i = 0; i< step->GetEntries(); i++)
	{
	 	step->GetEntry(i);	
		if(edep!=0){
		hedep0->Fill(edep);
		}

	}
	hedep0->Draw();

	TCanvas* c1 = new TCanvas("c1","edep",0,0,900,600);
        c1->SetBottomMargin(0.1);
	hedep->Draw();
        c1->Modified();
        c1->Update();
        c1->Print("edep.png");

	TCanvas* c2 = new TCanvas("c2","edep0",100,0,900,600);
        c2->SetBottomMargin(0.1);
        hedep0->Draw();
        c2->Modified();
        c2->Update();
        c2->Print("edep0.png");

	
	hst->Write();
	return 0;
}
