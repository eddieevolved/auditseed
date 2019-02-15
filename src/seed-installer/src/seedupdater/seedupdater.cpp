#include "seedupdater.h"
#include "seedupdater_p.h"
#include "../updatecontroller_p.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>

using namespace QtSeedUpdater;

const QStringList SeedUpdater::NormalUpdateArguments = {QStringLiteral("--updater")};
const QStringList SeedUpdater::PassiveUpdateArguments = {QStringLiteral("--updater"), QStringLiteral("skipPrompt=true")};
const QStringList SeedUpdater::HiddenUpdateArguments = {QStringLiteral("--silentUpdate")};

SeedUpdater::SeedUpdater(QObject *parent) :
	SeedUpdater("", parent)
{}

SeedUpdater::SeedUpdater(const QString &currentVersion, QObject *parent) :
	QObject(parent),
	d(new SeedUpdaterPrivate(this))
{
	d->currentVersion = currentVersion;
}

SeedUpdater::~SeedUpdater() {}

bool SeedUpdater::exitedNormally() const
{
	return d->normalExit;
}

int SeedUpdater::errorCode() const
{
	return d->lastErrorCode;
}

QByteArray SeedUpdater::errorLog() const
{
	return d->lastErrorLog;
}

bool SeedUpdater::willRunOnExit() const
{
	return d->runOnExit;
}

QString SeedUpdater::currentVersion() const
{
	return d->currentVersion;
}

bool SeedUpdater::isRunning() const
{
	return isUpdaterRunning;
}

QList<SeedUpdater::SeedUpdateInfo> SeedUpdater::updateInfo() const
{
	return d->updateInfos;
}

bool SeedUpdater::checkForUpdates()
{
	return d->startUpdateCheck();
}

void SeedUpdater::abortUpdateCheck(int maxDelay, bool async)
{
	d->stopUpdateCheck(maxDelay, async);
}

int SeedUpdater::scheduleUpdate(int delaySeconds, bool repeated)
{
	if((((qint64)delaySeconds) * 1000ll) > (qint64)INT_MAX) {
		qCWarning(logSeedUpdater) << "delaySeconds to big to be converted to msecs";
		return 0;
	}
	return d->scheduler->startSchedule(delaySeconds * 1000, repeated);
}

int SeedUpdater::scheduleUpdate(const QDateTime &when)
{
	return d->scheduler->startSchedule(when);
}

void SeedUpdater::cancelScheduledUpdate(int taskId)
{
	d->scheduler->cancelSchedule(taskId);
}

void SeedUpdater::runUpdaterOnExit(AdminAuthoriser *authoriser)
{
	runUpdaterOnExit(NormalUpdateArguments, authoriser);
}

void SeedUpdater::runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser)
{
	d->runOnExit = true;
	d->runArguments = arguments;
	d->adminAuth.reset(authoriser);
}

void SeedUpdater::cancelExitRun()
{
	d->runOnExit = false;
	d->adminAuth.reset();
}



SeedUpdater::SeedUpdateInfo::SeedUpdateInfo() :
	name(),
	version(),
	size(0ull)
{}

SeedUpdater::SeedUpdateInfo::SeedUpdateInfo(const SeedUpdater::SeedUpdateInfo &other) :
	name(other.name),
	version(other.version),
	size(other.size)
{}

SeedUpdater::SeedUpdateInfo::SeedUpdateInfo(QString name, QString version, quint64 size) :
	name(name),
	version(version),
	size(size)
{}

QDebug &operator<<(QDebug &debug, const SeedUpdater::SeedUpdateInfo &info)
{
	QDebugStateSaver state(debug);
	Q_UNUSED(state);

	debug.noquote() << QStringLiteral("{Name: \"%1\"; Version: %2; Size: %3}")
					   .arg(info.name)
					   .arg(info.version.toUtf8().constData())
					   .arg(info.size);
	return debug;
}
