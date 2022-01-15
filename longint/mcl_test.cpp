#include "mcl.h"
#include <cybozu/benchmark.hpp>
#include <cybozu/xorshift.hpp>
#include <cybozu/test.hpp>
#include <mcl/gmp_util.hpp>
#include <gmp.h>
#include <low_func.hpp>

const int C = 1000000;

template<int N>
void gmp_mulPre(uint64_t *z, const uint64_t *x, const uint64_t *y)
{
	mpn_mul_n((mp_limb_t*)z, (const mp_limb_t*)x, (const mp_limb_t*)y, N);
}

struct Montgomery {
	typedef mcl::fp::Unit Unit;
	mpz_class p_;
	mpz_class R_; // (1 << (pn_ * 64)) % p
	mpz_class RR_; // (R * R) % p
	Unit rp_; // rp * p = -1 mod M = 1 << 64
	size_t pn_;
	Montgomery() {}
	explicit Montgomery(const mpz_class& p)
	{
		p_ = p;
		rp_ = mcl::fp::getMontgomeryCoeff(mcl::gmp::getUnit(p, 0));
		pn_ = mcl::gmp::getUnitSize(p);
		R_ = 1;
		R_ = (R_ << (pn_ * 64)) % p_;
		RR_ = (R_ * R_) % p_;
	}

	void toMont(mpz_class& x) const { mul(x, x, RR_); }
	void fromMont(mpz_class& x) const { mul(x, x, 1); }

	void mul(mpz_class& z, const mpz_class& x, const mpz_class& y) const
	{
#if 1
		const size_t ySize = mcl::gmp::getUnitSize(y);
		mpz_class c = x * mcl::gmp::getUnit(y, 0);
//z=c&((mpz_class(1) << (64*11))-1); return;
		Unit q = mcl::gmp::getUnit(c, 0) * rp_;
		c += p_ * q;
		c >>= sizeof(Unit) * 8;
		for (size_t i = 1; i < pn_; i++) {
			if (i < ySize) {
				c += x * mcl::gmp::getUnit(y, i);
			}
			Unit q = mcl::gmp::getUnit(c, 0) * rp_;
			c += p_ * q;
			c >>= sizeof(Unit) * 8;
		}
		if (c >= p_) {
			c -= p_;
		}
		z = c;
#else
		z = x * y;
		for (size_t i = 0; i < pn_; i++) {
			Unit q = mcl::gmp::getUnit(z, 0) * rp_;
#ifdef MCL_USE_VINT
			z += p_ * q;
#else
			mpz_class t;
			mcl::gmp::set(t, q);
			z += p_ * t;
#endif
			z >>= sizeof(Unit) * 8;
		}
		if (z >= p_) {
			z -= p_;
		}
#endif
	}
	void mod(mpz_class& z, const mpz_class& xy) const
	{
		z = xy;
		for (size_t i = 0; i < pn_; i++) {
//printf("i=%zd\n", i);
//std::cout << "z=" << std::hex << z << std::endl;
			Unit q = mcl::gmp::getUnit(z, 0) * rp_;
//std::cout << "q=" << q << std::endl;
			mpz_class t;
			mcl::gmp::set(t, q);
			z += p_ * t;
			z >>= sizeof(Unit) * 8;
//std::cout << "z=" << std::hex << z << std::endl;
		}
		if (z >= p_) {
			z -= p_;
		}
//std::cout << "z=" << std::hex << z << std::endl;
	}
};

template<int N>
void mulPreTest()
{
	cybozu::XorShift rg;
	uint64_t x[N], y[N], xy1[N * 2], xy2[N * 2];
	for (int i = 0; i < N; i++) {
		x[i] = rg.get64();
		y[i] = rg.get64();
	}
	mcl_mulPre(xy1, x, y);
	gmp_mulPre<N>(xy2, x, y);
	CYBOZU_TEST_EQUAL_ARRAY(xy1, xy2, N * 2);
	CYBOZU_BENCH_C("mcl_mulPre", C, mcl_mulPre, xy1, x, y);
	CYBOZU_BENCH_C("gmp", C, gmp_mulPre<N>, xy2, x, y);
}

