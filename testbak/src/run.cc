#include "run.hh"
//#include "G4VAnalysisManager.hh"

MyrunAction::MyrunAction()
{

}

MyrunAction::~MyrunAction()
{
}

void MyrunAction::BeginOfRunAction(const G4Run*)
{
  //G4AnalysisManager * man = new  G4AnalysisManager::Instance();

  G4AnalysisManager * man =  G4AnalysisManager::Instance();
  man->OpenFile("output.root");
  man->CreateNtuple("Hits","Hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->FinishNtuple(0);

  man->CreateNtuple("Scoring","Scoring");
  man->CreateNtupleDColumn("fEdep");
  man->FinishNtuple(1);

}

void MyrunAction::EndOfRunAction(const G4Run*)
{
  //G4AnalysisManager * man = new  G4AnalysisManager::Instance();
 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();

}  


