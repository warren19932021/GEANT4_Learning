#include "construction.hh"
#include "detector.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
   fMessenger = new G4GenericMessenger(this,"/detector/","Detector Construction");
   fMessenger->DeclareProperty("nCols",nCols,"Number of columns");
   fMessenger->DeclareProperty("nRows",nRows,"Number of rows");
   fMessenger->DeclareProperty("isCherenkov",isCherenkov,"Toggle Cherenkov setup");
   fMessenger->DeclareProperty("isScintillator",isScintillator,"Toggle isScintillator setup");
   nCols=100;
   nRows=100;

   DefineMaterials();

   xWorld = 0.5*m;
   yWorld = 0.5*m;
   zWorld = 0.5*m;

   isCherenkov = false;
   isScintillator = true;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}	

void MyDetectorConstruction::DefineMaterials()
{
   G4NistManager * nist = G4NistManager::Instance();


   SiO2 = new G4Material("SiO2",2.2021*g/cm3,2);
   SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
   SiO2->AddElement(nist->FindOrBuildElement("O"),2);

   H2O = new G4Material("H2O",1.000*g/cm3,2);
   H2O->AddElement(nist->FindOrBuildElement("H"),2);
   H2O->AddElement(nist->FindOrBuildElement("O"),1);

   C = nist->FindOrBuildElement("C");

   Aerogel = new G4Material("Aerogel",0.200*g/cm3,3);
   Aerogel->AddMaterial(SiO2,62.5*perCent);
   Aerogel->AddMaterial(H2O,37.4*perCent);
   Aerogel->AddElement(C,0.1*perCent);

   worldMat = nist->FindOrBuildMaterial("G4_AIR");

   Na = nist->FindOrBuildElement("Na");
   I = nist->FindOrBuildElement("I");
   //G4Material * NaI = new G4Material("NaI",3.67*g/cm3,2);
   NaI = new G4Material("NaI",3.67*g/cm3,2);
   NaI->AddElement(Na,1);
   NaI->AddElement(I,1);

   G4double energy[2] =  {1.239841939*eV/0.2,1.239841939*eV/0.9};
   G4double rindexAerogel[2] = {1.1, 1.1};
   G4double rindexWorld[2] = {1.0, 1.0};

   mptAerogel = new G4MaterialPropertiesTable();
   mptAerogel->AddProperty("RINDEX",energy,rindexAerogel,2);

   mptWorld = new G4MaterialPropertiesTable();
   mptWorld->AddProperty("RINDEX",energy,rindexWorld,2 );

}

void MyDetectorConstruction::ConstrcutCherekov()
{

   //G4Box * solidRadiator = new G4Box("solidRadiator", 0.4*m,0.4*m,0.01*m);
   solidRadiator = new G4Box("solidRadiator", 0.4*m,0.4*m,0.01*m);



   logicalRadiator = new G4LogicalVolume(solidRadiator,Aerogel,"logicalRadiator");

   fScoringVolume = logicalRadiator;

   physRadiator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.25*m),logicalRadiator,"physRadiator",logicalWorld,false,0,true);

   //G4Box * solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m,0.01*m);
   //G4Box * solidDetector = new G4Box("solidDetector", xWorld/nCols, yWorld/nRows,0.01*m);
   solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols,0.01*m);
   logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicDetector");

 //  for(G4int i=0;i<100;i++)
 //  {
 //     for(G4int j=0;j<100;j++)
 //     {

   for(G4int i=0;i<nRows;i++)
   {
      for(G4int j=0;j<nCols;j++)
      {
          //G4VPhysicalVolume *physDetector = new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100,0.49*m),
          //logicDetector,"physDetector",logicalWorld,false,j+i*100,true);   

          physDetector = new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/nRows,-0.5*m+(j+0.5)*m/nCols,0.49*m),
          logicDetector,"physDetector",logicalWorld,false,j+i*nCols,true);   

      }

   }
}


void MyDetectorConstruction::ConstrcutScintillator()
{
   solidScintillator = new G4Tubs("solidScintillator",10*cm,20*cm,30*cm,0*deg,360*deg);
   logicalScintillator = new G4LogicalVolume(solidScintillator,NaI,"logicalScintillaotr");
   fScoringVolume = logicalScintillator;
   physScintillator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalScintillator,"physScintillaotr",logicalWorld,false,0,true);  
}



G4VPhysicalVolume* MyDetectorConstruction::Construct()
{


   Aerogel->SetMaterialPropertiesTable(mptAerogel);
   worldMat->SetMaterialPropertiesTable(mptWorld);



   //G4Box * solidWorld =  new G4Box("SolidWorld",0.5*m,0.5*m,0.5*m); 
   //G4Box * solidWorld =  new G4Box("SolidWorld",xWorld,yWorld,zWorld); 
   solidWorld =  new G4Box("SolidWorld",xWorld,yWorld,zWorld); 

   logicalWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");

   physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalWorld,"physWolrd",0,false,0,true); 


   if(isCherenkov)
      ConstrcutCherekov();

   if(isScintillator)
      ConstrcutScintillator();


   return physWorld;
}

//void ConstructSDandField()
void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector* senDet = new MySensitiveDetector("Test");
  if(isCherenkov)
  logicDetector->SetSensitiveDetector(senDet); 
}
	

//}   
