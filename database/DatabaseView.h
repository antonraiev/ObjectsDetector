#pragma once
#include <QtGui>
#include <map>
#include "Database.h"
#include "Structs.h"

enum DbTables {SNAPSHOTS, SCENES, DESCRIPTIONS, OBJECTS, MAPS};

class DatabaseView
{
public:
	static DatabaseView& getInstance();
	QTableWidget* snapshotsTable();
	QTableWidget* scenesTable();
	QTableWidget* descriptionsTable();
	QTableWidget* objectsTable();

private:
	DatabaseView(void);	
	DatabaseView(DatabaseView const&);
	void operator=(DatabaseView const&);
private:
	std::map<int,std::pair<QString, QTableWidget*> > tables;
};

