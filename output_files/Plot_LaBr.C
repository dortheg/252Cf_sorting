#include <iostream>
#include <sstream>
#include <string>

void Plot_LaBr(){
	TFile *file = TFile::Open("28Si_test.root");

	TH2 *histograms[32];
	for(int i=0;i<=32;i++){
		std::ostringstream oss;
		oss << "energy_labr_" ;

		//Prefix 0 for i <=1 to 10
		if(i<10){
			oss << "0";
		}

		oss << i;

		auto name = oss.str().c_str();

		TH2 *histogram = (TH2 *)file->Get(name);

		histograms[i] = histogram;
		histogram->SetLineColor(i);
		histogram->Draw("SAME");
		histogram->GetXaxis()->SetLabelSize(0.037);
		histogram->GetYaxis()->SetLabelSize(0.037);
		histogram->GetYaxis()->SetTitleSize(0.040);
		histogram->GetXaxis()->SetTitleSize(0.040);
		histogram->GetZaxis()->SetLabelSize(0.037);
		gStyle->SetOptStat(0);
		histogram->SetTitle(" ");
		histogram->GetXaxis()->SetTitle("Energy [keV]");
		histogram->GetYaxis()->SetTitle("Counts/bin");

	}


	/*TH2 *energy_labr_01 = (TH2 *)file->Get("energy_labr_01");
	TH2 *energy_labr_02 = (TH2 *)file->Get("energy_labr_02");
	TH2 *energy_labr_03 = (TH2 *)file->Get("energy_labr_03");
	TH2 *energy_labr_04 = (TH2 *)file->Get("energy_labr_04");
	TH2 *energy_labr_05 = (TH2 *)file->Get("energy_labr_05");
	TH2 *energy_labr_06 = (TH2 *)file->Get("energy_labr_06");
	TH2 *energy_labr_07 = (TH2 *)file->Get("energy_labr_07");
	TH2 *energy_labr_08 = (TH2 *)file->Get("energy_labr_08");
	TH2 *energy_labr_09 = (TH2 *)file->Get("energy_labr_09");
	TH2 *energy_labr_10 = (TH2 *)file->Get("energy_labr_10");
	TH2 *energy_labr_11 = (TH2 *)file->Get("energy_labr_11");
	TH2 *energy_labr_12 = (TH2 *)file->Get("energy_labr_12");
	TH2 *energy_labr_13 = (TH2 *)file->Get("energy_labr_13");
	TH2 *energy_labr_14 = (TH2 *)file->Get("energy_labr_14");
	TH2 *energy_labr_15 = (TH2 *)file->Get("energy_labr_15");
	TH2 *energy_labr_16 = (TH2 *)file->Get("energy_labr_16");
	TH2 *energy_labr_17 = (TH2 *)file->Get("energy_labr_17");
	TH2 *energy_labr_18 = (TH2 *)file->Get("energy_labr_18");
	TH2 *energy_labr_19 = (TH2 *)file->Get("energy_labr_19");
	TH2 *energy_labr_20 = (TH2 *)file->Get("energy_labr_20");
	TH2 *energy_labr_21 = (TH2 *)file->Get("energy_labr_21");
	TH2 *energy_labr_22 = (TH2 *)file->Get("energy_labr_22");
	TH2 *energy_labr_23 = (TH2 *)file->Get("energy_labr_23");
	TH2 *energy_labr_24 = (TH2 *)file->Get("energy_labr_24");
	TH2 *energy_labr_25 = (TH2 *)file->Get("energy_labr_25");
	TH2 *energy_labr_26 = (TH2 *)file->Get("energy_labr_26");
	TH2 *energy_labr_27 = (TH2 *)file->Get("energy_labr_27");
	TH2 *energy_labr_28 = (TH2 *)file->Get("energy_labr_28");
	TH2 *energy_labr_29 = (TH2 *)file->Get("energy_labr_29");
	TH2 *energy_labr_30 = (TH2 *)file->Get("energy_labr_30");
	TH2 *energy_labr_31 = (TH2 *)file->Get("energy_labr_31");
	TH2 *energy_labr_32 = (TH2 *)file->Get("energy_labr_32");

	energy_labr_01->SetLineColor(1);
	energy_labr_01->Draw();
	//gPad->SetLogy();
	//energy_labr_raw->GetXaxis()->SetTitle("Photon multiplicity PM");
	energy_labr_01->GetXaxis()->SetLabelSize(0.037);
	energy_labr_01->GetYaxis()->SetLabelSize(0.037);
	energy_labr_01->GetYaxis()->SetTitleSize(0.040);
	energy_labr_01->GetXaxis()->SetTitleSize(0.040);
	energy_labr_01->GetZaxis()->SetLabelSize(0.037);
	gStyle->SetOptStat(0);
	energy_labr_01->SetTitle(" ");
	energy_labr_01->GetXaxis()->SetTitle("Energy [channel]");
	energy_labr_01->GetYaxis()->SetTitle("Counts/bin");
	
	energy_labr_02->SetLineColor(2);
	energy_labr_03->SetLineColor(3);
	energy_labr_04->SetLineColor(4);
	energy_labr_05->SetLineColor(5);
	energy_labr_06->SetLineColor(6);
	energy_labr_07->SetLineColor(7);
	energy_labr_08->SetLineColor(8);
	energy_labr_09->SetLineColor(9);
	energy_labr_10->SetLineColor(11);
	energy_labr_11->SetLineColor(12);
	energy_labr_12->SetLineColor(13);
	energy_labr_13->SetLineColor(14);
	energy_labr_14->SetLineColor(15);
	energy_labr_15->SetLineColor(49);
	energy_labr_16->SetLineColor(30);
	energy_labr_17->SetLineColor(31);
	energy_labr_18->SetLineColor(32);
	energy_labr_19->SetLineColor(33);
	energy_labr_20->SetLineColor(34);
	energy_labr_21->SetLineColor(35);
	energy_labr_22->SetLineColor(36);
	energy_labr_23->SetLineColor(37);
	energy_labr_24->SetLineColor(38);
	energy_labr_25->SetLineColor(39);
	energy_labr_26->SetLineColor(40);
	energy_labr_27->SetLineColor(41);
	energy_labr_28->SetLineColor(42);
	energy_labr_29->SetLineColor(43);
	energy_labr_30->SetLineColor(44);
	energy_labr_31->SetLineColor(45);
	energy_labr_32->SetLineColor(46);

	//energy_labr_02->Draw("same");
	energy_labr_03->Draw("same");
	energy_labr_04->Draw("same");
	energy_labr_05->Draw("same");
	//energy_labr_06->Draw("same");
	energy_labr_07->Draw("same");
	//energy_labr_08->Draw("same");
	energy_labr_09->Draw("same");
	//energy_labr_10->Draw("same");
	//energy_labr_11->Draw("same");
	//energy_labr_12->Draw("same");
	//energy_labr_13->Draw("same");
	//energy_labr_14->Draw("same");
	//energy_labr_15->Draw("same");
	//energy_labr_16->Draw("same");
	//energy_labr_17->Draw("same");
	//energy_labr_18->Draw("same");
	//energy_labr_19->Draw("same");
	//energy_labr_20->Draw("same");
	//energy_labr_21->Draw("same");
	energy_labr_22->Draw("same");
	energy_labr_23->Draw("same");
	//energy_labr_24->Draw("same");
	//energy_labr_25->Draw("same");
	//energy_labr_26->Draw("same");
	//energy_labr_27->Draw("same");
	//energy_labr_28->Draw("same");
	//energy_labr_29->Draw("same");
	//energy_labr_30->Draw("same");
	energy_labr_31->Draw("same");
	//energy_labr_32->Draw("same");*/

	//energy_labr_raw->GetXaxis()->SetRangeUser(0,7000);
	//energy_labr_raw->GetYaxis()->SetRangeUser(0,100000);
}