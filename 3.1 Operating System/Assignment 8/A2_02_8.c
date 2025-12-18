
/***********************************************************************
 *
 * 3rd Year 1st Semester OS Lab - Information Technology
 * Section: A2
 * Team Number: 02
 *    Team Member Names                   Roll Numbers
 * 1. Abishkar Chatterjee (Team Leader) - 002311001080
 * 2. Atrij Roy                         - 002311001086
 * 3. Soyeb Hoque                       - 002311001065
 *
 * Assignment: ASSIGNMENT_8T_A2
 * Total Marks – 10 [CO2]
 * NAME: Observing the OS through the /proc file system
 * HOW TO RUN:
Compile and run with ./a.out for:
● Processor Informations (Vendor ID, Model Name, CPU Clock Speed
and Cache Size in MB)
● Kernel Name, Kernel Release and Operating System Name.
● The amount of memory configured into this computer and Free
Memory
● Amount of time since the system was last booted (In Hours, Minutes,
Seconds)

Run with ./a.out c for:
● The percentage of time the processor(s) spend in user mode, system
mode, and idle mode
● The amount and percentage of available (or free) memory
● The rate (number per second) of context switches in the kernel
● The rate (number per second) of process creations in the system
● Per second disk read/write in the system
● Per second Timer Interrupts
● Currently executing kernel scheduling entities (processes, threads)
● Number of kernel scheduling entities that currently exist on the
system
 * ===================================================================
 * 			SAMPLE OUTPUT GENERATED
 * ===================================================================
 * $ gcc A2_02_8.c
 * $ ./a.out
-- Processor Information ---
Vendor ID: 	GenuineIntel
Model Name: 	12th Gen Intel(R) Core(TM) i5-12500
CPU Clock Speed: 3000.000 MHz
Cache Size: 	18.00 MB

--- System Information ---
Kernel Name: 	Linux
Kernel Release: 	5.15.0-139-generic
OS Name: 	Ubuntu

--- Memory Information ---
Total Memory: 	16053796 kB
Free Memory: 	7950456 kB

--- Uptime ---
System Uptime: 	287 hours, 18 minutes, 28 seconds

 * $ ./a.out c
 --- Dynamic System Stats (Updating every 1s) ---

CPU Usage:	User: 0.00%  System: 0.00%  Idle: 100.00%
Free Memory:	7309424 kB out of 16053796 kB (45.53% / 100%) 
Context Switches:	2 per second
Process Creations:	0 per second
Disk I/O Rate:	Read: 0.00 KB/s  Write: 0.00 KB/s
Timer Interrupts:	0 per second
Kernel Entities:	1 executing, 1010 total
--- Dynamic System Stats (Updating every 1s) ---

CPU Usage:	User: 0.67%  System: 0.08%  Idle: 98.75%
Free Memory:	7304344 kB out of 16053796 kB (45.50% / 100%) 
Context Switches:	1231 per second
Process Creations:	0 per second
Disk I/O Rate:	Read: 0.00 KB/s  Write: 4032.00 KB/s
Timer Interrupts:	592 per second
Kernel Entities:	1 executing, 1009 total

 * ===================================================================
 * 		Verification of Output with commands
 * ===================================================================
 *
 * --- STATIC INFORMATION VERIFICATION ---
 *
 * [Processor Info]
 * $ lscpu | grep -E "Vendor ID|Model name|CPU MHz|Cache"
 * Vendor ID:                            GenuineIntel
 * Model name:                           12th Gen Intel(R) Core(TM) i5-12500
 * CPU MHz:   			          3000.000
 *
 * $ grep -m 1 "cache size" /proc/cpuinfo
 * cache size	: 18432 KB
 *
 * [Kernel/OS Info]
 * $ uname -snr
 * Linux adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC 5.15.0-139-generic
 *
 * $ cat /etc/os-release | grep "PRETTY_NAME"
 * PRETTY_NAME="Ubuntu 20.04.6 LTS"
 *
 * [Memory Info]
 * $ free -h
 *               total        used        free      shared  buff/cache   available
 * Mem:           15Gi       2.1Gi       7.7Gi       559Mi       5.6Gi        12Gi
 * Swap:         2.0Gi          0B       2.0Gi
 *
 *
 * [Uptime]
 * $ uptime
 * 12:50:11 up 11 days, 23:17,  1 user,  load average: 0.69, 0.63, 0.58
 *
 *
 *
 * --- DYNAMIC INFORMATION VERIFICATION (using sar) ---
 *
 * [Install sar]
 * $ sudo apt install sysstat
 *
 * [CPU % (user, system, idle)]
 * $ sar -u 1 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	29/10/25 	_x86_64_	(12 CPU)

 * 12:53:15 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
 * 12:53:16 PM IST     all      0.34      0.00      0.08      0.00      0.00     99.58
 * Average:        all      0.34      0.00      0.08      0.00      0.00     99.58

 *
 * [Free Memory (Amount, %)]
 * $ sar -r 1 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	29/10/25 	_x86_64_	(12 CPU)
 *
 * 12:54:00 PM IST kbmemfree   kbavail kbmemused  %memused kbbuffers  kbcached  kbcommit   %commit  kbactive   kbinact   kbdirty
 * 12:54:01 PM IST   8014624  12960064   2009428     12.52    921700   4732424   6662040     36.70   3065076   3812276       348
 * Average:      8014624  12960064   2009428     12.52    921700   4732424   6662040     36.70   3065076   3812276       348

 * [Context Switch & Process Creation Rate]
 * $ sar -w 1 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	29/10/25 	_x86_64_	(12 CPU)
 *
 * 12:54:48 PM IST    proc/s   cswch/s
 * 12:54:49 PM IST      0.00   2064.00
 * Average:         0.00   2064.00

 *
 * [Disk R/W Rate]
 * $ sar -b 1 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	29/10/25 	_x86_64_	(12 CPU)

 * 12:55:18 PM IST       tps      rtps      wtps      dtps   bread/s   bwrtn/s   bdscd/s
 * 12:55:19 PM IST      0.00      0.00      0.00      0.00      0.00      0.00      0.00
 * Average:         0.00      0.00      0.00      0.00      0.00      0.00      0.00
 * 
 *
 * [Timer Interrupts Rate]
 * $ vmstat 1 2
 * procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 * r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 * 1  0      0 7947916 921856 4918960    0    0     0     3    2    0  0  0 100  0  0
 * 0  0      0 7952292 921856 4915136    0    0     0     0 1029 2604  1  0 99  0  0
 *
 * [Scheduling Entities (Executing, Total)]
 * $ sar -q 1 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	29/10/25 	_x86_64_	(12 CPU)

 * 01:00:50 PM IST   runq-sz  plist-sz   ldavg-1   ldavg-5  ldavg-15   blocked
 * 01:00:51 PM IST         0       919      0.86      0.66      0.62         0
 * Average:            0       919      0.86      0.66      0.62         0
 * (Note: 'runq-sz' = executing, 'plist-sz' = total entities)
 *
 * ===================================================================
 * 				   CODE
 * ===================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep()
#include <ctype.h>  // For isspace()

// --- Helper Function to trim leading/trailing whitespace ---
char *trim_whitespace(char *str) {
    char *end;
    // Trim leading space
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str; // All spaces?

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end + 1) = 0;
    return str;
}

// --- Helper Function to parse key-value files like /proc/cpuinfo ---
/**
 * A robust helper function to parse files with key-value pairs.
 * It can handle delimiters of both ':' (colon) and '=' (equals sign).
 * It also handles leading/trailing whitespace.
 */
