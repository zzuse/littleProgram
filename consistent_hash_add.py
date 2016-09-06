from hashlib import md5
from struct import unpack_from
from bisect import bisect_left

ITEMS = 10000
NODES = 100
NEW_NODES = 101


def _hash(value):
    k = md5(str(value)).digest()
    ha = unpack_from(">I", k)[0]
    return ha

ring = []
new_ring = []

for n in range(NODES):
    ring.append(_hash(n))
    ring.sort()

for n in range(NEW_NODES):
    new_ring.append(_hash(n))
    new_ring.sort()

change = 0

print("ring,%s"%ring)
print("new ring,%s"%ring)
for item in range(ITEMS):
    h = _hash(item)
    n = bisect_left(ring, h) % NODES

    print("n,%d"%n)
    new_n = bisect_left(new_ring, h) % NEW_NODES
    if new_n != n:
        change += 1

print("Change: %d\t(%0.2f%%)" % (change, change * 100.0 / ITEMS))
