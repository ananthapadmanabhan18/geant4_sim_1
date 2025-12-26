#include "detector.hh"
#include "run.hh"


SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name){}
SensitiveDetector::~SensitiveDetector(){}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist){


    G4Track* aTrack = aStep->GetTrack();
    // aTrack->SetTrackStatus(fStopAndKill);

    if (!aStep->IsFirstStepInVolume()) {
            return false; 
    }

    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector pos_pre = preStepPoint->GetPosition();
    G4ThreeVector pos_post = postStepPoint->GetPosition();

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillH3(0, pos_pre.x(), pos_pre.y(), pos_pre.z());
    man->FillH3(1, pos_post.x(), pos_post.y(), pos_post.z());

    return true;
}