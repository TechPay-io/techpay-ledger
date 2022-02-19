#ifndef TECHPAY_LEDGER_GET_TX_SIGN_H
#define TECHPAY_LEDGER_GET_TX_SIGN_H

#include "common.h"
#include "handlers.h"
#include "transaction.h"
#include "tx_stream.h"
#include "bip44.h"

// WEI_TO_TPC_DECIMALS defines how many decimals we need to push
// to convert between WEI units used for transaction amounts and human readable TPCs
#define WEI_TO_TPC_DECIMALS 18

// EXPECTED_CHAIN_ID represents expected chain id for the TechPay network
// We don't sign transaction outside of the TechPay space, the whole chain
// is EIP155 compliant and tries to prevent any replay attack vectors.
// This is one of the mitigation in place.
#define EXPECTED_CHAIN_ID 0xfa

// handleSignTransaction implements Sign Transaction APDU instruction handler.
handler_fn_t handleSignTransaction;

// tx_stage_t declares stages of the transaction signature building
typedef enum {
    SIGN_STAGE_NONE = 0,
    SIGN_STAGE_INIT = 1,
    SIGN_STAGE_COLLECT = 2,
    SIGN_STAGE_FINALIZE = 4,
    SIGN_STAGE_DONE = 8,
} tx_stage_t;

// ins_sign_tx_context_t declares context
// for transaction signature building APDU instruction
typedef struct {
    int16_t responseReady;
    bip44_path_t path;
    transaction_t tx;
    tx_stream_context_t stream;
    cx_sha3_t sha3Context;
    tx_signature_t signature;
    tx_stage_t stage;
    int uiStep;
} ins_sign_tx_context_t;

#endif //TECHPAY_LEDGER_GET_TX_SIGN_H
