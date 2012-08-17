#include "Database.h"


Database::Database(void)
{
	db=QSqlDatabase::addDatabase("QODBC3");
	db.setDatabaseName("Driver={SQL Server Native Client 10.0};Server=NOTEBOOK;"\
		"Database=ObstacleDetectorDB;Trusted_Connection=yes;");
}
bool Database::connect()
{
	if(db.isOpen())
		return true;
	else
		return db.open();
}
void Database::disconnect()
{
	db.close();
}
int Database::addSnapshot(QImage &image)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	image.save( &buffer,"PNG");
	QSqlQuery query;
	query.setForwardOnly(true);
	query.prepare("{CALL dbo.ADD_SNAPSHOT(:snapshot,:width,:height,:id)}");
	query.bindValue(":snapshot",imageBytes);
	query.bindValue(":width",image.width());
	query.bindValue(":height",image.height());
	int id;
	query.bindValue(":id",id,QSql::Out);
	if(!query.exec())
		return -1;
	else 
	{
		id=query.boundValue(":id").toInt();
		return id;
	}
}
int Database::addSnapshot(QPixmap &pixmap)
{
	QImage image=pixmap.toImage();
	return addSnapshot(image);
}
Snapshot Database::getSnapshot(int id) const
{
	QByteArray imageBytes;
	Snapshot snapshot;
	QBuffer buffer;
	QSqlQuery query;
	query.setForwardOnly(true);
	query.prepare("{call GET_SNAPSHOT(:id)}");//,:datetime)}");
	query.bindValue(":id",id);
	if(!query.exec())
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
		return Snapshot();
	}
	else
	{
		QSqlRecord record=query.record();
		query.next();
		snapshot.width=query.value(record.indexOf("width")).toInt();
		snapshot.height=query.value(record.indexOf("height")).toInt();
		imageBytes=query.value(record.indexOf("snapshot")).toByteArray();
		snapshot.created=query.value(record.indexOf("datetime")).toDateTime();
		QImage image(snapshot.width,snapshot.height,QImage::Format_ARGB32);
		buffer.setBuffer(&imageBytes);
		buffer.open(QBuffer::ReadOnly);
		image.load(&buffer,"PNG");
		snapshot.image=image;
		snapshot.id=id;
		return snapshot;
	}
}
QList<Snapshot> Database::getSnapshots() const
{
	QByteArray imageBytes;
	Snapshot snapshot;
	QBuffer buffer;
	QSqlQuery query;
	QList<Snapshot> snapslist;
	query.setForwardOnly(true);
	if(!query.exec("{call GET_SNAPSHOTS}"))
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
			return QList<Snapshot>();
	}
	else
	{
		QSqlRecord record=query.record();
		while(query.next())
		{
			snapshot.id=query.value(record.indexOf("id")).toInt();
			snapshot.width=query.value(record.indexOf("width")).toInt();
			snapshot.height=query.value(record.indexOf("height")).toInt();
			imageBytes=query.value(record.indexOf("snapshot")).toByteArray();
			snapshot.created=query.value(record.indexOf("datetime")).toDateTime();
			QImage image(snapshot.width,snapshot.height,QImage::Format_ARGB32);
			buffer.setBuffer(&imageBytes);
			buffer.open(QBuffer::ReadOnly);
			image.load(&buffer,"PNG");
			snapshot.image=image;
			int snapId=query.value(record.indexOf("snapshot_id")).toInt();
			if(snapId!=0)
				snapshot.in_scene=true;
			else
				snapshot.in_scene=false;
			snapslist.push_back(snapshot);
		}
		return snapslist;
	}
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
	query.prepare("{CALL dbo.ADD_SCENE(:scene,:width,:height,:id)}");
	query.bindValue(":scene",imageBytes);
	query.bindValue(":width",pixmap.width());
	query.bindValue(":height",pixmap.height());
	int id;
	query.bindValue(":id",id,QSql::Out);
	if(!query.exec())
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
		return -1;
	}
	else 
	{
		id=query.boundValue(":id").toInt();
		return id;
	}
}
void Database::addObject(int nameId,QPixmap object,int physHeight)
{
	QByteArray imageBytes;
	QBuffer buffer(&imageBytes);
	buffer.open(QBuffer::WriteOnly);
	object.save( &buffer,"PNG");
	QSqlQuery query;
	query.setForwardOnly(true);
	query.prepare("{CALL dbo.ADD_OBJECT(:object,:iwidth,:iheight,:phys_height,:name_id)}");
	query.bindValue(":object",imageBytes);
	query.bindValue(":iwidth",object.width());
	query.bindValue(":iheight",object.height());
	query.bindValue(":phys_height",physHeight);
	query.bindValue(":name_id",nameId);
	query.exec();
}
QList<Object> Database::getObjects()
{
	QByteArray imageBytes;
	Object object;
	QBuffer buffer;
	QSqlQuery query;
	QList<Object> objlist;
	int width,height;
	query.setForwardOnly(true);
	if(!query.exec("{call GET_OBJECTS}"))
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
			return QList<Object>();
	}
	else
	{
		QSqlRecord record=query.record();
		while(query.next())
		{
			width=query.value(record.indexOf("image_width")).toInt();
			height=query.value(record.indexOf("height")).toInt();
			imageBytes=query.value(record.indexOf("object")).toByteArray();
			object.descr.name=query.value(record.indexOf("name")).toString();
			object.descr.description=query.value(record.indexOf("description")).toString();
			object.id=query.value(record.indexOf("id")).toInt();
			object.phys_height=query.value(record.indexOf("phys_height")).toInt();
			QImage image(width,height,QImage::Format_ARGB32);
			buffer.setBuffer(&imageBytes);
			buffer.open(QBuffer::ReadOnly);
			image.load(&buffer,"PNG");
			object.object=image;
			objlist.push_back(object);
		}
		return objlist;
	}
}
Scene Database::getScene(int id) const
{
	QByteArray imageBytes;
	int width,height;
	QBuffer buffer;
	QSqlQuery query;
	query.setForwardOnly(true);
	query.prepare("{call GET_SCENE(:id)}");
	query.bindValue(":id",id);
	if(!query.exec())
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
		return Scene();
	}
	else
	{
		QSqlRecord record=query.record();
		query.next();
		width=query.value(record.indexOf("width")).toInt();
		height=query.value(record.indexOf("height")).toInt();
		imageBytes=query.value(record.indexOf("scene")).toByteArray();
		QImage image(width,height,QImage::Format_ARGB32);
		buffer.setBuffer(&imageBytes);
		buffer.open(QBuffer::ReadOnly);
		image.load(&buffer,"PNG");
		Scene scene;
		scene.pixmap=QPixmap::fromImage(image);
		scene.id=id;
		scene.created=query.value(record.indexOf("datetime")).toDateTime();
		return scene;
	}
}
QList<Scene> Database::getScenes() const
{
	QByteArray imageBytes;
	Scene scene;
	int width,height;
	QBuffer buffer;
	QSqlQuery query;
	QList<Scene> sceneslist;
	query.setForwardOnly(true);
	if(!query.exec("{call GET_SCENES}"))
	{
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
			return QList<Scene>();
	}
	else
	{
		QSqlRecord record=query.record();
		while(query.next())
		{
			scene.id=query.value(record.indexOf("id")).toInt();
			width=query.value(record.indexOf("width")).toInt();
			height=query.value(record.indexOf("height")).toInt();
			imageBytes=query.value(record.indexOf("scene")).toByteArray();
			scene.created=query.value(record.indexOf("datetime")).toDateTime();
			QImage image(width,height,QImage::Format_ARGB32);
			buffer.setBuffer(&imageBytes);
			buffer.open(QBuffer::ReadOnly);
			image.load(&buffer,"PNG");
			scene.pixmap=QPixmap::fromImage(image);
			int mapId=query.value(record.indexOf("map_id")).toInt();
			if(mapId!=0)
				scene.have_map=true;
			else
				scene.have_map=false;
			sceneslist.push_back(scene);
		}
		return sceneslist;
	}
}
void Database::addDescription(QString name,QString description)
{
	QSqlQuery query;
	query.prepare("{CALL ADD_OBJECT_DESCRIPTION(:name,:description)}");
	query.bindValue(":name",name);
	query.bindValue(":description",description);
	query.exec();
}
QList<Description> Database::getDescriptions()
{
	QSqlQuery query;
	QList<Description> descrlist;
	Description descr;
	query.exec("{CALL GET_OBJECTS_DESCRIPTION}");
	QSqlRecord record=query.record();
	while(query.next())
	{
		descr.name=query.value(record.indexOf("name")).toString();
		descr.description=query.value(record.indexOf("description")).toString();
		descr.id=query.value(record.indexOf("id")).toInt();
		descrlist.push_back(descr);
	}
	return descrlist;
}
void Database::changeDescription(Description descr)
{
	QSqlQuery query;
	query.prepare("{CALL CHANGE_OBJECT_DESCRIPTION(:id,:name,:description)}");
	query.bindValue(":id",descr.id);
	query.bindValue(":name",descr.name);
	query.bindValue(":description",descr.description);
	query.exec();
}
void Database::deleteDescription(int id)
{
	QSqlQuery query;
	query.prepare("{CALL DELETE_OBJECT_DESCRIPTION(:id)}");
	query.bindValue(":id",id);
	query.exec();
}
void Database::deleteSnapshot(int id)
{
	QSqlQuery query;
	query.prepare("{CALL DELETE_SNAPSHOT(:id)}");
	query.bindValue(":id",id);
	query.exec();

}
void Database::deleteScene(int id)
{
	QSqlQuery query;
	query.prepare("{CALL DELETE_SCENE(:id)}");
	query.bindValue(":id",id);
	query.exec();

}
void Database::deleteObject(int id)
{
	QSqlQuery query;
	query.prepare("{CALL DELETE_OBJECT(:id)}");
	query.bindValue(":id",id);
	query.exec();
}

void Database::addPart(int sceneId,int snapshotId)
{
	QSqlQuery query;
	query.prepare("{CALL ADD_PART(:scene_id,:snapshot_id)}");
	query.bindValue(":scene_id",sceneId);
	query.bindValue(":snapshot_id",snapshotId);
	if(!query.exec())
		QMessageBox::warning(0,"Ошибка базы данных",query.lastError().text());
}
Database::~Database(void)
{
}
