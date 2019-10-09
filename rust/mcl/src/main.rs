// env RUSTFLAGS="-L ../../../mcl/lib" cargo run

fn main() {
    println!("mcl version={:04x}", mcl::get_version());
    let b = mcl::init(mcl::CurveType::BN254);
    if !b {
        println!("init err");
    }
    let mut x = mcl::Fr::zero();
    println!("x={}", x.get_str(10));
    x.set_int(123456);
    println!("x={}", x.get_str(10));
    x.set_int(0xfff);
    println!("x={}", x.get_str(16));
    x.clear();
    println!("x={}", x.get_str(10));
    x.set_str("0x123", 0);
    println!("x={}", x.get_str(16));
    let buf = x.serialize();
    println!("serialize={:x?}", buf); // put hex byte
    let mut y = mcl::Fr::zero();
    if y.deserialize(&buf) {
        println!("y={}", y.get_str(16));
    } else {
        println!("err deserialize");
    }
    if x != y {
        println!("ng");
    }
    x.set_int(1);
    if x == y {
        println!("ng");
    }
    if !x.is_one() {
        println!("ng");
    }
	x.set_int(123);
	y.set_int(567);
    let mut z = unsafe { std::mem::uninitialized() };
	mcl::Fr::add(&mut z, &x, &y);

	println!("z={}", z.get_str(10));
	println!("x={}", x.get_str(10));
	println!("y={}", y.get_str(10));
}
