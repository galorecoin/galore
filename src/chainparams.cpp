// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It will only connect to one or two seed nodes because once it connects,
	// it will get a pile of addresses with newer timestamps.
	// Seed nodes are given a random "last seen time" of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xbc;
		pchMessageStart[1] = 0x2a;
		pchMessageStart[2] = 0x14;
		pchMessageStart[3] = 0x5c;
		vAlertPubKey = ParseHex("04465944b7b7989cec0b7d5c9fd4938df1d087e45bf0f6adc13e9143583692817b93d44783d2ff3d27601c00b26a21353b4cb5cccb4b18c2f685bbdbd3247870c5");
		nDefaultPort = 46555;
		nRPCPort = 46722;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.
		//
		
		const char* pszTimestamp = "start galore coin most wonderful way";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1550056549, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1550056549;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 340111;

		hashGenesisBlock = genesis.GetHash();
  
        LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
	    LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("Display nonce so we can input it below %s\n", genesis.nNonce);
        LogPrintf("Display time so we can input it below %s\n", genesis.nTime);

		assert(genesis.hashMerkleRoot == uint256("0xb8ba5a6357f4601eea10412a2a3343aa6227a88f8ab7ea7c20ecea26590f2316"));
		assert(hashGenesisBlock == uint256("0x7f7cf987368ae1c00f93894e6bc887b8082d115509ad81f66d9355dfe0d1a2ec"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 97);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 98);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 99);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0", "80.211.101.159"));
		vSeeds.push_back(CDNSSeedData("1", "80.211.169.34"));
		vSeeds.push_back(CDNSSeedData("3", "80.211.80.221"));
//		vSeeds.push_back(CDNSSeedData("2", ""));
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		//strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		//strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		strDarksendPoolDummyAddress = "hFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";
		nLastPOWBlock = 2000000;
		nPOSStartBlock = 20;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x1d;
		pchMessageStart[1] = 0x7e;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0x2c;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("047a8fc5e29bdc543c6b9a326c880ad3c82e1895a907324d7af08e4d7bb8f1a9719a9dd96a14222325f798b4e2d0093c02ae665596f285592dd99fc21a9450369b");
		nDefaultPort = 20316;
		nRPCPort = 20317;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 216893;
		genesis.nTime    = 1550056550;

        hashGenesisBlock = genesis.GetHash();

        LogPrintf("Display testNet genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());

		assert(hashGenesisBlock == uint256("0x3b2c66d1e740ebe1ca48e423fab04cf02e1f67265747d51d1f96504867164eb0"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}