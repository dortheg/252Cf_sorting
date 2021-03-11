/*******************************************************************************
 * Copyright (C) 2016 Vetle W. Ingeberg                                        *
 * Author: Vetle Wegner Ingeberg, v.w.ingeberg@fys.uio.no                      *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * This program is free software; you can redistribute it and/or modify it     *
 * under the terms of the GNU General Public License as published by the       *
 * Free Software Foundation; either version 3 of the license, or (at your      *
 * option) any later version.                                                  *
 *                                                                             *
 * This program is distributed in the hope that it will be useful, but         *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General   *
 * Public License for more details.                                            *
 *                                                                             *
 * You should have recived a copy of the GNU General Public License along with *
 * the program. If not, see <http://www.gnu.org/licenses/>.                    *
 *                                                                             *
 *******************************************************************************/

#include "UserSort.h"

#include "DefineFile.h"

#include "TDRWordBuffer.h"
#include "DetectorRead.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include "Histograms.h"
#include "Event.h"


#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

//#include <printf.h>
#include <stdint.h>
#include <stdlib.h>

static bool set_par(Parameters& parameters, std::istream& ipar,
                    const std::string& name, int size)
{
    Parameter* p = parameters.Find(name);
    if( !p )
        return false;

    std::vector<Parameter::param_t> values;
    float tmp;
    for(int i=0; i<size; ++i) {
        tmp = 0;
        ipar >> tmp;
        values.push_back(tmp);
    }
    p->Set( values );

    return true;
}

static bool set_gainshift(Parameters& parameters, std::istream& ipar)
{
    bool p1 = set_par(parameters, ipar, "gain_labr",    NUM_LABR_DETECTORS );
    bool p2 = set_par(parameters, ipar, "shift_labr",   NUM_LABR_DETECTORS );
    bool p3 = set_par(parameters, ipar, "gain_de", NUM_SI_DE_DET );
    bool p4 = set_par(parameters, ipar, "shift_de", NUM_SI_DE_DET );
    bool p5 = set_par(parameters, ipar, "gain_e", NUM_SI_DE_DET );
    bool p6 = set_par(parameters, ipar, "shift_e", NUM_SI_DE_DET );
    bool p7 = set_par(parameters, ipar, "shift_time_labr", NUM_LABR_DETECTORS );
    bool p8 = set_par(parameters, ipar, "shift_time_de", NUM_SI_DE_DET );
    bool p9 = set_par(parameters, ipar, "shift_time_e", NUM_SI_E_DET );
    bool p10 = set_par(parameters, ipar, "shift_time_ppac", NUM_PPAC );
    return (p1 && p2 && p3 && p4 && p5 && p6 && p7 && p8 && p9 && p10);
}

UserSort::UserSort()
    : gain_labr( GetParameters(), "gain_labr", NUM_LABR_DETECTORS, 1)
    , shift_labr( GetParameters(), "shift_labr", NUM_LABR_DETECTORS, 0)
    , gain_dE( GetParameters(), "gain_de", NUM_SI_DE_DET, 1)
    , shift_dE( GetParameters(), "shift_de", NUM_SI_DE_DET, 0)
    , gain_E( GetParameters(), "gain_e", NUM_SI_DE_DET, 1)
    , shift_E( GetParameters(), "shift_e", NUM_SI_DE_DET, 0)
    , shift_time_labr( GetParameters(), "shift_time_labr", NUM_LABR_DETECTORS, 0)
    , shift_time_de( GetParameters(), "shift_time_de", NUM_SI_DE_DET, 0)
    , shift_time_e( GetParameters(), "shift_time_e", NUM_SI_E_DET, 0)
    , shift_time_ppac( GetParameters(), "shift_time_ppac", NUM_PPAC, 0)
    , ex_from_ede    ( GetParameters(), "ex_from_ede", NUM_SI_RINGS*3)
