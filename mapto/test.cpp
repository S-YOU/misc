#include <cybozu/test.hpp>
#include <mcl/bls12_381.hpp>
#include <iostream>
#include <fstream>

using namespace mcl;
using namespace mcl::bn;

#define PUT(x) std::cout << #x "=" << (x) << std::endl;

template<class T>
void testSign(const T& mapto)
{
	const Fp& H = mapto.half;
	const size_t N = 4;
	const Fp tbl[N] = { 0, 1, H, H + 1 };
	const int expect[N][N] = {
		{  1, 1, 1, -1 },
		{  1, 1, 1, -1 },
		{  1, 1, 1, -1 },
		{ -1, 1, 1, -1 },
	};
	Fp2 t;
	for (size_t i = 0; i < N; i++) {
		t.a = tbl[i];
		for (size_t j = 0; j < N; j++) {
			t.b = tbl[j];
			if (mapto.isNegSign(t) != (expect[i][j] < 0)) {
				printf("err %zd %zd\n", i, j);
			}
		}
	}
	puts("ok");
}

template<class T>
void helpTest(const T& mapto)
{
	const struct {
		const char *ta;
		const char *tb;
		const char *xa;
		const char *xb;
		const char *ya;
		const char *yb;
		const char *za;
		const char *zb;
	} tbl[] = {
		{
			"0xe54bc0f2e26071a79ba5fe7ae5307d39cf5519e581e03b43f39a431eccc258fa1477c517b1268b22986601ee5caa5ea",
			"0x17e8397d5e687ff7f915c23f27fe1ca2c397a7df91de8c88dc82d34c9188a3ef719f9f20436ea8a5fe7d509fbc79214d",

			"0x11d568058220b1826cacde2e367beef98ea1edfde5fbf0491231b7ffdfc867e5269f9cfe65347c32ead182ba6b8c3ba1",
			"0x19f2778213e671ac444b1b579bfdf4e7fabeed9626dc909ce243b60397a6b5f65af0fbbe02a43c1e289f28c927012da1",

			"0xfe17bc695a84ec060b6287a4e77a50f65ba8f2c6c433f8131036ddfe34e3071d1cb71c0000f6bcfada947b19d8588df",
			"0xb76abd285945f787721e7e306895149523941586ac44f25a294c406a70ed570020992025aa307777cfe6c590567dfbe",

			"0x1910249ae63241608e013eb13578b9b3d96774d35e5732fc75efd17c212dd310d7f4016d6f212f62f33d34f10252e3e3",
			"0xdcd076cea67c76a6d0594c8f30c8cd8e9ead24f90870f723228f2203a55e04a5517c426ea2c4bae9d37a11c3d0f1912",
		},
		{
			"0x2a8663422cc279aa8591819195a62cfd57357b7bcb6f4a9174275c2e2e754fb23e2f8a444d0d164990dc03dcb95a129",
			"0x15cf611083511955a70fdcc80cb08c6e22b8043a3038065251d4d3f82c6051bac4933e41d589514c42fba13f78f297ef",

			"0x74ee12dce0c9a8836017172b562ebe491273964dd63df71dea6eb778cd9040e8c9a7136e745013c1def93cc57ef0dae",
			"0xedce8fa83a2435a796d207943b14ea4d1a9850e10a6c2035912f1c5bd579e9cabc54027b87a779af28f380cc5edc8a6",

			"0x11367627461d742b4afac12bd789f1437787f2dc675cf2c7896f004ab8480c06cd06589748d8b9791b4969763962f73c",
			"0x101d8e4c1598e72d943dad4695cfa74236d5065345f1e62e62c75ca30cb0c41c3f6197d7c57d46e8cdd07845d77e1e34",

			"0x3952479e45a0826275c1481fbd78a2b4c5076b6a5cd4ad7e132c1ec460dcaef504943e2c6a969ba182e230da3850b4",
			"0x13b8e64e2e233d1dc4506360c3bff93535642c2d3115c53c049e287e35c03212be882f0618cc50557e55b42be53e4893",
		},
	};
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Fp2 t(tbl[i].ta, tbl[i].tb);
		Fp2 x0(tbl[i].xa, tbl[i].xb);
		Fp2 y0(tbl[i].ya, tbl[i].yb);
		Fp2 z0(tbl[i].za, tbl[i].zb);
		typename T::Point P;
		mapto.osswu2_help(P, t);
		CYBOZU_TEST_EQUAL(P.x, x0);
		CYBOZU_TEST_EQUAL(P.y, y0);
		CYBOZU_TEST_EQUAL(P.z, z0);
		CYBOZU_TEST_ASSERT(mapto.isValidPoint(P));
	}
}

