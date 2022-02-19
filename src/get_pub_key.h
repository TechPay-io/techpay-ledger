#ifndef TECHPAY_LEDGER_GET_PUB_KEY_H
#define TECHPAY_LEDGER_GET_PUB_KEY_H

#include "common.h"
#include "handlers.h"
#include "bip44.h"
#include "derive_key.h"

// handleGetPublicKey implements Get Public Key APDU instruction handler.
handler_fn_t handleGetPublicKey;

// ins_get_ext_pubkey_context_t defines instruction context for Get Public Key APU instruction.
typedef struct {
    int16_t responseReady;
    bip44_path_t path;
    extended_public_key_t pubKey;
    int uiStep;
} ins_get_ext_pubkey_context_t;

#endif //TECHPAY_LEDGER_GET_PUB_KEY_H
