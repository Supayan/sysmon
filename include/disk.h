#include <limits.h>

#ifndef DISK_H
#define DISK_H

typedef struct
{
    char name [50];
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

typedef struct{
    double size;
    char unit[3];
}SizeUnit;

typedef struct {
    unsigned int major;
    unsigned int minor;
    char name[50];
    unsigned long read;
    unsigned long read_merged;
    unsigned long sectors_read;
    unsigned int read_time_ms;
    unsigned long write;
    unsigned long write_merged;
    unsigned long sectors_written;
    unsigned int write_time_ms;
    unsigned int io_in_progress;
    unsigned int io_in_ms;
} IOStat;

void read_disk_stat(DiskStat *ds, int *count);
void total_disk_size(unsigned long num, SizeUnit *su);
void read_disk_io_stat(IOStat *io, int* count);
void calculate_io(IOStat *io1, IOStat *io2, IOStat *result);
#endif