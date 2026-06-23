#include <stdio.h>
#include <stdlib.h>
#include "../include/disk.h"
#include <unistd.h>
#include <sys/statvfs.h>
#include <string.h>
#include <ctype.h>

void read_disk_stat(DiskStat *ds, int *count)
{
    FILE *fp;
    char data[150];
    MountDevice tmpmd;
    struct statvfs sv;
    char *arr[] = {"ext4", "ext3", "ext2", "xfs", "btrfs", "vfat", "ntfs", "exfat", "fuseblk"};
    fp = fopen("/proc/mounts", "r");
    if (fp == NULL)
    {
        perror("Failed to open /proc/mounts");
        exit(EXIT_FAILURE);
    }
    while (fgets(data, sizeof(data), fp) != NULL)
    {
        sscanf(data, "%s %s %s", tmpmd.name, tmpmd.path, tmpmd.type);
        for (int i = 0; i < (int)(sizeof(arr) / sizeof(arr[0])); i++)
        {
            if (strcmp(tmpmd.type, arr[i]) == 0)
            {
                if (statvfs(tmpmd.path, &sv) == 0)
                {
                    strcpy(ds->name, tmpmd.name);
                    strcpy(ds->mount, tmpmd.path);
                    ds->total = sv.f_blocks * sv.f_frsize;
                    ds->avalible = sv.f_bavail * sv.f_frsize;
                    ds->used = (sv.f_bfree - sv.f_bavail) * sv.f_frsize;
                    ds++;
                    (*count)++;
                    break;
                }
                else
                {
                    perror("Unable to read the disk stat");
                    break;
                }
            }
        }
    }
    fclose(fp);
}

void total_disk_size(unsigned long num, SizeUnit *su)
{
    double size = 0.00;
    size = (double)num / (double)(1024 * 1024 * 1024);
    if (size < 1.0)
    {
        size = size * 1024;
        if (size < 1.0)
        {
            size = size * 1024;
            su->size = size;
            strcpy(su->unit, "KB");
        }
        else
        {
            su->size = size;
            strcpy(su->unit, "MB");
        }
    }
    else
    {
        su->size = size;
        strcpy(su->unit, "GB");
    }
}