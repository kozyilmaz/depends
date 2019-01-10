#ifndef __BITCOIN_COMMON_H__
#define __BITCOIN_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

bool bitcoin_init (const char *network);
bool bitcoin_fini (void);

#ifdef __cplusplus
}
#endif

#endif /* __BITCOIN_COMMON_H__ */
