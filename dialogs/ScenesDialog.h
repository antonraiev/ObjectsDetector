#ifndef SCENESDIALOG_H
#define SCENESDIALOG_H

#include <QtGui>
#include "../database/Structs.h"
#include "../database/DatabaseModel.h"

class ScenesDialog : public QDialog
{
	Q_OBJECT

public:
	ScenesDialog(QWidget *parent=0);
	~ScenesDialog();
	void setDbModel(DatabaseModel &dbModel);
	int exec();
	int selectedSceneId();
protected slots:
	void selectionChanged();
private:
	QTableWidget *table;
	QList<Scene> sceneslist;
	int selectedId;
	DatabaseModel *dbModel;	
};

#endif // SCENESDIALOG_H
