#include "run.hh"

RunAction::RunAction(){

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    man->CreateH3("pre-Step-point", "XY Distribution Pre-Step ;X (cm);Y (cm)", 20, -10000, 10000, 20, -10000, 10000, 1000, 0, 50000);
    man->CreateH3("post-Step-point", "XY Distribution Post-Step ;X (cm);Y (cm)", 20, -10000, 10000, 20, -10000, 10000, 1000, 0, 50000);

}
RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run* run){
    std::cout << "Run started!" << std::endl;

    G4int runNumber = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runNumber;


    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->OpenFile(strRunID.str() + ".root");

}

void RunAction::EndOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
    std::cout << "Run ended!" << std::endl;
}