// Copyright (c) 2019 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TYZEN_TEST_UTIL_WALLET_H
#define TYZEN_TEST_UTIL_WALLET_H

#include <string>

namespace wallet {
class CWallet;
} // namespace wallet

// Constants //

extern const std::string ADDRESS_BCRT1_UNSPENDABLE;

// RPC-like //

/** Import the address to the wallet */
void importaddress(wallet::CWallet& wallet, const std::string& address);
/** Returns a new address from the wallet */
std::string getnewaddress(wallet::CWallet& w);


#endif // TYZEN_TEST_UTIL_WALLET_H
