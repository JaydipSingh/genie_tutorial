//____________________________________________________________________________
/*
Jaydip Singh Developed for the ND group proposal( STT ) 
Date : 20/03/2015 
Prof. Sanjib Mishra
*/

#include <string>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TIterator.h>
#include <TCanvas.h>


#include "Framework/EventGen/EventRecord.h"
#include "Framework/GHEP/GHepParticle.h"
#include "Framework/Ntuple/NtpMCFormat.h"
#include "Framework/Ntuple/NtpMCTreeHeader.h"
#include "Framework/Ntuple/NtpMCEventRecord.h"
#include "Framework/Messenger/Messenger.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/Utils/CmdLnArgParser.h"



#include <fstream>
using namespace std;

using std::string;
using namespace genie;

void GetCommandLineArgs (int argc, char ** argv);

int    gOptNEvt;
string gOptInpFilename;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  GetCommandLineArgs (argc, argv);

  //-- open the ROOT file and get the TTree & its header
  TTree *           tree = 0;
  NtpMCTreeHeader * thdr = 0;

  TFile file(gOptInpFilename.c_str(),"READ");

  tree = dynamic_cast <TTree *>           ( file.Get("gtree")  );
  thdr = dynamic_cast <NtpMCTreeHeader *> ( file.Get("header") );

     TCanvas *c1 = new TCanvas("c1", "", 700, 600);

     TH1D *p_mu = new TH1D("p_mu","Muons Momentum",40,0,2); // Event/ 100 MeV Bins 
     TH1D *p_had = new TH1D("p_had","Hadrons Momentum",40,0,2);
     TH1D *p_cal = new TH1D("p_cal","Cal-Reco Neutino Energy",40,0,2);
     TH1D *h_q2 = new TH1D("h_q2","Momentum transfer (Q^{2})",20,0,1); // Event/10 Mev Bins
     TH1D *h_Erec_ccqe = new TH1D("h_Erec_ccqe","Kin-Reco Neutrino Energy",40,0,2);
     TH1D *hN_Etrue = new TH1D("hN_Etrue","Neutrons Kinatic Energy",40,0,1);
     TH1D *h_RNeutNu = new TH1D("h_RNeutNu","Fractionl Neutron Energy",100,0,1); 
     TH1D *h_RNHadNu = new TH1D("h_RNHadNu","Fractionl Hadrons Energy",100,0,1);
  if(!tree) return 1;

     NtpMCEventRecord * mcrec = 0;
     tree->SetBranchAddress("gmcrec", &mcrec);

  int nev = (gOptNEvt > 0) ?
        TMath::Min(gOptNEvt, (int)tree->GetEntries()) :
        (int) tree->GetEntries();

  //
  // Loop over all events
  //
  for(int i = 0; i < nev; i++) {

    // get next tree entry
    tree->GetEntry(i);

    // get the GENIE event
    EventRecord &  event = *(mcrec->event);

    LOG("GENIE Info : ", pNOTICE) << event;

                  // get the neutrino, f/s primary lepton and hit
// nucleon event record entries
//
          GHepParticle * neu = event.Probe();
          GHepParticle * fsl = event.FinalStatePrimaryLepton();
          GHepParticle * nuc = event.HitNucleon();
// the hit nucleon may not be defined
// (eg. for coherent, or ve- events)
//
      //     if(!nuc) return 0;  // comment/uncomment in COH process is required for your analysis

    
          double M = .938;
          double phad= 0.0, Erec_ccqe=0.00;
          double pmu= 0.0, ENeutron = 0.00, ENHad = 00;
          double pz= 0.0,px=0.0,py=0.0,pxh=0.0,pyh=0.0,pzh=0.0;

    //
    // Loop over all particles in this event
    //

    GHepParticle * pmc = 0;
    TIter event_iter(&event);

    while((pmc=dynamic_cast<GHepParticle *>(event_iter.Next())))
    {

       if (pmc->Status() == kIStStableFinalState ) {



        //if (p_genie->Pdg() == kPdgPi0 || p_genie->Pdg() == kPdgPiP || p_genie->Pdg() == kPdgPiM)
	  
           {   if ( (pmc->Pdg() == kPdgMuon || pmc->Pdg() == kPdgAntiMuon) && ((pmc->E()-0.1056)>.350) )
                                  { pmu= pmu + sqrt(pmc->Px()*pmc->Px()+pmc->Py()*pmc->Py()+pmc->Pz()*pmc->Pz());
			                                                             pz=pz+pmc->Pz();
			                                                             py=py+pmc->Py();
			                                                             px=px+pmc->Px();
                                                                                     Erec_ccqe = (1.81912*pmu+0.0418939)/(2*(0.909-pmu+pz));}
                 else
                        if (pmc->Pdg() == kPdgPi0 || pmc->Pdg() == kPdgPiP || pmc->Pdg() == kPdgPiM & (pmc->E()-0.1380)>.080)
                   			 {phad= phad + sqrt(pmc->Px()*pmc->Px()+pmc->Py()*pmc->Py()+pmc->Pz()*pmc->Pz());
					   pxh=pxh+pmc->Px();
					   pyh=pyh+pmc->Py();
					   pzh=pzh+pmc->Pz();
                                           cout<<"PiD=\t"<<pmc->Pdg()<<"\tPhad = \t "<<phad<<"\n";
                                      if(pmc->Pdg() == kPdgNeutron ){ ENeutron=(ENeutron+((pmc->E())-.939));}
                                      if(pmc->Pdg() == kPdgPi0 || pmc->Pdg() == kPdgNeutron) { ENHad= ENeutron + ENHad + ((pmc->E())-.135);}  
                        }//  phad

          }
       }

    }// end loop over particles	
              
	
        double Pvis = sqrt((px+pxh)*(px+pxh)+(py+pyh)*(py+pyh)+(pz+pzh)*(pz+pzh)); // hadrons + muon component 
        double Pcal = sqrt(pxh*pxh+pyh*pyh+pzh*pzh);                               // Only hadronic component  
        double Q2 = 2*Pvis*(sqrt(px*px+py*py+pz*pz)-pz);
        double Ybj= Pcal/Pvis; 
        double Xbj= Q2/(2*M*Pcal);
        double mPT= sqrt((px+pxh)*(px+pxh)+(py+pyh)*(py+pyh));// Missing Energy
        cout<<"Pcal="<<"\t"<<Pcal<<"\tPvis=\t"<<Pvis<<"\tXbj=\t"<<Xbj<<"\tW2=\t"<<M*M+2*M*(Pvis-pmu)-Q2<<"\tYbj=\t"<<Ybj<<"\tQ2=\t"<<Q2<<"\ts=\t"<<(Q2/(Xbj*Ybj))+M*M<<"\n"; 
       p_mu->Fill(pmu); 
       p_had->Fill(Pcal);
       p_cal->Fill(Pvis);
       h_q2->Fill(Q2);
       h_Erec_ccqe->Fill(Erec_ccqe);
      if(ENeutron)hN_Etrue->Fill(ENeutron);
      if(ENeutron) h_RNeutNu->Fill(ENeutron/neu->E());
      if(ENHad)h_RNHadNu->Fill(ENHad/neu->E());
   
   // Clear all the variables // 
    
     phad = 0.0, pmu=0.0,px=0.0,py=0.0,pz=0.0,pxh=0.0,pyh=0.0,pzh=0.0,Ybj=0.0, Erec_ccqe=0.00, ENeutron=0.0, ENHad=0.00;
    
    // clear current mc event record
  
       mcrec->Clear();

    // REset Histogrames // 

       p_mu->GetXaxis()->SetTitle("P_{\mu} (GeV)");
       p_mu->GetYaxis()->CenterTitle();
       p_mu->GetYaxis()->SetTitleOffset(1.3);
       p_mu->GetXaxis()->CenterTitle();
 
       p_had->GetXaxis()->SetTitle("P_{had} (GeV)");
       p_had->GetYaxis()->CenterTitle();
       p_had->GetYaxis()->SetTitleOffset(1.3);
       p_had->GetXaxis()->CenterTitle();

       p_cal->GetXaxis()->SetTitle("P_{cal} (GeV)");
       p_cal->GetYaxis()->CenterTitle();
       p_cal->GetYaxis()->SetTitleOffset(1.3);
       p_cal->GetXaxis()->CenterTitle();
    
       h_q2->GetXaxis()->SetTitle("Q2 (GeV/c)^2");
       h_q2->GetYaxis()->CenterTitle();
       h_q2->GetYaxis()->SetTitleOffset(1.3);
       h_q2->GetXaxis()->CenterTitle();


       h_Erec_ccqe->GetXaxis()->SetTitle("E_{rec} (GeV)");
       h_Erec_ccqe->GetYaxis()->CenterTitle();
       h_Erec_ccqe->GetYaxis()->SetTitleOffset(1.3);
       h_Erec_ccqe->GetXaxis()->CenterTitle();

       hN_Etrue->GetXaxis()->SetTitle("E_{Kinatic} (GeV)");
       hN_Etrue->GetYaxis()->CenterTitle();
       hN_Etrue->GetYaxis()->SetTitleOffset(1.3);
       hN_Etrue->GetXaxis()->CenterTitle();

       h_RNeutNu->GetXaxis()->SetTitle("RNeutNu");
       h_RNeutNu->GetYaxis()->CenterTitle();
       h_RNeutNu->GetYaxis()->SetTitleOffset(1.3);
       h_RNeutNu->GetXaxis()->CenterTitle();

       h_RNHadNu->GetXaxis()->SetTitle("RNHadNu");
       h_RNHadNu->GetYaxis()->CenterTitle();
       h_RNHadNu->GetYaxis()->SetTitleOffset(1.3);
       h_RNHadNu->GetXaxis()->CenterTitle();
  
        TFile Ana_File("EventHisto.root","RECREATE");
         p_mu->Write();
         p_had->Write();
         p_cal->Write();
         h_q2->Write();
         h_Erec_ccqe->Write();
         hN_Etrue->Write();
         h_RNeutNu->Write();
         h_RNHadNu->Write();
    /*  p_mu->Draw("hist");
    c1->SaveAs("EnergyTransfer.png");*/

   
    } //end loop over events

  // close input GHEP event file
  file.Close();
  LOG("myAnalysis", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________
void GetCommandLineArgs(int argc, char ** argv)
{
  LOG("myAnalysis", pINFO) << "Parsing commad line arguments";

  CmdLnArgParser parser(argc,argv);

  // get GENIE event sample
  if( parser.OptionExists('f') ) {
    LOG("myAnalysis", pINFO) 
       << "Reading event sample filename";
    gOptInpFilename = parser.ArgAsString('f');
  } else {
    LOG("myAnalysis", pFATAL) 
        << "Unspecified input filename - Exiting";
    exit(1);
  }

  // number of events to analyse
  if( parser.OptionExists('n') ) {
    LOG("myAnalysis", pINFO) 
      << "Reading number of events to analyze";
    gOptNEvt = parser.ArgAsInt('n');
  } else {
    LOG("myAnalysis", pINFO)
      << "Unspecified number of events to analyze - Use all";
    gOptNEvt = -1;
  }
}
//_________________________________________________________________________________
