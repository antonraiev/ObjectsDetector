#ifndef DBTAB_H
#define DBTAB_H

#include <QtGui>
#include "../database/Database.h"
#include "../database/DatabaseModel.h"
#include <map>

class DbTab : public QWidget
{
	Q_OBJECT

public:
	DbTab(Database &db,QWidget *parent=0);
	~DbTab();
	void setDatabase(Database &db);
public slots:
	void tableChanged(int index);
	void addButtonPressed();
	void changeButtonPressed();
	void delButtonPressed();
	void reloadTable(int pos=-1);
private:
	std::map<int,std::pair<QString,QTableWidget*> > tables;
	Database *db;
	DatabaseModel dbModel;
	QTableWidget *table;
	QComboBox *tableBox;
	QGridLayout *mainLayout;
	QPushButton *addButton;
	QPushButton *changeButton;
};

#endif // DBTAB_H
