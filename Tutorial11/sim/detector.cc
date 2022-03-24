#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory * ROhist)//
{

    
    G4Track * track =  aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint * preStepPoint =  aStep->GetPreStepPoint();
    G4StepPoint * postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    #ifndef G4MULTITHREADED 
    G4cout<<"Photom Position: "<<posPhoton<<G4endl;
    #endif
    const G4VTouchable * touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo =  touchable->GetCopyNumber();
    #ifndef G4MULTITHREADED 
    G4cout<<"Copy number: "<<copyNo<<G4endl;
    #endif
    
    G4VPhysicalVolume *physvol = touchable->GetVolume();
    G4ThreeVector posDetector = physvol->GetTranslation();
    #ifndef G4MULTITHREADED 
    G4cout<<"Detector Position: "<<posDetector<<G4endl;
    #endif

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    //G4int evt = G4RunManger::GetRunManager()->GetCurrentEvent()->GetEventID();
    #ifndef G4MULTITHREADED 
    G4cout<<"evt: "<<evt<<G4endl;
    #endif

   // G4AnalysisManager * man = new G4AnalysisManager::Instance();
    G4AnalysisManager * man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0,evt);
    man->FillNtupleDColumn(1,posDetector[0]);
    man->FillNtupleDColumn(2,posDetector[1]);
    man->FillNtupleDColumn(3,posDetector[2]);
    man->AddNtupleRow(0);
    
    return true;
}
