#include "frame_engine.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

bool fe_build_jcs(const frame_t *f, char *out_buffer, size_t max_len) {
    if (!f || !out_buffer || max_len < 512) return false;

    int offset = snprintf(out_buffer, max_len, "{\"id\":\"%s\",\"qh\":[", f->id);
    if (offset < 0 || (size_t)offset >= max_len) return false;

    for (int i = 0; i < 56; ++i) {
        int written = snprintf(out_buffer + offset, max_len - offset, "%u%s", 
                               f->qh[i], (i < 55) ? "," : "");
        if (written < 0 || (size_t)written >= max_len - offset) return false;
        offset += written;
    }

    int final_write = snprintf(out_buffer + offset, max_len - offset, "],\"t\":%llu}", 
                               (unsigned long long)f->time);
    
    if (final_write < 0 || (size_t)final_write >= max_len - offset) return false;

    return true;
}

bool fe_compute_hash(frame_t *f) {
    if (!f) return false;

    char jcs_buffer[4096];
    if (!fe_build_jcs(f, jcs_buffer, sizeof(jcs_buffer))) {
        return false;
    }

    unsigned char hash_raw[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)jcs_buffer, strlen(jcs_buffer), hash_raw);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(f->hash + (i * 2), "%02x", hash_raw[i]);
    }
    f->hash[64] = '\0'; 

    return true;
}