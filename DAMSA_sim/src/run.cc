#include "run.hh"
#include "G4AnalysisManager.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*) {

	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man -> OpenFile("200_MeV.root");

	man -> CreateNtuple("elecHits", "elecHits");
	man -> CreateNtupleIColumn("fEvent");
	man -> CreateNtupleDColumn("feX");
	man -> CreateNtupleDColumn("feY");
	man -> CreateNtupleDColumn("feZ");
	man -> CreateNtupleDColumn("fepX");
	man -> CreateNtupleDColumn("fepY");
	man -> CreateNtupleDColumn("fepZ");

	man -> FinishNtuple(0);

	man -> CreateNtuple("posiHits", "posiHits");
	man -> CreateNtupleIColumn("fEvent");
	man -> CreateNtupleDColumn("fpX");
	man -> CreateNtupleDColumn("fpY");
	man -> CreateNtupleDColumn("fpZ");
	man -> CreateNtupleDColumn("fppX");
	man -> CreateNtupleDColumn("fppY");
	man -> CreateNtupleDColumn("fppZ");

	man -> FinishNtuple(1);

	man -> CreateNtuple("t_elecHits", "t_elecHits");
	man -> CreateNtupleIColumn("fEvent");
	man -> CreateNtupleDColumn("fteX");
	man -> CreateNtupleDColumn("fteY");
	man -> CreateNtupleDColumn("fteZ");
	man -> CreateNtupleDColumn("ftepX");
	man -> CreateNtupleDColumn("ftepY");
	man -> CreateNtupleDColumn("ftepZ");

	man -> FinishNtuple(2);

	man -> CreateNtuple("t_posiHits", "t_posiHits");
	man -> CreateNtupleIColumn("fEvent");
	man -> CreateNtupleDColumn("ftpX");
	man -> CreateNtupleDColumn("ftpY");
	man -> CreateNtupleDColumn("ftpZ");
	man -> CreateNtupleDColumn("ftppX");
	man -> CreateNtupleDColumn("ftppY");
	man -> CreateNtupleDColumn("ftppZ");

	man -> FinishNtuple(3);

}

void MyRunAction::EndOfRunAction(const G4Run*) {

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man -> Write();
	man -> CloseFile();

}
