#include <exception>
#include <qstring.h>

class DbException : public std::exception
{
public:
	DbException(QString message = "Unknown database error");
	void setMessage(QString message);
	virtual const char *what() const throw();
private:
	QString errorMessage;
};