#include <immintrin.h>

#include <math.h>

// Interne AVX-Funktion für T520 (AVX1)

float calculate_resonance(const float* a, const float* b) {

__m256 sum_ab = _mm256_setzero_ps();

__m256 sum_a2 = _mm256_setzero_ps();

__m256 sum_b2 = _mm256_setzero_ps();

for (int i = 0; i < 4; i++) {

__m256 va = _mm256_loadu_ps(&a[i * 8]);

__m256 vb = _mm256_loadu_ps(&b[i * 8]);

sum_ab = _mm256_add_ps(sum_ab, _mm256_mul_ps(va, vb));

sum_a2 = _mm256_add_ps(sum_a2, _mm256_mul_ps(va, va));

sum_b2 = _mm256_add_ps(sum_b2, _mm256_mul_ps(vb, vb));

}

float res_ab[8], res_a2[8], res_b2[8];

_mm256_storeu_ps(res_ab, sum_ab);

_mm256_storeu_ps(res_a2, sum_a2);

_mm256_storeu_ps(res_b2, sum_b2);

float dot = 0, norm_a = 0, norm_b = 0;

for (int i = 0; i < 8; i++) {

dot += res_ab[i];

norm_a += res_a2[i];

norm_b += res_b2[i];

}

return dot / (sqrtf(norm_a) * sqrtf(norm_b) + 1e-9f);

}

// EXPORT: Muss exakt so heißen wie im Python-Modul definiert

void qh256_batch_resonance(const float* query, const float* targets, int num_targets, float* output) {

for (int i = 0; i < num_targets; i++) {

output[i] = calculate_resonance(query, &targets[i * 32]);

}

}

#include <immintrin.h>

#include <math.h>

// Interne AVX-Funktion für T520 (AVX1)

float calculate_resonance(const float* a, const float* b) {

__m256 sum_ab = _mm256_setzero_ps();

__m256 sum_a2 = _mm256_setzero_ps();

__m256 sum_b2 = _mm256_setzero_ps();

for (int i = 0; i < 4; i++) {

__m256 va = _mm256_loadu_ps(&a[i * 8]);

__m256 vb = _mm256_loadu_ps(&b[i * 8]);

sum_ab = _mm256_add_ps(sum_ab, _mm256_mul_ps(va, vb));

sum_a2 = _mm256_add_ps(sum_a2, _mm256_mul_ps(va, va));

sum_b2 = _mm256_add_ps(sum_b2, _mm256_mul_ps(vb, vb));

}

float res_ab[8], res_a2[8], res_b2[8];

_mm256_storeu_ps(res_ab, sum_ab);

_mm256_storeu_ps(res_a2, sum_a2);

_mm256_storeu_ps(res_b2, sum_b2);

float dot = 0, norm_a = 0, norm_b = 0;

for (int i = 0; i < 8; i++) {

dot += res_ab[i];

norm_a += res_a2[i];

norm_b += res_b2[i];

}

return dot / (sqrtf(norm_a) * sqrtf(norm_b) + 1e-9f);

}

// EXPORT: Muss exakt so heißen wie im Python-Modul definiert

void qh256_batch_resonance(const float* query, const float* targets, int num_targets, float* output) {

for (int i = 0; i < num_targets; i++) {

output[i] = calculate_resonance(query, &targets[i * 32]);

}

}

# K501 Core Makefile - T520 Optimized (AVX1)

CC = gcc

CFLAGS = -O3 -mavx -pthread -fPIC -Wall

LDFLAGS = -shared

TARGET = libk501.so

SRCS = qh256_algebra.c

all: $(TARGET)

$(TARGET): $(SRCS)

$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCS)

clean:

rm -f $(TARGET) *.o

#!/usr/bin/env python3

import sys

import json

import numpy as np

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

def run_search(query_text):

print(f"[*] STARTE SEMANTISCHE RESONANZ-ANALYSE")

print(f"[*] Query: \"{query_text}\"")

# 1. Komponenten laden

llm = QH256LLM()

algebra = QH256Algebra("/K501GeminiNet/core/libk501.so")

ledger_path = "/K501GeminiNet/Node01/vault/ledger/frames.ndjson"

# 2. Such-Vektor generieren & Formatierung erzwingen (float32, 32-dim)

raw_vector = llm.get_semantic_vector(query_text)

query_vector = np.array(raw_vector, dtype=np.float32)[:32].tolist()

# 3. Frames aus Ledger laden

results = []

try:

with open(ledger_path, "r") as f:

for line in f:

if not line.strip(): continue

frame = json.loads(line)

# Vektor aus Frame validieren

f_vec = np.array(frame["vector"], dtype=np.float32)[:32].tolist()

# Resonanz berechnen via C-Kern

res = algebra.compute_resonance(query_vector, [f_vec])[0]

results.append((res, frame))

except FileNotFoundError:

print("[!] ERROR: Ledger Datei nicht gefunden!")

return

except Exception as e:

print(f"[!] Fehler beim Lesen des Ledgers: {e}")

return

# 4. Sortieren und Ausgeben

results.sort(key=lambda x: x[0], reverse=True)

print("\n--- [ERGEBNISSE AUS DEM GITTER] ---")

for score, frame in results[:3]:

print(f"Resonanz: {score:.4f} | ID: {frame['id'][:10]}")

print(f"Inhalt: {frame['payload'][:120]}...")

print("-" * 40)

if __name__ == '__main__':

if len(sys.argv) < 2:

print("Usage: search.py \"suchbegriff\"")

else:

run_search(sys.argv[1])