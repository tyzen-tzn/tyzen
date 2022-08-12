// Copyright (c) 2017-2022 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TYZEN_RPC_MEMPOOL_H
#define TYZEN_RPC_MEMPOOL_H

class CTxMemPool;
class UniValue;

/** Mempool information to JSON */
UniValue MempoolInfoToJSON(const CTxMemPool& pool);

/** Mempool to JSON */
UniValue MempoolToJSON(const CTxMemPool& pool, bool verbose = false, bool include_mempool_sequence = false);

#endif // TYZEN_RPC_MEMPOOL_H
