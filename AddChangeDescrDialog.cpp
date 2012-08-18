#include "AddChangeDescrDialog.h"

AddChangeDescrDialog::AddChangeDescrDialog(bool isAddDialog,QWidget *parent)
	: QDialog(parent)
{
	this->isAddDialog=isAddDialog;
	if(isAddDialog)
		setWindowTitle("Добавить запись");
	else
		setWindowTitle("Изменить запись");
	resize(350,250);
	QGridLayout *layout=new QGridLayout();
	QLabel *nameLabel=new QLabel("Введите название:");
	QLabel *descrLabel=new QLabel("Введите описание:");	
	nameEdit=new QLineEdit();
	descrEdit=new QTextEdit();
	QPushButton *button=new QPushButton();
	if(isAddDialog)
		button->setText("Добавить");
	else
		button->setText("Изменить");
	connect(button,SIGNAL(clicked()),SLOT(accept()));
	QPushButton *cancelButton=new QPushButton("Отмена");
	connect(cancelButton,SIGNAL(clicked()),SLOT(reject()));
	layout->addWidget(nameLabel,0,1,1,4);
	layout->addWidget(nameEdit,1,1,1,4);
	layout->addWidget(descrLabel,2,1,1,4);
	layout->addWidget(descrEdit,3,1,3,4);
	layout->addWidget(button,6,3,1,1);
	layout->addWidget(cancelButton,6,4,1,1);
	setLayout(layout);
}
void AddChangeDescrDialog::setDescription(QString description)
{
	descrEdit->setText(description);
}
void AddChangeDescrDialog::setName(QString name)
{
	nameEdit->setText(name);
	if(name=="Робот")
		nameEdit->setEnabled(false);
}
QString AddChangeDescrDialog::description()
{
	return descrEdit->toPlainText();
}
QString AddChangeDescrDialog::name()
{
	return nameEdit->text();
}
AddChangeDescrDialog::~AddChangeDescrDialog()
{

}
