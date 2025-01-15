#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    // method from the base class
    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);

    void AddEnergyDeposit1(G4double edep) { edep1 += edep; };


  private:
    G4double edep1;
    G4double edep2;
    G4double edep_gamma;
    G4double edep_electron;
    G4double edep_muon;
    G4double edep_pion;
    G4double edep_proton;
    G4double edep_neutron;
    G4double edep_kaon;




};

#endif