int parse_file_value(const char *filepath, const char *key, char *buffer, int buffer_size) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror(filepath);
        return 0;
    }

    char line[512];
    int found = 0;
    size_t key_len = strlen(key);

    while (fgets(line, sizeof(line), fp)) {
        // Trim leading whitespace
        char *trimmed_line = line;
        while (isspace((unsigned char)*trimmed_line)) {
            trimmed_line++;
        }

        // Check if the line starts with our key
        if (strncmp(trimmed_line, key, key_len) == 0) {
            
            // Find the delimiter (':' or '=')
            char *delimiter = strchr(trimmed_line, ':');
            if (delimiter == NULL) {
                delimiter = strchr(trimmed_line, '=');
            }

            // If we found a delimiter...
            if (delimiter) {
                char *value = delimiter + 1; // Point to the character after the delimiter

                // Trim leading whitespace from the value
                while (isspace((unsigned char)*value)) {
                    value++;
                }
                
                // Remove trailing newline
                value[strcspn(value, "\r\n")] = 0;
                
                // Copy the final value into the buffer
                strncpy(buffer, value, buffer_size - 1);
                buffer[buffer_size - 1] = '\0'; // Ensure null-termination
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found; // Will be 1 if found, 0 if not
}

// --- Helper Function to get a single long value from /proc/stat ---
long get_stat_line_value(const char* key) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("/proc/stat");
        return 0;
    }
    
    char line[512];
    long value = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, key, strlen(key)) == 0) {
            // e.g., "ctxt 123456" or "processes 789"
            if (sscanf(line + strlen(key), "%ld", &value) == 1) {
                break;
            }
        }
    }
    fclose(fp);
    return value;
}


