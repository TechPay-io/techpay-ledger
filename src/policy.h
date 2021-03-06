#ifndef TECHPAY_LEDGER_POLICY_H
#define TECHPAY_LEDGER_POLICY_H

#include <os_io_seproxyhal.h>
#include "bip44.h"
#include "errors.h"

// security_policy_t defines levels of security policy enforcement
typedef enum {
    // POLICY_DENY is used to tag an action that is denied by security policy.
    POLICY_DENY = 1,

    // POLICY_PROMPT is used to tag an action that is allowed
    // by security policy only if confirmed by user.
    POLICY_PROMPT = 2,

    // POLICY_WARN is used to tag an action that is allowed
    // by security policy, but user is warned on screen that
    // it's under unusual conditions (i.e. unusual account, or address depth).
    POLICY_WARN = 3,

    // POLICY_SHOW is used to tag an action that is allowed by security policy,
    // but user is informed with the data on screen.
    POLICY_SHOW = 4,

    // POLICY_ALLOW is used to tag an action that is allowed by security policy,
    // user will not be notified about this action since it's considered safe.
    POLICY_ALLOW = 5,
} security_policy_t;

// policyForGetPublicKey implements policy test for public key extraction.
security_policy_t policyForGetPublicKey(const bip44_path_t* path);

// policyForGetPublicKey implements policy test for address derivation.
security_policy_t policyForGetAddress(const bip44_path_t* path, const bool isShowAddress);

// policyForSignTxInit implements policy test for new transaction being signed.
security_policy_t policyForSignTxInit(const bip44_path_t* path);

// policyForSignTxFinalize implements policy test for transaction signature being provided.
security_policy_t policyForSignTxFinalize();

// ASSERT_NOT_DENIED tests given policy for denied status and throws
// an exception if the action has indeed been denied.
static inline void ASSERT_NOT_DENIED(security_policy_t policy) {
    if (policy == POLICY_DENY) {
        THROW(ERR_REJECTED_BY_POLICY);
    }
}

#endif //TECHPAY_LEDGER_POLICY_H
