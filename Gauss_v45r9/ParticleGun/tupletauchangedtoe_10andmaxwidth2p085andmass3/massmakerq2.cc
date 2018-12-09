#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"

using namespace std;

class DataSample {
 public:
  DataSample(std::string filename, std::string treename) : _filename(filename), _treename(treename), f(NULL), t(NULL) 
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;
  TString _treename;  
  TFile *f;
  TTree *t;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
  t = (TTree*)f->Get(_treename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
	f->Close();
  delete f;
}

void hist()
{

  gStyle->SetOptStat(0);
  DataSample hist1("/home/hep/ss4314/cmtuser/Gauss_v45r9/ParticleGun/tupletauchangedtoe_10andmaxwidth2p085andmass3/masstupletauchangedtoe_26andmaxwidth2p085nomasschange.root", "KstarMass");
 
   
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
  TH1F* a = new TH1F("KstarMassfinal2", "KstarMassfinal2", 100, -10 , 6000);
  hist1.t->Draw("q2 >> KstarMassfinal2");
  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/
  
 DataSample hist2("/home/hep/ss4314/cmtuser/Gauss_v45r9/ParticleGun/tupletauchangedtoe_10andmaxwidth2p085andmass3/masstupletauchangedtoe_26andmaxwidth2p085andmass2.root", "KstarMass");
  TH1F* b = new TH1F("KstarMassfinal3", "KstarMassfinal3", 100, -10 , 6000);
  hist2.t->Draw("q2 >> KstarMassfinal3");
 
 DataSample hist3("/home/hep/ss4314/cmtuser/Gauss_v45r9/ParticleGun/tupletauchangedtoe_10andmaxwidth2p085andmass3/masstupletauchangedtoe_26andmaxwidth2p085andmass3.root", "KstarMass");
  TH1F* c = new TH1F("KstarMassfinal4", "KstarMassfinal4", 100, -10 , 6000);
  hist3.t->Draw("q2 >> KstarMassfinal4");

 DataSample hist4("/home/hep/ss4314/cmtuser/Gauss_v45r9/ParticleGun/tupletauchangedtoe_10andmaxwidth2p085andmass3/masstupletauchangedtoe_26andmaxwidth2p085andmass4.root", "KstarMass");
  TH1F* d = new TH1F("KstarMass_", "KstarMass_", 100, -10 , 6000);
  hist4.t->Draw("q2 >> KstarMass_");

/*
 * DataSample hist2("/home/hep/ss4314/Project/week23mar/finalsignal.root", "/B_Tuple/DecayTree");
 *    TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, -10 , 10000);
 *      hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
 *        double nSel2 = hist2.t->GetEntries();*/
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");
 *
 *    TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
 *      hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
 *        double nSel3 = hist3.t->GetEntries();
 *        */
   
 
   d->SetLineColor(1);
   d->Draw();

   d->SetTitle("q2 ");
   d->SetXTitle("Mass(Mev/c^2)");
   d->SetYTitle("NEvents");
   a->Draw("same");
   
   b->SetLineColor(2);
   b->Draw("same");
 
   c->SetLineColor(3);
   c->Draw("same");
    
/*   hm->SetLineColor(8);
 *      hm->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
 *         hm->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
 *            hm->SetYTitle("NCandidatesSel/NCandidatesGen"); 
 *               hm->Draw("same");*/

/*   ha->SetLineColor(8);
 *      ha->SetTitle("Efficiency");
 *         ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
 *            ha->SetYTitle("NCandidatesSel/NCandidatesGen");
 *               ha->Draw("same");*/
   
    Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.015);
    leg->AddEntry(b,"q2 mass with tau 10^-26 maxwidth 2.085 mass 2 Gev","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(a,"q2 mass with tau 10^-26 maxwidth 2.085 mass 0.89 Gev","l");
    leg->AddEntry(c,"q2 mass with tau 10^-26 maxwidth 2.085 mass 3 Gev","l");
    leg->AddEntry(d,"q2 mass with tau 10^-26 maxwidth 2.085 mass 4 Gev","l");
/*    leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos","l");
 *    */
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("newq2.pdf");
 
   return;
  
}