struct Fp2Str {
	const char *a;
	const char *b;
};

struct PointStr {
	Fp2Str x;
	Fp2Str y;
	Fp2Str z;
};

void set(Fp2& x, const Fp2Str& s)
{
	x.a.setStr(s.a);
	x.b.setStr(s.b);
}

template<class Point>
void set(Point& P, const PointStr& s)
{
	set(P.x, s.x);
	set(P.y, s.y);
	set(P.z, s.z);
}

template<class T>
void addTest(const T& mapto)
{
	const struct Tbl {
		PointStr P;
		PointStr Q;
		PointStr R;
	} tbl[] = {
		{
			{
				{
					"0x111fe4d895d4a8eb21b87f8717727a638cb3f79b91217ac2b47ea599513a5e9bff14cd85f91e5bef822160e0ad4f6726",
					"0x29180cfc2d6a6c717ad4b93725475117c959496d3163974cc08068c0319cb47ba7c8d49c0ebb1ed1a4659b91acab3f",
				},
				{
					"0x192e14063ab46786058c355387e4141921a2b0fd1bcecd6bbf6e3e25f972b2b88fe23b1fd6b14f8070c7ada0bbcfb8d7",
					"0x153bc38ad032b044e55f649b9b1e6384cfe0936b3be350e16a8cf847790bf718e9099b102fbdab5ad8f0acca6b0ac65a",
				},
				{
					"0x119f8d49f20b7a3ef00527779ef9326250a835a742770e9599b3be1939d5e00f8b329781bea38e725e1b0de76354b2ea",
					"0xd95d36844c2ef0678e3614c0d9698daf7d54cb41322fb6acf90a4fd61122c36213e6f811c81c573385110d98e49136",
				},
			},
			{
				{
					"0x738abc340e315a70a95d22c68e4beb8f8ce8cb17ec4d8104285b5770a63b2e9fdceaffb88df1fde2104d807bd0fb5df",
					"0x19edac9569a018b7a17ddd9554430318500e83e38c798d6f8e0a22e9e54ef2b0ec0cf4866013e3a43237eaf949c4548b",
				},
				{
					"0x12234a4947cf5c0a0fc04edadefa7c3766489d927ad3d7d7236af997b0e0fd7deaaf4ab78aad390c6a8f0088f21256af",
					"0x4a1cddb800e9fc6fb9f12e036bd0dae9a75c276f8007407cb9be46177e4338ac43d00f3dc413cab629d6305327ffbc",
				},
				{
					"0x187212ac7f7d68aa32dafe6c1c52dc0411ea11cffa4c6a10e0ba407c94b8663376f1642379451a09a4c7ce6e691a557f",
					"0x1381999b5cc68ae42d64d71ac99a20fb5874f3883a222a9e15c8211610481642b32b85da288872269480383b62696e5a",
				},
			},
			{
				{
					"0x1027d652690099dd3bea0c8ec2f8686c8db37444b08067a40780a264f2edd995d3a39941a302289ac8025007e7f08e35",
					"0xe4c1e12005a577f2a7487bd0bca91253bfff829258e7120716d70133dfc1c8f4aa80d2b4c076f267f3483ec1ca66cdc",
				},
				{
					"0x16bd53f43f8acfb29d3a451a274445ca87d43f0e1a6550c6107654516fda0b4cd1a346369ef0d44d4ee78904ce1b3e4b",
					"0xf0f67bbce56d7791c676b7af20f0d91382973c6c7b971a920525dbd58b13364ec226651308c8bc56e636d0458d46f50",
				},
				{
					"0x8027cefbfd3e7e7fdc88735eddd7e669520197227bd2a7014078f56489267256fdfb27d080515412d69f86770f3ce",
					"0x2470e1d8896cfe74ab01b68071b97d121333ebcec7a41cddd4581d736a25ba154ac94321a119906e3f41beec971d082",
				},
			},
		},
	};
	typedef typename T::Point Point;
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
		Point P, Q, R;
		set(P, tbl[i].P);
		set(Q, tbl[i].Q);
		set(R, tbl[i].R);
		Point E;
		mapto.add(E, P, Q);
		CYBOZU_TEST_EQUAL(R.x, E.x);
		CYBOZU_TEST_EQUAL(R.y, E.y);
		CYBOZU_TEST_EQUAL(R.z, E.z);
	}
}

