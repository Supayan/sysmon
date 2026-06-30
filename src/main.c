#include <stdio.h>
#include <unistd.h>
#include <string.h>
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

    IOStat io_stat1[10], io_stat2[10], result[10];
    int io_count1 = 0, io_count2 =0, k=0;
    read_disk_io_stat(io_stat1, &io_count1);
    sleep(1);
    read_disk_io_stat(io_stat2,&io_count2);

    for (int i = 0; i <io_count1;i++){
        for (int j = 0; j < io_count2;j++)
        {
            if(strcmp(io_stat1[i].name,io_stat2[j].name)==0){
                calculate_io(&io_stat1[i],&io_stat2[j],&result[k++]);
            }
        }
    }

    for (int i =0;i<k;i++){
        printf("Device Name : %s\t\n", result[i].name);
        printf("Total Read : %lu\t\n", result[i].read);
        printf("Total Read merged : %lu\t\n", result[i].read_merged);
        printf("Total Read sector: %lu\t\n", result[i].sectors_read);
        printf("Total Read MS: %d\t\n", result[i].read_time_ms);
        printf("Total write : %lu\t\n", result[i].write);
        printf("Total write merged : %lu\t\n", result[i].write_merged);
        printf("Total write sector: %lu\t\n", result[i].sectors_written);
        printf("Total write ms: %d\t\n", result[i].write_time_ms);
        printf("Total io : %d\t\n", result[i].io_in_progress);
        printf("Total io ms: %d\t\n", result[i].io_in_ms);
        
        
    }

    return 0;
}