mod configfactory;

fn main() {
    let config = match configfactory::nginx::get_config_https(
        "blog.ban.gy", 
        "us1-1.edge.icbix.com", 
        "1g",  
        "12h"
    ) {
        Ok(config) => config, 
        Err(e) => { 
            eprintln!("Error: {}", e);
            return;
        }
    };

    println!("{config}");
}