// --- PART 1: Static Information ---
void print_static_info() {
    char buffer[256];

    printf("--- Processor Information ---\n");
    if (parse_file_value("/proc/cpuinfo", "vendor_id", buffer, sizeof(buffer))) {
        printf("Vendor ID: \t%s\n", buffer);
    }
    if (parse_file_value("/proc/cpuinfo", "model name", buffer, sizeof(buffer))) {
        printf("Model Name: \t%s\n", buffer);
    }
    if (parse_file_value("/proc/cpuinfo", "cpu MHz", buffer, sizeof(buffer))) {
        printf("CPU Clock Speed: %s MHz\n", buffer);
    }
    if (parse_file_value("/proc/cpuinfo", "cache size", buffer, sizeof(buffer))) {
        // Value is like "12288 KB"
        float cache_kb = atof(buffer);
        printf("Cache Size: \t%.2f MB\n", cache_kb / 1024.0);
    }
    
    printf("\n--- System Information ---\n");
    FILE *fp_ver = fopen("/proc/version", "r");
    if (fp_ver) {
        char kernel_name[64], version[64], kernel_release[128];
        if (fscanf(fp_ver, "%s %s %s", kernel_name, version, kernel_release) == 3) {
            printf("Kernel Name: \t%s\n", kernel_name);
            printf("Kernel Release: \t%s\n", kernel_release);
        }
        fclose(fp_ver);
    }
    
    if (parse_file_value("/etc/os-release", "NAME", buffer, sizeof(buffer))) {
        // The value from the file is in quotes, like "Ubuntu 22.04 LTS"
        // This code removes the quotes for clean printing:
        
        buffer[strlen(buffer)-1] = '\0'; // Remove trailing "
        printf("OS Name: \t%s\n", buffer + 1); // Skip leading "
    } else {
        printf("OS Name: \tNot found\n");
    }
    //if (parse_file_value("/etc/os-release", "PRETTY_NAME", buffer, sizeof(buffer))) {
        // Value is like "Ubuntu 22.04.3 LTS" with quotes
        //buffer[strlen(buffer)-1] = '\0'; // Remove trailing "
        //printf("OS Name: \t%s\n", buffer + 1); // Skip leading "
    //}

    printf("\n--- Memory Information ---\n");
    if (parse_file_value("/proc/meminfo", "MemTotal", buffer, sizeof(buffer))) {
        printf("Total Memory: \t%s\n", buffer);
    }
    if (parse_file_value("/proc/meminfo", "MemFree", buffer, sizeof(buffer))) {
        printf("Free Memory: \t%s\n", buffer);
    }

    printf("\n--- Uptime ---\n");
    FILE *fp_up = fopen("/proc/uptime", "r");
    if (fp_up) {
        double uptime_seconds;
        if (fscanf(fp_up, "%lf", &uptime_seconds) == 1) {
            long total_seconds = (long)uptime_seconds;
            long hours = total_seconds / 3600;
            long minutes = (total_seconds % 3600) / 60;
            long seconds = total_seconds % 60;
            printf("System Uptime: \t%02ld hours, %02ld minutes, %02ld seconds\n", hours, minutes, seconds);
        }
        fclose(fp_up);
    }
}


