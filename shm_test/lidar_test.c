#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

struct lidar_data {
    float theta;
    float distance;
    int quality;
};

int main(int argc, char *argv[]) {
    const char* name = "SHARED_MEMORY";
    int shm_fd = shm_open(name, O_RDONLY, 0666);
    struct lidar_data *data = (lidar_data*)mmap(NULL, sizeof(*data), PROT_READ, MAP_SHARED, shm_fd, 0);

    while (1) {
        printf("THETA [%f] | DISTANCE [%f] | QUALITY [%d]\n", data->theta, data->distance, data->quality);
    }

    return (0);
}