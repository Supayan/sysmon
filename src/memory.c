#include "../include/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_mem_stat(MemStat *m)
{
    FILE *fp;
    char data[100];
    int counter = 0;
    char *arr[] = {"MemTotal:", "MemAvailable:", "Buffers:", "Cached:","SwapTotal:", "SwapFree:"};
    unsigned long *fields[] = {&m->memtotal, &m->memAvailable, &m->buffers, &m->cached, &m->swapTotal, &m->swapFree};
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Failed to open /proc/meminfo");
        exit(EXIT_FAILURE);
    }
    while (fgets(data, sizeof(data), fp) != NULL)
    {
        for (int i = 0; i < (int)(sizeof(arr)/sizeof(arr[0])); i++)
        {
            if (strncmp(data, arr[i], strlen(arr[i])) == 0)
            {
                sscanf(data, "%*s %lu", fields[i]);
                counter++;
            }
        }
        if (counter == 6)break;
    }
    fclose(fp);
}

long mem_used_cal (MemStat *m){
    return m->memtotal-m->memAvailable;
}

double mem_percentage(MemStat *m){
    return ((double)mem_used_cal(m)/m->memtotal)*100;
}

long swap_cal(MemStat *m){
    return m->swapTotal-m->swapFree;
}

double swap_percentage(MemStat *m){
    return ((double)swap_cal(m)/m->swapTotal)*100;
}