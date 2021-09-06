#include "Matrix/Memory/memory.h"

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"
#include "Matrix/Core/error.h"

#ifdef ___MTRX_LINUX
#define ___MTRX_MMAP
#endif // ___MTRX_LINUX

#ifdef ___MTRX_DARWIN
#define ___MTRX_MMAP
#endif // ___MTRX_DARWIN

#ifdef ___MTRX_WINDOWS
#include <windows.h>
#endif // ___MTRX_WINDOWS

#ifdef ___MTRX_MMAP
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif // ___MTRX_MMAP

char* matrix_file_mapp(const char* file_path)
{
#ifdef ___MTRX_WINDOWS
    HANDLE handle_a = CreateFileA(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle_a == INVALID_HANDLE_VALUE)
    {
        MTRX_ERROR_UNEXPECTED_VALUE;
    }
    else
    {
        HANDLE handle_mapped = CreateFileMapping(handle_a, NULL, PAGE_READONLY, 0, 0, 0);
        if (handle_mapped == INVALID_HANDLE_VALUE)
        {
            CloseHandle(handle_a);
        }
        else
        {
            if (0 == handle_mapped)
            {
                MTRX_ERROR_UNEXPECTED_VALUE;
            }
            else
            {
                char* raw = MapViewOfFile(handle_mapped, FILE_MAP_READ, 0, 0, 0);
                if (raw == NULL)
                {
                    MTRX_ERROR_UNEXPECTED_NULL;
                }
                else
                {
                    if (0 == handle_mapped)
                    {
                        MTRX_ERROR_UNEXPECTED_VALUE;
                    }
                    else
                    {
                        CloseHandle(handle_mapped);
                    }

                    return raw;
                }
            }
        }
    }
#endif // ___MTRX_WINDOWS

#ifdef ___MTRX_MMAP
    int file = open(file_path, O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat file_stats;

    if (-1 == fstat(file, &file_stats))
    {
        MTRX_ERROR_UNEXPECTED_VALUE;
    }
    else
    {
        char* raw = mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE, file, 0);
        if (NULL == raw)
        {
            MTRX_ERROR_UNEXPECTED_NULL;
        }
        else
        {
            return raw;
        }
    }
#endif // ___MTRX_MMAP
}