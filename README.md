# CS230_project
This was our CS230 project on Cache hierarchy in graph analytics done by Gargi, Khushi, Sathwika, Shreya.
commands we used:
1. to build: 
Usage: ./build_champsim.sh [branch_pred] [l1i_pref] [l1d_pref] [l2c_pref] [llc_pref] [llc_repl] [num_core]
example: ./build_champsim.sh bimodal no no no no lru 1

2. to run:
Usage: ./run_champsim.sh [BINARY] [N_WARM] [N_SIM] [TRACE] [OPTION]
example: ./run_champsim.sh bimodal-no-no-no-no-lru-1core 10 10 pr-3.trace.gz 1

To check the implememtation of inclusive, non-inclusive and exclusive policies, copy the contents of the cache_inclusive.cc, cache_inclusive.cc
