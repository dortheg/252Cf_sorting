/***************** ROOT Macro to verify the quality of the particle calibration ***************
***********************************************************************************************
********************************** Author: Alexander Springer *********************************
***********************************************************************************************

How to use this macro:

Call macro with .x verify_cal.C ,
then choose witch ring you want to look at and call a function accordingly.
It would be draw_h_ede_f0() for the first ring and so on...

If the calibration is good the peaks should be nicely aligned up to the Neutron separation energy.

draw_h_ede() shows all the 64 spectra on top of each other.

draw_h_ede_f() draws the h_ede_fX spectra, which are the summed detectors of the same angle.

We can also have a look at the excitation energy. This plots the different h_ex_fX root matrices into one plot:
draw_h_ex()

I tried to use colours that are easy to difference between, not following any code.
They are the same in every plot, so after a while you will know which is which spectrum.

***********************************************************************************************
************************************** Have a nice day. **************************************/

// Main function without any special purpose, one could add some if he/she wants.
void verify_cal(){
    ;
}

void draw_h_ede_f0(){
    h_ede_b0f0->SetLineColor(1);
    h_ede_b1f0->SetLineColor(85);
    h_ede_b2f0->SetLineColor(28);
    h_ede_b3f0->SetLineColor(2);
    h_ede_b4f0->SetLineColor(46);
    h_ede_b5f0->SetLineColor(14);
    h_ede_b6f0->SetLineColor(51);
    h_ede_b7f0->SetLineColor(62);
    h_ede_b0f0->Draw();
    h_ede_b1f0->Draw("SAME");
    h_ede_b2f0->Draw("SAME");
    h_ede_b3f0->Draw("SAME");
    h_ede_b4f0->Draw("SAME");
    h_ede_b5f0->Draw("SAME");
    h_ede_b6f0->Draw("SAME");
    h_ede_b7f0->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 0");
}
void draw_h_ede_f1(){
    h_ede_b0f1->SetLineColor(1);
    h_ede_b1f1->SetLineColor(85);
    h_ede_b2f1->SetLineColor(28);
    h_ede_b3f1->SetLineColor(2);
    h_ede_b4f1->SetLineColor(46);
    h_ede_b5f1->SetLineColor(14);
    h_ede_b6f1->SetLineColor(51);
    h_ede_b7f1->SetLineColor(62);
    h_ede_b0f1->Draw();
    h_ede_b1f1->Draw("SAME");
    h_ede_b2f1->Draw("SAME");
    h_ede_b3f1->Draw("SAME");
    h_ede_b4f1->Draw("SAME");
    h_ede_b5f1->Draw("SAME");
    h_ede_b6f1->Draw("SAME");
    h_ede_b7f1->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 1");
}
void draw_h_ede_f2(){
    h_ede_b0f2->SetLineColor(1);
    h_ede_b1f2->SetLineColor(85);
    h_ede_b2f2->SetLineColor(28);
    h_ede_b3f2->SetLineColor(2);
    h_ede_b4f2->SetLineColor(46);
    h_ede_b5f2->SetLineColor(14);
    h_ede_b6f2->SetLineColor(51);
    h_ede_b7f2->SetLineColor(62);
    h_ede_b0f2->Draw();
    h_ede_b1f2->Draw("SAME");
    h_ede_b2f2->Draw("SAME");
    h_ede_b3f2->Draw("SAME");
    h_ede_b4f2->Draw("SAME");
    h_ede_b5f2->Draw("SAME");
    h_ede_b6f2->Draw("SAME");
    h_ede_b7f2->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 2");
}
void draw_h_ede_f3(){
    h_ede_b0f3->SetLineColor(1);
    h_ede_b1f3->SetLineColor(85);
    h_ede_b2f3->SetLineColor(28);
    h_ede_b3f3->SetLineColor(2);
    h_ede_b4f3->SetLineColor(46);
    h_ede_b5f3->SetLineColor(14);
    h_ede_b6f3->SetLineColor(51);
    h_ede_b7f3->SetLineColor(62);
    h_ede_b0f3->Draw();
    h_ede_b1f3->Draw("SAME");
    h_ede_b2f3->Draw("SAME");
    h_ede_b3f3->Draw("SAME");
    h_ede_b4f3->Draw("SAME");
    h_ede_b5f3->Draw("SAME");
    h_ede_b6f3->Draw("SAME");
    h_ede_b7f3->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 3");
}
void draw_h_ede_f4(){
    h_ede_b0f4->SetLineColor(1);
    h_ede_b1f4->SetLineColor(85);
    h_ede_b2f4->SetLineColor(28);
    h_ede_b3f4->SetLineColor(2);
    h_ede_b4f4->SetLineColor(46);
    h_ede_b5f4->SetLineColor(14);
    h_ede_b6f4->SetLineColor(51);
    h_ede_b7f4->SetLineColor(62);
    h_ede_b0f4->Draw();
    h_ede_b1f4->Draw("SAME");
    h_ede_b2f4->Draw("SAME");
    h_ede_b3f4->Draw("SAME");
    h_ede_b4f4->Draw("SAME");
    h_ede_b5f4->Draw("SAME");
    h_ede_b6f4->Draw("SAME");
    h_ede_b7f4->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 4");
}
void draw_h_ede_f5(){
    h_ede_b0f5->SetLineColor(1);
    h_ede_b1f5->SetLineColor(85);
    h_ede_b2f5->SetLineColor(28);
    h_ede_b3f5->SetLineColor(2);
    h_ede_b4f5->SetLineColor(46);
    h_ede_b5f5->SetLineColor(14);
    h_ede_b6f5->SetLineColor(51);
    h_ede_b7f5->SetLineColor(62);
    h_ede_b0f5->Draw();
    h_ede_b1f5->Draw("SAME");
    h_ede_b2f5->Draw("SAME");
    h_ede_b3f5->Draw("SAME");
    h_ede_b4f5->Draw("SAME");
    h_ede_b5f5->Draw("SAME");
    h_ede_b6f5->Draw("SAME");
    h_ede_b7f5->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 5");
}
void draw_h_ede_f6(){
    h_ede_b0f6->SetLineColor(1);
    h_ede_b1f6->SetLineColor(85);
    h_ede_b2f6->SetLineColor(28);
    h_ede_b3f6->SetLineColor(2);
    h_ede_b4f6->SetLineColor(46);
    h_ede_b5f6->SetLineColor(14);
    h_ede_b6f6->SetLineColor(51);
    h_ede_b7f6->SetLineColor(62);
    h_ede_b0f6->Draw();
    h_ede_b1f6->Draw("SAME");
    h_ede_b2f6->Draw("SAME");
    h_ede_b3f6->Draw("SAME");
    h_ede_b4f6->Draw("SAME");
    h_ede_b5f6->Draw("SAME");
    h_ede_b6f6->Draw("SAME");
    h_ede_b7f6->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 6");
}
void draw_h_ede_f7(){
    h_ede_b0f7->SetLineColor(1);
    h_ede_b1f7->SetLineColor(85);
    h_ede_b2f7->SetLineColor(28);
    h_ede_b3f7->SetLineColor(2);
    h_ede_b4f7->SetLineColor(46);
    h_ede_b5f7->SetLineColor(14);
    h_ede_b6f7->SetLineColor(51);
    h_ede_b7f7->SetLineColor(62);
    h_ede_b0f7->Draw();
    h_ede_b1f7->Draw("SAME");
    h_ede_b2f7->Draw("SAME");
    h_ede_b3f7->Draw("SAME");
    h_ede_b4f7->Draw("SAME");
    h_ede_b5f7->Draw("SAME");
    h_ede_b6f7->Draw("SAME");
    h_ede_b7f7->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Strip 7");
}

