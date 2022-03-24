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

    //G4cout<<"Photom Position: "<<posPhoton<<G4endl;

    const G4VTouchable * touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo =  touchable->GetCopyNumber();

    G4cout<<"Copy number: "<<copyNo<<G4endl;

    G4VPhysicalVolume *physvol = touchable->GetVolume();
    G4ThreeVector posDetector = physvol->GetTranslation();

    G4cout<<"Detector Position: "<<posDetector<<G4endl;


    return true;
}
