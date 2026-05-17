# ============================================================

# K501 · Post-Migrations-Akt: Resonanz-Dashboard

# Node: N_T520

# Version: 1.0

# Zweck: Aktivierung der Sensorik, Visualisierung, Föderation

# Optimiert für >1.400 Frames, progress bar + RAM-effizientes Threading

# ============================================================

import os

import json

import hashlib

import numpy as np

from tqdm import tqdm

from concurrent.futures import ThreadPoolExecutor

import networkx as nx

import matplotlib.pyplot as plt

# -------------------------

# Konfiguration

# -------------------------

FRAME_DIR = "./frames" # Verzeichnis mit 1.416 Frames

TOP_N = 50 # Anzahl der Top-Resonanz-Frames für Föderation

THREADS = 8 # Parallel Threads für Berechnung

VISUALIZE = True # Obsidian/Graph-Visualisierung aktivieren

# -------------------------

# Hilfsfunktionen

# -------------------------

def load_frame(file_path):

"""Lädt Frame und berechnet SHA256-Identität"""

with open(file_path, "r", encoding="utf-8") as f:

content = f.read()

sha = hashlib.sha256(content.encode('utf-8')).hexdigest()

return {"id": sha, "content": content}

def vectorize_frame(frame):

"""Konvertiert Frame-Inhalt in Vektor (Dummy-Beispiel, kann durch Embeddings ersetzt werden)"""

text = frame["content"]

vec = np.array([ord(c) for c in text[:256]], dtype=np.float32)

if vec.size < 256:

vec = np.pad(vec, (0, 256 - vec.size))

return vec

def compute_resonance(vec_i, vec_j):

"""Berechnet strukturelle Resonanz (Kosinus-Ähnlichkeit)"""

norm_i = np.linalg.norm(vec_i)

norm_j = np.linalg.norm(vec_j)

if norm_i == 0 or norm_j == 0:

return 0.0

return float(np.dot(vec_i, vec_j) / (norm_i * norm_j))

# -------------------------

# Schritt 1: Aktivierung der Sensorik

# -------------------------

print("=== Schritt 1: Aktivierung der Sensorik ===")

frame_files = [os.path.join(FRAME_DIR, f) for f in os.listdir(FRAME_DIR) if f.endswith(".json")]

frames = []

for file in tqdm(frame_files, desc="Frames laden"):

frames.append(load_frame(file))

# Frames vektorisieren

vectors = []

for frame in tqdm(frames, desc="Frames vektorisieren"):

vectors.append(vectorize_frame(frame))

vectors = np.array(vectors)

# Resonanz-Matrix berechnen (Threaded)

num_frames = len(frames)

resonance_matrix = np.zeros((num_frames, num_frames), dtype=np.float32)

def compute_row(i):

row = np.zeros(num_frames, dtype=np.float32)

for j in range(num_frames):

if i == j:

row[j] = 1.0

else:

row[j] = compute_resonance(vectors[i], vectors[j])

return i, row

print("Resonanz-Matrix berechnen...")

with ThreadPoolExecutor(max_workers=THREADS) as executor:

futures = [executor.submit(compute_row, i) for i in range(num_frames)]

for f in tqdm(futures, desc="Berechnung"):

i, row = f.result()

resonance_matrix[i] = row

# -------------------------

# Schritt 2: Visualisierung

# -------------------------

if VISUALIZE:

print("\n=== Schritt 2: Visualisierung ===")

G = nx.Graph()

for idx, frame in enumerate(frames):

G.add_node(frame["id"], label=f"F{idx+1}")

# Kanten nur für Resonanz > Threshold

threshold = 0.75

for i in range(num_frames):

for j in range(i+1, num_frames):

if resonance_matrix[i,j] > threshold:

G.add_edge(frames[i]["id"], frames[j]["id"], weight=resonance_matrix[i,j])

# Layout + Zeichnen

plt.figure(figsize=(14,14))

pos = nx.spring_layout(G, seed=42)

edges = G.edges()

weights = [G[u][v]['weight']*2 for u,v in edges] # Linienbreite proportional

nx.draw(G, pos, edges=edges, width=weights, with_labels=False, node_size=50, node_color='skyblue')

plt.title("K501 Resonanz-Netzwerk (Gemini-Space)")

plt.show()

# -------------------------

# Schritt 3: Föderation

# -------------------------

print("\n=== Schritt 3: Föderation ===")

frame_scores = resonance_matrix.sum(axis=1)

top_indices = np.argsort(frame_scores)[-TOP_N:][::-1]

print(f"Top {TOP_N} Resonanz-Frames für Föderation:")

for idx in top_indices:

print(f"- Frame ID: {frames[idx]['id']} | Score: {frame_scores[idx]:.4f}")

# Speichern als JSON für weitere Verwendung

federation_frames = [frames[idx]["id"] for idx in top_indices]

with open("federation_frames.json", "w", encoding="utf-8") as f:

json.dump(federation_frames, f, indent=2)

print("\nPost-Migrations-Akt abgeschlossen ✅")