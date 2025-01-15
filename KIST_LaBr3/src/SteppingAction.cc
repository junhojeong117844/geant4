#include "SteppingAction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "TString.h"

SteppingAction::SteppingAction()
: G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int volumeID = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
  G4double totalEdep = step->GetTotalEnergyDeposit();
  G4double trackLength = step->GetTrack()->GetTrackLength();
  
  EventAction *eventAction = (EventAction*)G4EventManager::GetEventManager()->GetUserEventAction();

  if( volumeID==1 ) {
    eventAction -> AddEnergyDeposit1(totalEdep);
  }
  else if( volumeID==2 || volumeID==3 ) {
  }

}
