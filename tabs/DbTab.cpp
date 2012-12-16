#include "DbTab.h"
#include "../dialogs/AddChangeDescrDialog.h"
#include "../dialogs/AddObjectDialog.h"
#include "../database/QModelIndexListHack.h"

DbTab::DbTab(QWidget *parent)
	: QWidget(parent)
{
	currentTable = SNAPSHOTS;
	tableBox = new QComboBox();
	mainLayout = new QGridLayout();
	mainLayout->addWidget(tableBox,0,4,1,2);

	QStringList tableNamesList = DatabaseView::getInstance().getTableNames();
	for(int i = 0; i < tableNamesList.size(); i++)
	{
		tableBox->addItem(tableNamesList[i]);
	}
	connect(tableBox,SIGNAL(currentIndexChanged(int)),SLOT(tableChanged(int)));

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

void DbTab::showEvent(QShowEvent *ev)
{
	table = DatabaseView::getInstance().getTable(currentTable);
	mainLayout->addWidget(table, 1, 1, 5, 5);
	table->show();
}

void DbTab::tableChanged(int index)
{
	currentTable = (DbTableName)index;
	table->hide();
	mainLayout->removeWidget(table);
	table = DatabaseView::getInstance().getTable(currentTable);
	mainLayout->addWidget(table, 1, 1, 5, 5);
	table->show();
	if(currentTable == DESCRIPTIONS || currentTable == OBJECTS)
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
	if(currentTable == DESCRIPTIONS)
	{
		AddChangeDescrDialog *dialog=new AddChangeDescrDialog(this);
		int result = dialog->exec();
		if(result == QDialog::Accepted)
		{
			Database::getInstance().addDescription(dialog->name(),dialog->description());
			reloadCurrentTable();
		}
	}
	if(currentTable == OBJECTS)
	{
		AddObjectDialog *dialog=new AddObjectDialog(this);
		int result = dialog->exec();
		if(result == QDialog::Accepted)
		{
			QPixmap object=dialog->object();
			Database::getInstance().addObject(dialog->nameId(),dialog->object(),dialog->physHeight());
			reloadCurrentTable();
		}
	}
}
void DbTab::changeButtonPressed()
{
	if(currentTable == DESCRIPTIONS)
	{
		AddChangeDescrDialog *dialog=new AddChangeDescrDialog(false,this);
		dialog->setName(table->item(table->currentRow(),0)->data(Qt::DisplayRole).toString());
		dialog->setDescription(table->item(table->currentRow(),1)->data(Qt::DisplayRole).toString());
		int result = dialog->exec();
		if(result == QDialog::Accepted)
		{
			Description description;
			description.name=dialog->name();
			description.description=dialog->description();
			description.id=table->item(table->currentRow(),2)->data(Qt::DisplayRole).toInt();
			Database::getInstance().changeDescription(description);
		}
	}
	if(currentTable == OBJECTS)
	{
		AddObjectDialog *dialog=new AddObjectDialog(this, false);
		dialog->setPhysHeight(table->item(table->currentRow(),1)->data(Qt::DisplayRole).toInt());
		int result=dialog->exec();
	}
}
void DbTab::delButtonPressed()
{
	QModelIndexList list = selectedIndexes(table);
	
	if(currentTable == SNAPSHOTS)
	{
		for(int i = 0; i < list.count(); i++)
		{
			int id = table->item(list.at(i).row(),5)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteSnapshot(id);
			DatabaseView::getInstance().removeRow(SNAPSHOTS, list.at(i).row());
		}
	}
	else if(currentTable == SCENES)
	{
		for(int i = 0; i < list.count(); i++)
		{
			int id = table->item(list.at(i).row(),5)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteScene(id);
			DatabaseView::getInstance().removeRow(SCENES, list.at(i).row());
		}
	}
	else if(currentTable == DESCRIPTIONS)
	{
		for(int i = 0; i < list.count(); i++)
		{
			int id = table->item(list.at(i).row(),2)->data(Qt::DisplayRole).toInt();
			if(id == ROBOT_ID)
			{
				QMessageBox::warning(this, "Ошибка", "Робот не может быть удален", QMessageBox::Ok);
				return;
			}
			Database::getInstance().deleteDescription(id);
			DatabaseView::getInstance().removeRow(DESCRIPTIONS, list.at(i).row());
		}
	}
	else if(currentTable == OBJECTS)
	{
		for(int i = 0; i < list.count(); i++)
		{
			int id = table->item(list.at(i).row(),4)->data(Qt::DisplayRole).toInt();
			Database::getInstance().deleteObject(id);
			DatabaseView::getInstance().removeRow(OBJECTS, list.at(i).row());
		}
	}
	reloadCurrentTable();	
}
void DbTab::reloadCurrentTable()
{
	table->hide();
	mainLayout->removeWidget(table);
	table = DatabaseView::getInstance().getTable(currentTable);
	mainLayout->addWidget(table, 1, 1, 5, 5);
	table->show();
}
DbTab::~DbTab()
{

}
