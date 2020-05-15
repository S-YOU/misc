#pragma once
/**
	@author herumi
	@note modified new BSD license
	http://opensource.org/licenses/BSD-3-Clause
*/
#include <xbyak_aarch64/xbyak_aarch64.h>
#include <cmath>

namespace fmath {

namespace local {

union fi {
	float f;
	uint32_t i;
};

inline float cvt(uint32_t x)
{
	fi fi;
	fi.i = x;
	return fi.f;
}

struct ConstVar {
	static const size_t expN = 5;
	static const size_t logN = 9;
	float expMin; // exp(expMin) = 0
	float expMax; // exp(expMax) = inf
	float log2; // log(2)
	float log2_e; // log_2(e) = 1 / log2
	float expCoeff[expN]; // near to 1/(i + 1)!
	//
	float log1p5; // log(1.5)
	float f2div3; // 2/3
	float logCoeff[logN];
	void init()
	{
		expMin = cvt(0xc2aeac50);
		expMax = cvt(0x42b17218);
		log2 = std::log(2.0f);
		log2_e = 1.0f / log2;
		log1p5 = std::log(1.5f);
		f2div3 = 2.0f/3;
#if 0
		// maxe=4.888831e-06
		float z = 1;
		for (size_t i = 0; i < expN; i++) {
			expCoeff[i] = z;
			z /= (i + 2);
		}
#else
		// maxe=1.938668e-06
		const uint32_t expTbl[expN] = {
			0x3f800000,
			0x3effff12,
			0x3e2aaa56,
			0x3d2b89cc,
			0x3c091331,
		};
		for (size_t i = 0; i < expN; i++) {
			expCoeff[i] = cvt(expTbl[i]);
		}
#endif
		const float logTbl[logN] = {
			 1.0, // must be 1
			-0.49999985195974875681242,
			 0.33333220526061677705782,
			-0.25004206220486390058000,
			 0.20010985747510067100077,
			-0.16481566812093889672203,
			 0.13988269735629330763020,
			-0.15049504706005165294002,
			 0.14095711402233803479921,
		};
		for (size_t i = 0; i < logN; i++) {
			logCoeff[i] = logTbl[i];
		}
	}
};

/*
The constans expCoeff are generated by Maple.
f := x->A+B*x+C*x^2+D*x^3+E*x^4+F*x^5;
g:=int((f(x)-exp(x))^2,x=-L..L);
sols:=solve({diff(g,A)=0,diff(g,B)=0,diff(g,C)=0,diff(g,D)=0,diff(g,E)=0,diff(g,F)=0},{A,B,C,D,E,F});
Digits:=1000;
s:=eval(sols,L=log(2)/2);
evalf(s,20);
*/
struct Code : public Xbyak::CodeGenerator {
	typedef Xbyak::ZReg ZReg;
	ConstVar *constVar;
	typedef void (*VecFunc)(float *dst, const float *src, size_t n);
	VecFunc expf_v;
//	VecFunc logf_v;
	Code()
		: Xbyak::CodeGenerator(4096 * 2)
		, expf_v(0)
//		, logf_v(0)
	{
		size_t dataSize = sizeof(ConstVar);
		dataSize = (dataSize + 4095) & ~size_t(4095);
		Xbyak::Label constVarL = L();
		constVar = (ConstVar*)getCode();
		constVar->init();
		setSize(dataSize / 4);
		expf_v = getCurr<VecFunc>();
		genExpAVX512(constVarL);
#if 0
		align(16);
		logf_v = getCurr<VecFunc>();
		genLogAVX512(constVarL);
#endif
		ready();
	}
#if 1
	// zm0 = exp(zm0)
	// use zm0, zm1, zm2
	void genExpOneSVE(const ZReg& i127, const ZReg& expMin, const ZReg& expMax, const ZReg& log2, const ZReg& log2_e, const ZReg expCoeff[5])
	{
		fmin(z0.s, p0, expMax.s);
		fmax(z0.s, p0, expMin.s);
		fmul(z0.s, z0.s, log2_e.s);
		frintn(z0.s, p0, z0.s); // (float)round()
//		scvtf(z0.s, p0, z1.s);

#if 0
		// a little faster if we can assume nearest round mode
		vcvtps2dq(zm1, zm0);
		vcvtdq2ps(zm2, zm1);
		vsubps(zm0, zm2);
		vmulps(zm0, log2);
		vpaddd(zm1, zm1, i127);
		vpslld(zm1, zm1, 23); // fi.f
		vmovaps(zm2, expCoeff[4]);
		vfmadd213ps(zm2, zm0, expCoeff[3]);
		vfmadd213ps(zm2, zm0, expCoeff[2]);
		vfmadd213ps(zm2, zm0, expCoeff[1]);
		vfmadd213ps(zm2, zm0, expCoeff[0]);
		vfmadd213ps(zm2, zm0, expCoeff[0]);
		vmulps(zm0, zm2, zm1);
#endif
	}
#endif
	// exp_v(float *dst, const float *src, size_t n);
	void genExpAVX512(const Xbyak::Label& constVarL)
	{
		using namespace Xbyak;
		const XReg& dst = x0;
		const XReg& src = x1;
		const XReg& n = x2;

		// setup constant
		const ZReg& i127 = z3;
		const ZReg& expMin = z4;
		const ZReg& expMax = z5;
		const ZReg& log2 = z6;
		const ZReg& log2_e = z7;
		const ZReg expCoeff[] = { z8, z9, z10, z11, z12 };

		adr(x3, constVarL);
		ptrue(p0.s);
		cpy(z0.s, p0, 127);
		ldr(w4, ptr(x3, (uint32_t)offsetof(ConstVar, expMin)));
		cpy(expMin.s, p0/T_z, w4);
		ldr(w4, ptr(x3, (uint32_t)offsetof(ConstVar, expMax)));
		cpy(expMax.s, p0/T_z, w4);
		ldr(w4, ptr(x3, (uint32_t)offsetof(ConstVar, log2)));
		cpy(log2.s, p0/T_z, w4);
		ldr(w4, ptr(x3, (uint32_t)offsetof(ConstVar, log2_e)));
		cpy(log2_e.s, p0/T_z, w4);
		for (size_t i = 0; i < ConstVar::expN; i++) {
			ldr(w4, ptr(x3, uint32_t(offsetof(ConstVar, expCoeff[0]) + sizeof(float) * i)));
			cpy(expCoeff[i].s, p0/T_z, w4);
		}
		ld1w(z0.s, p0/T_z, ptr(src));
		genExpOneSVE(i127, expMin, expMax, log2, log2_e, expCoeff);

		st1w(z0.s, p0/T_z, ptr(dst));
#if 0

		// main loop
		Label mod16, exit;
		mov(ecx, n);
		and_(n, ~15);
		jz(mod16);
	Label lp = L();
		vmovups(zm0, ptr[src]);
		add(src, 64);
		genExpOneAVX512(i127, expMin, expMax, log2, log2_e, expCoeff);
		vmovups(ptr[dst], zm0);
		add(dst, 64);
		sub(n, 16);
		jnz(lp);
	L(mod16);
		and_(ecx, 15);
		jz(exit);
		mov(eax, 1);
		shl(eax, cl);
		sub(eax, 1);
		kmovd(k1, eax);
		vmovups(zm0|k1|T_z, ptr[src]);
		genExpOneAVX512(i127, expMin, expMax, log2, log2_e, expCoeff);
		vmovups(ptr[dst]|k1, zm0|k1);
	L(exit);
#endif
		ret();
	}
#if 0
	// zm0 = log(zm0)
	// use zm0, zm1, zm2
	void genLogOneAVX512(const Zmm& i127shl23, const Zmm& x7fffff, const Zmm& log2, const Zmm& log1p5, const Zmm& f2div3, const Zmm *logCoeff)
	{
		vpsubd(zm1, zm0, i127shl23);
		vpsrad(zm1, zm1, 23); // e
		vcvtdq2ps(zm1, zm1); // float(e)
		vpandd(zm0, zm0, x7fffff);
		vpord(zm0, zm0, i127shl23); // y

		vfmsub213ps(zm0, f2div3, logCoeff[0]); // a
		vfmadd213ps(zm1, log2, log1p5); // e

		int logN = ConstVar::logN;
		vmovaps(zm2, logCoeff[logN - 1]);
		for (int i = logN - 2; i >= 0; i--) {
			vfmadd213ps(zm2, zm0, logCoeff[i]);
		}
		vfmadd213ps(zm0, zm2, zm1);
	}
	// log_v(float *dst, const float *src, size_t n);
	void genLogAVX512(const Xbyak::Label& constVarL)
	{
		const int keepRegN = 11;
		using namespace Xbyak;
		util::StackFrame sf(this, 3, util::UseRCX, 64 * keepRegN);
		const Reg64& dst = sf.p[0];
		const Reg64& src = sf.p[1];
		const Reg64& n = sf.p[2];

		// prolog
#ifdef XBYAK64_WIN
		vmovups(ptr[rsp + 64 * 0], zm6);
		vmovups(ptr[rsp + 64 * 1], zm7);
#endif
		for (int i = 2; i < keepRegN; i++) {
			vmovups(ptr[rsp + 64 * i], Zmm(i + 6));
		}

		// setup constant
		const Zmm& i127shl23 = zmm3;
		const Zmm& x7fffff = zmm4;
		const Zmm& log2 = zmm5;
		const Zmm& log1p5 = zmm6;
		const Zmm& f2div3 = zmm7;
		const Zmm logCoeff[ConstVar::logN] = {
			zm8, zm9, zm10, zm11, zm12, zm13, zm14, zm15, zm16
		};
		mov(eax, 127 << 23);
		vpbroadcastd(i127shl23, eax);
		mov(eax, 0x7fffff);
		vpbroadcastd(x7fffff, eax);

		lea(rax, ptr[rip+constVarL]);
		vbroadcastss(log2, ptr[rax + offsetof(ConstVar, log2)]);
		vbroadcastss(log1p5, ptr[rax + offsetof(ConstVar, log1p5)]);
		vbroadcastss(f2div3, ptr[rax + offsetof(ConstVar, f2div3)]);
		for (size_t i = 0; i < ConstVar::logN; i++) {
			vbroadcastss(logCoeff[i], ptr[rax + offsetof(ConstVar, logCoeff[0]) + sizeof(float) * i]);
		}

		// main loop
		Label mod16, exit;
		mov(ecx, n);
		and_(n, ~15);
		jz(mod16, T_NEAR);
	Label lp = L();
		vmovups(zm0, ptr[src]);
		add(src, 64);
		genLogOneAVX512(i127shl23, x7fffff, log2, log1p5, f2div3, logCoeff);
		vmovups(ptr[dst], zm0);

		add(dst, 64);
		sub(n, 16);
		jnz(lp);
	L(mod16);
		and_(ecx, 15);
		jz(exit, T_NEAR);
		mov(eax, 1);
		shl(eax, cl);
		sub(eax, 1);
		kmovd(k1, eax);
		vmovups(zm0|k1|T_z, ptr[src]);
		genLogOneAVX512(i127shl23, x7fffff, log2, log1p5, f2div3, logCoeff);
		vmovups(ptr[dst]|k1, zm0|k1);
	L(exit);

		// epilog
#ifdef XBYAK64_WIN
		vmovups(zm6, ptr[rsp + 64 * 0]);
		vmovups(zm7, ptr[rsp + 64 * 1]);
#endif
		for (int i = 2; i < keepRegN; i++) {
			vmovups(Zmm(i + 6), ptr[rsp + 64 * i]);
		}
	}
#endif
};

template<size_t dummy = 0>
struct Inst {
	static const Code code;
};

template<size_t dummy>
alignas(32) const Code Inst<dummy>::code;

} // fmath::local

inline void expf_v(float *dst, const float *src, size_t n)
{
	local::Inst<>::code.expf_v(dst, src, n);
}

#if 0
inline void logf_v(float *dst, const float *src, size_t n)
{
	local::Inst<>::code.logf_v(dst, src, n);
}
#endif

} // fmath2
