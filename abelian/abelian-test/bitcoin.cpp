#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bitcoin/compat/sanity.h"
#include "bitcoin/random.h"
#include "bitcoin/key.h"
#include "bitcoin/pubkey.h"

#include "bitcoin/init.h"
#include "bitcoin/util.h"
#include "bitcoin/base58.h"
#include "bitcoin/key_io.h"
#include "bitcoin/chainparams.h"
#include "bitcoin/outputtype.h"
#include "bitcoin/utilstrencodings.h"

#include "bitcoin.h"

static std::unique_ptr<ECCVerifyHandle> globalVerifyHandle;

bool bitcoin_init (const char *network)
{
	std::string chain;
	std::string sha256_algo;
	// sanity
	if (network == NULL) {
		printf("no network\n");
		goto err0;
	}
	// init network params
	if (strcmp(network, "main") == 0) {
		chain = CBaseChainParams::MAIN;
	} else if (strcmp(network, "testnet") == 0) {
		chain = CBaseChainParams::TESTNET;
	} else if (strcmp(network, "regtest") == 0) {
		chain = CBaseChainParams::REGTEST;
	} else {
		printf("invalid network\n");
		goto err0;
	}
	// init sha256
	sha256_algo = SHA256AutoDetect();
	printf("using the '%s' SHA256 implementation\n", sha256_algo.c_str());
	// init randomness
	RandomInit();
	// init elliptic curve
	ECC_Start();
	// setup environment
	SetupEnvironment();
	// required for secp256k1
	globalVerifyHandle.reset(new ECCVerifyHandle());

	// test elliptic curve
	if(!ECC_InitSanityCheck()) {
		printf("elliptic curve cryptography sanity check failure!\n");
		goto err1;
	}
	// test glibc/glibxx
	if (!glibc_sanity_test() || !glibcxx_sanity_test()) {
		printf("glibc/glibcxx sanity check failure!\n");
		goto err1;
	}
	// test randomness
	if (!Random_SanityCheck()) {
		printf("OS cryptographic RNG sanity check failure!\n");
		goto err1;
	}
	// select network
	SelectParams(chain);
	return true;

err1:	globalVerifyHandle.reset();
	ECC_Stop();
err0:	return false;
}

bool bitcoin_fini (void)
{
	globalVerifyHandle.reset();
	ECC_Stop();
	return true;
}
