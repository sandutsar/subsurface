// SPDX-License-Identifier: GPL-2.0
/* implements iOS specific functions */
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include "dive.h"
#include "file.h"
#include "device.h"
#include "core/qthelper.h"
#include <CoreFoundation/CoreFoundation.h>
#if !defined(__IPHONE_5_0)
#include <CoreServices/CoreServices.h>
#endif
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <zip.h>
#include <string>

#include <QStandardPaths>

static std::string system_default_path()
{
	// Qt appears to find a working path for us - let's just go with that
	return QStandardPaths::standardLocations(QStandardPaths::DataLocation).first().toStdString();
}

static std::string make_default_filename()
{
	return system_default_path() + "/subsurface.xml";
}

extern "C" {

const char mac_system_divelist_default_font[] = "Arial";
const char *system_divelist_default_font = mac_system_divelist_default_font;
double system_divelist_default_font_size = -1.0;

void subsurface_OS_pref_setup(void)
{
	// nothing
}

bool subsurface_ignore_font(const char*)
{
	// there are no old default fonts that we would want to ignore
	return false;
}

const char *system_default_directory(void)
{
	static const std::string path = system_default_path();
	return path.c_str();
}

const char *system_default_filename(void)
{
	static const std::string fn = make_default_filename();
	return fn.c_str();
}

int enumerate_devices(device_callback_t, void *, unsigned int)
{
	// we can't read from devices on iOS
	return -1;
}

/* NOP wrappers to comform with windows.c */
int subsurface_rename(const char *path, const char *newpath)
{
	return rename(path, newpath);
}

int subsurface_open(const char *path, int oflags, mode_t mode)
{
	return open(path, oflags, mode);
}

FILE *subsurface_fopen(const char *path, const char *mode)
{
	return fopen(path, mode);
}

void *subsurface_opendir(const char *path)
{
	return (void *)opendir(path);
}

int subsurface_access(const char *path, int mode)
{
	return access(path, mode);
}

int subsurface_stat(const char* path, struct stat* buf)
{
	return stat(path, buf);
}

struct zip *subsurface_zip_open_readonly(const char *path, int flags, int *errorp)
{
	return zip_open(path, flags, errorp);
}

int subsurface_zip_close(struct zip *zip)
{
	return zip_close(zip);
}

/* win32 console */
void subsurface_console_init(void)
{
	/* NOP */
}

void subsurface_console_exit(void)
{
	/* NOP */
}

bool subsurface_user_is_root()
{
	return false;
}
}
