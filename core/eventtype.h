// collect all event names and whether we display events of that type
// SPDX-License-Identifier: GPL-2.0
#ifndef EVENTNAME_H
#define EVENTNAME_H

#ifdef __cplusplus
extern "C" {
#endif

extern void clear_event_types(void);
extern void remember_event_type(const struct event *ev);
extern bool is_event_type_hidden(const struct event *ev);
extern void hide_event_type(const struct event *ev);
extern void show_all_event_types();
extern void show_event_type(int idx);
extern bool any_event_types_hidden();

#ifdef __cplusplus
}

// C++-only functions

#include <vector>
#include <QString>
extern std::vector<int> hidden_event_types();
QString event_type_name(const event *ev);
QString event_type_name(int idx);

#endif

#endif
