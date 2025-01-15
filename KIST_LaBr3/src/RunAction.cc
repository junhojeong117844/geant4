#include "RunAction.hh"

RunAction::RunAction()
: G4UserRunAction()
{
}

RunAction::~RunAction()
{
  ;
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> OpenFile("data.root");

  analysisManager -> CreateNtuple("step", "step");
  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> CreateNtupleDColumn("edep");
  analysisManager -> FinishNtuple();

  analysisManager -> CreateNtuple("pdg", "pdg");
  analysisManager -> CreateNtupleIColumn("gamma");
  analysisManager -> CreateNtupleDColumn("electron");
  analysisManager -> CreateNtupleDColumn("muon");
  analysisManager -> CreateNtupleDColumn("pion");
  analysisManager -> CreateNtupleDColumn("proton");
  analysisManager -> CreateNtupleDColumn("neutron");
  analysisManager -> CreateNtupleDColumn("kaon");
  analysisManager -> FinishNtuple();

  analysisManager -> CreateNtuple("Primary", "Primary");
  analysisManager -> CreateNtupleDColumn("eset");
  analysisManager -> CreateNtupleDColumn("momentum_set");
  analysisManager -> CreateNtupleDColumn("momentum_theta");
  analysisManager -> CreateNtupleDColumn("momentum_phi");
  analysisManager -> CreateNtupleDColumn("theta_dist");
  analysisManager -> FinishNtuple();

 
  analysisManager -> CreateH1("PDG Count","PDG Count",7,0,14);
  analysisManager -> SetH1Activation(true);
  

}

void RunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> Write();
  analysisManager -> CloseFile();
}
