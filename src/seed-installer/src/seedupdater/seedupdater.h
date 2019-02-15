#ifndef SEEDUPDATER_SEEDUPDATER_H
#define SEEDUPDATER_SEEDUPDATER_H

#include "adminauthoriser.h"

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qlist.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qversionnumber.h>
#include <QtCore/qscopedpointer.h>

namespace QtSeedUpdater
{

class SeedUpdaterPrivate;
//! The main updater. Can check for updates and run the current app as updater
class SeedUpdater : public QObject
{
	Q_OBJECT

	//! Holds currentVersion
	Q_PROPERTY(QString currentVersion READ currentVersion CONSTANT FINAL)
	//! Specifies whether the updater is currently checking for updates or not
	Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)
	//! Holds extended information about the last update check
	Q_PROPERTY(QList<SeedUpdateInfo> updateInfo READ updateInfo NOTIFY updateInfoChanged)

public:
	//! Provides information about updates for components
	struct SeedUpdateInfo
	{
		//! The name of the component that has an update
		QString name;
		//! The new version for that compontent
		QString version;
		//! The update download size (in Bytes)
		quint64 size;

		//! Default Constructor
		SeedUpdateInfo();
		//! Copy Constructor
		SeedUpdateInfo(const SeedUpdateInfo &other);
		//! Constructor that takes name, version and size
		SeedUpdateInfo(QString name, QString version, quint64 size);
	};

	static const QStringList NormalUpdateArguments;
	static const QStringList PassiveUpdateArguments;
	static const QStringList HiddenUpdateArguments;

	//! Default constructor
	explicit SeedUpdater(QObject *parent = nullptr);
	//! Constructer with an explicitly set currentVersion
	explicit SeedUpdater(const QString &currentVersion, QObject *parent = nullptr);
	//! Destroyes the updater and kills the update check (if running)
	~SeedUpdater();

	//! Returns `true`, if the updater exited normally
	bool exitedNormally() const;
	//! Returns the error code of the last update
	int errorCode() const;
	//! returns the error output (stderr) of the last update
	QByteArray errorLog() const;

	//! Returns `true` if will be started on exit
	bool willRunOnExit() const;

	//! readAcFn{SeedUpdater::currentVersion}
	QString currentVersion() const;
	//! readAcFn{SeedUpdater::running}
	bool isRunning() const;
	//! readAcFn{SeedUpdater::updateInfo}
	QList<SeedUpdateInfo> updateInfo() const;

public Q_SLOTS:
	//! Starts checking for updates
	bool checkForUpdates();
	//! Aborts checking for updates
	void abortUpdateCheck(int maxDelay = 5000, bool async = false);

	//! Schedules an update after a specific delay, optionally repeated
	int scheduleUpdate(int delaySeconds, bool repeated = false);
	//! Schedules an update for a specific timepoint
	int scheduleUpdate(const QDateTime &when);
	//! Cancels the scheduled update with taskId
	void cancelScheduledUpdate(int taskId);

	//! Runs the updater on exit, using the given admin authorisation
	void runUpdaterOnExit(AdminAuthoriser *authoriser = nullptr);
	//! Runs the updater on exit, using the given arguments and admin authorisation
	void runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser = nullptr);
	//! The updater will not run the updater on exit anymore
	void cancelExitRun();

Q_SIGNALS:
	//! Will be emitted as soon as the updater finished checking for updates
	void checkUpdatesDone(bool hasUpdates, bool hasError);

	//! notifyAcFn{SeedUpdater::running}
	void runningChanged(bool running);
	//! notifyAcFn{SeedUpdater::updateInfo}
	void updateInfoChanged(QList<SeedUpdater::SeedUpdateInfo> updateInfo);

private:
	QScopedPointer<SeedUpdaterPrivate> d;
};

}

Q_DECLARE_METATYPE(QtSeedUpdater::SeedUpdater::SeedUpdateInfo)

QDebug &operator<<(QDebug &debug, const QtSeedUpdater::SeedUpdater::SeedUpdateInfo &info);

#endif // SEEDUPDATER_SEEDUPDATER_H
