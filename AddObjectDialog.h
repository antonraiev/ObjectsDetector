#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QtGui>
#include "Database.h"
#include "ObjectView.h"
class AddObjectDialog : public QDialog
{
	Q_OBJECT
public:
	AddObjectDialog(QWidget *parent=0,bool isAddDialog=true);
	void setDatabase(Database &db);
	QPixmap object();
	void setNameId(int id);
	int nameId();
	void setPhysHeight(int height);
	int physHeight();
	virtual int exec();
	~AddObjectDialog();
public slots:
	void fromSceneButtonPressed();
	void fromSnapshotButtonPressed();
private:
	bool isAddDialog;
	Database *db;
	QComboBox *objNames;
	QList<Description> descriptions;
	QLineEdit *physHeightEdit;
	QGraphicsScene *scene;
	ObjectView *sceneView;
};

#endif // ADDOBJECTDIALOG_H
