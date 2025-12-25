#include "stepping.hh"


SteppingAction::SteppingAction(EventAction* eventAction){

    fEventAction = eventAction;

}
SteppingAction::~SteppingAction(){

}

void SteppingAction::UserSteppingAction(const G4Step* step){

    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();   

    const DetectorConstruction* detectorConstruction_1 = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    G4LogicalVolume* fScoringVolume = detectorConstruction_1->GetScoringVolume();
    
    if(volume != fScoringVolume){
        return;
    }
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);

}

