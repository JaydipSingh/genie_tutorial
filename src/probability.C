

void probability()
{
    
    ifstream f1;
    ofstream f2;
    ofstream f3;
    
    f1.open("DUNE-numu-NDFlux.dat");
    f2.open("DUNE-numu-FDflux.dat"); 
    f3.open("prob3.dat");

    Double_t  px1, px2, px3;
    
    while(f1>>px1)
    {
        f1>>px2;
       
        if(px1<=20.0)
         
         {

     double theta23=0.866, theta13=0.150, theta12=0.5903, l=1285, delta_cp1=-90, delta_cp2=0, delta_cp3=90, delta31_square= 2.525e-3,  delta21_square=7.39e-5, rho=2.848;
     double delta31,delta21,a;
     delta31 = 1.267*delta31_square*l/px1;
     delta21=1.267*delta21_square*l/px1;
     a= rho/(3500*3.0);
     double deltaM2_32 = 2.451e-3;
  // cout<<delta21<<"\t"<<delta31<<endl;
            
           
 
// Double_t Prob= pow(sin(theta23),2)*pow(sin(2*theta13),2)*(pow(sin(delta31-a*l),2)/pow((delta31-a*l),2))*delta31_square+ sin(2*theta23)*sin(2*theta13)*sin(2*theta12)*(sin(delta31-a*l)/(delta31-a*l))*delta31*(sin(a*l)/(a*l))*delta21*cos(delta31+delta_cp) + pow(cos(theta23),2)*pow(sin(2*theta12),2)*(pow(sin(a*l),2)/pow((a*l),2))*delta21;
          

 Double_t Prob_mue1 = pow(sin(theta23),2)*pow(sin(2*theta13),2)*(pow(sin(delta31-a*l),2)*delta31*delta31/pow((delta31-a*l),2))+ sin(2*theta23)*sin(2*theta13)*sin(2*theta12)*(sin(delta31-a*l)*delta31/(delta31-a*l))*(sin(a*l)/(a*l))*delta21*cos(delta31+delta_cp1) + pow(cos(theta23),2)*pow(sin(2*theta12),2)*(pow(sin(a*l),2)*delta21*delta21/pow((a*l),2));
          
Double_t Prob_mue2 = pow(sin(theta23),2)*pow(sin(2*theta13),2)*(pow(sin(delta31-a*l),2)*delta31*delta31/pow((delta31-a*l),2))+ sin(2*theta23)*sin(2*theta13)*sin(2*theta12)*(sin(delta31-a*l)*delta31/(delta31-a*l))*(sin(a*l)/(a*l))*delta21*cos(delta31+delta_cp2) + pow(cos(theta23),2)*pow(sin(2*theta12),2)*(pow(sin(a*l),2)*delta21*delta21/pow((a*l),2));
          
Double_t Prob_mue3 = pow(sin(theta23),2)*pow(sin(2*theta13),2)*(pow(sin(delta31-a*l),2)*delta31*delta31/pow((delta31-a*l),2))+ sin(2*theta23)*sin(2*theta13)*sin(2*theta12)*(sin(delta31-a*l)*delta31/(delta31-a*l))*(sin(a*l)/(a*l))*delta21*cos(delta31+delta_cp3) + pow(cos(theta23),2)*pow(sin(2*theta12),2)*(pow(sin(a*l),2)*delta21*delta21/pow((a*l),2));

     double  Posc_mutau = pow(sin(2*theta23),2) * pow(cos(theta13),4) * pow(sin(deltaM2_32 * l/(4*px1)*5.068),2);


        Double_t Prob_d1 = 1-Prob_mue1-Posc_mutau;

        Double_t Prob_d2 = 1-Prob_mue2-Posc_mutau;

        Double_t Prob_d3 = 1-Prob_mue3-Posc_mutau;
        //cout<<Prob_d3<<"\n";
        //cout<<Prob_d3<<"\n";
         //  Double_t Prob=1-0.98*pow(sin(2.65/px1),2);//disappearance IO

//cout<<Prob_mue3<<"\t"<<Posc_mutau<<endl;
          f2<<px1<<"\t"<<Prob_d3*px2<<endl;
          f3<<px1<<"\t"<<Prob_d3<<"\n";
          cout<<Prob_d3<<"\n";
        }
    }
   
    f1.close();
    f2.close();
    f3.close();
    
}
