#pragma once
#include <QtGui>
#include <QtSql>
#include "Structs.h"
#define ROBOT_ID 8

class Database
{
public:
	Database(void);
	~Database(void);
	bool connect();
	void disconnect();
	int addSnapshot(QImage &image);
	int addSnapshot(QPixmap &pixmap);
	Snapshot getSnapshot(int id) const;
	int addScene(QPixmap &pixmap);
	Scene getScene(int id) const;
	void addPart(int sceneId,int snapshotId);
	void addObject(int nameId,QPixmap object,int physHeight);
	QList<Snapshot> getSnapshots() const;
	QList<Scene> getScenes() const;
	void addDescription(QString name,QString description);
	QList<Description> getDescriptions();
	QList<Object> getObjects();
	void changeDescription(Description descr);
	void deleteDescription(int id);
	void deleteSnapshot(int id);
	void deleteScene(int id);
	void deleteObject(int id);
private:
	QSqlDatabase db;
};