// --- PART 2: Dynamic Information ---

// Struct to hold CPU time values (in jiffies)
typedef struct {
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
} CpuStats;

// Get current total CPU stats
int get_cpu_stats(CpuStats* stats) {
    FILE* fp = fopen("/proc/stat", "r");
    if (!fp) return 0;
    
    char line[256];
    int found = 0;
    if (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "cpu ", 4) == 0) {
            sscanf(line, "cpu  %ld %ld %ld %ld %ld %ld %ld %ld",
                &stats->user, &stats->nice, &stats->system, &stats->idle,
                &stats->iowait, &stats->irq, &stats->softirq, &stats->steal);
            found = 1;
        }
    }
    fclose(fp);
    return found;
}

// Get current total disk I/O stats (in sectors)
int get_disk_stats(long* sectors_read, long* sectors_written) {
    FILE* fp = fopen("/proc/diskstats", "r");
    if (!fp) return 0;

    char line[256];
    long total_read = 0;
    long total_written = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        char dev_name[64];
        long s_read, s_written;
        
        // Fields 3 (name), 6 (sectors read), 10 (sectors written)
        int fields = sscanf(line, "%*d %*d %63s %*d %*d %ld %*d %*d %*d %ld",
                            dev_name, &s_read, &s_written);
        
        if (fields == 3) {
            // Only sum major block devices, ignore partitions
            // This checks for "sd[a-z]" or "nvme[0-9]n[0-9]"
            if ((strncmp(dev_name, "sd", 2) == 0 && strlen(dev_name) == 3) ||
                (strncmp(dev_name, "nvme", 4) == 0 && strchr(dev_name, 'n') != NULL)) 
            {
                total_read += s_read;
                total_written += s_written;
            }
        }
    }
    fclose(fp);
    *sectors_read = total_read;
    *sectors_written = total_written;
    return 1;
}


