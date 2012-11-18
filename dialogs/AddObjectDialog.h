#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QtGui>
#include "../database/Database.h"
#include "../views/ObjectView.h"
class AddObjectDialog : public QDialog
{
	Q_OBJECT
public:
	AddObjectDialog(QWidget *parent=0,bool isAddDialog=true);
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
	QComboBox *objNames;
	QList<Description> descriptions;
	QLineEdit *physHeightEdit;
	QGraphicsScene *scene;
	ObjectView *sceneView;
};

#endif // ADDOBJECTDIALOG_H
