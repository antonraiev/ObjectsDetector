#pragma once
#include <QtGui>
#include <map>
#include "Database.h"
#include "Structs.h"

enum DbTableName {SNAPSHOTS, SCENES, DESCRIPTIONS, OBJECTS, MAPS};

class DatabaseView
{
public:
	static DatabaseView& getInstance();
	QStringList& getTableNames();
	void removeRow(DbTableName tableName, int row);
	void addToSnapshots(Snapshot &snapshot);
	void addToScenes(Scene &scene);
	void addToDescriptions(Description &description);
	void addToObjects(Object &object);
	QTableWidget* getTable(DbTableName tableName);

private:
	QTableWidget* loadSnapshotsTable();
	QTableWidget* loadScenesTable();
	QTableWidget* loadDescriptionsTable();
	QTableWidget* loadObjectsTable();

	DatabaseView(void);	
	DatabaseView(DatabaseView const&);
	void operator=(DatabaseView const&);
private:
	const QSize snapshotPreviewSize;
	const QSize scenePreviewSize;

	std::map<int,std::pair<QString, QTableWidget*> > tables;
	QStringList tableNames;
};

