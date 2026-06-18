#include <limits.h>

#ifndef DISK_H
#define DISK_H

typedef struct
{
    char mount[PATH_MAX];
    unsigned long total;
    unsigned long used;
    unsigned long avalible;
} DiskStat;

typedef struct
{
    char name[50];
    char path[50];
    char type[50];
} MountDevice;

void read_disk_stat(DiskStat *ds, int *count);

#endif