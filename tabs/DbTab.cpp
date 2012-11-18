#include "DbTab.h"
#include "../dialogs/AddChangeDescrDialog.h"
#include "../dialogs/AddObjectDialog.h"
#include "../database/QModelIndexListHack.h"

DbTab::DbTab(QWidget *parent)
	: QWidget(parent)
{
//	tables[0]=std::make_pair("Снимки", DatabaseView::getInstance().snapshotsTable());
//	tables[1]=std::make_pair("Сцены", DatabaseView::getInstance().scenesTable());
//	tables[2]=std::make_pair("Описания объектов", DatabaseView::getInstance().descriptionsTable());
//	tables[3]=std::make_pair("Объекты", DatabaseView::getInstance().objectsTable());
//	tables[4]=std::make_pair("Карты",DatabaseView::getInstance().descriptionsTable());
	tableBox = new QComboBox();
	mainLayout = new QGridLayout();
	mainLayout->addWidget(tableBox,0,4,1,2);
	for(std::map<int,std::pair<QString,QTableWidget*> >::iterator it=tables.begin(); it!=tables.end(); it++)
	{
		tableBox->addItem(it->second.first);
		mainLayout->addWidget(it->second.second,1,1,5,5);
		it->second.second->hide();
	}
	connect(tableBox,SIGNAL(currentIndexChanged(int)),SLOT(tableChanged(int)));
	table=tables[0].second;
	table->show();
	addButton=new QPushButton("Добавить");
	connect(addButton,SIGNAL(clicked()),SLOT(addButtonPressed()));
	mainLayout->addWidget(addButton,6,2,1,1);
	addButton->hide();
	changeButton=new QPushButton("Изменить");
	connect(changeButton,SIGNAL(clicked()),SLOT(changeButtonPressed()));
	mainLayout->addWidget(changeButton,6,3,1,1);
	changeButton->hide();
	QPushButton *reloadButton=new QPushButton("Обновить");
	connect(reloadButton,SIGNAL(clicked()),SLOT(reloadTable()));
	mainLayout->addWidget(reloadButton,6,4,1,1);
	QPushButton *delButton=new QPushButton("Удалить");
	connect(delButton,SIGNAL(clicked()),SLOT(delButtonPressed()));
	mainLayout->addWidget(delButton,6,5,1,1);
	setLayout(mainLayout);
}

void DbTab::tableChanged(int index)
{
	table->hide();
	table=tables[index].second;
	table->show();
	if(table==tables[2].second || table==tables[3].second)
	{
		addButton->show();
		changeButton->show();
	}
	else
	{
		addButton->hide();
		changeButton->hide();
	}
}
void DbTab::addButtonPressed()
{
	if(table==tables[2].second)
	{
		AddChangeDescrDialog *dialog=new AddChangeDescrDialog(this);
		int result=dialog->exec();
		if(result==QDialog::Accepted)
		{
			
			Database::getInstance().addDescription(dialog->name(),dialog->description());
			delete tables[2].second;
			tables[2].second=DatabaseView::getInstance().descriptionsTable();
			mainLayout->addWidget(tables[2].second,1,1,5,5);
			table=tables[2].second;
			
		}
	}
	if(table==tables[3].second)
	{
		AddObjectDialog *dialog=new AddObjectDialog(this);
		int result=dialog->exec();
		if(result==QDialog::Accepted)
		{
			QPixmap object=dialog->object();
			
			Database::getInstance().addObject(dialog->nameId(),dialog->object(),dialog->physHeight());
			
			delete tables[3].second;
			tables[3].second=DatabaseView::getInstance().objectsTable();
			mainLayout->addWidget(tables[3].second,1,1,5,5);
			table=tables[3].second;
		}
	}
}
void DbTab::changeButtonPressed()
{
	if(table==tables[2].second)
	{
		AddChangeDescrDialog *dialog=new AddChangeDescrDialog(false,this);
		dialog->setName(table->item(table->currentRow(),0)->data(Qt::DisplayRole).toString());
		dialog->setDescription(table->item(table->currentRow(),1)->data(Qt::DisplayRole).toString());
		int result=dialog->exec();
		if(result==QDialog::Accepted)
		{
			Description description;
			description.name=dialog->name();
			description.description=dialog->description();
			description.id=table->item(table->currentRow(),2)->data(Qt::DisplayRole).toInt();
			
			Database::getInstance().changeDescription(description);
			
			reloadTable(2);
		}
	}
	if(table==tables[3].second)
	{
		AddObjectDialog *dialog=new AddObjectDialog(this,false);
		dialog->setPhysHeight(table->item(table->currentRow(),1)->data(Qt::DisplayRole).toInt());
		int result=dialog->exec();
	}
}
void DbTab::delButtonPressed()
{
	QModelIndexList list = selectedIndexes(table);
	
	if(table==tables[0].second)
	{
		for(int i=0; i<list.count(); i++)
		{
			int id=table->item(list.at(i).row(),5)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteSnapshot(id);
		}
		reloadTable(0);
	}
	else if(table==tables[1].second)
	{
		for(int i=0; i<list.count(); i++)
		{
			int id=table->item(list.at(i).row(),5)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteScene(id);
		}
		reloadTable(1);
	}
	else if(table==tables[2].second)
	{
		for(int i=0; i<list.count(); i++)
		{
			int id=table->item(list.at(i).row(),2)->data(Qt::DisplayRole).toInt();
			if(id == ROBOT_ID)
			{
				QMessageBox::warning(this, "Ошибка", "Робот не может быть удален", QMessageBox::Ok);
				
				return;
			}
			Database::getInstance().deleteDescription(id);
		}
		reloadTable(2);
	}
	else if(table==tables[3].second)
	{
		for(int i=0; i<list.count(); i++)
		{
			int id=table->item(list.at(i).row(),4)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteObject(id);
		}
		reloadTable(3);
	}
	
}
void DbTab::reloadTable(int pos)
{
	if(pos==-1)
		pos=tableBox->currentIndex();
	
	delete tables[pos].second;
	if(pos==0)
	{
		tables[pos].second=DatabaseView::getInstance().snapshotsTable();
	}
	else if(pos==1)
	{
		tables[pos].second=DatabaseView::getInstance().scenesTable();
	}
	else if(pos==2)
	{
		tables[pos].second=DatabaseView::getInstance().descriptionsTable();
	}
	else if(pos==3)
	{
		tables[pos].second=DatabaseView::getInstance().objectsTable();
	}
	mainLayout->addWidget(tables[pos].second,1,1,5,5);
	table=tables[pos].second;
	
}
DbTab::~DbTab()
{

}
