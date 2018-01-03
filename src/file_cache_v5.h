#ifndef FILE_CACHE_V5_H
#define FILE_CACHE_V5_H

#include "ngx_compat_types.h"

ngx_http_file_cache_header_v5_t read_v5(char *filename);
void print_v5(ngx_http_file_cache_header_v5_t file_cache_header);

#endif /* FILE_CACHE_V5_H */
