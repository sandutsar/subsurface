#include "divesiteimportmodel.h"
#include "core/divelog.h"
#include "core/qthelper.h"
#include "core/taxonomy.h"

DivesiteImportedModel::DivesiteImportedModel(QObject *o) : QAbstractTableModel(o),
	firstIndex(0),
	lastIndex(-1),
	importedSitesTable(nullptr)
{
}

int DivesiteImportedModel::columnCount(const QModelIndex &) const
{
	return 5;
}

int DivesiteImportedModel::rowCount(const QModelIndex &) const
{
	return lastIndex - firstIndex + 1;
}

QVariant DivesiteImportedModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical)
		return QVariant();

	if (role == Qt::DisplayRole) {
		switch (section) {
		case NAME:
			return tr("Name");
		case LOCATION:
			return tr("Location");
		case COUNTRY:
			return tr("Country");
		case NEAREST:
			return tr("Nearest\nExisting Site");
		case DISTANCE:
			return tr("Distance");
		}
	}
	return QVariant();
}

QVariant DivesiteImportedModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() + firstIndex > lastIndex)
		return QVariant();

	struct dive_site *ds = get_dive_site(index.row() + firstIndex, importedSitesTable);
	if (!ds)
		return QVariant();

	// widgets access the model via index.column()
	// Not supporting QML access via roles
	if (role == Qt::DisplayRole) {
		switch (index.column()) {
		case NAME:
			return QString(ds->name);
		case LOCATION:
			return printGPSCoords(&ds->location);
		case COUNTRY:
			return taxonomy_get_country(&ds->taxonomy);
		case NEAREST: {
			// 40075000 is circumference of the earth in meters
			struct dive_site *nearest_ds =
				get_dive_site_by_gps_proximity(&ds->location,
				40075000, divelog.sites);
			if (nearest_ds)
				return QString(nearest_ds->name);
			else
				return QString();
		}
		case DISTANCE: {
			unsigned int distance = 0;
			struct dive_site *nearest_ds =
				get_dive_site_by_gps_proximity(&ds->location,
				40075000, divelog.sites);
			if (nearest_ds)
				distance = get_distance(&ds->location,
					&nearest_ds->location);
			return distance_string(distance);
		}
		case SELECTED:
			return checkStates[index.row()];
		}
	}
	if (role == Qt::CheckStateRole) {
		if (index.column() == 0)
			return checkStates[index.row()] ? Qt::Checked : Qt::Unchecked;
	}
	return QVariant();
}

void DivesiteImportedModel::changeSelected(QModelIndex clickedIndex)
{
	checkStates[clickedIndex.row()] = !checkStates[clickedIndex.row()];
	dataChanged(index(clickedIndex.row(), 0), index(clickedIndex.row(), 0), QVector<int>() << Qt::CheckStateRole << SELECTED);
}

void DivesiteImportedModel::selectAll()
{
	std::fill(checkStates.begin(), checkStates.end(), true);
	dataChanged(index(0, 0), index(lastIndex - firstIndex, 0), QVector<int>() << Qt::CheckStateRole << SELECTED);
}

void DivesiteImportedModel::selectRow(int row)
{
	checkStates[row] = !checkStates[row];
	dataChanged(index(row, 0), index(row, 0), QVector<int>() << Qt::CheckStateRole << SELECTED);
}

void DivesiteImportedModel::selectNone()
{
	std::fill(checkStates.begin(), checkStates.end(), false);
	dataChanged(index(0, 0), index(lastIndex - firstIndex,0 ), QVector<int>() << Qt::CheckStateRole << SELECTED);
}

Qt::ItemFlags DivesiteImportedModel::flags(const QModelIndex &index) const
{
	if (index.column() != 0)
		return QAbstractTableModel::flags(index);
	return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable;
}

void DivesiteImportedModel::repopulate(struct dive_site_table *sites)
{
	beginResetModel();

	importedSitesTable = sites;
	firstIndex = 0;
	lastIndex = importedSitesTable->nr - 1;
	checkStates.resize(importedSitesTable->nr);
	for (int row = 0; row < importedSitesTable->nr; row++)
		if (get_dive_site_by_gps(&importedSitesTable->dive_sites[row]->location, divelog.sites))
			checkStates[row] = false;
		else
			checkStates[row] = true;
	endResetModel();
}
