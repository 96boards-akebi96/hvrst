// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2018 Socionext Inc.

#include <unistd.h>

#define LOG_TAG "hvrst"
#include <log/log.h>

#define PORT_ID "375" // P84 = 307 + 8*8 + 4 = 375
#define SYSFS_EXPORT  "/sys/class/gpio/export"
#define SYSFS_GPIO375_DIR "/sys/class/gpio/gpio375/direction"
#define SYSFS_GPIO375_VAL "/sys/class/gpio/gpio375/value"

int main(int , char **)
{
    int ret = 0;
    int fd = -1;

    // create gpio375
    fd = open(SYSFS_EXPORT, O_WRONLY);
    if (fd < 0) {
        ALOGE("%s:%d Can't open %s", __func__, __LINE__, SYSFS_EXPORT);
        return -1;
    }
    ret = write(fd, PORT_ID, sizeof(PORT_ID));
    if (ret != sizeof(PORT_ID)) {
        ALOGE("%s:%d Write error %d", __func__, __LINE__, ret);
        close(fd);
        return -1;
    }
    close(fd);

    // P84 direction : outout
    fd = open(SYSFS_GPIO375_DIR, O_WRONLY);
    if (fd < 0) {
        ALOGE("%s:%d Can't open %s", __func__, __LINE__, SYSFS_GPIO375_DIR);
        return -1;
    }
    ret = write(fd, "out", sizeof("out"));
    if (ret != sizeof("out")) {
        ALOGE("%s:%d Write error %d", __func__, __LINE__, ret);
        close(fd);
        return -1;
    }
    close(fd);

    // P84 value open
    fd = open(SYSFS_GPIO375_VAL, O_WRONLY);
    if (fd < 0) {
        ALOGE("%s:%d Can't open %s", __func__, __LINE__, SYSFS_GPIO375_VAL);
        return -1;
    }

    // P84 value : 1
    ret = write(fd, "1", sizeof("1"));
    if (ret != sizeof("1")) {
        ALOGE("%s:%d Write error %d", __func__, __LINE__, ret);
        close(fd);
        return -1;
    }

    usleep(500*1000);

    // P84 value : 0
    ret = write(fd, "0", sizeof("0"));
    if (ret != sizeof("0")) {
        ALOGE("%s:%d Write error %d", __func__, __LINE__, ret);
        close(fd);
        return -1;
    }

    usleep(500*1000);

    // P84 value : 1
    ret = write(fd, "1", sizeof("1"));
    if (ret != sizeof("1")) {
        ALOGE("%s:%d Write error %d", __func__, __LINE__, ret);
        close(fd);
        return -1;
    }

    close(fd);

    return ret;
    
}
