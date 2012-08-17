#ifndef ADDCHANGEDESCRDIALOG_H
#define ADDCHANGEDESCRDIALOG_H

#include <QtGui>

class AddChangeDescrDialog : public QDialog
{
	Q_OBJECT

public:
	AddChangeDescrDialog(bool isAddDialog=true,QWidget *parent=0);
	~AddChangeDescrDialog();
	void setDescription(QString description);
	void setName(QString name);
	QString description();
	QString name();
private:
	bool isAddDialog;
	QLineEdit *nameEdit;
	QTextEdit *descrEdit;
};

#endif // ADDCHANGEDESCRDIALOG_H
