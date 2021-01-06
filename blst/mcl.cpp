//#define MCL_DONT_USE_XBYAK
//#define MCL_MAX_BIT_SIZE 384
#define MCL_USE_VINT
#define CYBOZU_DONT_USE_OPENSSL
#define PUT(x) std::cout << #x "=" << x << std::endl;
#include <cybozu/benchmark.hpp>
cybozu::CpuClock clk;
#include <mcl/bls12_381.hpp>
#include <cybozu/xorshift.hpp>

using namespace mcl::bn;

int main()
	try
{
	initPairing(mcl::BLS12_381);
	G1 P;
	G2 Q;
puts("P");
	P.setStr(
	"1 3685416753713387016781088315183077757961620795782546409894578378688607592378376318836054947676345821548104185464507"
	" 1339506544944476473020471379941921221584933875938349620426543736416511423956333506472724655353366534992391756441569",
	10);
puts("Q");
	Q.setStr(
	"1 352701069587466618187139116011060144890029952792775240219908644239793785735715026873347600343865175952761926303160"
	" 3059144344244213709971259814753781636986470325476647558659373206291635324768958432433509563104347017837885763365758"
	" 1985150602287291935568054521177171638300868978215655730859378665066344726373823718423869104263333984641494340347905"
	" 927553665492332455747201965776037880757740193453592970025027978793976877002675564980949289727957565575433344219582",
	10);

	printf("P=%s\n", P.getStr(16).c_str());
	printf("Q=%s\n", Q.getStr(16).c_str());
	GT e;
	millerLoop(e, P, Q);
	finalExp(e, e);
	printf("e\n%s\n", e.getStr(16).c_str());
	CYBOZU_BENCH_C("pairing", 1000, pairing, e, P, Q);
	CYBOZU_BENCH_C("ML", 1000, millerLoop, e, P, Q);
	CYBOZU_BENCH_C("FE", 1000, finalExp, e, e);
	{
		Fp a = e.a.a.a;
		Fp b = e.a.a.b;
		CYBOZU_BENCH_C("fp::mul", 10000, Fp::mul, a, a, b);
	}
	{
		Fp2 a = e.a.a;
		Fp2 b = e.a.b;
		CYBOZU_BENCH_C("fp2::mul", 10000, Fp2::mul, a, a, b);
		CYBOZU_BENCH_C("fp2::sqr", 10000, Fp2::sqr, a, a);
	}
} catch (std::exception& e) {
	printf("ERR %s\n", e.what());
	return 1;
}