void run_continuous_mode() {
    // Store previous values to calculate rates
    CpuStats prev_cpu;
    get_cpu_stats(&prev_cpu);
    
    long prev_ctxt = get_stat_line_value("ctxt");
    long prev_procs = get_stat_line_value("processes");
    long prev_intr = get_stat_line_value("intr");
    
    long prev_sectors_read = 0, prev_sectors_written = 0;
    get_disk_stats(&prev_sectors_read, &prev_sectors_written);

    while (1) {
        //printf("\033[2J\033[H");
        printf("--- Dynamic System Stats (Updating every 1s) ---\n\n");

        // --- 1. CPU Percentage ---
        CpuStats curr_cpu;
        get_cpu_stats(&curr_cpu);

        long prev_total = prev_cpu.user + prev_cpu.nice + prev_cpu.system + prev_cpu.idle +
                          prev_cpu.iowait + prev_cpu.irq + prev_cpu.softirq + prev_cpu.steal;
        long curr_total = curr_cpu.user + curr_cpu.nice + curr_cpu.system + curr_cpu.idle +
                          curr_cpu.iowait + curr_cpu.irq + curr_cpu.softirq + curr_cpu.steal;

        long delta_total = curr_total - prev_total;
        
        if (delta_total > 0) {
            double pct_user = 100.0 * (curr_cpu.user - prev_cpu.user) / delta_total;
            double pct_system = 100.0 * (curr_cpu.system - prev_cpu.system) / delta_total;
            double pct_idle = 100.0 * (curr_cpu.idle - prev_cpu.idle) / delta_total;
            printf("CPU Usage:\tUser: %.2f%%  System: %.2f%%  Idle: %.2f%%\n",
                   pct_user, pct_system, pct_idle);
        } else {
            printf("CPU Usage:\tUser: 0.00%%  System: 0.00%%  Idle: 100.00%%\n");
        }
        prev_cpu = curr_cpu;

        // --- 2. Free Memory ---
        char total_buf[64], free_buf[64];
        long mem_total_kb = 0, mem_free_kb = 0;
        if (parse_file_value("/proc/meminfo", "MemTotal", total_buf, sizeof(total_buf))) {
            mem_total_kb = atol(total_buf);
        }
        if (parse_file_value("/proc/meminfo", "MemFree", free_buf, sizeof(free_buf))) {
            mem_free_kb = atol(free_buf);
        }
        if (mem_total_kb > 0) {
            double pct_free = 100.0 * mem_free_kb / mem_total_kb;
            printf("Free Memory:\t%ld kB out of %ld kB (%.2f%% / 100%%) \n", mem_free_kb, mem_total_kb, pct_free);
        }

        // --- 3. Context Switches Rate ---
        long curr_ctxt = get_stat_line_value("ctxt");
        printf("Context Switches:\t%ld per second\n", curr_ctxt - prev_ctxt);
        prev_ctxt = curr_ctxt;

        // --- 4. Process Creations Rate ---
        long curr_procs = get_stat_line_value("processes");
        printf("Process Creations:\t%ld per second\n", curr_procs - prev_procs);
        prev_procs = curr_procs;

        // --- 5. Disk Read/Write Rate ---
        long curr_sectors_read = 0, curr_sectors_written = 0;
        get_disk_stats(&curr_sectors_read, &curr_sectors_written);
        
        // Sector size is 512 bytes. (Rate * 512) / 1024 = Rate / 2 (in KB/s)
        double read_rate_kb = (double)(curr_sectors_read - prev_sectors_read) * 512.0 / 1024.0;
        double write_rate_kb = (double)(curr_sectors_written - prev_sectors_written) * 512.0 / 1024.0;
        printf("Disk I/O Rate:\tRead: %.2f KB/s  Write: %.2f KB/s\n",
               read_rate_kb, write_rate_kb);
        
        prev_sectors_read = curr_sectors_read;
        prev_sectors_written = curr_sectors_written;

        // --- 6. Timer Interrupts Rate ---
        long curr_intr = get_stat_line_value("intr");
        printf("Timer Interrupts:\t%ld per second\n", curr_intr - prev_intr);
        prev_intr = curr_intr;

        // --- 7. & 8. Scheduling Entities ---
        FILE *fp_load = fopen("/proc/loadavg", "r");
        if (fp_load) {
            int executing, total;
            // Format: 1.23 1.11 1.00 1/500 12345
            if (fscanf(fp_load, "%*f %*f %*f %d/%d", &executing, &total) == 2) {
                printf("Kernel Entities:\t%d executing, %d total\n", executing, total);
            }
            fclose(fp_load);
        }
        
        fflush(stdout); // Flush output to terminal
        sleep(1);       // Wait for one second
    }
}


// --- Main Function ---
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments: Print static info and exit
        print_static_info();
    } else if (argc == 2 && strcmp(argv[1], "c") == 0) {
        // Argument 'c': Run in continuous mode
        run_continuous_mode();
    } else {
        // Invalid arguments
        fprintf(stderr, "Usage: %s [c]\n", argv[0]);
        fprintf(stderr, "  (no argument) \t- Print static system information.\n");
        fprintf(stderr, "  c \t\t\t- Run continuously and print dynamic stats.\n");
        return 1; // Exit with an error
    }

    return 0; // Success
}
