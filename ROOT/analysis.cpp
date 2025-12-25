#include <iostream> 
#include <cmath>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TVector3.h>
#include <TCanvas.h>
#include <TApplication.h>

int analysis(){
    TFile *file = new TFile("output.root");
    TTree *tree = (TTree*)file->Get("Hits");
    TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 700, 500);
    tree->Draw("X:Y:Z", "", "colz");
    c1->SaveAs("plot.png");
    TApplication *app = new TApplication("app", 0, 0);
    if(!app->IsRunning()){
        app->Run();
    }
    app->Terminate();
    return 0;
}