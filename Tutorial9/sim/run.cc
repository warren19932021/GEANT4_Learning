#include "run.hh"
//#include "G4VAnalysisManager.hh"

MyrunAction::MyrunAction()
{
  G4AnalysisManager * man =  G4AnalysisManager::Instance();
  man->CreateNtuple("Hits","Hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->FinishNtuple(0);
}

MyrunAction::~MyrunAction()
{

}

//void MyrunAction::BeginOfRunAction(const G4Run*)
void MyrunAction::BeginOfRunAction(const G4Run* run)
{
  //G4AnalysisManager * man = new  G4AnalysisManager::Instance();
  G4AnalysisManager * man =  G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();
  std::stringstream strRunID;
  strRunID <<  runID;
  man->OpenFile("output"+strRunID.str()+".root");
  //man->OpenFile("output.root");

}

void MyrunAction::EndOfRunAction(const G4Run*)
{
  //G4AnalysisManager * man = new  G4AnalysisManager::Instance();
 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();

}  


