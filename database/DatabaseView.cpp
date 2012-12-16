#include "DatabaseView.h"


DatabaseView::DatabaseView(void) :
	snapshotPreviewSize(QSize(64, 64)),
	scenePreviewSize(QSize(128, 96))
{
	tableNames<<"Снимки"<<"Сцены"<<"Описания"<<"Объекты";
	loadSnapshotsTable();
	loadScenesTable();
	loadDescriptionsTable();
	loadObjectsTable();
}

DatabaseView& DatabaseView::getInstance()
{
	static DatabaseView instance;
	return instance;
}

QStringList& DatabaseView::getTableNames()
{
	return tableNames;
}

QTableWidget* DatabaseView::getTable(DbTableName tableName)
{
	return tables[(int)tableName].second;
}

void DatabaseView::addToSnapshots(Snapshot &snapshot)
{
	QTableWidget *table = tables[SNAPSHOTS].second;
	int newRow = table->rowCount();
	table->setRowCount(newRow + 1);

	QPixmap scaledSnapshot = QPixmap::fromImage(snapshot.image.scaled(snapshotPreviewSize, Qt::KeepAspectRatio));
	table->setItem(newRow, 0, new QTableWidgetItem(scaledSnapshot, ""));		
	table->setItem(newRow, 1, new QTableWidgetItem(QString("%1").arg(snapshot.width)));
	table->setItem(newRow, 2, new QTableWidgetItem(QString("%1").arg(snapshot.height)));
	table->setItem(newRow, 3, new QTableWidgetItem(snapshot.created.toString()));
	table->setItem(newRow, 4, new QTableWidgetItem(snapshot.in_scene ? "Да" : "Нет"));
	table->setItem(newRow, 5, new QTableWidgetItem(QString("%1").arg(snapshot.id)));
	table->verticalHeader()->resizeSection(newRow, snapshotPreviewSize.height());
	for(int i = 0; i < 4; i++)
	{
		table->item(newRow,i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
}

void DatabaseView::addToScenes(Scene &scene)
{
	QTableWidget *table = tables[SCENES].second;
	int newRow = table->rowCount();
	table->setRowCount(newRow + 1);

	table->setItem(newRow, 0, new QTableWidgetItem(scene.pixmap.scaled(scenePreviewSize, Qt::KeepAspectRatio),""));		
	table->setItem(newRow, 1, new QTableWidgetItem(QString("%1").arg(scene.pixmap.width())));
	table->setItem(newRow, 2, new QTableWidgetItem(QString("%1").arg(scene.pixmap.height())));
	table->setItem(newRow, 3, new QTableWidgetItem(scene.created.toString()));
	table->setItem(newRow, 4, new QTableWidgetItem(scene.have_map ? "Да" : "Нет"));
	table->setItem(newRow, 5, new QTableWidgetItem(QString("%1").arg(scene.id)));
	table->verticalHeader()->resizeSection(newRow, scenePreviewSize.height());
	for(int i = 0; i < 4; i++)
	{
		table->item(newRow,i)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	}
}

void DatabaseView::addToDescriptions(Description &description)
{
}

void DatabaseView::addToObjects(Object &object)
{
}

void DatabaseView::removeRow(DbTableName tableName, int row)
{
	tables[(int)tableName].second->removeRow(row);
}

QTableWidget* DatabaseView::loadSnapshotsTable()
{
	QList<Snapshot> snapslist = Database::getInstance().getSnapshots();
	QTableWidget *table;
	table = new QTableWidget();
	table->setColumnCount(6);
	table->setIconSize(snapshotPreviewSize);
	table->setHorizontalHeaderLabels(QStringList()<<"Снимок"<<"Ширина"<<"Высота"<<"Дата"<<"На сцене"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	tables[SNAPSHOTS] = std::make_pair("Снимки", table);
	foreach(Snapshot snapshot,snapslist)
	{
		addToSnapshots(snapshot);
	}
	table->setColumnHidden(5, true);
	return table;
}

QTableWidget* DatabaseView::loadScenesTable()
{
	QList<Scene> sceneslist=Database::getInstance().getScenes();	
	QTableWidget *table;
	table=new QTableWidget();
	table->setColumnCount(6);
	table->setIconSize(scenePreviewSize);
	table->setHorizontalHeaderLabels(QStringList()<<"Сцена"<<"Ширина"<<"Высота"<<"Дата"<<"Карта построена"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	tables[SCENES] = std::make_pair("Сцены", table);
	foreach(Scene scene,sceneslist)
	{
		addToScenes(scene);
	}
	table->horizontalHeader()->resizeSection(0, scenePreviewSize.width());
	table->setColumnHidden(5, true);
	return table;
}
QTableWidget* DatabaseView::loadObjectsTable()
{
	QList<Object> objlist = Database::getInstance().getObjects();
	
	QTableWidget *table;
	const QSize previewSize=QSize(64,64);
	table=new QTableWidget(objlist.count(),5);
	table->setHorizontalHeaderLabels(QStringList()<<"Объект"<<"Высота"<<"Название"<<"Описание"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setIconSize(previewSize);
	int row=0;
	foreach(Object object,objlist)
	{
		table->setItem(row,0,new QTableWidgetItem(QPixmap::fromImage(object.object.scaled(previewSize,Qt::KeepAspectRatio)),""));		
		table->setItem(row,1,new QTableWidgetItem(QString("%1").arg(object.phys_height)));
		table->setItem(row,2,new QTableWidgetItem(object.descr.name));
		table->setItem(row,3,new QTableWidgetItem(object.descr.description));
		table->setItem(row,4,new QTableWidgetItem(QString::number(object.id)));
		table->verticalHeader()->resizeSection(row,previewSize.height());
		for(int i=0; i<5; i++)
			table->item(row,i)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		row++;
	}
	table->horizontalHeader()->resizeSection(3,150);
	table->setColumnHidden(4,true);
	tables[OBJECTS] = std::make_pair("Объекты", table);
	return table;
}
QTableWidget* DatabaseView::loadDescriptionsTable()
{
	QList<Description> descrlist=Database::getInstance().getDescriptions();
	
	QTableWidget *table;
	table=new QTableWidget(descrlist.count(),3);
	table->setHorizontalHeaderLabels(QStringList()<<"Название"<<"Описание"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	int row=0;
	foreach(Description description,descrlist)
	{
		table->setItem(row,0,new QTableWidgetItem(description.name));
		table->setItem(row,1,new QTableWidgetItem(description.description));
		table->setItem(row,2,new QTableWidgetItem(QString("%1").arg(description.id)));
		for(int i=0; i<2; i++)
			table->item(row,i)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		row++;
	}
	table->horizontalHeader()->resizeSection(0,150);
	table->horizontalHeader()->resizeSection(1,300);
	table->setColumnHidden(2, true);
	tables[DESCRIPTIONS] = std::make_pair("Описания", table);
	return table;
}