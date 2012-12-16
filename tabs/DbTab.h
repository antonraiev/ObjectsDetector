#ifndef DBTAB_H
#define DBTAB_H

#include <QtGui>
#include "../database/Database.h"
#include "../database/DatabaseView.h"

class DbTab : public QWidget
{
	Q_OBJECT

public:
	DbTab(QWidget *parent = 0);
	~DbTab();
public slots:
	void tableChanged(int index);
	void addButtonPressed();
	void changeButtonPressed();
	void delButtonPressed();
	void reloadCurrentTable();
protected:
	virtual void showEvent(QShowEvent *ev);
private:
	DbTableName currentTable;
	QTableWidget *table;
	QComboBox *tableBox;
	QGridLayout *mainLayout;
	QPushButton *addButton;
	QPushButton *changeButton;
};

#endif // DBTAB_H
