#include <stdio.h>
#include <unistd.h>
#include "../include/cpu.h"


int main()
{

    printf("sysmon starting......\n");
    CpuStat stat1, stat2;
    read_cpu_stat(&stat1);
    sleep(1);
    read_cpu_stat(&stat2);

    double cpu_time =0;
    long total_delta = cal_total_delta(&stat1, &stat2);
    long idle_delta = cal_idle_delta(&stat1, &stat2);
    cpu_time = total_cpu_usage(total_delta,idle_delta);
    printf("\n cpu : %.2f%%\n", cpu_time);
    return 0;
}