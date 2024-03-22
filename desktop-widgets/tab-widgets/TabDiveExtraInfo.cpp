// SPDX-License-Identifier: GPL-2.0
#include "TabDiveExtraInfo.h"
#include "ui_TabDiveExtraInfo.h"
#include "core/dive.h"
#include "core/selection.h"
#include "qt-models/divecomputerextradatamodel.h"

TabDiveExtraInfo::TabDiveExtraInfo(MainTab *parent) :
	TabBase(parent),
	ui(new Ui::TabDiveExtraInfo()),
	extraDataModel(new ExtraDataModel(this))
{
	ui->setupUi(this);
	ui->extraData->setModel(extraDataModel);
}

TabDiveExtraInfo::~TabDiveExtraInfo()
{
	delete ui;
}

void TabDiveExtraInfo::updateData(const std::vector<dive *> &, dive *currentDive, int currentDC)
{
	const struct divecomputer *currentdc = get_dive_dc(currentDive, currentDC);
	if (currentdc)
		extraDataModel->updateDiveComputer(currentdc);
}

void TabDiveExtraInfo::clear()
{
	extraDataModel->clear();
}
