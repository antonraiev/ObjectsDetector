#include "DatabaseView.h"


DatabaseView::DatabaseView(void)
{
}

DatabaseView& DatabaseView::getInstance()
{
	static DatabaseView instance;
	return instance;
}

QTableWidget* DatabaseView::snapshotsTable()
{
	if(tables.find(SNAPSHOTS) != tables.end())
	{
		return tables[SNAPSHOTS].second;
	}

	QList<Snapshot> snapslist = Database::getInstance().getSnapshots();
	QTableWidget *table;
	const QSize previewSize = QSize(64,64);
	table = new QTableWidget(snapslist.count(), 6);
	table->setIconSize(previewSize);
	table->setHorizontalHeaderLabels(QStringList()<<"Снимок"<<"Ширина"<<"Высота"<<"Дата"<<"На сцене"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	int row = 0;
	QByteArray imageBytes;
	foreach(Snapshot snapshot,snapslist)
	{
		table->setItem(row, 0, new QTableWidgetItem(QPixmap::fromImage(snapshot.image.scaled(previewSize,Qt::KeepAspectRatio)),""));		
		table->setItem(row, 1, new QTableWidgetItem(QString("%1").arg(snapshot.width)));
		table->setItem(row, 2, new QTableWidgetItem(QString("%1").arg(snapshot.height)));
		table->setItem(row, 3, new QTableWidgetItem(snapshot.created.toString()));
		table->setItem(row, 4, new QTableWidgetItem(snapshot.in_scene ? "Да" : "Нет"));
		table->setItem(row, 5, new QTableWidgetItem(QString("%1").arg(snapshot.id)));
		table->verticalHeader()->resizeSection(row, previewSize.height());
		for(int i = 0; i < 4; i++)
			table->item(row,i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		row++;
	}
	table->setColumnHidden(5, true);
	tables[SNAPSHOTS] = std::make_pair("Снимки", table);
	return table;
}
QTableWidget* DatabaseView::scenesTable()
{
	if(tables.find(SCENES) != tables.end())
	{
		return tables[SCENES].second;
	}
	
	QList<Scene> sceneslist=Database::getInstance().getScenes();
	
	QTableWidget *table;
	const QSize previewSize=QSize(128,96);
	table=new QTableWidget(sceneslist.count(),6);
	table->setIconSize(previewSize);
	table->setHorizontalHeaderLabels(QStringList()<<"Сцена"<<"Ширина"<<"Высота"<<"Дата"<<"Карта построена"<<"hidden");
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	int row=0;
	QByteArray imageBytes;
	foreach(Scene scene,sceneslist)
	{
		table->setItem(row,0,new QTableWidgetItem(scene.pixmap.scaled(previewSize,Qt::KeepAspectRatio),""));		
		table->setItem(row,1,new QTableWidgetItem(QString("%1").arg(scene.pixmap.width())));
		table->setItem(row,2,new QTableWidgetItem(QString("%1").arg(scene.pixmap.height())));
		table->setItem(row,3,new QTableWidgetItem(scene.created.toString()));
		table->setItem(row,4,new QTableWidgetItem(scene.have_map ? "Да" : "Нет"));
		table->setItem(row,5,new QTableWidgetItem(QString("%1").arg(scene.id)));
		table->verticalHeader()->resizeSection(row,previewSize.height());
		for(int i=0; i<4; i++)
			table->item(row,i)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		row++;
	}
	table->horizontalHeader()->resizeSection(0,previewSize.width());
	table->setColumnHidden(5,true);
	tables[SCENES] = std::make_pair("Сцены", table);
	return table;
}
QTableWidget* DatabaseView::objectsTable()
{
	if(tables.find(OBJECTS) != tables.end())
	{
		return tables[OBJECTS].second;
	}

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
QTableWidget* DatabaseView::descriptionsTable()
{
	if(tables.find(DESCRIPTIONS) != tables.end())
	{
		return tables[DESCRIPTIONS].second;
	}

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