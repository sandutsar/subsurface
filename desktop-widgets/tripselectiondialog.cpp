// SPDX-License-Identifier: GPL-2.0
#include "tripselectiondialog.h"
#include "core/divelog.h"
#include "core/string-format.h"
#include "core/trip.h"
#include <QShortcut>
#include <QPushButton>

TripSelectionDialog::TripSelectionDialog(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.trips, &QListWidget::itemSelectionChanged, this, &TripSelectionDialog::selectionChanged);

	QShortcut *close = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_W), this);
	connect(close, &QShortcut::activated, this, &QDialog::close);
	QShortcut *quit = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this);
	connect(quit, &QShortcut::activated, parent, &QWidget::close);

	// We could use a model, but it seems barely worth the hassle.
	QStringList list;
	list.reserve(divelog.trips->nr);
	for (int i = 0; i < divelog.trips->nr; ++i)
		list.push_back(formatTripTitleWithDives(divelog.trips->trips[i]));
	ui.trips->addItems(list);
}

void TripSelectionDialog::selectionChanged()
{
	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(selectedTrip() != nullptr);
}

dive_trip *TripSelectionDialog::selectedTrip() const
{
	// Accessing the selected index of a QListWidget is ridiculously cumbersome.
	// Note that "currentItem" is a different beast.
	QModelIndexList rows = ui.trips->selectionModel()->selectedRows();
	if (rows.size() != 1)
		return nullptr;
	int idx = rows[0].row();
	if (idx < 0 || idx >= divelog.trips->nr)
		return nullptr;
	return divelog.trips->trips[idx];
}

dive_trip *TripSelectionDialog::getTrip()
{
	return exec() ? selectedTrip() : nullptr;
}