// All the spectra in one plot
void draw_h_ede(){
    h_ede_b0f0->SetLineColor(1);
    h_ede_b1f0->SetLineColor(85);
    h_ede_b2f0->SetLineColor(28);
    h_ede_b3f0->SetLineColor(2);
    h_ede_b4f0->SetLineColor(46);
    h_ede_b5f0->SetLineColor(14);
    h_ede_b6f0->SetLineColor(51);
    h_ede_b7f0->SetLineColor(62);
    h_ede_b0f0->Draw();
    h_ede_b1f0->Draw("SAME");
    h_ede_b2f0->Draw("SAME");
    h_ede_b3f0->Draw("SAME");
    h_ede_b4f0->Draw("SAME");
    h_ede_b5f0->Draw("SAME");
    h_ede_b6f0->Draw("SAME");
    h_ede_b7f0->Draw("SAME");
    h_ede_b0f1->SetLineColor(1);
    h_ede_b1f1->SetLineColor(85);
    h_ede_b2f1->SetLineColor(28);
    h_ede_b3f1->SetLineColor(2);
    h_ede_b4f1->SetLineColor(46);
    h_ede_b5f1->SetLineColor(14);
    h_ede_b6f1->SetLineColor(51);
    h_ede_b7f1->SetLineColor(62);
    h_ede_b0f1->Draw("SAME");
    h_ede_b1f1->Draw("SAME");
    h_ede_b2f1->Draw("SAME");
    h_ede_b3f1->Draw("SAME");
    h_ede_b4f1->Draw("SAME");
    h_ede_b5f1->Draw("SAME");
    h_ede_b6f1->Draw("SAME");
    h_ede_b7f1->Draw("SAME");
    h_ede_b0f2->SetLineColor(1);
    h_ede_b1f2->SetLineColor(85);
    h_ede_b2f2->SetLineColor(28);
    h_ede_b3f2->SetLineColor(2);
    h_ede_b4f2->SetLineColor(46);
    h_ede_b5f2->SetLineColor(14);
    h_ede_b6f2->SetLineColor(51);
    h_ede_b7f2->SetLineColor(62);
    h_ede_b0f2->Draw("SAME");
    h_ede_b1f2->Draw("SAME");
    h_ede_b2f2->Draw("SAME");
    h_ede_b3f2->Draw("SAME");
    h_ede_b4f2->Draw("SAME");
    h_ede_b5f2->Draw("SAME");
    h_ede_b6f2->Draw("SAME");
    h_ede_b7f2->Draw("SAME");
    h_ede_b0f3->SetLineColor(1);
    h_ede_b1f3->SetLineColor(85);
    h_ede_b2f3->SetLineColor(28);
    h_ede_b3f3->SetLineColor(2);
    h_ede_b4f3->SetLineColor(46);
    h_ede_b5f3->SetLineColor(14);
    h_ede_b6f3->SetLineColor(51);
    h_ede_b7f3->SetLineColor(62);
    h_ede_b0f3->Draw("SAME");
    h_ede_b1f3->Draw("SAME");
    h_ede_b2f3->Draw("SAME");
    h_ede_b3f3->Draw("SAME");
    h_ede_b4f3->Draw("SAME");
    h_ede_b5f3->Draw("SAME");
    h_ede_b6f3->Draw("SAME");
    h_ede_b7f3->Draw("SAME");
    h_ede_b0f4->SetLineColor(1);
    h_ede_b1f4->SetLineColor(85);
    h_ede_b2f4->SetLineColor(28);
    h_ede_b3f4->SetLineColor(2);
    h_ede_b4f4->SetLineColor(46);
    h_ede_b5f4->SetLineColor(14);
    h_ede_b6f4->SetLineColor(51);
    h_ede_b7f4->SetLineColor(62);
    h_ede_b0f4->Draw("SAME");
    h_ede_b1f4->Draw("SAME");
    h_ede_b2f4->Draw("SAME");
    h_ede_b3f4->Draw("SAME");
    h_ede_b4f4->Draw("SAME");
    h_ede_b5f4->Draw("SAME");
    h_ede_b6f4->Draw("SAME");
    h_ede_b7f4->Draw("SAME");
    h_ede_b0f5->SetLineColor(1);
    h_ede_b1f5->SetLineColor(85);
    h_ede_b2f5->SetLineColor(28);
    h_ede_b3f5->SetLineColor(2);
    h_ede_b4f5->SetLineColor(46);
    h_ede_b5f5->SetLineColor(14);
    h_ede_b6f5->SetLineColor(51);
    h_ede_b7f5->SetLineColor(62);
    h_ede_b0f5->Draw("SAME");
    h_ede_b1f5->Draw("SAME");
    h_ede_b2f5->Draw("SAME");
    h_ede_b3f5->Draw("SAME");
    h_ede_b4f5->Draw("SAME");
    h_ede_b5f5->Draw("SAME");
    h_ede_b6f5->Draw("SAME");
    h_ede_b7f5->Draw("SAME");
    h_ede_b0f6->SetLineColor(1);
    h_ede_b1f6->SetLineColor(85);
    h_ede_b2f6->SetLineColor(28);
    h_ede_b3f6->SetLineColor(2);
    h_ede_b4f6->SetLineColor(46);
    h_ede_b5f6->SetLineColor(14);
    h_ede_b6f6->SetLineColor(51);
    h_ede_b7f6->SetLineColor(62);
    h_ede_b0f6->Draw("SAME");
    h_ede_b1f6->Draw("SAME");
    h_ede_b2f6->Draw("SAME");
    h_ede_b3f6->Draw("SAME");
    h_ede_b4f6->Draw("SAME");
    h_ede_b5f6->Draw("SAME");
    h_ede_b6f6->Draw("SAME");
    h_ede_b7f6->Draw("SAME");
    h_ede_b0f7->SetLineColor(1);
    h_ede_b1f7->SetLineColor(85);
    h_ede_b2f7->SetLineColor(28);
    h_ede_b3f7->SetLineColor(2);
    h_ede_b4f7->SetLineColor(46);
    h_ede_b5f7->SetLineColor(14);
    h_ede_b6f7->SetLineColor(51);
    h_ede_b7f7->SetLineColor(62);
    h_ede_b0f7->Draw("SAME");
    h_ede_b1f7->Draw("SAME");
    h_ede_b2f7->Draw("SAME");
    h_ede_b3f7->Draw("SAME");
    h_ede_b4f7->Draw("SAME");
    h_ede_b5f7->Draw("SAME");
    h_ede_b6f7->Draw("SAME");
    h_ede_b7f7->Draw("SAME");
}

