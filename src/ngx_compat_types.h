#ifndef NGX_COMPAT_TYPES_H
#define NGX_COMPAT_TYPES_H

#include <stdint.h>

/*! \struct ngx_http_file_cache_header_v5_t
    \brief Same as ngx_http_file_cache_header_t, using basic data types.
*/
typedef struct
{
    uintptr_t   version;
    uint64_t    valid_sec;
    uint64_t    updating_sec;
    uint64_t    error_sec;
    uint64_t    last_modified;
    uint64_t    date;
    uint32_t    crc32;
    uint16_t    valid_msec;
    uint16_t    header_start;
    uint16_t    body_start;
    uint8_t     etag_len;
    uint8_t     etag[128];
    uint8_t     vary_len;
    uint8_t     vary[128];
    uint8_t     variant[16];
} ngx_http_file_cache_header_v5_t;

#endif /* NGX_COMPAT_TYPES_H */
