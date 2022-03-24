#include "construction.hh"
//#include "detector.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
   fMessenger = new G4GenericMessenger(this,"/detector/","Detector Construction");
   fMessenger->DeclareProperty("nCols",nCols,"Number of columns");
   fMessenger->DeclareProperty("nRows",nRows,"Number of rows");
   fMessenger->DeclareProperty("isCherenkov",isCherenkov,"Toggle Cherenkov setup");
   fMessenger->DeclareProperty("isScintillator",isScintillator,"Toggle isScintillator setup");
   fMessenger->DeclareProperty("tof",isTOF,"Construct Time of Flight");
   
   
   nCols=100;
   nRows=100;

   DefineMaterials();

   xWorld = 5*m;
   yWorld = 5*m;
   zWorld = 5*m;

   isCherenkov = false;
   isScintillator = false;
   isTOF = true;  
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
   G4double rindexNaI[2] = {1.78, 1.78};

   mptAerogel = new G4MaterialPropertiesTable();
   mptAerogel->AddProperty("RINDEX",energy,rindexAerogel,2);

   mptWorld = new G4MaterialPropertiesTable();
   mptWorld->AddProperty("RINDEX",energy,rindexWorld,2 );

   G4double fraction[2] = {1.0, 1.0};

   G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
   mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
   mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 2);
   mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
   mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
   mptNaI->AddConstProperty("FASTTIMECONSTANT", 250.*ns);
   mptNaI->AddConstProperty("YIELDRATIO",1.);
   NaI->SetMaterialPropertiesTable(mptNaI);


   mirrorSurface = new G4OpticalSurface("mirrorSurface");

    G4double reflectivity[2] = {1.0, 1.0};
   G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
   mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
   mirrorSurface->SetMaterialPropertiesTable(mptMirror);
   mirrorSurface->SetType(dielectric_metal);
   mirrorSurface->SetFinish(ground);
   mirrorSurface->SetModel(unified);


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
//   solidScintillator = new G4Tubs("solidScintillator",10*cm,20*cm,30*cm,0*deg,360*deg);
     solidScintillator = new G4Box("solidScintillator", 5*cm, 5*cm, 6*cm);
     logicalScintillator = new G4LogicalVolume(solidScintillator,NaI,"logicalScintillaotr");

     G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicalWorld, mirrorSurface);

     solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6*cm);
     logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
     fScoringVolume = logicalScintillator;

 for(G4int i = 0; i < 6; i++)
   {
     for(G4int j = 0; j < 16; j++)
      {
            G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));
            G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm, 0.*cm, -40.*cm + i*15*cm));
            G4Transform3D transformScint = (rotZ)*(transXScint);

            G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm+6.*cm, 0.*cm, -40.*cm + i*15*cm));
            G4Transform3D transformDet = (rotZ)*(transXDet);

            physScintillator = new G4PVPlacement(transformScint, logicalScintillator, "physScintillator", logicalWorld, false, 0, true);
            //physScintillator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalScintillator,"physScintillaotr",logicalWorld,false,0,true);  

            physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", logicalWorld, false, 0, true);
      }
   }

}



void MyDetectorConstruction::ConstructTOF()
{
    solidDetector = new G4Box("solidDetector", 1.*m, 1.*m, 0.1*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, -4.*m), logicDetector, "physDetector", logicalWorld, false, 0, true);

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 3.*m), logicDetector, "physDetector", logicalWorld, false, 1, true);
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

   if(isTOF)
      ConstructTOF();

   return physWorld;
}

//void ConstructSDandField()
void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector* senDet = new MySensitiveDetector("Test");
//  if(isCherenkov)
  if(logicDetector != NULL)
  logicDetector->SetSensitiveDetector(senDet); 
}
	

//}   