template<int N>
void montTest(const uint64_t *pp, const Montgomery& mont)
{
	uint64_t xa[N], ya[N], xy1a[N], xy2a[N + 1];
	cybozu::XorShift rg;
	for (int i = 0; i < N; i++) {
		xa[i] = rg.get64();
		ya[i] = rg.get64();
	}

	mpz_class x, y, z;
	mcl::gmp::setArray(x, xa, N);
	mcl::gmp::setArray(y, ya, N);

	mont.mul(z, x, y);
	mcl::gmp::getArray(xy1a, N, z);
	const uint64_t dummy = 0x1234567890abc;
	xy2a[N] = dummy;
	mcl_mont(xy2a, xa, ya);
	CYBOZU_TEST_EQUAL_ARRAY(xy1a, xy2a, N);

	mcl::fp::Mont<N, false>::func(xy1a, xa, ya, pp + 1);
	CYBOZU_TEST_EQUAL_ARRAY(xy1a, xy2a, N);

	for (int i = 0; i < 100; i++) {
		xa[0]++;
		mcl::fp::Mont<N, false>::func(xy1a, xa, ya, pp + 1);
		mcl_mont(xy2a, xa, ya);
		CYBOZU_TEST_EQUAL_ARRAY(xy1a, xy2a, N);

		mcl::fp::Mont<N, false>::func(xy1a, xa, xa, pp + 1);
		mcl_mont(xy2a, xa, xa);
		CYBOZU_TEST_EQUAL_ARRAY(xy1a, xy2a, N);
	}
	CYBOZU_TEST_EQUAL(xy2a[N], dummy);

	CYBOZU_BENCH_C("mcl_mont", C, mcl_mont, xy1a, xa, ya);
//	CYBOZU_BENCH_C("gmp", C, (mcl::fp::Mont<N, false>::func), xy2a, xa, ya, pp + 1);
}

template<int N>
void modTest(const mpz_class& p, const uint64_t *pp, const Montgomery& mont)
{
	uint64_t xya[N * 2], z1a[N], z2a[N + 1];
	cybozu::XorShift rg;
	for (int i = 0; i < N * 2; i++) {
		xya[i] = rg.get64();
	}

	mpz_class p2 = p * p;

	mpz_class xy, z;
	mcl::gmp::setArray(xy, xya, N * 2);
	xy %= p2;
	mcl::gmp::getArray(xya, N * 2, xy);

	mont.mod(z, xy);
	mcl::gmp::getArray(z1a, N, z);
	const uint64_t dummy = 0x1234567890abc;
	z2a[N] = dummy;
	mcl_mod(z2a, xya);
	CYBOZU_TEST_EQUAL_ARRAY(z1a, z2a, N);

	mcl::fp::MontRed<N, false>::func(z1a, xya, pp + 1);
	CYBOZU_TEST_EQUAL_ARRAY(z1a, z2a, N);

	for (int i = 0; i < 100; i++) {
		xya[0]++;
		mcl::fp::MontRed<N, false>::func(z1a, xya, pp + 1);
		mcl_mod(z2a, xya);
		CYBOZU_TEST_EQUAL_ARRAY(z1a, z2a, N);
	}
	CYBOZU_TEST_EQUAL(z2a[N], dummy);

	CYBOZU_BENCH_C("mcl_mod", C, mcl_mod, z2a, xya);
//	CYBOZU_BENCH_C("gmp", C, (mcl::fp::MontRed<N, false>::func), z1a, xya, pp + 1);
}

template<int N>
void addTest(const uint64_t *pp)
{
	uint64_t x1[N], x2[N], y[N];
	cybozu::XorShift rg;
	for (int i = 0; i < N; i++) {
		x1[i] = rg.get64();
		x2[i] = x1[i];
		y[i] = rg.get64();
	}

	for (int i = 0; i < 100; i++) {
		mcl::fp::Add<N, false>::func(x1, x1, y, pp + 1);
		mcl_add(x2, x2, y);
		CYBOZU_TEST_EQUAL_ARRAY(x1, x2, N);
	}
	CYBOZU_BENCH_C("mcl_add", C, mcl_add, x1, x1, y);
}

