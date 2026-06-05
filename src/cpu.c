#include <stdio.h>
#include <stdlib.h>
#include "../include/cpu.h"
#include <unistd.h>

void read_cpu_stat(CpuStat *s)
{
    FILE *fp;
    char data[100];
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }
    fgets(data, sizeof(data), fp);
    sscanf(data, "cpu %ld %ld %ld %ld %ld %ld %ld",
           &s->user, &s->nice, &s->system, &s->idle,
           &s->iowait, &s->irq, &s->softirq);
    fclose(fp);
} 

long cal_total_delta(CpuStat *s1, CpuStat *s2){
    return (s2->user+s2->nice+s2->system+s2->idle+s2->iowait+s2->irq+s2->softirq) - (s1->user+s1->nice+s1->system+s1->idle+s1->iowait+s1->irq+s1->softirq);
}

long cal_idle_delta(CpuStat *s1, CpuStat *s2){
    return (s2->idle+s2->iowait) - (s1->idle+s1->iowait);
}

double total_cpu_usage(long total_delta, long idle_delta){
    double cpu;
    cpu = (1.0-((double)idle_delta/total_delta))*100.0;
    return cpu;
}