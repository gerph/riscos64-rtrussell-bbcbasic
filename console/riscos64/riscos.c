#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "kernel.h"
#include "swis.h"

#define MAX_PATH 260

#include "swis_os.h"


int chdir(const char *dir)
{
    return (os_fscontrol2(0, dir) == NULL) ? 0 : -1;
}

int mkdir(const char *dir, int mode)
{
    return (os_file2(8, dir) == NULL) ? 0 : -1;
}

int rmdir(const char *dir)
{
    return remove(dir) ? 0 : -1;
}

int chmod(const char *file, int mode)
{
    /* No implementation on RISC OS */
    return 0;
}


char *realpath(const char *filename, char *result_path)
{
    _kernel_oserror *err;
    bool alloced = false;
    if (result_path == NULL)
    {
        alloced = true;
        result_path = malloc(MAX_PATH);
        if (result_path == NULL)
            return NULL;
    }
    err = _swix(OS_FSControl, _INR(0,5), 37, filename, result_path,
                                         NULL, NULL, MAX_PATH);
    if (err && alloced)
        free(result_path);
    return err == NULL ? result_path : NULL;
}

char *getcwd(void)
{
    static char buf[1024];
    return realpath("@", buf);
}

ssize_t write(int fileno, char *data, size_t size)
{
    _kernel_oserror *err;
    size_t not_transferred = 0;
    err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 2, fileno, data, size, &not_transferred);
    if (err)
        return -1;
    return size - not_transferred;
}

ssize_t read(int fileno, char *data, size_t size)
{
    _kernel_oserror *err;
    size_t not_transferred = 0;
    err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 4, fileno, data, size, &not_transferred);
    if (err)
        return -1;
    return size - not_transferred;
}

long long int llabs(long long int value)
{
    if (value < 0)
        value = -value;
    return value;
}

void __clear_cache(char *begin, char *end)
{
    _swix(OS_SynchroniseCodeAreas, _INR(0, 2), 1, begin, end);
}

void putevt(void)
{
    /* FIXME: Not implemented */
}
