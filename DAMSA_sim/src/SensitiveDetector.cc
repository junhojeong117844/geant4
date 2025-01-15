#include "SensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) :
G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {

    G4Track *track = aStep -> GetTrack();
	G4ParticleDefinition *particle = track -> GetDefinition();
	auto position = track -> GetPosition();

	if (position.z() > 40.0) {

		track -> SetTrackStatus(fStopAndKill);

	}

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4int evt = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

	if (particle -> GetPDGEncoding() == 11) {

    	G4StepPoint *elec = aStep -> GetPreStepPoint();
		auto elecmom = elec -> GetMomentum();
		auto elecpoint = elec -> GetPosition();

		man -> FillNtupleIColumn(0, 0, evt);
		man -> FillNtupleDColumn(0, 1, elecpoint[0]);
		man -> FillNtupleDColumn(0, 2, elecpoint[1]);
		man -> FillNtupleDColumn(0, 3, elecpoint[2]);
		man -> FillNtupleDColumn(0, 4, elecmom[0]);
		man -> FillNtupleDColumn(0, 5, elecmom[1]);
		man -> FillNtupleDColumn(0, 6, elecmom[2]);
		man -> AddNtupleRow(0);

		double interval = -1.3;
		double transformedValue = elecpoint[1];

		if (elecpoint[1] <= 0 && elecpoint[1] >= -13) {

			int index = static_cast<int>(elecpoint[1]/interval);
			transformedValue = (index +0.5) * interval;

		}

		man -> FillNtupleIColumn(2, 0, evt);
		man -> FillNtupleDColumn(2, 1, elecpoint[0]);
		man -> FillNtupleDColumn(2, 2, transformedValue);
		man -> FillNtupleDColumn(2, 3, elecpoint[2]);
		man -> FillNtupleDColumn(2, 4, elecmom[0]);
		man -> FillNtupleDColumn(2, 5, elecmom[1]);
		man -> FillNtupleDColumn(2, 6, elecmom[2]);
		man -> AddNtupleRow(2);

	} else if (particle -> GetPDGEncoding() == -11) {

    	G4StepPoint *posi = aStep -> GetPreStepPoint();
		auto posimom = posi -> GetMomentum();
		auto posipoint = posi -> GetPosition();

		man -> FillNtupleIColumn(1, 0, evt);
		man -> FillNtupleDColumn(1, 1, posipoint[0]);
		man -> FillNtupleDColumn(1, 2, posipoint[1]);
		man -> FillNtupleDColumn(1, 3, posipoint[2]);
		man -> FillNtupleDColumn(1, 4, posimom[0]);
		man -> FillNtupleDColumn(1, 5, posimom[1]);
		man -> FillNtupleDColumn(1, 6, posimom[2]);
		man -> AddNtupleRow(1);

		double interval = 1.3;
		double transformedValue = posipoint[1];

		if (posipoint[1] >= 0 && posipoint[1] <= 13) {

			int index = static_cast<int>(posipoint[1]/interval);
			transformedValue = (index +0.5) * interval;

		}

		man -> FillNtupleIColumn(3, 0, evt);
		man -> FillNtupleDColumn(3, 1, posipoint[0]);
		man -> FillNtupleDColumn(3, 2, transformedValue);
		man -> FillNtupleDColumn(3, 3, posipoint[2]);
		man -> FillNtupleDColumn(3, 4, posimom[0]);
		man -> FillNtupleDColumn(3, 5, posimom[1]);
		man -> FillNtupleDColumn(3, 6, posimom[2]);
		man -> AddNtupleRow(3);

	}
}
