#!/bin/python3

import hashlib
import sys
from pathlib import Path

key, msg = sys.argv[1:3]

# print(hmac.new(key, msg, hashlib.sha1).hexdigest())
file = Path('hash')
file.write_bytes(hashlib.sha256(f"{key}:{msg}".encode()).digest())
