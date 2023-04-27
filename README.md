# CS230_project
This is the repository for our CS230 project on Cache hierarchy in Graph Analytics.

### Members: 
Gargi Bakshi \
Sathwika Reddy \
Khushi Gondane \
Shreya Tiwari


## Commands to run:
 
Navigate to the ChampSim directory

To build:
```
./build_champsim.sh [branch_pred] [l1i_pref] [l1d_pref] [l2c_pref] [llc_pref] [llc_repl] [num_core]
```
Here, the options are for the L1I, L1D, L2, LLC prefetchers and the LLC replacement policy and the number of cores. To use the default set them as `no`. Else, use the specific name of the prefetcher/policy you need. Here is an example of a basic command: 
```
./build_champsim.sh bimodal no no no no lru 1
```
* Now, we need to run the `run_champsim.sh` file:
```
./run_champsim.sh [BINARY] [N_WARM] [N_SIM] [TRACE] [OPTION]
```
  * The binary is inside the bin folder, just provide the name of the binary(don't give the absolute path) 
  * N_WARM and N_SIM are in units of `1M`
  * The trace __should be__ inside the traces folder, just provide the name of the trace(don't give the absolute path) 
  * Look at `run_champsim.sh` to tweak and make your own changes
* There will be a `results-<num>M` folder created, which contains the results of the trace. Make sure to save these results to your machine, as it gets overwritten everytime.


To use different cache policies, copy the cotents of the respective ```cache_*.cc``` files into the ```ChampSim/src/cache.cc```.
