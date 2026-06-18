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
    char *arr[] = {"ext4", "zfs", "btrfs", "xfs", "exfat"};
    fp = fopen("/proc/mounts", "r");
    if (fp == NULL)
    {
        perror("Failed to open /proc/mounts");
        exit(EXIT_FAILURE);
    }
    while (fgets(data, sizeof(data), fp) != NULL)
    {
        sscanf(data, "%s %s %s", tmpmd.name, tmpmd.path, tmpmd.type);
        for (int i = 0; i < (int)(sizeof(arr)/sizeof(arr[0])); i++)
        {
            if (strcmp(tmpmd.type, arr[i]) == 0)
            {
                if (statvfs(tmpmd.path, &sv) == 0)
                {
                    strcpy(ds->mount,tmpmd.path);
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