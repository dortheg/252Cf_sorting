
void variable_bin_widths(){
	TFile *file = TFile::Open("252Cf_3ns_11jun2020.root");

	TH1 *energy_labr_fission = (TH1 *)file->Get("energy_labr_fission");

	//energy_labr_fission->Draw();
	//gPad->SetLogy();


	const Int_t NBINS = 170;
	double edges[NBINS+1];

	FILE *myFile;
    myFile = fopen("edge_list.dat", "r");

	for (int i = 0; i < NBINS+1; i++)
	{
    	fscanf(myFile, "%le", &edges[i]);
	}

	for (int i = 0; i < NBINS+1; i++)
            printf( "%le\n", edges[i]) ;


	// Double_t edges[NBINS + 1] = {0.000000000000000000e+00, 1.443099999999999916e+01, 7.112000000000000455e+01, 1.936730000000000018e+02, 
	// 	3.950240000000000009e+02, 6.822069999999999936e+02, 1.059410000000000082e+03, 1.529343000000000075e+03, 2.093880999999999858e+03,
	// 	2.754389999999999873e+03, 3.511902999999999793e+03, 4.367229999999999563e+03, 5.321016999999999825e+03, 6.373795000000000073e+03, 
	// 	7.526006000000000313e+03, 8.778022000000000844e+03, 1.013016300000000047e+04, 1.158270399999999972e+04, 1.313588700000000063e+04, 
	// 	1.478992400000000089e+04};

	TH1* h = new TH1D(
      /* name */ "h1",
      /* title */ "Hist with variable bin width",
      /* number of bins */ NBINS,
      /* edge array */ edges
    );



    Int_t lastbin1 = energy_labr_fission->GetNbinsX();

    for(int j=0; j<NBINS;j++){
    	double bin_sum = 0; 

    	for (int k=0;k<lastbin1;k++){
    		double energy = energy_labr_fission->GetBinCenter(k);

    		if(energy >= edges[j] && energy < edges[j+1] ){
    			bin_sum += energy_labr_fission->GetBinContent(k);
    		}
    	}
e
    	h->SetBinContent(j,bin_sum);

    }

    h->Draw();
    gPad->SetLogy();


}