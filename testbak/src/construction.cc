#include "construction.hh"
//#include "detector.hh"



MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();    
   isGeDet = false;
   isAndyGeDet = true;

}

MyDetectorConstruction::~MyDetectorConstruction()
{}	

void MyDetectorConstruction::DefineMaterials()
{

   G4NistManager * nist = G4NistManager::Instance();
   //G4Material * detectorMat = nist->FindOrBuildMaterial("G4_Ge");
   detectorMat = nist->FindOrBuildMaterial("G4_Ge");
   //G4Material * worldMat = nist->FindOrBuildMaterial("G4_AIR");
   worldMat = nist->FindOrBuildMaterial("G4_AIR");
}

void MyDetectorConstruction::ConstructGeDet()
{

   G4Box * solidDetector = new G4Box("solidDetector", 2.5*m, 2.5*m,0.1*m);
   logicDetector = new G4LogicalVolume(solidDetector,detectorMat,"logicDetector");

   fScoringVolume = logicDetector;

   G4cout<<"Output in MyDetectorConstruction::ConstrcutGeDet()!"<<G4endl;

   for(G4int i=0;i<2;i++)
   {
      for(G4int j=0;j<2;j++)
      {

          G4VPhysicalVolume *physDetector = new G4PVPlacement(0,G4ThreeVector(-2.5*m+i*5.*m,-2.5*m+j*5.*m,3*m),
          logicDetector,"physDetector",logicalWorld,false,j+i*10,true);   

      }

   }   
}   

void MyDetectorConstruction:: ConstructAndyGeDet()
{
  // fScoringVolume = logicDetector;
}   



G4VPhysicalVolume* MyDetectorConstruction::Construct()
{


   G4Box * solidWorld =  new G4Box("SolidWorld",5.*m,5.*m,5.*m); 
   //G4LogicalVolume * logicalWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");
   logicalWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");
   G4VPhysicalVolume * physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalWorld,"physWolrd",0,false,0,true); 


   if(isGeDet)
      ConstructGeDet();

   if(isAndyGeDet)
      ConstructAndyGeDet();

   return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector* senDet = new MySensitiveDetector("Test");
  if(isGeDet)
  logicDetector->SetSensitiveDetector(senDet); 
}
