#include "run.hh"

RunAction::RunAction(){

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->FinishNtuple(0);

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(1);

}
RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run* run){
    std::cout << "Run started!" << std::endl;

    G4int runNumber = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runNumber;


    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->OpenFile("D:\\Coding\\Codes\\GIthub_Repos\\Geant4_Trials\\Outputs\\output" + strRunID.str() + ".root");

}

void RunAction::EndOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
    std::cout << "Run ended!" << std::endl;
}