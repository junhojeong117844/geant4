#include "EventAction.hh"
#include "G4RunManager.hh"

EventAction::EventAction()
: G4UserEventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event*)
{
  edep1 = 0.;
  edep2 = 0.;
  edep_gamma = 0.;
  edep_electron = 0.;
  edep_muon = 0.;
  edep_pion = 0.;
  edep_proton = 0.;
  edep_neutron = 0.;
  edep_kaon = 0.;


}

void EventAction::EndOfEventAction(const G4Event*)
{
  G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager -> FillNtupleIColumn(0, 0, eventID);
  analysisManager -> FillNtupleDColumn(0, 1, edep1);

  analysisManager -> AddNtupleRow(0);

  analysisManager -> FillNtupleIColumn(1, 0, edep_gamma);
  analysisManager -> FillNtupleDColumn(1, 1, edep_electron);
  analysisManager -> FillNtupleDColumn(1, 2, edep_muon);
  analysisManager -> FillNtupleDColumn(1, 3, edep_pion);
  analysisManager -> FillNtupleDColumn(1, 4, edep_proton);
  analysisManager -> FillNtupleDColumn(1, 5, edep_neutron);
  analysisManager -> FillNtupleDColumn(1, 6, edep_pion);
  analysisManager -> AddNtupleRow(1);

}
