// SPDX-License-Identifier: GPL-2.0
#ifndef FILE_H
#define FILE_H

#include "filterpreset.h"

#include <sys/stat.h>
#include <stdio.h>

struct divelog;
struct zip;

#ifdef __cplusplus
extern "C" {
#endif
extern void ostctools_import(const char *file, struct divelog *log);

extern int parse_file(const char *filename, struct divelog *log);
extern int try_to_open_zip(const char *filename, struct divelog *log);

// Platform specific functions
extern int subsurface_rename(const char *path, const char *newpath);
extern int subsurface_dir_rename(const char *path, const char *newpath);
extern int subsurface_open(const char *path, int oflags, mode_t mode);
extern FILE *subsurface_fopen(const char *path, const char *mode);
extern void *subsurface_opendir(const char *path);
extern int subsurface_access(const char *path, int mode);
extern int subsurface_stat(const char *path, struct stat *buf);
extern struct zip *subsurface_zip_open_readonly(const char *path, int flags, int *errorp);
extern int subsurface_zip_close(struct zip *zip);

#ifdef __cplusplus

}

// C++ only functions

#include <vector>
#include <utility>

// return data, errorcode pair.
extern std::pair<std::string, int> readfile(const char *filename);
extern int try_to_open_cochran(const char *filename, std::string &mem, struct divelog *log);
extern int try_to_open_liquivision(const char *filename, std::string &mem, struct divelog *log);
extern int datatrak_import(std::string &mem, std::string &wl_mem, struct divelog *log);

#endif

#endif // FILE_H
