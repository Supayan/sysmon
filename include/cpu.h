#ifndef CPU_H
#define CPU_H

typedef struct CpuStat
{
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;

} CpuStat;

void read_cpu_stat(CpuStat *s);
long cal_total_delta(CpuStat *s1, CpuStat *s2);
long cal_idle_delta(CpuStat *s1, CpuStat *s2);
double total_cpu_usage(long total_delta, long idle_delta);

#endif