import numpy as np
import matplotlib.pyplot as plt
import utilities as ut
from uncertainties import unumpy

n_fissions = 133000
filename = "energy.un"
# filename = "energy.un1" # different unfoldingthreshold
# filename = "energy.hist"
data, cal, Ebins  = ut.read_mama_1D(filename)

# data *= 10 
# n_fissions *= 10
print(np.sum(data))

# N_final = 1600
# data, Ebins = ut.rebin_and_shift(data, Ebins, N_final, rebin_axis=0)
Ebins /= 1e3 # to MeV

data_unc = np.sqrt(data)

# efficiency
# multiply by total efficiency at 1.33 MeV??
# Note: Update efficiecies
eff = 0.279
# one Detector places far away
eff = eff /21 * 20

data /= eff 
data_unc /= eff

# counts per MeV
binwidth = Ebins[1] - Ebins[0]
print("binwidth = {} keV".format(binwidth))
data /= (binwidth) 
data_unc /= (binwidth)

# counts per fission (efficiency corrected from mama already)
data /= n_fissions
data_unc /= n_fissions

# rough unc. calculation
print(np.sum(data)*binwidth, " +- " ,np.sum(data_unc)*binwidth)


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.set_yscale('log')
plt.errorbar(Ebins, data, yerr=data_unc)
plt.xlabel("Energy [MeV]")
plt.ylabel("Photons/(fission * MeV)")
plt.show()
