// SPDX-License-Identifier: GPL-2.0
// A structure that contains all the values we save in a divelog file
#ifndef DIVELOG_H
#define DIVELOG_H

struct dive_table;
struct trip_table;
struct dive_site_table;
struct device_table;
struct filter_preset_table;

#include <stdbool.h>

struct divelog {
	struct dive_table *dives;
	struct trip_table *trips;
	struct dive_site_table *sites;
	struct device_table *devices;
	struct filter_preset_table *filter_presets;
	bool autogroup;
#ifdef __cplusplus
	void clear();
	divelog();
	~divelog();
	divelog(divelog &&log); // move constructor (argument is consumed).
	divelog &operator=(divelog &&log); // move assignment (argument is consumed).
#endif
};

extern struct divelog divelog;

#ifdef __cplusplus
extern "C" {
#endif

void clear_divelog(struct divelog *);

#ifdef __cplusplus
}
#endif

#endif
