#include <TMath.h>
#define MAXBIN 150  
void gen_Etheta_all(){
     TString filename;
     ifstream file1;
     TString target[4]={"H1","D2","He3","H3"};
     int kin[11]={0,1,2,3,4,5,7,9,11,13,15};

     for(int ii=0;ii<4;ii++){
       for(int jj=0;jj<11;jj++){
          if(ii==0&&jj>4)continue;
          filename=Form("%s_kin%d.txt",target[ii].Data(),kin[jj]);
          file1.open(Form("datafile/%s",filename.Data()));
     
          Double_t xbj[MAXBIN]={0.0},Q2[MAXBIN]={0.0};
          Ssiz_t from=0;
          TString content,tmp;
          int nn=0;
          while(tmp.ReadLine(file1)){
                if(nn==0){nn++;continue;}
                tmp.Tokenize(content,from,", ");
                tmp.Tokenize(content,from,", ");
                xbj[nn-1]=atof(content.Data());
                tmp.Tokenize(content,from,", ");
                Q2[nn-1]=atof(content.Data());
                nn++;
                from=0;
              }
          file1.close();
           
          Double_t Ep[MAXBIN]={0.0},theta[MAXBIN]={0.0};
          Double_t E0=10.589;
          Double_t M=0.938272;
          ofstream file;
          Ssiz_t pos=filename.Index(".");
          TString outfile=filename.Replace(pos,5,".inp",4);
	  outfile=Form("bin_avg/%s",outfile.Data());
          file.open(outfile);
          file<<"Marathon"<<endl;    
          file<<filename.Data()<<endl;    
          file<<endl;    
          file<<endl;    
          file<<endl;    
          file<<"E    Ep    theta"<<endl;    
          for(int ii=0;ii<MAXBIN;ii++){
              if(xbj[ii]==0.0)continue;
              Ep[ii]=E0-Q2[ii]/(2.0*M*xbj[ii]);
              theta[ii]=asin(sqrt(Q2[ii]/(4.0*E0*Ep[ii])))*2*180/TMath::Pi();
              file<<fixed<<setprecision(3)<<E0<<" "<<fixed<<setprecision(4)<<Ep[ii]<<" "<<theta[ii]<<endl;
          }
          file.close();
       }
     }

}
