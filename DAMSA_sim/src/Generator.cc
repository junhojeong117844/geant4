#include "Generator.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include <ctime>

MyPrimaryGenerator::MyPrimaryGenerator() {
	
	fParticleGun1 = new G4ParticleGun();
	fParticleGun2 = new G4ParticleGun();
	/*fParticleGun3 = new G4ParticleGun();
	fParticleGun4 = new G4ParticleGun();

	fParticleGun5 = new G4ParticleGun();
	fParticleGun6 = new G4ParticleGun();
	fParticleGun7 = new G4ParticleGun();
	fParticleGun8 = new G4ParticleGun();*/
}

MyPrimaryGenerator::~MyPrimaryGenerator() {

	delete fParticleGun1;
	delete fParticleGun2;
	/*delete fParticleGun3;
	delete fParticleGun4;

	delete fParticleGun5;
	delete fParticleGun6;
	delete fParticleGun7;
	delete fParticleGun8;*/
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {

	double seed = time(nullptr);
	G4Random::setTheSeed(seed);

	double i = CLHEP::RandFlat::shoot(-160, -60);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

	G4String particleName;

	G4ParticleDefinition* electron = particleTable -> FindParticle(particleName = "e-");
	G4ParticleDefinition* positron = particleTable -> FindParticle(particleName = "e+");

	fParticleGun1 -> SetParticleDefinition(electron);
	fParticleGun1 -> SetParticleEnergy(200*MeV);
	fParticleGun1 -> SetParticlePosition(G4ThreeVector(0, 0, i*mm));
	fParticleGun1 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun1 -> GeneratePrimaryVertex(anEvent);

	fParticleGun2 -> SetParticleDefinition(positron);
	fParticleGun2 -> SetParticleEnergy(200*MeV);
	fParticleGun2 -> SetParticlePosition(G4ThreeVector(0, 0, i*mm));
	fParticleGun2 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun2 -> GeneratePrimaryVertex(anEvent);

	/*fParticleGun1 -> SetParticleDefinition(electron);
	fParticleGun2 -> SetParticleDefinition(electron);
	fParticleGun3 -> SetParticleDefinition(electron);
	fParticleGun4 -> SetParticleDefinition(electron);

	fParticleGun5 -> SetParticleDefinition(positron);
	fParticleGun6 -> SetParticleDefinition(positron);
	fParticleGun7 -> SetParticleDefinition(positron);
	fParticleGun8 -> SetParticleDefinition(positron);

	fParticleGun1 -> SetParticleEnergy(200*MeV);
	fParticleGun2 -> SetParticleEnergy(300*MeV);
	fParticleGun3 -> SetParticleEnergy(400*MeV);
	fParticleGun4 -> SetParticleEnergy(500*MeV);

	fParticleGun5 -> SetParticleEnergy(200*MeV);
	fParticleGun6 -> SetParticleEnergy(300*MeV);
	fParticleGun7 -> SetParticleEnergy(400*MeV);
	fParticleGun8 -> SetParticleEnergy(500*MeV);

	fParticleGun1 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun2 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun3 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun4 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));

	fParticleGun5 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun6 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun7 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));
	fParticleGun8 -> SetParticlePosition(G4ThreeVector(0, 0, -500*mm));

	fParticleGun1 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun2 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun3 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun4 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

	fParticleGun5 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun6 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun7 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
	fParticleGun8 -> SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

	fParticleGun1 -> GeneratePrimaryVertex(anEvent);
	fParticleGun2 -> GeneratePrimaryVertex(anEvent);
	fParticleGun3 -> GeneratePrimaryVertex(anEvent);
	fParticleGun4 -> GeneratePrimaryVertex(anEvent);

	fParticleGun5 -> GeneratePrimaryVertex(anEvent);
	fParticleGun6 -> GeneratePrimaryVertex(anEvent);
	fParticleGun7 -> GeneratePrimaryVertex(anEvent);
	fParticleGun8 -> GeneratePrimaryVertex(anEvent);*/
}
