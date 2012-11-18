#ifndef DBTAB_H
#define DBTAB_H

#include <QtGui>
#include "../database/Database.h"
#include "../database/DatabaseView.h"
#include <map>

class DbTab : public QWidget
{
	Q_OBJECT

public:
	DbTab(QWidget *parent=0);
	~DbTab();
public slots:
	void tableChanged(int index);
	void addButtonPressed();
	void changeButtonPressed();
	void delButtonPressed();
	void reloadTable(int pos=-1);
private:
	std::map<int,std::pair<QString,QTableWidget*> > tables;
	QTableWidget *table;
	QComboBox *tableBox;
	QGridLayout *mainLayout;
	QPushButton *addButton;
	QPushButton *changeButton;
};

#endif // DBTAB_H
