#include "AddObjectDialog.h"
#include "ScenesDialog.h"
#include "SnapshotsDialog.h"
AddObjectDialog::AddObjectDialog(QWidget *parent,bool isAddDialog)
	: QDialog(parent)
{
	this->isAddDialog=isAddDialog;
	if(isAddDialog)
		setWindowTitle("Добавить объект");
	else
		setWindowTitle("Изменить объект");
	resize(450,500);
	QLabel *nameLabel=new QLabel("Название объекта:");
	objNames=new QComboBox();
	QLabel *objectLabel=new QLabel("Объект:");
	QPushButton *fromSnapshot=new QPushButton("Выбрать на слайде...");
	connect(fromSnapshot,SIGNAL(clicked()),SLOT(fromSnapshotButtonPressed()));
	QPushButton *fromScene=new QPushButton("Выбрать на сцене...");
	connect(fromScene,SIGNAL(clicked()),SLOT(fromSceneButtonPressed()));
	scene=new QGraphicsScene();
	sceneView=new ObjectView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	QLabel *physHeight=new QLabel("Высота объекта (см):");
	physHeightEdit=new QLineEdit();
	physHeightEdit->setValidator(new QIntValidator(this));
	QPushButton *addButton=new QPushButton();
	if(isAddDialog)
		addButton->setText("Добавить");
	else
		addButton->setText("Изменить");
	connect(addButton,SIGNAL(clicked()),SLOT(accept()));
	QPushButton *cancelButton=new QPushButton("Отмена");
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
	ScenesDialog *dialog=new ScenesDialog(this);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
	{
		
		QPixmap pixmap=Database::getInstance().getScene(dialog->selectedSceneId()).pixmap;
		
		scene->clear();
		scene->addPixmap(pixmap);
	}
}
void AddObjectDialog::fromSnapshotButtonPressed()
{
	SnapshotsDialog *dialog=new SnapshotsDialog(this);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
	{
		
		QPixmap pixmap=QPixmap::fromImage(Database::getInstance().getSnapshot(dialog->selectedIdentifiers()[0]).image);
		
		scene->clear();
		scene->addPixmap(pixmap);
	}
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
	
	descriptions=Database::getInstance().getDescriptions();
	
	foreach(Description descr,descriptions)
	{
		objNames->addItem(descr.name);
	}
	return QDialog::exec();
}
AddObjectDialog::~AddObjectDialog()
{

}
