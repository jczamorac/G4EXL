{
gStyle->SetPalette(1);
gROOT->ProcessLine(".L $ROOTSYS/lib/libPhysics.so");
cout << "*********Se esta rodando Programa tree2histo.C*************\n";
gROOT->ProcessLine(".L simClassEXL.C++");
gROOT->ProcessLine(".L simClassEXL_C.so");
gROOT->ProcessLine("simClassEXL simEXL");
}
