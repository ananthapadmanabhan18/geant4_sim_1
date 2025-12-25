#include "event.hh"

EventAction::EventAction(RunAction*){
    fEdep = 0;
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event*){
    fEdep = 0;
}

void EventAction::EndOfEventAction(const G4Event*){

    G4cout << "Energy deposited: " << fEdep << G4endl;
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(1, 0, fEdep);
    man->AddNtupleRow(1);

}