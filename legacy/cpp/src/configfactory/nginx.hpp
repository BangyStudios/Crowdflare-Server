#ifndef NGINX_HPP
#define NGINX_HPP

#include <string>
#include <utility>

namespace configfactory {
    namespace nginx {

    /**
     * Generates an Nginx configuration for HTTPS proxying.
     *
     * @param host_website The hostname of the website (e.g., "blog.ban.gy").
     * @param host_origin The origin server to proxy to (e.g., "us1-1.edge.icbix.com").
     * @param cache_max_size The maximum size of the cache (e.g., "1g").
     * @param cache_ttl The time-to-live for cached items (e.g., "12h").
     * @return A pair where the first element is the generated configuration string,
     *         and the second element is an error code (0 if no error occurred).
     */
    std::pair<std::string, std::uint8_t> get_config_https(
        const std::string& host_website,
        const std::string& host_origin,
        const std::string& cache_max_size,
        const std::string& cache_ttl
    );

    }
}

#endif // NGINX_HPP