# CS230_project

commands we used(for lru cache replacement policy):
1. to build: 
Usage: ./build_champsim.sh [branch_pred] [l1i_pref] [l1d_pref] [l2c_pref] [llc_pref] [llc_repl] [num_core]
example: ./build_champsim.sh bimodal no no no no lru 1

2. to run:
Usage: ./run_champsim.sh [BINARY] [N_WARM] [N_SIM] [TRACE] [OPTION]
example: ./run_champsim.sh bimodal-no-no-no-no-lru-1core 10 10 pr-3.trace.gz 1
