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

#ifndef USERSORT_H
#define USERSORT_H

#include "TDRRoutine.h"
#include "Event.h"

class UserSort : public TDRRoutine
{
public:
    UserSort();
    ~UserSort() { }

    bool Sort(const Event& event);

    bool End();

    //! We have no user commands that needs to be set.
    /*! \return true allways.
     */
    bool UserCommand(const std::string &cmd);

protected:
    void CreateSpectra();

private:

    // Enum describing the 'prompt' status of a gamma-ray
    typedef enum {
        is_prompt,          //!< To indicate that the hit is within the 'prompt' window.
        is_background,      //!< To indicate that the hit is within the 'background' window.
        ignore              //!< To indicate that the hit is neither in the 'prompt' nor the 'background window.
    } prompt_status_t;

    // Method to check if the time is within a gate.
    prompt_status_t CheckTimeStatus(const double &time,         /*!< Time of the hit        */
                                    const Parameter &paramter   /*!< Gates of the detector  */) const;


    // Method to give names to some paramters
    void NameTimeParameters();

    // Method for calibrating energy of a detector.
    double CalibrateE(const word_t &w) const;

    // Method for getting time difference between two words.
    double CalcTimediff(const word_t &start, const word_t &stop) const;

    Histogram1Dp energy_labr_raw[NUM_LABR_DETECTORS], energy_labr[NUM_LABR_DETECTORS], energy_labr_fission, energy_labr_fission_bg, energy_labr_fission_all;

    Histogram1Dp energy_labr_9_fission;

    Histogram1Dp time_gamma_gamma, time_gamma_gamma_veto_cfdfail_labr;

    Histogram2Dp energy_labr_all, time_labr_all;

    Histogram2Dp time_energy_labr;

    // Particle gated E-DE
    Histogram2Dp ede_gate;

    // Excitation energy figure
    Histogram1Dp h_ex;

    // Particle - gamma-ray coincidence matrix
    Histogram2Dp exgam_ppac, exgam_ppac_bg, exgam_ppac_all; // gated on ppacs

    // Gain labr
    Parameter gain_labr;

    // Shift labr
    Parameter shift_labr;

    // Gain dE
    Parameter gain_dE;

    // Shift dE
    Parameter shift_dE;

    // Gain E
    Parameter gain_E;

    // Shift E
    Parameter shift_E;

    // Time alignment LaBr
    Parameter shift_time_labr;

    // Time alignment dE
    Parameter shift_time_de;

    // Time alignment E
    Parameter shift_time_e;

    // Time alignment PPACs
    Parameter shift_time_ppac;
    Histogram2Dp ppac_align_time, labr_align_time;   // LaBr 0 as start and PPAC as stop. For aligning the PPACs.


    // Coefficients of 2nd order Polynomial to calculate excitation energy from SiRi energy (E+dE).
    Parameter ex_from_ede;

    //   // Two rectangles to cut away SiRi noise/electrons
    //     Parameter ede_rect;

    // Apparent thickness gate SiRi
    Parameter thick_range;

    // Struct to hold the time gates
    struct TimeGate
    {
    double lower_prompt;
    double higher_prompt;
    double lower_bg;
    double higher_bg;
    };

    // Time gates for the NaI detectors, e.g. for making the exgam matrices
    Parameter labr_time_cuts;
    TimeGate labr_time_cut;

    // Time gates for the ppacs.
    Parameter ppac_time_cuts;
    TimeGate ppac_time_cut;


    int n_fail_de, n_fail_e, n_fission, n_gamma, n_gamma_fiss, n_cfdfail_labr;


};

#endif // USERROUTINE2_H
