#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"

#include "vtree.h"

#include "vcc_if.h"

struct key {
	const char *key;
	VRB_ENTRY(key) tree;
};

static int
keycmp(const struct key *k1, const struct key *k2) {
	return (strcmp(k1->key, k2->key));
}

VRB_HEAD(tbtree, key);
VRB_PROTOTYPE_STATIC(tbtree, key, tree, keycmp)
VRB_GENERATE_STATIC(tbtree, key, tree, keycmp);

/* Represents a token bucket for a specific key. */
struct tbucket {
	struct key k;
	unsigned magic;
#define TBUCKET_MAGIC 0x53345eb9
	double last_used;
	double period;
	long tokens;
	long capacity;
	pthread_mutex_t mtx;
};

struct vsthrottle {
	unsigned magic;
#define VSTHROTTLE_MAGIC 0xc9f28325
	pthread_mutex_t mtx;
	struct tbtree tbs;
};

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf) {
	return (0);
}

static struct tbucket *
get_bucket(const char *key) {
	return (NULL);
}

static void
update_tokens(struct tbucket *b) {
	/* XXX: Assert b->mtx is held. */
}

VCL_BOOL
vmod_is_denied(const struct vrt_ctx *ctx, VCL_STRING key, VCL_INT limit,
    VCL_DURATION period) {
	return (1);
}