//    , ede_rect       ( GetParameters(), "ede_rect", 4         )
    , thick_range    ( GetParameters(), "thick_range", 2      )
    , labr_time_cuts  ( GetParameters(), "labr_time_cuts", 2*2  )
    , ppac_time_cuts ( GetParameters(), "ppac_time_cuts", 2*2 )
{
}

void UserSort::NameTimeParameters()
 {
labr_time_cut.lower_prompt = labr_time_cuts[0];
labr_time_cut.higher_prompt = labr_time_cuts[1];
labr_time_cut.lower_bg = labr_time_cuts[2];
labr_time_cut.higher_bg = labr_time_cuts[3];

ppac_time_cut.lower_prompt = ppac_time_cuts[0];
ppac_time_cut.higher_prompt = ppac_time_cuts[1];
ppac_time_cut.lower_bg = ppac_time_cuts[2];
ppac_time_cut.higher_bg = ppac_time_cuts[3];

 }

double UserSort::CalibrateE(const word_t &w) const
{
    DetectorInfo_t info = GetDetector(w.address);
    switch ( info.type ) {

    case labr : {
        return gain_labr[info.detectorNum]*(w.adcdata + drand48() - 0.5) + shift_labr[info.detectorNum];
    }
    case deDet : {
        return gain_dE[info.detectorNum]*(w.adcdata + drand48() - 0.5) + shift_dE[info.detectorNum];
    }
    case eDet : {
        return gain_E[info.detectorNum]*(w.adcdata + drand48() - 0.5) + shift_E[info.detectorNum];
    }
    case ppac : {
        return w.adcdata;
    }
    case rfchan : {
        return w.adcdata;
    }
    default:
        return w.adcdata;
    }
}

double UserSort::CalcTimediff(const word_t &start, const word_t &stop) const
{
    // First we fetch the correct shift parameters.
    double start_shift, stop_shift;

    DetectorInfo_t info_start = GetDetector(start.address);
    DetectorInfo_t info_stop = GetDetector(stop.address);

    switch ( info_start.type ){
        case labr : {
            start_shift = shift_time_labr[info_start.detectorNum];
            break;
        }
        case deDet : {
            start_shift = shift_time_de[info_start.detectorNum];
            break;
        }
        case eDet : {
            start_shift = shift_time_e[info_start.detectorNum];
            break;
        }
        case ppac : {
            start_shift = shift_time_ppac[info_start.detectorNum];
            break;
        }
        default : {
            start_shift = 0;
            break;
        }
    }

    switch ( info_stop.type ){
        case labr : {
            stop_shift = shift_time_labr[info_stop.detectorNum];
            break;
        }
        case deDet : {
            stop_shift = shift_time_de[info_stop.detectorNum];
            break;
        }
        case eDet : {
            stop_shift = shift_time_e[info_stop.detectorNum];
            break;
        }
        case ppac : {
            stop_shift = shift_time_ppac[info_stop.detectorNum];
            break;
        }
        default : {
            stop_shift = 0;
            break;
        }
    }

    // 'Coarse' time difference.
    int64_t diff_coarse = stop.timestamp - start.timestamp;

    // 'Fine' time difference
    double diff_fine = stop.cfdcorr -start.cfdcorr;

    // Actual time difference.
    double diff = diff_coarse + diff_fine;

    // Now we add shift of stop time and subtract shift of start time.
    diff += (stop_shift - start_shift);

    return diff;

}


