#include "AddObjectDialog.h"
#include "ScenesDialog.h"
#include "SnapshotsDialog.h"
AddObjectDialog::AddObjectDialog(QWidget *parent,bool isAddDialog)
	: QDialog(parent)
{
	this->isAddDialog=isAddDialog;
	if(isAddDialog)
		setWindowTitle("�������� ������");
	else
		setWindowTitle("�������� ������");
	resize(450,500);
	QLabel *nameLabel=new QLabel("�������� �������:");
	objNames=new QComboBox();
	QLabel *objectLabel=new QLabel("������:");
	QPushButton *fromSnapshot=new QPushButton("������� �� ������...");
	connect(fromSnapshot,SIGNAL(clicked()),SLOT(fromSnapshotButtonPressed()));
	QPushButton *fromScene=new QPushButton("������� �� �����...");
	connect(fromScene,SIGNAL(clicked()),SLOT(fromSceneButtonPressed()));
	scene=new QGraphicsScene();
	sceneView=new ObjectView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	QLabel *physHeight=new QLabel("������ ������� (��):");
	physHeightEdit=new QLineEdit();
	physHeightEdit->setValidator(new QIntValidator(this));
	QPushButton *addButton=new QPushButton();
	if(isAddDialog)
		addButton->setText("��������");
	else
		addButton->setText("��������");
	connect(addButton,SIGNAL(clicked()),SLOT(accept()));
	QPushButton *cancelButton=new QPushButton("������");
	connect(cancelButton,SIGNAL(clicked()),SLOT(reject()));
	QGridLayout *mainLayout=new QGridLayout();
	mainLayout->addWidget(nameLabel,0,0,1,3);
	mainLayout->addWidget(objNames,1,0,1,3);
	mainLayout->addWidget(objectLabel,2,0,1,3);
	QHBoxLayout *buttonsLayout=new QHBoxLayout();
	buttonsLayout->addWidget(fromSnapshot);
	buttonsLayout->addWidget(fromScene);
	mainLayout->addLayout(buttonsLayout,3,0,1,3);
	mainLayout->addWidget(sceneView,4,0,6,3);
	mainLayout->addWidget(physHeight,10,0,1,3);
	mainLayout->addWidget(physHeightEdit,11,0,1,3);
	mainLayout->addWidget(addButton,12,1,1,1);
	mainLayout->addWidget(cancelButton,12,2,1,1);
	setLayout(mainLayout);
}
void AddObjectDialog::fromSceneButtonPressed()
{
	DatabaseModel model;
	model.setDatabase(*db);
	ScenesDialog *dialog=new ScenesDialog(this);
	dialog->setDbModel(model);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
	{
		db->connect();
		QPixmap pixmap=db->getScene(dialog->selectedSceneId()).pixmap;
		db->disconnect();
		scene->clear();
		scene->addPixmap(pixmap);
	}
}
void AddObjectDialog::fromSnapshotButtonPressed()
{
	DatabaseModel model;
	model.setDatabase(*db);
	SnapshotsDialog *dialog=new SnapshotsDialog(this);
	dialog->setDbModel(model);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
	{
		db->connect();
		QPixmap pixmap=QPixmap::fromImage(db->getSnapshot(dialog->selectedIdentifiers()[0]).image);
		db->disconnect();
		scene->clear();
		scene->addPixmap(pixmap);
	}
}
void AddObjectDialog::setDatabase(Database &db)
{
	this->db=&db;
}
QPixmap AddObjectDialog::object()
{
	QPixmap pixmap=QPixmap::grabWidget(sceneView,sceneView->selectedArea());
	return pixmap;
}
void AddObjectDialog::setNameId(int id)
{
	for(int i=0; i<descriptions.count(); i++)
		if(descriptions.at(i).id==id)
		{
			objNames->setCurrentIndex(i);
			break;
		}
}
int AddObjectDialog::nameId()
{
	int current=objNames->currentIndex();
	return descriptions.at(current).id;
}
void AddObjectDialog::setPhysHeight(int height)
{
	physHeightEdit->setText(QString::number(height));
}
int AddObjectDialog::physHeight()
{
	return physHeightEdit->text().toInt();
}
int AddObjectDialog::exec()
{
	db->connect();
	descriptions=db->getDescriptions();
	db->disconnect();
	foreach(Description descr,descriptions)
	{
		objNames->addItem(descr.name);
	}
	return QDialog::exec();
}
AddObjectDialog::~AddObjectDialog()
{

}
