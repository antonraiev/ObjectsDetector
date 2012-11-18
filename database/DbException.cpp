#include "DbException.h"

DbException::DbException(QString message)
{
	setMessage(message);
}

void DbException::setMessage(QString message)
{
	errorMessage = message;
}

const char *DbException::what() const throw()
{
	return errorMessage.toStdString().c_str();
}