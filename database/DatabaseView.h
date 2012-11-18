#pragma once
#include <QtGui>
#include <map>
#include "Database.h"
#include "Structs.h"

enum DbTables {SNAPSHOTS, SCENES, DESCRIPTIONS, OBJECTS, MAPS};

class DatabaseView
{
public:
	DatabaseView(void);
	QTableWidget* snapshotsTable();
	QTableWidget* scenesTable();
	QTableWidget* descriptionsTable();
	QTableWidget* objectsTable();
	~DatabaseView(void);
private:
	std::map<int,std::pair<QString, QTableWidget*> > tables;
};