template<class T>
void iso3Test(const T& mapto)
{
	const PointStr Ps = {
		{
			"0xf0d9554fa5b04dbc6b106727e987bd68fb8c0cc97226a3845b59cc9d09972f24ea5a0d93cd0eedd18318c0024bf3df0",
			"0x656650d143a2cf4a913821fa6a90ab6baa0bb063d1207b15108ea919258bfa4bdd1ba7247e8e65300d526801e43dca6",
		},
		{
			"0x13a4b7c833b2702dc6ac4f5ee6ee74923a24c28e5a9b8e3b5626f700489ea47f9b1c3aa8cc0f4b525ae56e1e89aba868",
			"0x16c0b9a89dcbe4e375f1e4d064013adff8e6e09866d38769c08ce355fbac9c823d52df971286b091b46d2cd49625c09",
		},
		{
			"0x176ce067d52f676d4f6778eda26f2e2e75f9f39712583e60e2b3f345e2b2a84df1ae9ffa241ce89b1a377e4286c85ccf",
			"0x822bc033cf0eec8bea9037ede74db0a73d932dc9b43f855e1862b747b0e53312dde5ed301e32551a11a5ef2dfe2dbf4",
		}
	};
	const PointStr Qs = {
		{
			"0x8d5483693b4cf3fd5c7a62dad4179503094a66a52f2498dcedb5c97a33697ba4110e2da42ddef98beeeab04619ec0fe",
			"0xd45728bb18737fb6abf8cc94ad37957f95855da867ca718708503fd072d3707ca6059fefb5c52b2745210cdd7991d10",
		},
		{
			"0x17027ae16e10908f87e79c70f96ba44b1b11fa40fb5ac5456162133860f14896ca363b58d81ef8cb068bdaca2e576ed7",
			"0xfb2d1655b00027d5580bbff8afa6eec6e6caacf5df4020c5255eafb51d50710193a8e39eac760745c45cc6ec556a820",
		},
		{
			"0x376b86a7d664dc080485c29a57618eee792396f154806f75c78599ee223103e77bee223037bb99354114201619ea06",
			"0xf0c64e52dbb8e2dca3c790993c8f101012c516b2884db16de4d857ae6bfb85e9101ab15906870b3e5a18268a57bfc99",
		}
	};
	const PointStr clearPs = {
		{
			"0x6f3d4cbd80011d9cbf0f0772502d1e6571d00bc24efc892659339fc8ae049e757c57d22368c33cfc6c64bc2df59b3da",
			"0x71e02679953af97ed57d9301d126c3243de7faa3bbebd40b46af880ba3ba608b8c09c0a876401545ce6f901950f192",
		},
		{
			"0x174d1e92bd85b0cf1dd2808bd96a25ed48ba1e8d15c1af5557f62719e9f425bd8df58c900cf036e57bce1b1c78efb859",
			"0x1cfc358b91d57bf6aa9fa6c688b0ef516fdac0c9bfd9ef310ea11e44aaf778cca99430594a8f5eb37d31c1b1f72c2f6",
		},
		{
			"0x17614e52aacf8804ed2e7509db5b72395e586e2edc92dba02da24e6f73d059226a6deb6e396bd39567cec952f3849a6c",
			"0xb7b36b9b1bbcf801d21ca5164aa9a0e71df2b4710c67dc0cd275b786800935fc29defbdf9c7e23dc84e26af13ba761d",
		}
	};
	typename T::Point P;
	G2 Q1, Q2;
	set(P, Ps);
	set(Q1, Qs);
	mapto.iso3(Q2, P);
	CYBOZU_TEST_EQUAL(Q1, Q2);
	set(Q1, clearPs);
	mapto.clear_h2(Q2, Q2);
	CYBOZU_TEST_EQUAL(Q1, Q2);
}

