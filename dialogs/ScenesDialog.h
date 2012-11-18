#ifndef SCENESDIALOG_H
#define SCENESDIALOG_H

#include <QtGui>
#include "../database/Structs.h"
#include "../database/DatabaseView.h"

class ScenesDialog : public QDialog
{
	Q_OBJECT

public:
	ScenesDialog(QWidget *parent=0);
	~ScenesDialog();
	int exec();
	int selectedSceneId();
protected slots:
	void selectionChanged();
private:
	QTableWidget *table;
	QList<Scene> sceneslist;
	int selectedId;
};

#endif // SCENESDIALOG_H
