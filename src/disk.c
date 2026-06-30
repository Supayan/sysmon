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

void read_disk_io_stat(IOStat *io,  int *count)
{
    FILE *fp;
    char data[150];

    fp = fopen("/proc/diskstats", "r");
    if (fp == NULL)
    {
        perror("Error opening file : /proc/diskstats\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(data, sizeof(data), fp) != NULL)
    {
        sscanf(data, "%u %u %s %lu %lu %lu %u %lu %lu %lu %u %u %u",
               &io->major, &io->minor, io->name, &io->read, &io->read_merged, &io->sectors_read, &io->read_time_ms, &io->write, &io->write_merged, &io->sectors_written, &io->write_time_ms, &io->io_in_progress, &io->io_in_ms);
        io++;       
        (*count)++;
    }
    fclose(fp);
}
void calculate_io(IOStat *io1, IOStat *io2, IOStat *result)
{
    strcpy(result->name,io1->name);

    result->read = (io2->read - io1->read) * 512; // update the sector size for cross  device. Remove the hardcoded value and get it from /sys/block/sdX/queue/hw_sector_size
    result->read_merged = (io2->read_merged - io1->read_merged) * 512;
    result->sectors_read = (io2->sectors_read - io1->sectors_read) * 512;
    result->read_time_ms = (io2->read_time_ms - io1->read_time_ms);

    result->write = (io2->write - io1->write) * 512; // update the sector size for cross  device. Remove the hardcoded value and get it from /sys/block/sdX/queue/hw_sector_size
    result->write_merged = (io2->write_merged - io1->write_merged) * 512;
    result->sectors_written = (io2->sectors_written - io1->sectors_written) * 512;
    result->write_time_ms = (io2->write_time_ms - io1->write_time_ms);

    result->io_in_progress = (io2->io_in_progress-io1->io_in_progress);
    result->io_in_ms = (io2->io_in_ms-io1->io_in_ms);
}
