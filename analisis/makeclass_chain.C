{
TChain chain("SiTelescope") ;
chain->Add("/mnt/ext_drive/simulaciones/geant4/EXL_v0/tree_run_0.root");
chain->GetListOfFiles()->Print();
chain->MakeClass("simClassEXL");
} 
