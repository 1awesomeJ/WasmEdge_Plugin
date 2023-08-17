use wasmedge_sdk::VmBuilder;
use std::{env, process};


fn main() {
	let args: Vec<String> = env::args().collect();

	if args.len() != 2 {
		println!("Usage cargo run <path/to/videofile>");
		process::exit(1);
	}

	let file_path = &args[1];
	/* passing the path to wasmedge to be implemented */

}

