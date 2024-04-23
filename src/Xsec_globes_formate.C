//filename: XCCGenieArXsec.dat- cross section is not divided by energy
//filename: XCCGenieAr.dat - cross section is divided by energy


#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

void Xsec_globes_formate()
{
   TFile file("dune10GeVallflaverAr40.root","read");
   ofstream f1;
   f1.open("XCCGenieArXsecNodivideE.dat");
   
   Double_t i=0.1,ii=0.0,iid=0.0,iii=0.0,iiii=0.0,p[10000]={0.0},q[20000]={0.0},pp[100]={0.0},ppd[100]={0.0},qqd[100]={0.0},qq[200]={0.0},ppp[100]={0.0},qqq[200]={0.0},
   pppp[100]={0.0},qqqq[200]={0.0};
   int s=0,ss=0,ssd=0,sss=0,ssss=0;
     
   TCanvas *c1 = new TCanvas("c1","Muons flux variation with zenith angle",0,0,1000,800);
   TDirectory *dir = (TDirectory*) file.Get("nu_e_Ar40");
   TDirectory *dir1 = (TDirectory*) file.Get("nu_mu_Ar40");
    TDirectory *dir2 = (TDirectory*) file.Get("nu_tau_Ar40");
   TDirectory *dir3 = (TDirectory*) file.Get("nu_e_bar_Ar40");
    TDirectory *dir4 = (TDirectory*) file.Get("nu_mu_bar_Ar40");
   TDirectory *dir5 = (TDirectory*) file.Get("nu_tau_bar_Ar40");
   TGraph * graph = (TGraph*) dir->Get("tot_cc");
   TGraph * graph1 = (TGraph*) dir1->Get("tot_cc");
   TGraph * graph2 = (TGraph*) dir2->Get("tot_cc");
   TGraph * graph3 = (TGraph*) dir3->Get("tot_cc");
   TGraph * graph4 = (TGraph*) dir4->Get("tot_cc");
   TGraph * graph5 = (TGraph*) dir5->Get("tot_cc");
    // c1->Divide(2,2);
   while(i<=10.10)
     { 
   //   cout <<log(i)/log(10)<<"\t"<<graph->Eval(i)/(i*40)<<"\t"<<graph1->Eval(i)/(i*40)<<"\t"<<graph2->Eval(i)/(i*40)<<"\t"<<graph3->Eval(i)/(i*40)<<"\t"
   //   <<graph4->Eval(i)/(i*40)<<"\t"<<graph5->Eval(i)/(i*40)<< "\t"<<endl;
//  f1<<log(i)/log(10)<<"\t"<<graph->Eval(i)/(i*40)<<"\t"<<graph1->Eval(i)/(i*40)<<"\t"<<graph2->Eval(i)/(i*40)<<"\t"<<graph3->Eval(i)/(i*40)<<"\t"
   //   <<graph4->Eval(i)/(i*40)<<"\t"<<graph5->Eval(i)/(i*40)<< "\t"<<endl;
  f1<<i<<"\t"<<graph->Eval(i)/(40)<<"\t"<<graph1->Eval(i)/(40)<<"\t"<<graph2->Eval(i)/(40)<<"\t"<<graph3->Eval(i)/(40)<<"\t"<<graph4->Eval(i)/(40)<<"\t"<<graph5->Eval(i)/(40)<<"\t"<<endl;    
         p[s]=i;
         q[s]=graph->Eval(i)/40;
       i=i+0.01;
       s++;
     }

       TGraph* gr = new TGraph(s-1,p,q);

  // gr1->SetTitle("Probability distribution for Neutrino in Matter");
   gr->SetMarkerColor(1);
   gr->SetLineWidth(2);
   gr->SetMarkerStyle(24);
   gr->SetMarkerSize(.5);
   gr->SetLineColor(5);
  //  c1->cd(1);
    gr->Draw("AC*");

    

      leg = new TLegend(0.4,0.2,0.28,0.4);
   //leg->SetHeader("Mu+ identification");
   leg->AddEntry(gr,"tot_CCQE","lp");
 
   leg->Draw();

}
