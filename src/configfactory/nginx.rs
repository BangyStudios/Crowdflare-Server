pub fn get_config_https(
    host_website : &str, 
    host_origin : &str, 
    cache_max_size : &str, 
    cache_ttl : &str, 
) -> Result<String, String> {
    let host_website_us = host_website.replace(".", "_");
    let config = format!(
        r#"proxy_cache_path /var/www/cache/{host_website} levels=1:2 keys_zone={host_website_us}:10m max_size={cache_max_size} inactive={cache_ttl} use_temp_path=off;

server {{
    server_name {host_website};

    location / {{
        proxy_pass https://{host_origin};
        proxy_set_header Host {host_website};
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        # Enable caching
        proxy_cache {host_website_us};
        proxy_cache_valid 200 301 {cache_ttl};
        proxy_cache_valid 302 404 1m;
        proxy_cache_background_update on;  # Enable background update
        proxy_cache_use_stale updating error timeout invalid_header http_500 http_502 http_503 http_504;
        add_header X-Proxy-Cache $upstream_cache_status;
    }}

    listen 443 ssl;
    ssl_certificate /var/www/ssl/{host_website}/fullchain.pem;
    ssl_certificate_key /var/www/ssl/{host_website}/privkey.pem;
    include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot

}}

server {{
    if ($host = {host_website}) {{
        return 301 https://$host$request_uri;
    }}

    listen 80;
    server_name {host_website};
    return 404;

}}
"#,
        host_website = host_website, 
        host_origin = host_origin
    );
    Ok(config)
}