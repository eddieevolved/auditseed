// Copyright (c) 2012-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The Seedcore developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for communicating with SeedGate.
 */
#ifndef BITCOIN_SEEDCONTROL_H
#define BITCOIN_SEEDCONTROL_H

#include <string>

#include <boost/function.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/thread.hpp>

extern const std::string DEFAULT_SEED_CONTROL;
static const bool DEFAULT_LISTEN_ONION = true;

void StartSeedControl(boost::thread_group& threadGroup);
void InterruptSeedControl();
void StopSeedControl();

#endif /* BITCOIN_SEEDCONTROL_H */


