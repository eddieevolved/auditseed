#ifndef QTSEEDUPDATER_ADMINAUTHORIZATION_P_H
#define QTSEEDUPDATER_ADMINAUTHORIZATION_P_H

#include "seedupdater/adminauthoriser.h"

namespace QtSeedUpdater
{

class AdminAuthorization : public AdminAuthoriser
{
public:
	bool hasAdminRights() override;
	bool executeAsAdmin(const QString &program, const QStringList &arguments) override;
};

}

#endif // QTSEEDUPDATER_ADMINAUTHORIZATION_P_H
