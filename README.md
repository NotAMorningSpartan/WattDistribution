# Watt Distribution
A C++ program that randomly samples from the Watt Fission Spectrum.

The following equation is used to simulate the Watt Distribution: P(E) = 0.4865 * sinh(sqrt(2*E)) * e^-E

The program then takes the derivative of the function and calculates its local maximum.

From there, it uses rejection sampling to generate a sample of 100,000. The sample of energies that was randomly generated is divided into bins, which keep track of how many energies fit into a bin. 100 bins are generated.

The bins and their frequencies are then outputted to the user, with bin number and frequency separated by a tab to allow for an easy copy/paste into Excel, and then plotted using a histogram.

Original Assignment Description created by: Dr. Leslie Kerby, Idaho State University.