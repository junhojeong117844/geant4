//code for histo gamma

int primary(){
	
	gROOT->Reset();
    TStyle* hjbStyle = new TStyle("hjbStyle","");
	gStyle->SetOptFit(1111);
	gStyle->SetOptStat(1111);
	
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
        
    gStyle->SetTitleH(0.06);
    gStyle->SetTitleSize(0.03);

    TFile *f = new TFile("data.root");
    TTree* Primary = (TTree*)f->Get("Primary");
	TTree* step = (TTree*)f->Get("step");
	
    Primary->Print();
	step->Print();

	TFile *hst = new TFile("data_analysis.root","recreate");

	TH1F* heset = new TH1F("heset", "heset", 5000, 0, 100000);
	TH1F* hmomentum_set = new TH1F("hmomentum_set", "hmomentum_set", 5000, 0, 100000);
	TH1F* hmomentum_phi = new TH1F("hmomentum_phi", "hmomentum_phi", 200, -4, 4);
	TH1F* hmomentum_theta = new TH1F("hmomentum_theta","hmomentum_theta", 200, 0, 180);
	TH1F* htheta_dist = new TH1F("htheta_dist","htheta_dist", 200, -1, 1);
	
	Primary->Draw("eset>>heset");
	Primary->Draw("momentum_set>>hmomentum_set");
	Primary->Draw("momentum_phi>>hmomentum_phi");
	Primary->Draw("momentum_theta>>hmomentum_theta");
	Primary->Draw("theta_dist>>htheta_dist");


	TH1F* hedep = new TH1F("hedep","hedep",120,0,120);
	TH1F* hedep0 = new TH1F("hedep0","hedep0",120,0,120);


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

	//making fitting fuction
	TF1 *fitFunc_theta = new TF1("fitFunc","landau",0,4);
	//hmomentum_theta->Fit(fitFunc_theta);

	TF1 *fitFunc_edep = new TF1("fitFunc","landau",22,60);
	hedep->Fit(fitFunc_edep,"","",22,60);
	hedep0->Fit(fitFunc_edep,"","",22,60);

	//show maximum value
	int maxBin_theta = hmomentum_theta->GetMaximumBin();
	double hmaxX_theta = hmomentum_theta->GetXaxis()->GetBinCenter(maxBin_theta);
	double hmaxY_theta = hmomentum_theta->GetBinContent(maxBin_theta);

	double fmaxX_theta = fitFunc_theta -> GetMaximumX();	
	
	int maxBin_edep = hedep0->GetMaximumBin();
	double hmaxX_edep = hedep0->GetXaxis()->GetBinCenter(maxBin_edep);
	double hmaxY_edep = hedep0->GetBinContent(maxBin_edep);

	double fmaxX_edep = fitFunc_edep -> GetMaximumX();



	//making cos(x)^2 fuction
	TF1 *cosTheta2 = new TF1("cosTheta2","cos(x)*cos(x)*290",0,4);

	//show the maximum point
	TPaveText *pt_theta = new TPaveText(0.25,0.7,0.45,0.9,"NDC");
	pt_theta->AddText(Form("HMax Value at theta = %.2f",hmaxX_theta));
	pt_theta->AddText(Form("FMax value at theta = %.2f",fmaxX_theta));

	TPaveText *pt_edep = new TPaveText(0.25,0.7,0.45,0.9,"NDC");
	pt_edep->AddText(Form("HMax Value at %.2f",hmaxX_edep));
	pt_edep->AddText(Form("FMax value at %.2f",fmaxX_edep));


	TMarker *marker_theta = new TMarker(hmaxX_theta,hmaxY_theta,kFullCircle);
	marker_theta->SetMarkerColor(kRed);
	marker_theta->SetMarkerSize(1);

	TMarker *marker_edep = new TMarker(hmaxX_edep,hmaxY_edep,kFullCircle);
	marker_edep->SetMarkerColor(kRed);
	marker_edep->SetMarkerSize(1);


	TCanvas* c1 = new TCanvas("c1","eset",0,0,900,600);
        c1->SetBottomMargin(0.1);
		heset->Draw();
        c1->Modified();
        c1->Update();
        c1->Print("eset.png");

	TCanvas* c2 = new TCanvas("c2","momentum_set",50,0,900,600);
        c2->SetBottomMargin(0.1);
		hmomentum_set->Draw();
        c2->Modified();
        c2->Update();
        c2->Print("mom_set.png");

	TCanvas* c3 = new TCanvas("c3","momentum_phi",100,0,900,600);
        c3->SetBottomMargin(0.1);
		hmomentum_phi->Draw();
        c3->Modified();
        c3->Update();
        c3->Print("mom_phi.png");
	
	TCanvas* c4 = new TCanvas("c4","momentum_theta",200,0,900,600);
        c4->SetBottomMargin(0.1);
		hmomentum_theta->Draw();
		//pt_theta->Draw("same");
		//marker_theta->Draw("same");
		//cosTheta2->SetLineColor(kGreen);
		//cosTheta2->Draw("same");
        c4->Modified();
        c4->Update();
        c4->Print("mom_theta.png");
	

	TCanvas* c5 = new TCanvas("c5","edep",300,0,900,600);
        c5->SetBottomMargin(0.1);
		hedep->Draw();
        c5->Modified();
        c5->Update();
        c5->Print("edep.png");

	TCanvas* c6 = new TCanvas("c6","edep0",400,0,900,600);
        c6->SetBottomMargin(0.1);
        hedep0->Draw();
		pt_edep->Draw("same");
		marker_edep->Draw("same");
        c6->Modified();
        c6->Update();
        c6->Print("edep0.png");

	TCanvas* c7 = new TCanvas("c7","theta_dist",400,0,900,600);
        c7->SetBottomMargin(0.1);
        htheta_dist->Draw();
        c7->Modified();
        c7->Update();
        c7->Print("theta_cos");
	
	hst->Write();
	return 0;
}