bool UserSort::UserCommand(const std::string &cmd)
{
    std::istringstream icmd(cmd.c_str());

    std::string name, tmp;
    icmd >> name;

    if ( name == "Gain" ) {
        icmd >> tmp;
        if ( tmp == "file" ) {
            std::string filename;
            icmd >> filename;
            std::ifstream gainfile(filename.c_str());
            if ( !set_gainshift(GetParameters(), gainfile) ){
                std::cerr << __PRETTY_FUNCTION__ << ", gain file: error reading '" << filename << "'" << std::endl;
                return false;
            }
        } else if ( tmp=="data" ){
            if ( !set_gainshift(GetParameters(), icmd) ){
                std::cerr << __PRETTY_FUNCTION__ << ", gain data: error reading calibration data" << std::endl;
                return false;
            }
        } else {
            std::cerr << __PRETTY_FUNCTION__ << ", gain: Expected 'file' or 'data', not '" << tmp << "'" << std::endl;
        }
    } else if ( name == "parameter" ){
        return GetParameters().SetAll(icmd);
    } else {
        return false;
    }
    return true;
}


void UserSort::CreateSpectra()
{
    char tmp[1024], tmp1[1024], tmp2[1024], tmp3[1024];

    for (int i = 0 ; i < NUM_LABR_DETECTORS ; ++i){

        // Create energy spectra
        sprintf(tmp, "energy_raw_labr_%02d", i+1);
        energy_labr_raw[i] = Spec(tmp, tmp, 32768, 0, 32768, "Energy [ch]");

        sprintf(tmp, "energy_labr_%02d", i+1);
        energy_labr[i] = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");
    }

    sprintf(tmp, "energy_labr_all");
    energy_labr_all = Mat(tmp, tmp, 10000, 0, 10000, "Energy [keV]", NUM_LABR_DETECTORS, 0, NUM_LABR_DETECTORS, "LaBr_{3}(Ce) nr.");

    sprintf(tmp, "energy_labr_all_px");
    energy_labr_all_px = Spec(tmp, tmp, 2000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "ppac_align_time");
    sprintf(tmp2, "t_{PPAC} - t_{LaBr nr. 1}");
    ppac_align_time = Mat(tmp, tmp2, 9000, -1500, 1500, "t_{PPAC} - t_{LaBr nr. 1} [ns]", NUM_PPAC, 0, NUM_PPAC, "PPAC id.");

    sprintf(tmp, "labr_align_time");
    sprintf(tmp2, "t_{LaBr} - t_{PPAC, any}");
    labr_align_time = Mat(tmp, tmp2, 9000, -1500, 1500, "t_{LaBr} - t_{PPAC, any} [ns]", NUM_LABR_DETECTORS, 0, NUM_LABR_DETECTORS, "LaBr id.");

    sprintf(tmp, "labr_align_time_RH");
    labr_align_time_RH = Spec(tmp, tmp, 9000, -1500, 1500, "t_{LaBr} - t_{PPAC, any} [ns]");

    sprintf(tmp, "labr_align_time_LH");
    labr_align_time_LH = Spec(tmp, tmp, 9000, -1500, 1500, "t_{LaBr} - t_{PPAC, any} [ns]");

    sprintf(tmp, "exgam_ppac_all");
    exgam_ppac_all = Mat(tmp, tmp, 1500, 0, 15000, "LaBr [keV]", 1100, -1000, 15000, "Ex [keV]");

    sprintf(tmp, "exgam_ppac");
    exgam_ppac = Mat(tmp, tmp, 1500, 0, 15000, "LaBr [keV]", 1100, -1000, 15000, "Ex [keV]");

    sprintf(tmp, "exgam_ppac_bg");
    exgam_ppac_bg = Mat(tmp, tmp, 1500, 0, 15000, "LaBr [keV]", 1100, -1000, 15000, "Ex [keV]");

    sprintf(tmp, "energy_labr_fission");
    energy_labr_fission = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "energy_labr_fission_bg");
    energy_labr_fission_bg = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "energy_labr_fission_all");
    energy_labr_fission_all = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "energy_labr_fission_LH");
    energy_labr_fission_LH = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "energy_labr_fission_RH");
    energy_labr_fission_RH = Spec(tmp, tmp, 10000, 0, 10000, "Energy [keV]");

    sprintf(tmp, "time_gamma_gamma");
    time_gamma_gamma = Spec(tmp, tmp, 1000, -150, 150, "tdiff [ns]");

    sprintf(tmp, "time_energy_labr");
    sprintf(tmp2, "t_{LaBr} - t_{PPAC, any} : E_{LaBr}");
    time_energy_labr = Mat(tmp, tmp2, 4000, -150, 150, "t_{LaBr} - t_{PPAC} [ns]", 2000, 0, 10000, "Energy LaBr [keV]");

    sprintf(tmp, "time_energy_labr_1332gated");
    sprintf(tmp2, "t_{LaBr} - t_{LaBr_1332} : E_{LaBr}");
    time_energy_labr_1332gated = Mat(tmp, tmp2, 600, -150, 150, "t_{LaBr} - t_{LaBr_1332} [ns]", 140, 0, 1400, "Energy LaBr [keV]");

    sprintf(tmp, "time_energy_labr_fission_cfdfail");
    sprintf(tmp2, "t_{LaBr} - t_{dE ANY} : E_{LaBr}, fission");
    time_energy_labr_fission_cfdfail = Mat(tmp, tmp2, 1000, -200, 200, "t_{LaBr} - t_{DE} [ns]", 1000, 0, 10000, "Energy LaBr [keV]");

    sprintf(tmp, "multiplicity_distr");
    multiplicity_distr = Spec(tmp, tmp, 11, -0.5, 10.5, "tdiff [ns]");

    sprintf(tmp, "multiplicity_distr_all");
    multiplicity_distr_all = Spec(tmp, tmp, 11, -0.5, 10.5, "tdiff [ns]");

    sprintf(tmp, "multiplicity_distr_bg");
    multiplicity_distr_bg = Spec(tmp, tmp, 11, -0.5, 10.5, "tdiff [ns]");

    n_fail_e = 0;
    n_fail_de = 0;
    n_cfdfail_labr = 0;

    n_fission = 0;
    n_fission_veto_cfdfail_labr = 0;

    n_gamma = 0;
    n_gamma_fiss = 0;
}


