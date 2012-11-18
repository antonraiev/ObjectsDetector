#ifndef SNAPSHOTSDIALOG_H
#define SNAPSHOTSDIALOG_H

#include <QtGui>
#include "../database/Structs.h"
#include "../database/DatabaseView.h"
class SnapshotsDialog : public QDialog
{
	Q_OBJECT

public:
	SnapshotsDialog(QWidget *parent);
	~SnapshotsDialog();
	void setDbModel(DatabaseView &dbView);
	int exec();
	QList<int> selectedIdentifiers();
protected slots:
	void selectionChanged();
private:
	QTableWidget *table;
	QList<Snapshot> snapslist;
	QList<int> selectedId;
	DatabaseView *dbView;
};

#endif // SNAPSHOTSDIALOG_H
