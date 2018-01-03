#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "file_cache_v5.h"

#define ITEMS_TO_READ 1

ngx_http_file_cache_header_v5_t read_v5(char *filename)
{
    ngx_http_file_cache_header_v5_t header;
    FILE *f;
    size_t read_items;

    f = fopen(filename, "r");
    if(f != NULL)
    {
        read_items = fread(&header, sizeof(ngx_http_file_cache_header_v5_t), ITEMS_TO_READ, f);
        if(read_items != ITEMS_TO_READ)
        {
            memset(&header, 0, sizeof(ngx_http_file_cache_header_v5_t));
        }
    }

    return header;
}

void print_v5(ngx_http_file_cache_header_v5_t file_cache_header)
{
    struct tm ts;
    char buf_valid_sec[80];
    char buf_updating_sec[80];
    char buf_error_sec[80];
    char buf_last_modified[80];
    char buf_date[80];

    ts = *gmtime(&file_cache_header.valid_sec);
    strftime(buf_valid_sec, sizeof(buf_valid_sec), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    ts = *gmtime(&file_cache_header.updating_sec);
    strftime(buf_updating_sec, sizeof(buf_updating_sec), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    ts = *gmtime(&file_cache_header.error_sec);
    strftime(buf_error_sec, sizeof(buf_error_sec), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    ts = *gmtime(&file_cache_header.last_modified);
    strftime(buf_last_modified, sizeof(buf_last_modified), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    ts = *gmtime(&file_cache_header.date);
    strftime(buf_date, sizeof(buf_date), "%a %Y-%m-%d %H:%M:%S %Z", &ts);

    printf(
        "File cache header V5 -- Fields:\n"
        "version        [%p]\n"
        "valid_sec      [0x%" PRIX32 "][%s]\n"
        "updating_sec   [0x%" PRIX32 "][%s]\n"
        "error_sec      [0x%" PRIX32 "][%s]\n"
        "last_modified  [0x%" PRIX32 "][%s]\n"
        "date           [0x%" PRIX32 "][%s]\n"
        "crc32          [0x%" PRIX32 "]\n"
        "valid_msec     [%u]\n"
        "header_start   [%u]\n"
        "body_start     [%u]\n"
        "etag_len       [%u]\n"
        "etag[128]      [%s]\n"
        "vary_len       [%u]\n"
        "vary[128]      [%s]\n"
        "variant[16]    [%s]\n",
        file_cache_header.version, file_cache_header.valid_sec, buf_valid_sec,
        file_cache_header.updating_sec, buf_updating_sec,
        file_cache_header.error_sec, buf_error_sec,
        file_cache_header.last_modified, buf_last_modified,
        file_cache_header.date, buf_date,
        file_cache_header.crc32, file_cache_header.valid_msec,
        file_cache_header.header_start, file_cache_header.body_start,
        file_cache_header.etag_len, file_cache_header.etag,
        file_cache_header.vary_len,file_cache_header.vary,
        file_cache_header.variant);
}
