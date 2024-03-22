// SPDX-License-Identifier: GPL-2.0
#include "qPrefEquipment.h"
#include "qPrefPrivate.h"

static const QString group = QStringLiteral("Equipment");

qPrefEquipment *qPrefEquipment::instance()
{
	static qPrefEquipment *self = new qPrefEquipment;
	return self;
}

void qPrefEquipment::loadSync(bool doSync)
{
	disk_default_cylinder(doSync);
	disk_include_unused_tanks(doSync);
	disk_display_default_tank_infos(doSync);
}

HANDLE_PREFERENCE_TXT(Equipment, "default_cylinder", default_cylinder);
// Keeping the persisted preference name the same to avoid resetting this for everybody
HANDLE_PREFERENCE_BOOL(Equipment, "display_unused_tanks", include_unused_tanks);
HANDLE_PREFERENCE_BOOL(Equipment, "display_default_tank_infos", display_default_tank_infos);
