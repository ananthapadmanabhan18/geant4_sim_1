#include "generator.hh"
#define M_PI 3.14159265358979323846


PrimaryGenerator::PrimaryGenerator(){
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("proton");
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->SetParticleEnergy(1.*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.*m));
}

PrimaryGenerator::~PrimaryGenerator(){
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent){

    G4double random = G4UniformRand();
    random = random*2*M_PI;
    G4double x = 5.*m*cos(random);
    G4double y = 5.*m*sin(random);
    G4double z = 5.*m;
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x,y,z));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}