template<int N>
void subTest(const uint64_t *pp)
{
	uint64_t x1[N], x2[N], y[N];
	cybozu::XorShift rg;
	for (int i = 0; i < N; i++) {
		x1[i] = rg.get64();
		x2[i] = x1[i];
		y[i] = rg.get64();
	}

	for (int i = 0; i < 100; i++) {
		mcl::fp::Sub<N, false>::func(x1, x1, y, pp + 1);
		mcl_sub(x2, x2, y);
		CYBOZU_TEST_EQUAL_ARRAY(x1, x2, N);
	}
	CYBOZU_BENCH_C("mcl_sub", C, mcl_sub, x1, x1, y);
}

template<int N>
void negTest(const uint64_t *pp)
{
	uint64_t y1[N], y2[N], x[N];
	cybozu::XorShift rg;

	for (int i = 0; i < 100; i++) {
		for (int i = 0; i < N; i++) {
			x[i] = rg.get64();
		}
		mcl::fp::Neg<N>::func(y1, x, pp + 1);
		mcl_neg(y2, x);
		CYBOZU_TEST_EQUAL_ARRAY(y1, y2, N);
	}
	CYBOZU_BENCH_C("mcl_neg", C, mcl_neg, y2, y2);
	memset(x, 0, sizeof(x));
	mcl_neg(y2, x);
	CYBOZU_TEST_EQUAL_ARRAY(x, y2, N);
}

template<int N>
void addDblTest(const uint64_t *pp)
{
	uint64_t x1[N * 2], x2[N * 2], y[N * 2];
	cybozu::XorShift rg;
	for (int i = 0; i < N * 2; i++) {
		x1[i] = rg.get64();
		x2[i] = x1[i];
		y[i] = rg.get64();
	}
	for (int i = 0; i < 100; i++) {
		mcl::fp::DblAdd<N>::func(x1, x1, y, pp + 1);
		mcl_addDbl(x2, x2, y);
		CYBOZU_TEST_EQUAL_ARRAY(x1, x2, N * 2);
	}
	CYBOZU_BENCH_C("mcl_addDbl", C, mcl_addDbl, x1, x1, y);
}

template<int N>
void subDblTest(const uint64_t *pp)
{
	uint64_t x1[N * 2], x2[N * 2], y[N * 2];
	cybozu::XorShift rg;
	for (int i = 0; i < N * 2; i++) {
		x1[i] = rg.get64();
		x2[i] = x1[i];
		y[i] = rg.get64();
	}

	for (int i = 0; i < 100; i++) {
		mcl::fp::DblSub<N>::func(x1, x1, y, pp + 1);
		mcl_subDbl(x2, x2, y);
		CYBOZU_TEST_EQUAL_ARRAY(x1, x2, N * 2);
	}
	CYBOZU_BENCH_C("mcl_subDbl", C, mcl_subDbl, x1, x1, y);
}

template<int N>
void testAll(const char *pStr)
{
	printf("test N=%d\n", N);
	mcl_init(pStr);
	mpz_class p(pStr);
	uint64_t pp[N + 1];
	Montgomery mont(p);
	mcl::gmp::getArray(pp + 1, N, p);
	pp[0] = mont.rp_;
	mulPreTest<N>();
	montTest<N>(pp, mont);
	modTest<N>(p, pp, mont);
	addTest<N>(pp);
	subTest<N>(pp);
	negTest<N>(pp);
	addDblTest<N>(pp);
	subDblTest<N>(pp);
}

CYBOZU_TEST_AUTO(N11)
{
	const char *pStr = "0x9401ff90f28bffb0c610fb10bf9e0fefd59211629a7991563c5e468d43ec9cfe1549fd59c20ab5b9a7cda7f27a0067b8303eeb4b31555cf4f24050ed155555cd7fa7a5f8aaaaaaad47ede1a6aaaaaaaab69e6dcb";
	testAll<11>(pStr);
}

CYBOZU_TEST_AUTO(N9)
{
	const char *pStr = "0xbb9dfd549299f1c803ddd5d7c05e7cc0373d9b1ac15b47aa5aa84626f33e58fe66943943049031ae4ca1d2719b3a84fa363bcd2539a5cd02c6f4b6b645a58c1085e14411";
	testAll<9>(pStr);
}
