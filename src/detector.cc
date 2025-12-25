#include "detector.hh"
#include "run.hh"


SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name){}
SensitiveDetector::~SensitiveDetector(){}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist){


    G4Track* aTrack = aStep->GetTrack();
    aTrack->SetTrackStatus(fStopAndKill);
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    // G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector pos = preStepPoint->GetPosition();

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0, 0,pos.x());
    man->FillNtupleDColumn(0, 1,pos.y());
    man->FillNtupleDColumn(0, 2,pos.z());
    man->AddNtupleRow(0);

    return true;
}