#!/usr/bin/env python
from __future__ import print_function

from ledgerblue.comm import getDongle
from ledgerblue.commException import CommException
import argparse
import struct
import binascii

def parse_bip32_path(path):
    if len(path) == 0:
        return b""
    result = b""
    elements = path.split('/')
    for pathElement in elements:
        element = pathElement.split('\'')
        if len(element) == 1:
            result = result + struct.pack(">I", int(element[0]))
        else:
            result = result + struct.pack(">I", 0x80000000 | int(element[0]))
    return result


# inform what we do
print("~~ TechPay Nano Ledger Test ~~")
print("Requesting public key for BIP44 path: INS 0x10")

# what BIP44 path we will request
parser = argparse.ArgumentParser()
parser.add_argument('--path', help="BIP 32 path to retrieve")
args = parser.parse_args()

if args.path == None:
    args.path = "44'/60'/0'/0/0"

# parse the path and show it
bipPath = parse_bip32_path(args.path)

# Create APDU message.
# --------------------
# CLA 0xE0
# INS 0x10  GET PUBLIC KEY
# P1 0x00   NO DATA
# P2 0x00   NO DATA
# Lc <var>  PATH LENGTH
# --------------------
apdu = bytearray.fromhex("e0100000") + chr(len(bipPath) + 1).encode() + \
    chr(len(bipPath) // 4).encode() + bipPath

# send the APDU message to Ledger
dongle = getDongle(True)
result = dongle.exchange(bytes(apdu))

# parse response and show the key data
offset = 1 + result[0]
address = result[offset + 1: offset + 1 + result[offset]]

print("Public key", binascii.hexlify(result[1: 1 + result[0]]).decode())

