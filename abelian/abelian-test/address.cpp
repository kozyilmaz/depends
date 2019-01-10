#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

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
#include "util.h"

static struct option long_options[] = {
	{ "help",	no_argument,	0,	'h' },
	{ "verbose",	no_argument,	0,	'v' },
	{ "network",	required_argument,	0,	'n' },
	{ 0, 0, 0, 0 }
};

static int print_help (const char *pname)
{
	fprintf(stdout, "%s usage:\n", pname);
	fprintf(stdout, "  --help    | -h : print help\n");
	fprintf(stdout, "  --verbose | -v : print extra info\n");
	fprintf(stdout, "  --network | -n : use network name [main, testnet or regtest] (default is 'main')\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "examples:\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "  %s -n main\n", pname);
	fprintf(stdout, "  %s -n testnet\n", pname);
	fprintf(stdout, "  %s --v\n", pname);
	fprintf(stdout, "  %s --v -n regtest\n", pname);
	fprintf(stdout, "  %s --verbose -n testnet\n", pname);
	return 0;
}

int main (int argc, char *argv[])
{
	int c;
	int index;
	int verbose;
	const char *network;

	CKey key;
	CPubKey pubkey;
	CPrivKey privkey;

	char *keystr;
	char *pubkeystr;

	// defaults
	verbose = 0;
	network = NULL;

	index = 0;
	while (1) {
		c = getopt_long(argc, argv, "hvn:", long_options, &index);
		if (c == -1) {
			break;
		}
		switch (c) {
			case 'v':
				verbose = 1;
				break;
			case 'n':
				network = optarg;
				break;
			case 'h':
				print_help(argv[0]);
				goto out;
		}
	}
	// default to main
	if (network == NULL) {
		network = "main";
	}

	// init Bitcoin subsystem
	if (!bitcoin_init(network)) {
		printf("bitcoin init failed\n");
		goto out;
	}

	// create a new private key (RNG)
	key.MakeNewKey(true);
	if (!key.IsValid()) {
		printf("key invalid!\n");
		goto out;
	}
	printf("key size: %u (%s)\n", key.size(), (key.IsCompressed() == true) ? "compressed" : "uncompressed");

	// serialized OpenSSL private key data (DER encoded)
	privkey = key.GetPrivKey();
	printf("key size (DER): %lu\n", privkey.size());
	// serialized public key
	pubkey = key.GetPubKey();
	printf("public key size: %u\n", pubkey.size());

	// verify public key
	if (key.VerifyPubKey(pubkey) != true) {
		printf("pubkey failed!\n");
		goto out;
	}

	// private key (hex)
	bin_to_hex(key.begin(), key.size(), &keystr);
	printf("private key    : %s\n", keystr);

	// public key (hex)
	bin_to_hex(pubkey.begin(), pubkey.size(), &pubkeystr);
	printf("public key     : %s\n", pubkeystr);

	// create WIF formatted private key
	printf("WIF import key : %s\n", EncodeSecret(key).c_str());

	// get wallet address
	printf("legacy address : %s\n", EncodeDestination(GetDestinationForKey(key.GetPubKey(), OutputType::LEGACY)).c_str());
	printf("segwit address : %s\n", EncodeDestination(GetDestinationForKey(key.GetPubKey(), OutputType::P2SH_SEGWIT)).c_str());
	printf("bech32 address : %s\n", EncodeDestination(GetDestinationForKey(key.GetPubKey(), OutputType::BECH32)).c_str());

out:
	bitcoin_fini();
	return 0;
}
