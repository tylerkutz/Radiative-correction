#include <fstream>
#include "ReadFile.h"
using namespace std;

void plot_H3D()
{
     Double_t D2_x[11][MAXBIN],D2_Q2[11][MAXBIN],D2_Born[11][MAXBIN],D2_Rad[11][MAXBIN],D2_Born1[11][MAXBIN],D2_Rad1[11][MAXBIN];
     Double_t H3_x[11][MAXBIN],H3_Q2[11][MAXBIN],H3_Born[11][MAXBIN],H3_Rad[11][MAXBIN],H3_Born1[11][MAXBIN],H3_Rad1[11][MAXBIN];
     Double_t D2_Born2[11][MAXBIN],D2_Rad2[11][MAXBIN],H3_Born2[11][MAXBIN],H3_Rad2[11][MAXBIN];
     Double_t H3D_RC[11][MAXBIN],H3D_RC1[11][MAXBIN],H3D_RC2[11][MAXBIN];
     Double_t H3D_ratio[11][MAXBIN],H3D_ratio1[11][MAXBIN];
     Double_t D2_Yield[11][MAXBIN],D2_Yerr[11][MAXBIN]; 
     Double_t H3_Yield[11][MAXBIN],H3_Yerr[11][MAXBIN]; 
     Double_t H3D_data[11][MAXBIN],H3D_dataerr[11][MAXBIN]; 

     for(int ii=0;ii<11;ii++){
	 for(int jj=0;jj<MAXBIN;jj++){
             D2_x[ii][jj]=0.0; D2_Q2[ii][jj]=0.0; D2_Born[ii][jj]=0.0; D2_Rad[ii][jj]=0.0;D2_Born1[ii][jj]=0.0; D2_Rad1[ii][jj]=0.0;
             H3_x[ii][jj]=0.0; H3_Q2[ii][jj]=0.0; H3_Born[ii][jj]=0.0; H3_Rad[ii][jj]=0.0;H3_Born1[ii][jj]=0.0; H3_Rad1[ii][jj]=0.0;
	     D2_Born2[ii][jj]=0.0;  D2_Rad2[ii][jj]=0.0; 
	     H3_Born2[ii][jj]=0.0; H3_Rad2[ii][jj]=0.0; 
             H3D_RC[ii][jj]=0.0;H3D_RC1[ii][jj]=0.0; H3D_RC2[ii][jj]=0.0;
	     H3D_ratio[ii][jj]=0.0; H3D_ratio1[ii][jj]=0.0;
             D2_Yield[ii][jj]=0.0;  D2_Yerr[ii][jj]=0.0; 
     	     H3_Yield[ii][jj]=0.0;  H3_Yerr[ii][jj]=0.0; 
             H3D_data[ii][jj]=0.0;   H3D_dataerr[ii][jj]=0.0; 
     }}

   TString Yfile;
   int kin[11]={0,1,2,3,4,5,7,9,11,13,15};
   for(int ii=0;ii<11;ii++){
       Yfile=Form("model111/H3_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],H3_x,H3_Q2,H3_Born,H3_Rad); 
       Yfile=Form("model122_AllRes/H3_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],H3_x,H3_Q2,H3_Born1,H3_Rad1); 
       Yfile=Form("model411/H3_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],H3_x,H3_Q2,H3_Born2,H3_Rad2); 

       Yfile=Form("model111/D2_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],D2_x,D2_Q2,D2_Born,D2_Rad);
       Yfile=Form("model122_AllRes/D2_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],D2_x,D2_Q2,D2_Born1,D2_Rad1);
       Yfile=Form("model411/D2_kin%d_xs.out",kin[ii]);
       ReadYield(Yfile,kin[ii],D2_x,D2_Q2,D2_Born2,D2_Rad2);

       Yfile=Form("D2_kin%d.txt",kin[ii]);
       ReadData(Yfile,kin[ii],D2_Yield,D2_Yerr);
       Yfile=Form("H3_kin%d.txt",kin[ii]);
       ReadData(Yfile,kin[ii],H3_Yield,H3_Yerr);
   }

   TGraph *hborn=new TGraph();
   TGraph *hrad=new TGraph();
   TGraph *hRC=new TGraph();
   TGraph *hborn1=new TGraph();
   TGraph *hrad1=new TGraph();
   TGraph *hRC1=new TGraph();
   TGraph *hborn2=new TGraph();
   TGraph *hrad2=new TGraph();
   TGraph *hRC2=new TGraph();
   TGraph *hratio=new TGraph();
   TGraph *hratio1=new TGraph();
    
   int nn=0;
   for(int ii=0;ii<11;ii++){
       for(int jj=0;jj<MAXBIN;jj++){
	   if(H3_x[ii][jj]==0)continue;
           if(abs(H3_x[ii][jj]-D2_x[ii][jj])>0.001)continue;
           hborn->SetPoint(nn,H3_x[ii][jj],H3_Born[ii][jj]/D2_Born[ii][jj]);
           hrad->SetPoint(nn,H3_x[ii][jj],H3_Rad[ii][jj]/D2_Rad[ii][jj]);
           if(H3_Rad[ii][jj]>0&&D2_Rad[ii][jj]>0)H3D_RC[ii][jj]=(H3_Born[ii][jj]/H3_Rad[ii][jj])/(D2_Born[ii][jj]/D2_Rad[ii][jj]);
           hRC->SetPoint(nn,H3_x[ii][jj],H3D_RC[ii][jj]);

           hborn1->SetPoint(nn,H3_x[ii][jj],H3_Born1[ii][jj]/D2_Born1[ii][jj]);
           hrad1->SetPoint(nn,H3_x[ii][jj],H3_Rad1[ii][jj]/D2_Rad1[ii][jj]);
           if(H3_Rad1[ii][jj]>0&&D2_Rad1[ii][jj]>0)H3D_RC1[ii][jj]=(H3_Born1[ii][jj]/H3_Rad1[ii][jj])/(D2_Born1[ii][jj]/D2_Rad1[ii][jj]);
           hRC1->SetPoint(nn,H3_x[ii][jj],H3D_RC1[ii][jj]);

           hborn2->SetPoint(nn,H3_x[ii][jj],H3_Born2[ii][jj]/D2_Born2[ii][jj]);
           hrad2->SetPoint(nn,H3_x[ii][jj],H3_Rad2[ii][jj]/D2_Rad2[ii][jj]);
           if(H3_Rad2[ii][jj]>0&&D2_Rad2[ii][jj]>0)H3D_RC2[ii][jj]=(H3_Born2[ii][jj]/H3_Rad2[ii][jj])/(D2_Born2[ii][jj]/D2_Rad2[ii][jj]);
           hRC2->SetPoint(nn,H3_x[ii][jj],H3D_RC2[ii][jj]);

           if(H3D_RC1[ii][jj]>0)H3D_ratio[ii][jj]=H3D_RC[ii][jj]/H3D_RC1[ii][jj];
           hratio->SetPoint(nn,H3_x[ii][jj],H3D_ratio[ii][jj]);
	
           if(H3D_RC2[ii][jj]>0)H3D_ratio1[ii][jj]=H3D_RC[ii][jj]/H3D_RC2[ii][jj];
           hratio1->SetPoint(nn,H3_x[ii][jj],H3D_ratio1[ii][jj]);

           nn++;
       }
   } 

//   ofstream outfile;
//   outfile.open("H3D_ratio.csv");
   TGraphErrors *gH3DRaw[11];
   TGraphErrors *gH3D[11];
   for(int ii=0;ii<11;ii++){
       gH3DRaw[ii]=new TGraphErrors();
       gH3D[ii]=new TGraphErrors();
       int nn=0;
       for(int jj=0;jj<MAXBIN;jj++){
          if(H3_x[ii][jj]==0||D2_x[ii][jj]==0)continue;
          H3D_data[ii][jj]=H3_Yield[ii][jj]/D2_Yield[ii][jj];
          H3D_dataerr[ii][jj]=H3D_data[ii][jj]*sqrt(pow(H3_Yerr[ii][jj]/H3_Yield[ii][jj],2)+pow(D2_Yerr[ii][jj]/D2_Yield[ii][jj],2));
          if(H3D_dataerr[ii][jj]>0.1)continue;
          gH3DRaw[ii]->SetPoint(nn,H3_x[ii][jj],H3D_data[ii][jj]);
          gH3DRaw[ii]->SetPointError(nn,0.0,H3D_dataerr[ii][jj]);

	  Double_t tmp_ratio=H3D_data[ii][jj]*H3D_RC1[ii][jj];
	  Double_t tmp_err=H3D_dataerr[ii][jj]*H3D_RC1[ii][jj];
 	  gH3D[ii]->SetPoint(nn,H3_x[ii][jj],tmp_ratio);
 	  gH3D[ii]->SetPointError(nn,0.0,tmp_err);

//	  outfile<<H3_x[ii][jj]<<","<<H3_Q2[ii][jj]<<","<<tmp_ratio<<","<<tmp_err<<endl;
          nn++;
      }
   }
//   outfile.close();

   TCanvas *c1=new TCanvas("c1","c1",1500,1500);
   TMultiGraph *mg1=new TMultiGraph();
   hborn->SetMarkerStyle(8);
   hborn->SetMarkerColor(2);
   hborn1->SetMarkerStyle(8);
   hborn1->SetMarkerColor(4);
   hborn2->SetMarkerStyle(8);
   hborn2->SetMarkerColor(1);
   mg1->Add(hborn);
   mg1->Add(hborn1);
   mg1->Add(hborn2);
   mg1->Draw("AP");
   mg1->SetTitle("H3/D born cross section ratio;xbj;born");

   auto leg1=new TLegend(0.7,0.6,0.85,0.85);
   leg1->AddEntry(hborn,"model111","P");
   leg1->AddEntry(hborn1,"model111_noResAll","P");
   leg1->AddEntry(hborn2,"model111_ResOnlyD2H1","P");
   leg1->Draw();

   TCanvas *c3=new TCanvas("c3","c3",1500,1500);
   TMultiGraph *mg2=new TMultiGraph();
   hrad->SetMarkerStyle(8);
   hrad->SetMarkerColor(4);
   hrad1->SetMarkerStyle(8);
   hrad1->SetMarkerColor(8);
   hrad2->SetMarkerStyle(8);
   hrad2->SetMarkerColor(1);
   int color[11]={1,2,3,4,5,6,7,8,9,46,30};
   for(int ii=0;ii<11;ii++){
       gH3DRaw[ii]->SetMarkerStyle(22);
       gH3DRaw[ii]->SetMarkerColor(color[ii]);
       gH3D[ii]->SetMarkerStyle(8);
       gH3D[ii]->SetMarkerColor(color[ii]);
       mg2->Add(gH3DRaw[ii]);
       mg2->Add(gH3D[ii]);
   }
//   mg2->Add(hrad);
//   mg2->Add(hrad1);
   mg2->Draw("AP");
   mg2->SetTitle("H3/D rad cross section ratio;xbj;rad");

   auto leg2=new TLegend(0.7,0.6,0.85,0.85);
   leg2->AddEntry(hrad,"model111","P");
   leg2->AddEntry(hrad1,"model122_AllRes","P");
   leg2->AddEntry(hrad2,"model411","P");
   leg2->Draw();

   TCanvas *c2=new TCanvas("c2","c2",1500,1500);
   c2->Divide(2,1);
   c2->cd(1);
   TMultiGraph *mg3=new TMultiGraph();
   hRC->SetMarkerStyle(8);
   hRC->SetMarkerColor(2);
   hRC1->SetMarkerStyle(8);
   hRC1->SetMarkerColor(4);
   hRC2->SetMarkerStyle(8);
   hRC2->SetMarkerColor(1);
   mg3->Add(hRC);
   mg3->Add(hRC1);
   mg3->Add(hRC2);
   mg3->Draw("AP");
   mg3->SetTitle("H3/D RC=born/rad ratio;xbj;RC");

   auto leg3=new TLegend(0.7,0.6,0.85,0.85);
   leg3->AddEntry(hRC,"model111","P");
   leg3->AddEntry(hRC1,"model122_AllRes","P");
   leg3->AddEntry(hRC2,"model411","P");
   leg3->Draw();

   c2->cd(2);
   TMultiGraph *mg4=new TMultiGraph();
   hratio->SetMarkerStyle(8);
   hratio->SetMarkerColor(4);
   hratio1->SetMarkerStyle(8);
   hratio1->SetMarkerColor(2);
   mg4->Add(hratio);
   mg4->Add(hratio1);
   mg4->Draw("AP");
   mg4->SetTitle("H3/D RC ratio between models;xbj;");

   auto leg4=new TLegend(0.7,0.6,0.811,0.811);
   leg4->AddEntry(hratio,"model111/model122_AllRes","P");
   leg4->AddEntry(hratio1,"model111/model411","P");
   leg4->Draw();



}
