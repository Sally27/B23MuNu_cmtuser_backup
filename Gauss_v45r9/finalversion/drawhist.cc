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
  DataSample hist1("/home/hep/ss4314/cmtuser/Gauss_v45r9/finalversion/tau10e_26maxwidth1085mass2p5gev/massplayagain1.root", "KstarMass");
 
   
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
  TH1F* a = new TH1F("KstarMassfinal2", "KstarMassfinal2", 100, -10 , 6000);
  hist1.t->Draw("KstarMassfinal >> KstarMassfinal2");
  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/
  
 DataSample hist2("/home/hep/ss4314/cmtuser/Gauss_v45r9/finalversion/tau10e_26maxwidth2085mass3gev/massplayagain2.root", "KstarMass");
  TH1F* b = new TH1F("KstarMassfinal3", "KstarMassfinal3", 100, -10 , 6000);
  hist2.t->Draw("KstarMassfinal >> KstarMassfinal3");
 
 DataSample hist3("/home/hep/ss4314/cmtuser/Gauss_v45r9/finalversion/tau10e_30maxwidth1085mass2p5gev/massplayagain3.root", "KstarMass");
  TH1F* c = new TH1F("KstarMassfinal4", "KstarMassfinal4", 100, -10 , 6000);
  hist3.t->Draw("KstarMassfinal >> KstarMassfinal4");

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
 
  

   c->SetTitle("Kstar mass ");
   c->SetXTitle("Mass(Mev/c^2)");
   c->SetYTitle("NEvents");
   c->Draw();
   
   b->SetLineColor(2);
   b->Draw("same");
 
   a->SetLineColor(3);
   a->Draw("same");
    
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
    leg->AddEntry(b,"Kstar mass tau10e_26maxwidth2085mass3gev","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(a,"Kstar mass tau10e_26maxwidth1085mass2p5gev","l");
    leg->AddEntry(c,"Kstar mass tau10e_30maxwidth1085mass2p5gev","l");
 
/*    leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos","l");
 *    */
    leg->Draw("same");

   
/*   mp3->Update();*/
   mp3->SaveAs("new5.pdf");
 
   return;
  
}
