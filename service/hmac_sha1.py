#!/bin/python3

import hashlib
import hmac
import sys
from pathlib import Path

key, msg = map(lambda x: x.encode(), sys.argv[1:3])

# print(hmac.new(key, msg, hashlib.sha1).hexdigest())
file = Path('hash')
file.write_bytes(hmac.new(key, msg, hashlib.sha1).digest())
