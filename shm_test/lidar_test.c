/*
run make in rplidar_sdk
run make in rplidar_sdk/shm_test

cd into rplidar_sdk/output/Linux/Release
./ultra_simple --channel --serial /dev/ttyUSB0 115200

cd into rplidar_sdk/shm_test
./lidar_test
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

struct lidar_data {
    float theta;
    float distance;
    int quality;
}lidar_data;

int main(int argc, char *argv[]) {
    const char* name = "SHARED_MEMORY";
    int shm_fd = shm_open(name, O_RDONLY, 0666);
    struct lidar_data *data = mmap(NULL, sizeof(struct lidar_data), PROT_READ, MAP_SHARED, shm_fd, 0);

    while (1) {
        printf("THETA [%3.2f] | DISTANCE [%08.2f] | QUALITY [%d]\n", data->theta, data->distance, data->quality);
    }


    munmap(NULL, sizeof(*data));
    shm_unlink(name);
    close(shm_fd);

    return (0);
}