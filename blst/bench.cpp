#include "blst.hpp"
#include <cybozu/benchmark.hpp>

void put(const char *msg, const void *buf, size_t n)
{
	const uint8_t *src = (const uint8_t *)buf;
	if (msg && *msg) printf("%s\n", msg);
	for (size_t i = 0; i < n; i++) {
		printf("%02x", src[i]);
		if ((i % 48) == 47) printf("\n");
	}
}

void putRev(const void *buf, size_t n)
{
	const uint8_t *src = (const uint8_t *)buf;
	for (size_t i = 0; i < n; i++) {
		printf("%02x", src[n - 1 - i]);
	}
	printf("\n");
}

void put(const blst::blst_fp* x)
{
	uint32_t a[12];
	blst_uint32_from_fp(a, x);
	putRev(a, sizeof(a));
}

const blst::blst_fp2* get_fp2(const blst::PT& e)
{
	return &((const blst::blst_fp12*)(&e))->fp6[0].fp2[0];
}

const blst::blst_fp* get_fp(const blst::PT& e)
{
	return &get_fp2(e)->fp[0];
}

void put(const char *msg, const blst::PT& e)
{
	printf("%s\n", msg);
	for (int i = 0; i < 12; i++) {
		put(&get_fp(e)[i]);
	}
}

void pairing(const blst::P1_Affine& P, const blst::P2_Affine& Q)
{
	blst::PT e(Q, P);
	e.final_exp();
}

int main()
{
	using namespace blst;
	P1_Affine P = P1_Affine::generator();
	P2_Affine Q = P2_Affine::generator();
	byte buf1[96];
	byte buf2[192];
	P.serialize(buf1);
	Q.serialize(buf2);
	put("P", buf1, sizeof(buf1));
	put("Q", buf2, sizeof(buf2));
	
	PT e(Q, P);
	e.final_exp();
	put("e", e);
	CYBOZU_BENCH_C("pairing", 1000, pairing, P, Q);
	CYBOZU_BENCH_C("ML", 1000, PT, Q, P);
	CYBOZU_BENCH_C("FE", 1000, e.final_exp);
	{
		blst_fp a = get_fp(e)[0];
		blst_fp b = get_fp(e)[1];
		CYBOZU_BENCH_C("fp::mul", 10000, blst_fp_mul, &a, &a, &b);
	}
	{
		blst_fp2 a = get_fp2(e)[0];
		blst_fp2 b = get_fp2(e)[1];
		CYBOZU_BENCH_C("fp2::mul", 10000, blst_fp2_mul, &a, &a, &b);
		CYBOZU_BENCH_C("fp2::sqr", 10000, blst_fp2_sqr, &a, &a);
	}
}
