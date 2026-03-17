#include "frame_engine.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

bool fe_build_jcs(const frame_t *f, char *out_buffer, size_t max_len) {
    if (!f || !out_buffer) return false;

    // Erzeugt einen deterministischen JSON-String inklusive Inhalts-Hash
    int offset = snprintf(out_buffer, max_len, 
        "{\"id\":\"%s\",\"qh\":[", f->id);

    for (int i = 0; i < 56; ++i) {
        offset += snprintf(out_buffer + offset, max_len - offset, "%u%s", 
                           f->qh[i], (i < 55) ? "," : "");
    }

    snprintf(out_buffer + offset, max_len - offset, 
             "],\"d_hash\":\"%s\",\"t\":%llu}", 
             f->content_hash, (unsigned long long)f->time);
    
    return true;
}

bool fe_compute_hash(frame_t *f) {
    char jcs_buffer[8192];
    if (!fe_build_jcs(f, jcs_buffer, sizeof(jcs_buffer))) return false;

    unsigned char hash_raw[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)jcs_buffer, strlen(jcs_buffer), hash_raw);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(f->hash + (i * 2), "%02x", hash_raw[i]);
    }
    f->hash[64] = '\0'; 
    return true;
}