template<class T>
void opt_swu2_mapTest(const T& mapto)
{
	const Fp2Str t1s = {
		"0xafcfb20d836159f0cfb6f48c0ed808fd97a1cd1b9f1eb14451ff59e3884b1bf7665406cce673d434dde6933bdcf0ec9",
		"0x36714c33fa9c79b0bb9ac963f57b2d2b2659e211893e64292ee2a8c1259b1a834a769782bae17202b537a1fe901c55e",
	};
	const Fp2Str t2s = {
        "0xb9a2f39af0cc3264348ed00845545e2ccbed59ea541c726c8429871f9a0917fb4f7e049ac739065eea8354a2d1b2d21",
		"0xc8810a06deb536d70531352bd2a3aac7496e187a8fc102d800c5f8ed839bd64d7102197aeb2b6164d20ff920ff63afe",
	};
	const PointStr t1t1s = {
		{
			"0x13ea937301cfb2a071a265b08e176854034c2e2ae49898e89c042bff176a1be7bf02dfda06f67d38819ca334218b9ff4",
			"0x180ee537c06213034c842cad3b5a6d0053473e8bb92dd4c5826e59a45268cda3fe28814b1e9f3a58b9db657d9c24a0bd",
		},
		{
			"0x13f4530154b75ce311849e775242b5e791058fd8e1d7df292b8e936e8be05e1cd9fa6eed6280357393d54adf3af0eb9c",
			"0x10619dc087132cf699b02c905284c3449e80c295c8140345e45e21b7389c8f2cf7b5e223ef87f11f57eb1e689f6c141a",
		},
		{
			"0x40f98938abaece4e47427371b3b6c500f9cdacae9d8b4da79ba9107720bd038057a4cc8ec8427d651760fd795d2415",
			"0xac9cd43c4ba29f20ed5dd2aa4a634b39810e756313b4826f225efddfb1ae43185ac4f279e628731030e87405a965bf5",
		},
	};
	const PointStr t1t2s = {
		{
			"0x126b4982298792ed049850bb92b55d26c33a8e3139f9ca1a20821496c7396ce5ad9042b0da529e60ec9c3ff8e983befe",
			"0x11c1d2f6a6a81e1f82dee2278968326e23e6ae469252a51d86673bd8fb333b7bca615b63a068692ff419c5f3e388797b",
		},
		{
			"0x92468e5829b26cc976aff103403b4b5304dd206228c6eb84ecf7b45709307390bf29dced39f9aa037b014ad6fb5a6e4",
			"0x5bd54eef1fdade89c98ab5c27d3dd9e18868af4250ff3a49de71d060ab62b7be039a3b2a8ef0c870d9021f6eae22029",
		},
		{
			"0x154920adb9d857620c2835f4a5445bda35da53411710d559b18430f1b48c7cf2048cc275e0a9e01436d355f76fa0a9ec",
			"0xccc404e5d17aa51f7669402916cf86587ce7cd9c657e90b05d7c8860940f741e62628df420d92c659d159d4b7683cce",
		},
	};
	Fp2 t1, t2;
	set(t1, t1s);
	set(t2, t2s);
	G2 P1, P2;
	set(P1, t1t2s);
	mapto.opt_swu2_map(P2, t1, &t2);
	CYBOZU_TEST_EQUAL(P1, P2);
	set(P1, t1t1s);
	mapto.opt_swu2_map(P2, t1, &t1);
	CYBOZU_TEST_EQUAL(P1, P2);
}

template<class T>
void testVec(const T& mapto, const char *file)
{
	std::ifstream ifs(file);
	Fp2 t1, t2;
	G2 out, P;
	std::string s;
	for (;;) {
		ifs >> s;
		if (s != "t1") break;
		ifs >> t1;
		ifs >> s;
		CYBOZU_TEST_EQUAL(s, "t2");
		ifs >> t2;
		ifs >> s;
		CYBOZU_TEST_EQUAL(s, "out");
		ifs >> out.x >> out.y >> out.z;
		mapto.opt_swu2_map(P, t1, &t2);
		CYBOZU_TEST_EQUAL(P, out);
	}
}

CYBOZU_TEST_AUTO(test)
{
	initPairing(mcl::BLS12_381);
	bn::setMapToMode(MCL_MAP_TO_MODE_WB19);
	const mcl::bn::local::MapToG2_WB19& mapto = BN::param.mapTo.maptog2_wb19_;
	helpTest(mapto);
	addTest(mapto);
	iso3Test(mapto);
	opt_swu2_mapTest(mapto);
	testVec(mapto, "fips_186_3_B233.txt");
	testVec(mapto, "misc.txt");
}
