from hashlib import md5
from struct import unpack_from
from bisect import bisect_left

ITEMS = 1000
NODES = 100
node_stat = [0 for i in range(NODES)]


def _hash(value):
    k = md5(str(value)).digest()
    ha = unpack_from(">I", k)[0]
    return ha

ring = []
hash2node = {}

for n in range(NODES):
    h = _hash(n)
    ring.append(h)
    ring.sort()
    hash2node[h] = n


for item in range(ITEMS):
    h = _hash(item)
    print("hash number: %d" % h)
    n1 = bisect_left(ring, h) 
    print("insert pos: %d" % n1)
    n = n1 % NODES
    print("insert pos mod NODES : %d" % n)
    node_stat[hash2node[ring[n]]] += 1

print("ring : %s" % ring)
print("hash2node: %s" % hash2node)
print("node_stat: %s" % node_stat)

_ave = ITEMS / NODES
_max = max(node_stat)
_min = min(node_stat)

print("Ave: %d" % _ave)
print("Max: %d\t(%0.2f%%)" % (_max, (_max - _ave) * 100.0 / _ave))
print("Min: %d\t(%0.2f%%)" % (_min, (_ave - _min) * 100.0 / _ave))