// This one is for Drawing all h_ede_fX's so all summed up detectors
void draw_h_ede_f(){
    h_ede_f0->SetLineColor(1);
    h_ede_f1->SetLineColor(85);
    h_ede_f2->SetLineColor(28);
    h_ede_f3->SetLineColor(2);
    h_ede_f4->SetLineColor(46);
    h_ede_f5->SetLineColor(14);
    h_ede_f6->SetLineColor(51);
    h_ede_f7->SetLineColor(62);
    h_ede_f0->Draw();
    h_ede_f1->Draw("SAME");
    h_ede_f2->Draw("SAME");
    h_ede_f3->Draw("SAME");
    h_ede_f4->Draw("SAME");
    h_ede_f5->Draw("SAME");
    h_ede_f6->Draw("SAME");
    h_ede_f7->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Summed up detectors for different angles");
}

// This is concerning the excitation energy!
void draw_h_ex(){
    h_ex_f0->SetLineColor(1);
    h_ex_f1->SetLineColor(85);
    h_ex_f2->SetLineColor(28);
    h_ex_f3->SetLineColor(2);
    h_ex_f4->SetLineColor(46);
    h_ex_f5->SetLineColor(14);
    h_ex_f6->SetLineColor(51);
    h_ex_f7->SetLineColor(62);
    h_ex_f0->Draw();
    h_ex_f1->Draw("SAME");
    h_ex_f2->Draw("SAME");
    h_ex_f3->Draw("SAME");
    h_ex_f4->Draw("SAME");
    h_ex_f5->Draw("SAME");
    h_ex_f6->Draw("SAME");
    h_ex_f7->Draw("SAME");
    c1->BuildLegend(0.98,0.98,0.74,0.74);
    c1->SetTitle("Excitation Energy");
}

/*
For Key in the left top corner, use:
c1->BuildLegend(0.3,0.98,0.02,0.74);
*/