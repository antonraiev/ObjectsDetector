#pragma once
#include "Database.h"
#include <QtGui>
#include "Structs.h"
class DatabaseModel
{
public:
	DatabaseModel(void);
	void setDatabase(Database &db);
	QTableWidget* snapshotsTable();
	QTableWidget* scenesTable();
	QTableWidget* descriptionsTable();
	QTableWidget* objectsTable();
	~DatabaseModel(void);
private:
	Database *db;
};

