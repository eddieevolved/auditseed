#ifndef SEEDUPDATER_ADMINAUTHORISER_H
#define SEEDUPDATER_ADMINAUTHORISER_H

#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>

namespace QtSeedUpdater
{

//! An interface to run programs with elevated rights
class AdminAuthoriser
{
public:
	virtual inline ~AdminAuthoriser() {}
	//! Tests whether this program already has elevated rights or not
	virtual bool hasAdminRights() = 0;
	//! Runs a program with the given arguments with elevated rights
	virtual bool executeAsAdmin(const QString &program, const QStringList &arguments) = 0;
};

}

#endif // SEEDUPDATER_ADMINAUTHORISER_H
