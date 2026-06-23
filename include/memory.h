#ifndef MEMORY_H
#define MEMORY_H


typedef struct 
{
    unsigned long memtotal;
    unsigned long memAvailable;
    unsigned long swapTotal;
    unsigned long swapFree;
    unsigned long buffers;
    unsigned long cached;
} MemStat;

void read_mem_stat(MemStat *m);
long mem_used_cal(MemStat *m);
double mem_percentage(MemStat *m);
long swap_cal (MemStat *m);
double swap_percentage(MemStat *m);

#endif