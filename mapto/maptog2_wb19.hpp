#pragma once
/**
	@file
	@brief map to G2 on BLS12-381
	@author MITSUNARI Shigeo(@herumi)
	@license modified new BSD license
	http://opensource.org/licenses/BSD-3-Clause
	ref. https://eprint.iacr.org/2019/403 , https://github.com/kwantam/bls12-381_hash
*/

// clear_h2 == mulByCofactorBLS12fast
struct MapToG2_WB19 {
	Fp2 xi;
	Fp2 Ell2p_a;
	Fp2 Ell2p_b;
	Fp half;
	mpz_class sqrtConst; // (p^2 - 9) / 16
	Fp2 root4[4];
	Fp2 etas[4];
	Fp2 xnum[4];
	Fp2 xden[3];
	Fp2 ynum[4];
	Fp2 yden[4];
	struct Point {
		Fp2 x, y, z;
	};
	// P is on y^2 = x^3 + Ell2p_a x + Ell2p_b
	bool isValidPoint(const Point& P) const
	{
        Fp2 y2, x2, z2, z4, t;
        Fp2::sqr(x2, P.x);
        Fp2::sqr(y2, P.y);
        Fp2::sqr(z2, P.z);
        Fp2::sqr(z4, z2);
        Fp2::mul(t, z4, Ell2p_a);
        t += x2;
        t *= P.x;
        z4 *= z2;
        z4 *= Ell2p_b;
        t += z4;
        return y2 == t;
	}
	void init()
	{
		bool b;
		xi.a = -2;
		xi.b = -1;
		Ell2p_a.a = 0;
		Ell2p_a.b = 240;
		Ell2p_b.a = 1012;
		Ell2p_b.b = 1012;
		half = -1;
		half /= 2;
		sqrtConst = Fp::getOp().mp;
		sqrtConst *= sqrtConst;
		sqrtConst -= 9;
		sqrtConst /= 16;
		const char *rv1Str = "0x6af0e0437ff400b6831e36d6bd17ffe48395dabc2d3435e77f76e17009241c5ee67992f72ec05f4c81084fbede3cc09";
		root4[0].a = 1;
		root4[0].b.clear();
		root4[1].a.clear();
		root4[1].b = 1;
		root4[2].a.setStr(&b, rv1Str);
		assert(b); (void)b;
		root4[2].b = root4[2].a;
		root4[3].a = root4[2].a;
		Fp::neg(root4[3].b, root4[3].a);
		const char *ev1Str = "0x699be3b8c6870965e5bf892ad5d2cc7b0e85a117402dfd83b7f4a947e02d978498255a2aaec0ac627b5afbdf1bf1c90";
		const char *ev2Str = "0x8157cd83046453f5dd0972b6e3949e4288020b5b8a9cc99ca07e27089a2ce2436d965026adad3ef7baba37f2183e9b5";
		const char *ev3Str = "0xab1c2ffdd6c253ca155231eb3e71ba044fd562f6f72bc5bad5ec46a0b7a3b0247cf08ce6c6317f40edbc653a72dee17";
		const char *ev4Str = "0xaa404866706722864480885d68ad0ccac1967c7544b447873cc37e0181271e006df72162a3d3e0287bf597fbf7f8fc1";
		Fp& ev1 = etas[0].a;
		Fp& ev2 = etas[0].b;
		Fp& ev3 = etas[2].a;
		Fp& ev4 = etas[2].b;
		ev1.setStr(&b, ev1Str);
		assert(b); (void)b;
		ev2.setStr(&b, ev2Str);
		assert(b); (void)b;
		Fp::neg(etas[1].a, ev2);
		etas[1].b = ev1;
		ev3.setStr(&b, ev3Str);
		assert(b); (void)b;
		ev4.setStr(&b, ev4Str);
		assert(b); (void)b;
		Fp::neg(etas[3].a, ev4);
		etas[3].b = ev3;
		init_iso();
	}
	void init_iso()
	{
		const char *tbl[] = {
			"0x5c759507e8e333ebb5b7a9a47d7ed8532c52d39fd3a042a88b58423c50ae15d5c2638e343d9c71c6238aaaaaaaa97d6",
			"0x11560bf17baa99bc32126fced787c88f984f87adf7ae0c7f9a208c6b4f20a4181472aaa9cb8d555526a9ffffffffc71a",
			"0x11560bf17baa99bc32126fced787c88f984f87adf7ae0c7f9a208c6b4f20a4181472aaa9cb8d555526a9ffffffffc71e",
			"0x8ab05f8bdd54cde190937e76bc3e447cc27c3d6fbd7063fcd104635a790520c0a395554e5c6aaaa9354ffffffffe38d",
			"0x171d6541fa38ccfaed6dea691f5fb614cb14b4e7f4e810aa22d6108f142b85757098e38d0f671c7188e2aaaaaaaa5ed1",
			"0x1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffaa63",
			"0x1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffaa9f",
			"0x1530477c7ab4113b59a4c18b076d11930f7da5d4a07f649bf54439d87d27e500fc8c25ebf8c92f6812cfc71c71c6d706",
			"0x5c759507e8e333ebb5b7a9a47d7ed8532c52d39fd3a042a88b58423c50ae15d5c2638e343d9c71c6238aaaaaaaa97be",
			"0x11560bf17baa99bc32126fced787c88f984f87adf7ae0c7f9a208c6b4f20a4181472aaa9cb8d555526a9ffffffffc71c",
			"0x8ab05f8bdd54cde190937e76bc3e447cc27c3d6fbd7063fcd104635a790520c0a395554e5c6aaaa9354ffffffffe38f",
			"0x124c9ad43b6cf79bfbf7043de3811ad0761b0f37a1e26286b0e977c69aa274524e79097a56dc4bd9e1b371c71c718b10",
			"0x1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffa8fb",
			"0x1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffa9d3",
			"0x1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffaa99",
		};
		bool b;
		xnum[0].a.setStr(&b, tbl[0]); assert(b); (void)b;
		xnum[0].b = xnum[0].a;
		xnum[1].a.clear();
		xnum[1].b.setStr(&b, tbl[1]); assert(b); (void)b;
		xnum[2].a.setStr(&b, tbl[2]); assert(b); (void)b;
		xnum[2].b.setStr(&b, tbl[3]); assert(b); (void)b;
		xnum[3].a.setStr(&b, tbl[4]); assert(b); (void)b;
		xnum[3].b.clear();
		xden[0].a.clear();
		xden[0].b.setStr(&b, tbl[5]); assert(b); (void)b;
		xden[1].a = 0xc;
		xden[1].b.setStr(&b, tbl[6]); assert(b); (void)b;
		xden[2].a = 1;
		xden[2].b = 0;
		ynum[0].a.setStr(&b, tbl[7]); assert(b); (void)b;
		ynum[0].b = ynum[0].a;
		ynum[1].a.clear();
		ynum[1].b.setStr(&b, tbl[8]); assert(b); (void)b;
		ynum[2].a.setStr(&b, tbl[9]); assert(b); (void)b;
		ynum[2].b.setStr(&b, tbl[10]); assert(b); (void)b;
		ynum[3].a.setStr(&b, tbl[11]); assert(b); (void)b;
		ynum[3].b.clear();
		yden[0].a.setStr(&b, tbl[12]); assert(b); (void)b;
		yden[0].b = yden[0].a;
		yden[1].a.clear();
		yden[1].b.setStr(&b, tbl[13]); assert(b); (void)b;
		yden[2].a = 0x12;
		yden[2].b.setStr(&b, tbl[14]); assert(b); (void)b;
		yden[3].a = 1;
		yden[3].b.clear();
	}
	// refer (xnum, xden, ynum, yden)
	void iso3(G2& Q, const Point& P) const
	{
		Fp2 zpows[4];
		zpows[0] = 1;
		Fp2::sqr(zpows[1], P.z);
		Fp2::sqr(zpows[2], zpows[1]);
		Fp2::mul(zpows[3], zpows[2], zpows[1]);
PUT(zpows[0]);
PUT(zpows[1]);
PUT(zpows[2]);
PUT(zpows[3]);
	}
	/*
		(a+bi)*(-2-i) = (b-2a)-(a+2b)i
	*/
	void mul_xi(Fp2& y, const Fp2& x) const
	{
		Fp t;
		Fp::sub(t, x.b, x.a);
		t -= x.a;
		Fp::add(y.b, x.b, x.b);
		y.b += x.a;
		Fp::neg(y.b, y.b);
		y.a = t;
	}
	bool isNegSign(const Fp2& x) const
	{
		if (x.b > half) return true;
		if (!x.b.isZero()) return false;
		if (x.a > half) return true;
		if (!x.b.isZero()) return false;
		return false;
	}
	void osswu2_help(Point& P, const Fp2& t) const
	{
		Fp2 t2, t2xi;
		Fp2::sqr(t2, t);
		Fp2 den, den2;
//		Fp2::mul(t2xi, t2, xi);
		mul_xi(t2xi, t2);
		den = t2xi;
		Fp2::sqr(den2, den);
		// (t^2 * xi)^2 + (t^2 * xi)
		den += den2;
		Fp2 x0_num, x0_den;
		Fp2::add(x0_num, den, 1);
		x0_num *= Ell2p_b;
		if (den.isZero()) {
			Fp2::mul(x0_den, Ell2p_a, xi);
		} else {
			Fp2::mul(x0_den, -Ell2p_a, den);
		}
		Fp2 x0_den2, x0_den3, gx0_den, gx0_num;
		Fp2::sqr(x0_den2, x0_den);
		Fp2::mul(x0_den3, x0_den2, x0_den);
		gx0_den = x0_den3;

		Fp2::mul(gx0_num, Ell2p_b, gx0_den);
		Fp2 tmp, tmp1, tmp2;
		Fp2::mul(tmp, Ell2p_a, x0_num);
		tmp *= x0_den2;
		gx0_num += tmp;
		Fp2::sqr(tmp, x0_num);
		tmp *= x0_num;
		gx0_num += tmp;

		Fp2::sqr(tmp1, gx0_den); // x^2
		Fp2::sqr(tmp2, tmp1); // x^4
		tmp1 *= tmp2;
		tmp1 *= gx0_den; // x^7
		Fp2::mul(tmp2, gx0_num, tmp1);
		tmp1 *= tmp2;
		tmp1 *= gx0_den;
		Fp2 candi;
		Fp2::pow(candi, tmp1, sqrtConst);
		candi *= tmp2;
		bool isNegT = isNegSign(t);
		for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(root4); i++) {
			Fp2::mul(P.y, candi, root4[i]);
			Fp2::sqr(tmp, P.y);
			tmp *= gx0_den;
			if (tmp == gx0_num) {
				if (isNegSign(P.y) != isNegT) {
					Fp2::neg(P.y, P.y);
				}
				Fp2::mul(P.x, x0_num, x0_den);
				P.y *= x0_den3;
				P.z = x0_den;
				return;
			}
		}
		Fp2 x1_num, x1_den, gx1_num, gx1_den;
		Fp2::mul(x1_num, t2xi, x0_num);
		x1_den = x0_den;
		Fp2::mul(gx1_num, den2, t2xi);
		gx1_num *= gx0_num;
		gx1_den = gx0_den;
		candi *= t2;
		candi *= t;
		for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(etas); i++) {
			Fp2::mul(P.y, candi, etas[i]);
			Fp2::sqr(tmp, P.y);
			tmp *= gx1_den;
			if (tmp == gx1_num) {
				if (isNegSign(P.y) != isNegT) {
					Fp2::neg(P.y, P.y);
				}
				Fp2::mul(P.x, x1_num, x1_den);
				Fp2::sqr(tmp, x1_den);
				P.y *= tmp;
				P.y *= x1_den;
				P.z = x1_den;
				return;
			}
		}
		assert(0);
	}
#if 0
	void opt_swu2_map(G2& P, const Fp2& t, const Fp2 *t2 = 0) const
	{
		Point Pp;
		osswu2_help(Pp, t);
		if (t2) {
			G2 P2;
			osswu2_help(P2, *t2);
			P += P2;
		}
		iso3(P, P);
	}
#endif
};

