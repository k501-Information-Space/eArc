TASK: K501 Navigator Graph Implementation

TARGET: Obsidian Plugin Interface

OBJECTIVE

Implement causal visualization between RAW frames and OBS frames

within the K501 lattice navigator.

CONSTRAINTS

1. The system is append-only.

2. No modification of existing frames.

3. Graph must be reconstructed only from pointers.

DATA MODEL

Frame {

id

hash

frame_type

pointer

}

NODE TYPES

RAW:

class = "k501-neuron-raw"

OBS:

class = "k501-neuron-obs"

EDGE TYPE

RAW -> OBS

class = "k501-synapse"

ALGORITHM

for each frame F:

if F.frame_type == "OBS":

source = F.pointer

target = F.id

createEdge(source,target)

RENDERING

drawBezier(sourceNode,targetNode)

CSS

.k501-neuron-raw { color: #5B8CFF }

.k501-neuron-obs { color: #FFB347 }

.k501-synapse {

stroke: rgba(255,255,255,0.35)

}

PERFORMANCE

Graph must support >50k nodes.

Index edges using hash map:

Map<frame_id, node>

Complexity target:

O(n)

OUTPUT

Interactive causal graph

inside K501 navigator.