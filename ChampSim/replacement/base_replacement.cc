#include "cache.h"
#include <cstdlib>

//void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
//{
  //  if (type == WRITEBACK) {
    //    if (hit) // wrietback hit does not update LRU state
      //      return;
//    }

  //  return lru_update(set, way);
//}

uint32_t CACHE::rand_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set][way].valid == false) {

            DP ( if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // RAND victim
    if (way == NUM_WAY) {
        way = rand() % NUM_WAY;
    }


    return way;
}


uint32_t CACHE::lfu_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set][way].valid == false) {

            DP ( if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }



    // LFU victim
    uint32_t minway = way;
    if (way == NUM_WAY) {
        minway = 0;
        uint32_t minfreq = block[set][0].freq;
        for (way=0; way<NUM_WAY; way++) {
            if (block[set][way].freq < minfreq) {

                minway = way;
                minfreq = block[set][way].freq;

                DP ( if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " lru: " << block[set][way].lru << endl; });

                // break;
            }
        }
    }


    return minway;
}

uint32_t CACHE::fifo_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;
     
    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set][way].valid == false) {

            DP ( if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY) {
        for (way=0; way<NUM_WAY; way++) {
            if (block[set][way].counter == 0) {

                DP ( if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " fifo: " << block[set][way].lru << endl; });

                break;
            }
        }
    }

    if (way == NUM_WAY) {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }

    return way;
}


uint32_t CACHE::lru_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set][way].valid == false) {

            DP ( if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY) {
        for (way=0; way<NUM_WAY; way++) {
            if (block[set][way].lru == NUM_WAY-1) {

                DP ( if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " lru: " << block[set][way].lru << endl; });

                break;
            }
        }
    }

    if (way == NUM_WAY) {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }

    return way;
}

void CACHE::lru_update(uint32_t set, uint32_t way)
{
    // update lru replacement state
    for (uint32_t i=0; i<NUM_WAY; i++) {
        if (block[set][i].lru < block[set][way].lru) {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = 0; // promote to the MRU position
}

void CACHE::lfu_update(uint32_t set, uint32_t way, uint8_t hit)
{
    if (hit) block[set][way].freq++;
    else block[set][way].freq = 0; // promote to the MRU position
    return;

}


void CACHE::fifo_update(uint32_t set, uint32_t way, uint8_t hit)
{
    if (!hit)
    {
        for (uint32_t i = 0; i < NUM_WAY; i++)
        {
            if (i == way) block[set][way].counter = NUM_WAY - 1;
            else block[set][i].counter--;
        }
        
    }
}
void CACHE::rand_update(uint32_t set, uint32_t way)
{
    return;
}

void CACHE::replacement_final_stats()
{

}

#ifdef NO_CRC2_COMPILE
void InitReplacementState()
{

}

uint32_t GetVictimInSet (uint32_t cpu, uint32_t set, const BLOCK *current_set, uint64_t PC, uint64_t paddr, uint32_t type)
{
    return 0;
}

void UpdateReplacementState (uint32_t cpu, uint32_t set, uint32_t way, uint64_t paddr, uint64_t PC, uint64_t victim_addr, uint32_t type, uint8_t hit)
{

}

void PrintStats_Heartbeat()
{

}

void PrintStats()
{

}
#endif
