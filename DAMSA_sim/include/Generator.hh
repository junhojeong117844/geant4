#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {

	public:
	MyPrimaryGenerator();
	~MyPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);

	private:
	G4ParticleGun *fParticleGun1;
	G4ParticleGun *fParticleGun2;
	/*G4ParticleGun *fParticleGun3;
	G4ParticleGun *fParticleGun4;
	G4ParticleGun *fParticleGun5;
	G4ParticleGun *fParticleGun6;
	G4ParticleGun *fParticleGun7;
	G4ParticleGun *fParticleGun8;*/
};

#endif
