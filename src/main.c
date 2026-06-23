#include <stdio.h>
#include <unistd.h>
#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/disk.h"

int main()
{

    printf("sysmon starting......\n");
    CpuStat stat1, stat2;
    read_cpu_stat(&stat1);
    sleep(1);
    read_cpu_stat(&stat2);

    double cpu_time = 0;
    long total_delta = cal_total_delta(&stat1, &stat2);
    long idle_delta = cal_idle_delta(&stat1, &stat2);
    cpu_time = total_cpu_usage(total_delta, idle_delta);
    printf("\n cpu : %.2f%%\n", cpu_time);

    MemStat memory_status;
    read_mem_stat(&memory_status);

    printf("\n Memory used %% : %.2f%%\n", mem_percentage(&memory_status));
    printf("\n Swap used %% : %.2f%%\n", swap_percentage(&memory_status));

    DiskStat ds[10];
    int count = 0;
    read_disk_stat(ds, &count);
    SizeUnit su;

    for (int i = 0; i < count; i++)
    {
        printf("Name : %s\n", ds[i].name);
        printf("Mount Point : %s\n", ds[i].mount);
        total_disk_size(ds[i].total, &su);
        printf("Total Disk Size : %.2f %s\t", su.size, su.unit);
        printf("Total Disk Space : %lu\n", ds[i].total);
        total_disk_size(ds[i].used, &su);
        printf("Disk Space used : %.2f %s\t", su.size, su.unit);
        printf("Used space : %lu\n", ds[i].used);
        total_disk_size(ds[i].avalible, &su);
        printf("Disk Space Avalible : %.2f %s\t", su.size, su.unit);
        printf("Avalible space : %lu\n\n", ds[i].avalible);
    }
    return 0;
}