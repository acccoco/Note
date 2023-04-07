use std::{env, process};


use learn_rust::{Config, run};


fn main()
{
    // 参数解析
    let config = Config::build(env::args()).unwrap_or_else(|err| {
        eprintln!("problems parsing args: {err}");
        process::exit(1);
    });

    println!("search for {}", config.query);
    println!("in file {}", config.file_path);

    // 运行程序
    if let Err(e) = run(config) {
        eprintln!("application error: {}", e);
        process::exit(1);
    }
}
