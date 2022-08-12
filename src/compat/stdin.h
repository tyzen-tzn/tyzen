// Copyright (c) 2018 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TYZEN_COMPAT_STDIN_H
#define TYZEN_COMPAT_STDIN_H

struct NoechoInst {
    NoechoInst();
    ~NoechoInst();
};

#define NO_STDIN_ECHO() NoechoInst _no_echo

bool StdinTerminal();
bool StdinReady();

#endif // TYZEN_COMPAT_STDIN_H