bool UserSort::Sort(const Event &event)
{
    int i, j, k, l;
    double energy, energy_2;
    double tdiff_ppac_labr;
    double tdiff_gamma_gamma;

    NameTimeParameters();

//    //Test to see if any of the LaBr in the event are associated with CFDfail; if so, set CFD_fail_labr to true
//    // Will be used later to avoid CFD_fail events
//    bool CFD_fail_labr = false;
//    for ( i = 0 ; i < NUM_LABR_DETECTORS ; ++i ){
//        for ( j = 0 ; j < event.n_labr[i] ; ++j ){
//            n_cfdfail_labr += event.w_labr[i][j].cfdfail;
//            if(event.w_labr[i][j].cfdfail > 0)
//                CFD_fail_labr = true;
//        }
//    }

    //Fill ungated spectra
    for ( i = 0 ; i < NUM_LABR_DETECTORS ; ++i ){
        for ( j = 0 ; j < event.n_labr[i] ; ++j ){
            energy_labr_raw[i]->Fill(event.w_labr[i][j].adcdata);

            energy = CalibrateE(event.w_labr[i][j]);
            energy_labr[i]->Fill(energy);
            energy_labr_all->Fill(energy,i);
            energy_labr_all_px->Fill(energy);
            n_gamma += 1;
        }
    }

//    ///////////////////////////////////////////////////////////////
//    ///                Gamma-gamma coincidence                  ///
//    ///////////////////////////////////////////////////////////////

//    //Gate on 1.33 MeV line in 60Co, as know 1.1 MeV arrives in coincidence
//    double energy_one, energy_two;
//    double sigma_1_33 = 30.0;

//    for ( i = 0 ; i < NUM_LABR_DETECTORS ; ++i ){
//        for ( j = 0 ; j < event.n_labr[i] ; ++j ){

//            energy_one = CalibrateE(event.w_labr[i][j]);

//            if(1332 - sigma_1_33 < energy_one && 1332 + sigma_1_33 > energy_one){

//                for ( k = 0 ; k < NUM_LABR_DETECTORS ; ++k ){
//                    for ( l = 0 ; l < event.n_labr[k] ; ++l ){

//                        if(k!=i && j!=l){
//                            energy_two = CalibrateE(event.w_labr[k][l]);
//                            tdiff_gamma_gamma = CalcTimediff(event.w_labr[k][l], event.w_labr[i][j]);
//                            time_energy_labr_1332gated->Fill(tdiff_gamma_gamma, energy_two);
//                        }
//                    }
//                }
//            }
//        }
//    }


//    for ( i = 0 ; i < NUM_LABR_DETECTORS ; ++i ){
//        for ( j = 0 ; j < event.n_labr[i] ; ++j ){

//            for ( k = 0 ; k < NUM_LABR_DETECTORS ; ++k ){
//                for ( l = 0 ; l < event.n_labr[k] ; ++l ){

//                    if(k!=i && j!=l){
//                        energy_2 = CalibrateE(event.w_labr[k][l]);
//                        tdiff_gamma_gamma = CalcTimediff(event.w_labr[k][l], event.w_labr[i][j]);
//                        time_gamma_gamma->Fill(tdiff_gamma_gamma);
//                    }
//                }
//            }
//        }
//    }

    ///////////////////////////////////////////////////////////////
    ///                 PPAC-gamma coincidence                  ///
    ///////////////////////////////////////////////////////////////

    for (int k = 0 ; k < NUM_PPAC ; ++k){
        for (int l = 0 ; l < event.n_ppac[k] ; ++l){

            //Must count number of fissions for the different cases
            n_fission++;

            int multiplicity = 0;
            int multiplicity_all = 0;
            int multiplicity_bg = 0;

            for (i = 0 ; i < NUM_LABR_DETECTORS ; ++i){
                for (int j = 0 ; j < event.n_labr[i] ; ++j){

                    double labr_energy = CalibrateE(event.w_labr[i][j]);
                    tdiff_ppac_labr = CalcTimediff(event.w_ppac[k][l], event.w_labr[i][j]);

                    ppac_align_time->Fill(tdiff_ppac_labr,k);

                    if(k==0)
                        labr_align_time->Fill(tdiff_ppac_labr,i);

                    ppac_align_time->Fill(tdiff_ppac_labr,k);
                    time_energy_labr->Fill(tdiff_ppac_labr,labr_energy);

                    //events with CDFfail in owm spectra
                    if (event.w_labr[i][j].cfdfail > 0){
                        time_energy_labr_fission_cfdfail->Fill(tdiff_ppac_labr, labr_energy);
                    }

                    ///Split OSCAR in left and right halves
                    int labr_nr = -1;
                    if(i<=14){
                        labr_nr = i+1;
                    }
                    if(i>=17){
                        labr_nr = i-1;
                    }

                    if(labr_nr == 1 || labr_nr == 2 || labr_nr == 5 || labr_nr == 6 || labr_nr == 7|| labr_nr == 8 || labr_nr == 9|| labr_nr == 15|| labr_nr == 16|| labr_nr == 17 ||labr_nr == 18|| labr_nr == 19|| labr_nr == 25 || labr_nr == 26 || labr_nr == 27){
                        labr_align_time_RH->Fill(tdiff_ppac_labr);
                    }

                    if(labr_nr == 3 || labr_nr == 4 || labr_nr == 10 || labr_nr == 11 || labr_nr == 12 || labr_nr == 13 || labr_nr == 14 || labr_nr == 20 || labr_nr == 21 || labr_nr == 22 || labr_nr == 23 || labr_nr == 24 || labr_nr == 28 || labr_nr == 29 || labr_nr == 30){
                        labr_align_time_LH->Fill(tdiff_ppac_labr);
                    }

                    switch ( CheckTimeStatus(tdiff_ppac_labr, ppac_time_cuts) ) {
                        case is_prompt : {
                            energy_labr_fission->Fill(labr_energy);
                            energy_labr_fission_all->Fill(labr_energy);
                            exgam_ppac->Fill(labr_energy,1000);
                            exgam_ppac_all->Fill(labr_energy,1000);
                            n_gamma_fiss +=1;

                            multiplicity += 1.0;
                            multiplicity_all += 1.0;

                            //Split OSCAR in left and right halves
                            if(labr_nr == 1 || labr_nr == 2 || labr_nr == 5 || labr_nr == 6 || labr_nr == 7|| labr_nr == 8 || labr_nr == 9|| labr_nr == 15|| labr_nr == 16|| labr_nr == 17 ||labr_nr == 18|| labr_nr == 19|| labr_nr == 25 || labr_nr == 26 || labr_nr == 27){
                                energy_labr_fission_RH->Fill(labr_energy);
                            }

                            if(labr_nr == 3 || labr_nr == 4 || labr_nr == 10 || labr_nr == 11 || labr_nr == 12 || labr_nr == 13 || labr_nr == 14 || labr_nr == 20 || labr_nr == 21 || labr_nr == 22 || labr_nr == 23 || labr_nr == 24 || labr_nr == 28 || labr_nr == 29 || labr_nr == 30){
                                energy_labr_fission_LH->Fill(labr_energy);
                            }

                            break;
                        }

                        case is_background : {
                            energy_labr_fission->Fill(labr_energy, -1);
                            energy_labr_fission_bg->Fill(labr_energy);
                            exgam_ppac->Fill(labr_energy,1000,-1);
                            exgam_ppac_bg->Fill(labr_energy,1000);

                            multiplicity += -1.0;
                            multiplicity_bg += 1.0;

                            if(labr_nr == 1 || labr_nr == 2 || labr_nr == 5 || labr_nr == 6 || labr_nr == 7|| labr_nr == 8 || labr_nr == 9|| labr_nr == 15|| labr_nr == 16|| labr_nr == 17 ||labr_nr == 18|| labr_nr == 19|| labr_nr == 25 || labr_nr == 26 || labr_nr == 27){
                                energy_labr_fission_RH->Fill(labr_energy, -1);
                            }

                            if(labr_nr == 3 || labr_nr == 4 || labr_nr == 10 || labr_nr == 11 || labr_nr == 12 || labr_nr == 13 || labr_nr == 14 || labr_nr == 20 || labr_nr == 21 || labr_nr == 22 || labr_nr == 23 || labr_nr == 24 || labr_nr == 28 || labr_nr == 29 || labr_nr == 30){
                                energy_labr_fission_LH->Fill(labr_energy, -1);
                            }

                            break;
                        }

                        case ignore :{
                            break;
                        }
                    }
                }
            }
            multiplicity_distr->Fill(multiplicity);
            multiplicity_distr_all->Fill(multiplicity_all);
            multiplicity_distr_bg->Fill(multiplicity_bg);
        }
    }

    return true;
}

 UserSort::prompt_status_t UserSort::CheckTimeStatus(const double &time, const Parameter &parameter) const
 {
     if ( time > parameter[0] && time < parameter[1])
         return is_prompt;
     else if (time > parameter[2] && time < parameter[3])
         return is_background;
     else
         return ignore;
 }

bool UserSort::End()
{
    std::cout << "CFD fails in E - detectors: " << n_fail_e << std::endl;
    std::cout << "CFD fails in dE - detectors: " << n_fail_de << std::endl;
    std::cout << "CFD fails in LaBr: " << n_cfdfail_labr << std::endl;
    std::cout << "n_fission: " << n_fission << std::endl;
    std::cout << "ngamma: " << n_gamma << std::endl;
    std::cout << "ngammafiss: " << n_gamma_fiss << std::endl;
    return true;
}
