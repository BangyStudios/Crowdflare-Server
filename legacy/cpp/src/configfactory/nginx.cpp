#include <string>
#include <utility>

namespace configfactory {

    namespace nginx {

        std::pair<std::string, std::uint8_t> get_config_https(
            const std::string& host_website,
            const std::string& host_origin,
            const std::string& cache_max_size,
            const std::string& cache_ttl
        ) {
            std::string host_website_us;
            for (char ch : host_website) {
                host_website_us += (ch == '.') ? '_' : ch;
            }

            std::string config = R"(
        proxy_cache_path /var/www/cache/{host_website} levels=1:2 keys_zone={host_website_us}:10m max_size={cache_max_size} inactive={cache_ttl} use_temp_path=off;

        server {
            server_name {host_website};

            location / {
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
            }

            listen 443 ssl;
            ssl_certificate /var/www/ssl/{host_website}/fullchain.pem;
            ssl_certificate_key /var/www/ssl/{host_website}/privkey.pem;
            include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
            ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot
        }

        server {
            if ($host = {host_website}) {
                return 301 https://$host$request_uri;
            }

            listen 80;
            server_name {host_website};
            return 404;
        }
        )";

            // Replace placeholders with actual values
            size_t pos;
            pos = config.find("{host_website}");
            while (pos != std::string::npos) {
                config.replace(pos, 14, host_website);
                pos = config.find("{host_website}", pos + host_website.size());
            }

            pos = config.find("{host_website_us}");
            while (pos != std::string::npos) {
                config.replace(pos, 17, host_website_us);
                pos = config.find("{host_website_us}", pos + host_website_us.size());
            }

            pos = config.find("{host_origin}");
            while (pos != std::string::npos) {
                config.replace(pos, 13, host_origin);
                pos = config.find("{host_origin}", pos + host_origin.size());
            }

            pos = config.find("{cache_max_size}");
            while (pos != std::string::npos) {
                config.replace(pos, 16, cache_max_size);
                pos = config.find("{cache_max_size}", pos + cache_max_size.size());
            }

            pos = config.find("{cache_ttl}");
            while (pos != std::string::npos) {
                config.replace(pos, 11, cache_ttl);
                pos = config.find("{cache_ttl}", pos + cache_ttl.size());
            }

            return {config, 0};
        }
    }
}