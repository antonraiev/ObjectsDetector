#pragma once
#include <QtGui>
#include <QtSql>
#include "Structs.h"
#include "DbException.h"
#define ROBOT_ID 8

class Database
{
public:
	Database(void);
	~Database(void);
	int addSnapshot(QImage &image);
	int addSnapshot(QPixmap &pixmap);
	Snapshot getSnapshot(int id);
	int addScene(QPixmap &pixmap);
	Scene getScene(int id);
	void addPart(int sceneId,int snapshotId);
	void addObject(int nameId,QPixmap object,int physHeight);
	int addMap(QPixmap &pixmap);
	Map getMap(int id);
	QList<Snapshot> getSnapshots();
	QList<Scene> getScenes();
	void addDescription(QString name, QString description);
	QList<Description> getDescriptions();
	QList<Object> getObjects();
	void changeDescription(Description descr);
	void deleteDescription(int id);
	void deleteSnapshot(int id);
	void deleteScene(int id);
	void deleteObject(int id);

protected:
	void connect();
	void disconnect();
	void executeQuery(QSqlQuery query);
private:
	QSqlDatabase db;
};

