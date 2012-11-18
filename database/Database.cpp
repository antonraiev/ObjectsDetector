#include "Database.h"


Database::Database(void)
{
	db=QSqlDatabase::addDatabase("QODBC3");
	db.setDatabaseName("Driver={SQL Server Native Client 10.0};Server=ASPIRE-5738\\SQLEXPRESS;"\
		"Database=ObstacleDetectorDB;Trusted_Connection=yes;");
}
void Database::connect()
{
	if(db.isOpen())
	{
		return;
	}
	bool opened = db.open();
	if(!opened)
	{
		DbException ex;
		ex.setMessage("Failed to open database connection");
		throw ex;
	}
}
void Database::disconnect()
{
	db.close();
}

void Database::executeQuery(QSqlQuery query)
{
	bool executed = query.exec();
	if(!executed)
	{
		disconnect();
		DbException ex;
		ex.setMessage("Query execution failed: " + query.lastError().text());
		throw ex;
	}
}

int Database::addSnapshot(QImage &image)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	image.save( &buffer, "PNG");
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{call dbo.ADD_SNAPSHOT(:snapshot,:width,:height,:id)}");
	query.bindValue(":snapshot", imageBytes);
	query.bindValue(":width", image.width());
	query.bindValue(":height", image.height());
	int id;
	query.bindValue(":id",id,QSql::Out);
	executeQuery(query);
	disconnect();

	id = query.boundValue(":id").toInt();
	return id;
}
int Database::addSnapshot(QPixmap &pixmap)
{
	QImage image = pixmap.toImage();
	return addSnapshot(image);
}
Snapshot Database::getSnapshot(int id)
{
	QByteArray imageBytes;
	Snapshot snapshot;
	QBuffer buffer;
	QSqlQuery query;
	query.setForwardOnly(true);
	
	connect();
	query.prepare("{call GET_SNAPSHOT(:id)}");
	query.bindValue(":id", id);
	executeQuery(query);	
	QSqlRecord record = query.record();
	query.next();
	disconnect();

	snapshot.width = query.value(record.indexOf("width")).toInt();
	snapshot.height = query.value(record.indexOf("height")).toInt();
	imageBytes = query.value(record.indexOf("snapshot")).toByteArray();
	snapshot.created = query.value(record.indexOf("datetime")).toDateTime();

	QImage image(snapshot.width, snapshot.height, QImage::Format_ARGB32);
	buffer.setBuffer(&imageBytes);
	buffer.open(QBuffer::ReadOnly);
	image.load(&buffer,"PNG");
	snapshot.image = image;
	snapshot.id = id;
	return snapshot;
}
QList<Snapshot> Database::getSnapshots()
{
	QByteArray imageBytes;
	Snapshot snapshot;
	QBuffer buffer;
	QSqlQuery query;
	QList<Snapshot> snapslist;
	query.setForwardOnly(true);
	
	connect();
	query.prepare("{call GET_SNAPSHOTS}");
	executeQuery(query);
	QSqlRecord record = query.record();
	while(query.next())
	{
		snapshot.id = query.value(record.indexOf("id")).toInt();
		snapshot.width = query.value(record.indexOf("width")).toInt();
		snapshot.height = query.value(record.indexOf("height")).toInt();
		imageBytes = query.value(record.indexOf("snapshot")).toByteArray();
		snapshot.created = query.value(record.indexOf("datetime")).toDateTime();

		QImage image(snapshot.width, snapshot.height, QImage::Format_ARGB32);
		buffer.setBuffer(&imageBytes);
		buffer.open(QBuffer::ReadOnly);
		image.load(&buffer, "PNG");
		snapshot.image = image;
		
		int snapId = query.value(record.indexOf("snapshot_id")).toInt();
		snapId != 0 ? snapshot.in_scene = true : snapshot.in_scene = false;
		snapslist.push_back(snapshot);
	}
	disconnect();
	return snapslist;
}
int Database::addScene(QPixmap &pixmap)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	QImage image=pixmap.toImage();
	image.save(&buffer,"PNG");
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{CALL dbo.ADD_SCENE(:scene,:width,:height,:id)}");
	query.bindValue(":scene", imageBytes);
	query.bindValue(":width", pixmap.width());
	query.bindValue(":height", pixmap.height());
	int id = 0;
	query.bindValue(":id", id, QSql::Out);
	executeQuery(query);
	disconnect();

	id = query.boundValue(":id").toInt();
	return id;
}
void Database::addObject(int nameId, QPixmap object, int physHeight)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	object.save(&buffer, "PNG");
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{CALL dbo.ADD_OBJECT(:object,:iwidth,:iheight,:phys_height,:name_id)}");
	query.bindValue(":object",imageBytes);
	query.bindValue(":iwidth",object.width());
	query.bindValue(":iheight",object.height());
	query.bindValue(":phys_height",physHeight);
	query.bindValue(":name_id",nameId);
	executeQuery(query);
	disconnect();
}
QList<Object> Database::getObjects()
{
	QByteArray imageBytes;
	Object object;
	QBuffer buffer;
	QSqlQuery query;
	QList<Object> objList;
	int width, height;
	query.setForwardOnly(true);

	connect();
	query.prepare("{call GET_OBJECTS}");
	executeQuery(query);	
	QSqlRecord record = query.record();
	while(query.next())
	{
		width = query.value(record.indexOf("image_width")).toInt();
		height = query.value(record.indexOf("height")).toInt();
		imageBytes = query.value(record.indexOf("object")).toByteArray();
		object.descr.id = query.value(record.indexOf("name_id")).toInt();
		object.descr.name = query.value(record.indexOf("name")).toString();
		object.descr.description = query.value(record.indexOf("description")).toString();
		object.id = query.value(record.indexOf("id")).toInt();
		object.phys_height = query.value(record.indexOf("phys_height")).toInt();
		
		QImage image(width,height,QImage::Format_ARGB32);
		buffer.setBuffer(&imageBytes);
		buffer.open(QBuffer::ReadOnly);
		image.load(&buffer,"PNG");
		object.object=image;
		objList.push_back(object);
	}
	disconnect();
	return objList;
}
int Database::addMap(QPixmap &pixmap)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	QImage image = pixmap.toImage();
	image.save(&buffer,"PNG");
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{CALL dbo.ADD_MAP(:map,:width,:height,:id)}");
	query.bindValue(":map", imageBytes);
	query.bindValue(":width", pixmap.width());
	query.bindValue(":height", pixmap.height());
	int id;
	query.bindValue(":id", id, QSql::Out);
	executeQuery(query);
	disconnect();

	id = query.boundValue(":id").toInt();
	return id;
}
Map Database::getMap(int id)
{
	QByteArray imageBytes;
	int width, height;
	QBuffer buffer;
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{call GET_MAP(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	QSqlRecord record = query.record();
	query.next();
	disconnect();

	width = query.value(record.indexOf("width")).toInt();
	height = query.value(record.indexOf("height")).toInt();
	imageBytes = query.value(record.indexOf("map")).toByteArray();
	
	QImage image(width,height,QImage::Format_ARGB32);
	buffer.setBuffer(&imageBytes);
	buffer.open(QBuffer::ReadOnly);
	image.load(&buffer,"PNG");
	
	Map map;
	map.image = image;
	map.id = id;
	map.created = query.value(record.indexOf("datetime")).toDateTime();
	map.height = height;
	map.width = width;
	return map;
}

Scene Database::getScene(int id)
{
	QByteArray imageBytes;
	int width, height;
	QBuffer buffer;
	QSqlQuery query;
	query.setForwardOnly(true);

	connect();
	query.prepare("{call GET_SCENE(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	QSqlRecord record=query.record();
	query.next();
	disconnect();

	width = query.value(record.indexOf("width")).toInt();
	height = query.value(record.indexOf("height")).toInt();
	imageBytes = query.value(record.indexOf("scene")).toByteArray();
	QImage image(width,height,QImage::Format_ARGB32);
	buffer.setBuffer(&imageBytes);
	buffer.open(QBuffer::ReadOnly);
	image.load(&buffer,"PNG");
	
	Scene scene;
	scene.pixmap = QPixmap::fromImage(image);
	scene.id = id;
	scene.created = query.value(record.indexOf("datetime")).toDateTime();
	return scene;
}
QList<Scene> Database::getScenes()
{
	QByteArray imageBytes;
	Scene scene;
	int width, height;
	QBuffer buffer;
	QSqlQuery query;
	QList<Scene> scenesList;
	query.setForwardOnly(true);
	
	connect();
	query.prepare("{call GET_SCENES}");
	executeQuery(query);
	QSqlRecord record = query.record();
	while(query.next())
	{
		scene.id = query.value(record.indexOf("id")).toInt();
		width = query.value(record.indexOf("width")).toInt();
		height = query.value(record.indexOf("height")).toInt();
		imageBytes = query.value(record.indexOf("scene")).toByteArray();
		scene.created = query.value(record.indexOf("datetime")).toDateTime();
		
		QImage image(width, height, QImage::Format_ARGB32);
		buffer.setBuffer(&imageBytes);
		buffer.open(QBuffer::ReadOnly);
		image.load(&buffer, "PNG");
		scene.pixmap = QPixmap::fromImage(image);
		int mapId = query.value(record.indexOf("map_id")).toInt();
		mapId != 0 ? scene.have_map = true : scene.have_map = false;
		scenesList.push_back(scene);
	}
	disconnect();
	return scenesList;
}
void Database::addDescription(QString name, QString description)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL ADD_OBJECT_DESCRIPTION(:name,:description)}");
	query.bindValue(":name",name);
	query.bindValue(":description",description);
	executeQuery(query);
	disconnect();
}
QList<Description> Database::getDescriptions()
{
	QSqlQuery query;
	QList<Description> descrList;
	Description descr;

	connect();
	query.prepare("{CALL GET_OBJECTS_DESCRIPTION}");
	executeQuery(query);
	QSqlRecord record = query.record();
	while(query.next())
	{
		descr.name = query.value(record.indexOf("name")).toString();
		descr.description = query.value(record.indexOf("description")).toString();
		descr.id = query.value(record.indexOf("id")).toInt();
		descrList.push_back(descr);
	}
	disconnect();
	return descrList;
}
void Database::changeDescription(Description descr)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL CHANGE_OBJECT_DESCRIPTION(:id,:name,:description)}");
	query.bindValue(":id",descr.id);
	query.bindValue(":name",descr.name);
	query.bindValue(":description",descr.description);
	executeQuery(query);
	disconnect();
}
void Database::deleteDescription(int id)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL DELETE_OBJECT_DESCRIPTION(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	disconnect();
}
void Database::deleteSnapshot(int id)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL DELETE_SNAPSHOT(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	disconnect();
}
void Database::deleteScene(int id)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL DELETE_SCENE(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	disconnect();
}
void Database::deleteObject(int id)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL DELETE_OBJECT(:id)}");
	query.bindValue(":id",id);
	executeQuery(query);
	disconnect();
}

void Database::addPart(int sceneId,int snapshotId)
{
	QSqlQuery query;

	connect();
	query.prepare("{CALL ADD_PART(:scene_id,:snapshot_id)}");
	query.bindValue(":scene_id",sceneId);
	query.bindValue(":snapshot_id",snapshotId);
	executeQuery(query);
	disconnect();
}
Database::~Database(void)
{
}
