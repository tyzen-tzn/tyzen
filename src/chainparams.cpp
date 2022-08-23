// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <deploymentinfo.h>
#include <hash.h> // for signet block challenge hash
#include <script/interpreter.h>
#include <util/string.h>
#include <util/system.h>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
 static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
 {
     const char* pszTimestamp = "CryotoNoon Community October 29 2020 Bitcoin reaches its highest price in 2020";
     const CScript genesisOutputScript = CScript() << ParseHex("045c943f203a366efeb5a39839496a0220576341e34ea863150c47d44f657aebe53c5060d9a8f8a8cd083fd0d39c4b78d8f743492c2ecc8643f702d5e94d3b1092") << OP_CHECKSIG;
     return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
 }

/**
 * Main network on which people trade goods and services.
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 950000;
        consensus.script_flag_exceptions.emplace( // BIP16 exception
            uint256S("0x00"), SCRIPT_VERIFY_NONE);
        consensus.script_flag_exceptions.emplace( // Taproot exception
            uint256S("0x00"), SCRIPT_VERIFY_P2SH | SCRIPT_VERIFY_WITNESS);
        consensus.BIP34Height = 42470;
        consensus.BIP34Hash = uint256S("0x9185932f37769357e51b3dd2b8562797b5f4e73e8e8be4acb74659d3982c6bb5");
        consensus.BIP65Height = 42470;
        consensus.BIP66Height = 42470;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 100000;
        consensus.MinBIP9WarningHeight = 0; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 1 * 90;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1661999084;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1693535084;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 1661999084;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = 1693535084;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        consensus.nMinimumChainWork = uint256S("0x00");
        consensus.defaultAssumeValid = uint256S("0x59ceec40a8afa8bd23bbb5fff924b47cf5a320afa3c2de6f78cab06fdfe83427"); //1155631

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
         pchMessageStart[0]  = 0xfd;
         pchMessageStart[1]  = 0xd9;
         pchMessageStart[2]  = 0x10;
         pchMessageStart[3]  = 0xce;
         nDefaultPort = 2333;
         nPruneAfterHeight = 100000;
         m_assumed_blockchain_size = 3;
         m_assumed_chain_state_size = 6;

         genesis = CreateGenesisBlock(1603935375, 2229, 0x20000fff, 1, 50 * COIN);
         consensus.hashGenesisBlock = genesis.GetHash();
         assert(consensus.hashGenesisBlock == uint256S("0x59ceec40a8afa8bd23bbb5fff924b47cf5a320afa3c2de6f78cab06fdfe83427"));
         assert(genesis.hashMerkleRoot == uint256S("0x15f4f969a7196ff4fb32b2a70ad32133e05b0c8f1b5ef20847e58b030da47bca"));
        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as an addrfetch if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.

        vSeeds.emplace_back("node1.tyzen.io.");
        vSeeds.emplace_back("node2.tyzen.io.");
        vSeeds.emplace_back("node3.tyzen.io.");
        vSeeds.emplace_back("node4.tyzen.io.");
        vSeeds.emplace_back("node5.tyzen.io.");
        vSeeds.emplace_back("node6.tyzen.io.");
        vSeeds.emplace_back("node7.tyzen.io.");
        vSeeds.emplace_back("node8.tyzen.io.");
        vSeeds.emplace_back("node9.tyzen.io.");
        vSeeds.emplace_back("node10.tyzen.io.");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,128);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,205);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x03, 0xb4, 0x73, 0x34};
        base58Prefixes[EXT_SECRET_KEY] = {0x03, 0xb4, 0x73, 0xb9};

        bech32_hrp = "ty";

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_main), std::end(chainparams_seed_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x000000fd190d1f1f7685c1873e51cd8f1a543d9f7af17a7fe9a6fa90321b80f8")},
                { 50324, uint256S("0xd489e209c8a7af85b7c4637e8e79510cbefb6d3abedd0f0b79087c73ebffc499")},

            }
        };

        m_assumeutxo_data = MapAssumeutxo{
         // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 000000000000000000052d314a259755ca65944e68df6b12a067ea8f1f5a7091
            /* nTime    */  1660260146,
            /* nTxCount */ 0,
            /* dTxRate  */ 0.01,
        };
    }
};

/**
 * Testnet (v3): public test network which is reset from time to time.
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 950000;
        consensus.script_flag_exceptions.emplace( // BIP16 exception
            uint256S("0x00"), SCRIPT_VERIFY_NONE);
        consensus.BIP34Height = 76;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 76; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 76; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 0; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 0; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 600000; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 1 * 90;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        consensus.nMinimumChainWork = uint256S("0x00");
        consensus.defaultAssumeValid = uint256S("0xda67b050263323f14b35e9793ff9991366ef8e92fe5f83fb7e2781f9a3fd953b"); // 2143398

        pchMessageStart[0] = 0x4e;
        pchMessageStart[1] = 0x19;
        pchMessageStart[2] = 0x70;
        pchMessageStart[3] = 0xaf;
        nDefaultPort = 20595;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 40;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1603935376, 4606, 0x20000fff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xda67b050263323f14b35e9793ff9991366ef8e92fe5f83fb7e2781f9a3fd953b"));
        assert(genesis.hashMerkleRoot == uint256S("0x15f4f969a7196ff4fb32b2a70ad32133e05b0c8f1b5ef20847e58b030da47bca"));


        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet1.tyzen.io.");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,105);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,206);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x03, 0xba, 0x2f, 0x80};
        base58Prefixes[EXT_SECRET_KEY] = {0x03, 0xba, 0x30, 0x05};

        bech32_hrp = "tq";

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_test), std::end(chainparams_seed_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {0, uint256S("0xda67b050263323f14b35e9793ff9991366ef8e92fe5f83fb7e2781f9a3fd953b")},
            }
        };

        m_assumeutxo_data = MapAssumeutxo{
            // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000d18cfe81cbeea665076807789bd8f831d557632e635bc6e3c003069e
            /* nTime    */  1603935376,
            /* nTxCount */ 0,
            /* dTxRate  */ 0.001,
        };
    }
};


static void MaybeUpdateHeights(const ArgsManager& args, Consensus::Params& consensus)
{
    for (const std::string& arg : args.GetArgs("-testactivationheight")) {
        const auto found{arg.find('@')};
        if (found == std::string::npos) {
            throw std::runtime_error(strprintf("Invalid format (%s) for -testactivationheight=name@height.", arg));
        }
        const auto name{arg.substr(0, found)};
        const auto value{arg.substr(found + 1)};
        int32_t height;
        if (!ParseInt32(value, &height) || height < 0 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Invalid height value (%s) for -testactivationheight=name@height.", arg));
        }
        if (name == "segwit") {
            consensus.SegwitHeight = int{height};
        } else if (name == "bip34") {
            consensus.BIP34Height = int{height};
        } else if (name == "dersig") {
            consensus.BIP66Height = int{height};
        } else if (name == "cltv") {
            consensus.BIP65Height = int{height};
        } else if (name == "csv") {
            consensus.CSVHeight = int{height};
        } else {
            throw std::runtime_error(strprintf("Invalid name (%s) for -testactivationheight=name@height.", arg));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN) {
        return std::unique_ptr<CChainParams>(new CMainParams());
    } else if (chain == CBaseChainParams::TESTNET) {
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    }
  //  throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(gArgs, network);
}
