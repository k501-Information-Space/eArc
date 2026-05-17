[I built an offline semantic search plugin for Claude Code — search thousands of local documents with natural language](https://www.reddit.com/r/ClaudeAI/comments/1s2fc9k/i_built_an_offline_semantic_search_plugin_for/)

I work with a lot of local documents (project specs, contracts, meeting notes, research) and kept running into

the same problem: Claude can read one file at a time, but can't search across hundreds of files to find the

relevant pieces.

So I built cowork-semantic-search — an MCP plugin that indexes your local files into a vector database and lets

Claude search them using natural language.

How it works:

1. Point it at a folder → it chunks and embeds all your documents locally
2. Ask Claude a question → it searches the index and pulls only the relevant pieces
3. Claude answers using your actual data, not just training knowledge

What makes it different from cloud RAG tools:

- Fully offline — no API keys, no data leaves your machine. One-time model download (~120MB), then everything

runs local

- Incremental indexing — re-indexing 1000 files where 3 changed takes seconds, not minutes

- Hybrid search — combines vector similarity with full-text keyword search. Catches what pure semantic search

misses

- Multilingual — works across 50+ languages. Search in English, find results in German (or vice versa)

- Supports 6 formats — .txt, .md, .pdf, .docx, .pptx, .csv

Example — searching an Obsidian vault:

You: "Index my vault at ~/Documents/ObsidianVault"

Claude: Indexed 847 files → 3,291 chunks in 42s

You: "What did I write about API rate limiting?"

Claude: Found 6 relevant chunks across 3 files:

- notes/backend/rate-limiting-strategies.md

- projects/acme-api/design-decisions.md

- daily/2025-11-03.md

Setup takes about 2 minutes — clone, install, add to your .mcp.json, done.

GitHub: [https://github.com/ZhuBit/cowork-semantic-search](https://github.com/ZhuBit/cowork-semantic-search)

[11 comments](https://www.reddit.com/r/ClaudeAI/comments/1s2fc9k/i_built_an_offline_semantic_search_plugin_for/)

[https://github.com/ZhuBit/cowork-semantic-search](https://github.com/ZhuBit/cowork-semantic-search)

# **cowork-semantic-search**

**![the others](<Docx_Convert/Attachments/the%20others.png>)** ![the others](<Docx_Convert/Attachments/the%20others%201.png>) ![the others](<Docx_Convert/Attachments/the%20others%202.png>) ![the others](<Docx_Convert/Attachments/the%20others%203.png>)

If you find this useful, consider giving it a ⭐ — it helps others discover the project.

Local semantic search for your documents. No API keys. No cloud. Works with any MCP client.

![the others](<Docx_Convert/Attachments/the%20others%204.png>)

## **Why**

AI coding tools are powerful, but they have blind spots when it comes to your local files:

- Frozen knowledge -- training data has a cutoff. Your latest reports, notes, and contracts don't exist in the model's world.
- Context window limits -- you can't paste 500 documents into a prompt.
- No cross-file search -- your AI tool can read one file at a time, but can't search across your entire document library for the relevant pieces.

This plugin bridges that gap. It indexes your local documents into a small, fast vector database. When you ask a question, it retrieves only the relevant pieces -- so your AI tool can answer with your actual data.

Your documents --> chunked --> embedded --> local vector DB

|

Your question --> embedded --> similarity search --> relevant chunks --> AI answers

## **Features**

- Fully offline -- one-time model download (~120MB), then no network calls. No data leaves your machine.
- Incremental indexing -- SHA-256 content hashing. Only changed files get reprocessed. Re-indexing 1000 files where 3 changed takes seconds.
- Multilingual -- handles 50+ languages natively. Search in one language, find results in another.
- Hybrid search -- combines semantic similarity with full-text keyword search via Reciprocal Rank Fusion. Catches what pure vector search misses.
- Multiple formats -- txt, md, pdf, docx, pptx, csv out of the box.
- Any MCP client -- works with Claude Code, Cursor, Windsurf, Cline, and any other MCP-compatible tool.
- Zero infrastructure -- LanceDB stores everything as local files. No server, no Docker, no database to manage.

## **Supported Formats**

|**Format**|**Extension**|**Details**|
|---|---|---|
|Plain text|.txt|UTF-8 with fallback|
|---|---|---|
|Markdown|.md|Raw text preserved|
|---|---|---|
|PDF|.pdf|Page-level extraction with metadata|
|---|---|---|
|Word|.docx|Full paragraph extraction|
|---|---|---|
|PowerPoint|.pptx|Slide-level extraction with metadata|
|---|---|---|
|CSV|.csv|Row-based text extraction|
|---|---|---|

## **Quick Start**

### **1. Install**

git clone https://github.com/ZhuBit/cowork-semantic-search.git

cd cowork-semantic-search

python3 -m venv .venv && source .venv/bin/activate

pip install -e ".[all]"

### **2. Configure your MCP client**

Add the server to your MCP client's config. Replace paths with your own.

Claude Code -- .mcp.json in your project root

{

"mcpServers": {

"semantic-search": {

"command": "/absolute/path/to/.venv/bin/python",

"args": ["-m", "server.main"],

"cwd": "/absolute/path/to/cowork-semantic-search",

"env": {

"PYTHONPATH": "/absolute/path/to/cowork-semantic-search"

}

}

}

}

Cursor -- .cursor/mcp.json in your project root or ~/.cursor/mcp.json globally

{

"mcpServers": {

"semantic-search": {

"command": "/absolute/path/to/.venv/bin/python",

"args": ["-m", "server.main"],

"env": {

"PYTHONPATH": "/absolute/path/to/cowork-semantic-search"

}

}

}

}

Windsurf -- ~/.codeium/windsurf/mcp_config.json

{

"mcpServers": {

"semantic-search": {

"command": "/absolute/path/to/.venv/bin/python",

"args": ["-m", "server.main"],

"env": {

"PYTHONPATH": "/absolute/path/to/cowork-semantic-search"

}

}

}

}

Cline -- MCP Servers settings in the Cline VS Code extension

Open Cline > MCP Servers icon > Configure > Advanced MCP Settings, then add:

{

"mcpServers": {

"semantic-search": {

"command": "/absolute/path/to/.venv/bin/python",

"args": ["-m", "server.main"],

"env": {

"PYTHONPATH": "/absolute/path/to/cowork-semantic-search"

}

}

}

}

### **3. Restart your MCP client and go**

"Index all documents in ~/Documents/projects"

"Search for 'quarterly revenue report'"

First run downloads the embedding model (~120MB), then everything runs offline.

## **Example: Search Your Obsidian Vault**

If you keep notes in Obsidian (or any folder of markdown files), this plugin turns your AI tool into a search engine for your knowledge base.

You: "Index my vault at ~/Documents/ObsidianVault"

AI: Indexed 847 files -> 3,291 chunks in 42s

You: "What did I write about API rate limiting?"

AI: Found 6 relevant chunks across 3 files:

- notes/backend/rate-limiting-strategies.md

- projects/acme-api/design-decisions.md

- daily/2025-11-03.md

...

You: "Find anything about the client meeting last November, use hybrid search"

AI: Found 4 results using hybrid search (vector + keyword):

- meetings/2025-11-12-acme-kickoff.md

- daily/2025-11-12.md

...

Works the same with PDFs, Word docs, PowerPoints, and CSVs -- just point it at a folder.

## **Tools**

|**Tool**|**Description**|
|---|---|
|index_folder|Index or re-index all documents in a folder. Incremental -- skips unchanged files.|
|---|---|
|semantic_search|Search indexed documents using natural language. Supports vector and hybrid modes.|
|---|---|
|get_index_status|Show total chunks, file count, and list of indexed files.|
|---|---|
|reindex_file|Force re-index a single file, bypassing the hash cache.|
|---|---|

## **How It Works**

1. Parse -- extract text from each document, preserving structure (pages, slides)
2. Chunk -- split into ~400 character overlapping pieces for precise retrieval
3. Embed -- convert each chunk into a 384-dimensional vector using paraphrase-multilingual-MiniLM-L12-v2
4. Store -- save chunks + vectors in a LanceDB database (a local file, no server needed)
5. Search -- embed your query, find nearest chunks by cosine similarity, optionally combine with full-text keyword search via RRF

## **Advanced Usage**

Use as a Python library

from server.indexer import index_folder

from server.search import semantic_search

# Index a folder

result = index_folder("/path/to/docs")

print(f"{result['files_indexed']} files -> {result['total_chunks']} chunks")

# Search

results = semantic_search("project deadline", mode="hybrid")

for r in results["results"]:

print(f" {r['file_name']}: {r['text'][:100]}...")

## **Architecture**

server/

main.py # MCP server + tool definitions

parsers.py # Per-format text extraction

chunker.py # Text splitting with metadata

indexer.py # Discovery, hashing, embedding pipeline

store.py # LanceDB vector store + FTS + hybrid search

search.py # Query embedding + search orchestration

|**Component**|**Choice**|**Why**|
|---|---|---|
|MCP framework|FastMCP|Clean tool definitions, async support|
|---|---|---|
|Embeddings|sentence-transformers|Offline, multilingual, fast|
|---|---|---|
|Vector DB|LanceDB|Serverless, embedded, FTS built-in|
|---|---|---|
|Chunking|langchain-text-splitters|Battle-tested recursive splitting|
|---|---|---|
|PDF|PyMuPDF|Fast, accurate extraction|
|---|---|---|
|DOCX|python-docx|Lightweight, no system deps|
|---|---|---|
|PPTX|python-pptx|Slide-level extraction|
|---|---|---|

## **Development**

source .venv/bin/activate

pytest tests/ -v

56 tests covering parsers, chunking, indexing, search, and MCP tool integration.

Contributions welcome -- open an issue or submit a PR.

## **Roadmap**

- ONNX runtime for faster embeddings (drop PyTorch dependency)
- Configurable chunk size and overlap via tool params
- Multi-folder named indexes
- Metadata filtering (date ranges, tags, custom fields)
- Watch mode (auto-reindex on file changes)

## **Support**

If this is useful to you, consider giving it a ⭐ — it helps others find the project.

## **License**

AGPL-3.0 -- free to use, modify, and self-host. If you offer this as a network service, you must share your source code. See [LICENSE](https://github.com/ZhuBit/cowork-semantic-search/blob/main/LICENSE) for details.

—----------------------

[https://www.reddit.com/user/adverity_data/comments/1q6r20s/megathread_conversational_ai_a_gamechanger_for/?p=1&impressionid=5131722217129825672](https://www.reddit.com/user/adverity_data/comments/1q6r20s/megathread_conversational_ai_a_gamechanger_for/?p=1&impressionid=5131722217129825672)

[Megathread] Conversational AI: A gamechanger for Data Democratization

TL;DR

For years, data democratization has been touted as the key to unlocking better, faster marketing decisions. But the reality? Dashboards were too clunky, tools too technical, and insights too slow to act on. Data may have been “accessible”, but only to those who knew how to wrangle it.

That’s changing fast.

Thanks to conversational AI, marketers can now speak to their data and get instant, meaningful answers. No code, no jargon, just insights in plain English. And it’s reshaping how marketing teams operate.

[📖 The future of data democratization in marketing](https://www.adverity.com/blog/the-future-of-data-democratization-in-marketing-how-conversational-ai-is-changing-the-game?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting) - AI is finally delivering on the promise of data access for everyone.

![the others](<Docx_Convert/Attachments/the%20others%205.png>)

✨ What’s Changing with Conversational AI?

- Natural language interfaces: Ask questions like, _“Which campaign drove the most conversions last month?”_ and get real-time answers - no dashboard digging required.
- Smarter analysis: It doesn’t just fetch data, it interprets it, highlights trends, and recommends next steps.
- Rapid decisions: With faster insights comes faster action. Teams can pivot and optimize on the fly.
- No technical barrier: No SQL, no Python. If you can ask a question, you can use the tool.

📖 [Conversational AI: Bridging the gap between real-time data and real-time curiosity](https://www.adverity.com/blog/conversational-ai-bridging-the-gap-between-real-time-data-and-real-time-curiosity?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting) – Why natural language is a key interface for marketers.

Team collaboration: Share insights across platforms like Slack, email, or project boards with a click.

![the others](<Docx_Convert/Attachments/the%20others%206.png>)

🔍 Inside Adverity: Where AI Meets Accessibility

[📖 Data Conversations (Product overview)](https://info.adverity.com/data-conversations?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting) – See what Adverity is launching and how it works.

Here’s what we’re building at Adverity to help bring this to life, and bridge the gap between complex data and everyday users:

- 🧠 Transformation Co-Pilot: Describe how you want your data transformed. Our AI generates Python code instantly - no need to write a single line yourself.
- 💬 Data Conversations (coming soon!): A chat-based interface that lets you ask complex data questions, get instant answers, visualize results, and share them across teams.

We’re making it way easier for marketers to actually use their data, no code required.

![the others](<Docx_Convert/Attachments/the%20others%207.png>)

📈 Looking Ahead: The Future Is Conversational

By 2025 and beyond, the shift is clear:

_From dashboards_ → _dialogue._

_From data complexity_ → _data fluency._

_From gatekeeping insights_ → _empowering every marketer._

Conversational AI is making data democratization not just possible, but practical. It's changing how marketers think, act, and collaborate.

The future of data isn’t hidden in a dashboard. It speaks your language.

Check out some of our latest blogs for more context on how conversational AI is revolutionizing the way marketers work:

**Bonus context (for the curious)**

- [Conversational AI vs. Agentic AI](https://www.adverity.com/blog/conversational-ai-vs.-agentic-ai-what-marketers-need-to-know?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting) – A breakdown of the two AI types and how they differ in practice.
- [How to use AI in data analytics to drive marketing growth](https://www.adverity.com/blog/how-to-use-ai-in-data-analytics-to-drive-marketing-growth?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting) – A broader look at AI’s role across marketing analytics.

**🎥 Quick Watch**

- [How data democratization will shape marketing in 2025 (Video)](https://www.adverity.com/blog/the-quiet-revolution-how-data-democratization-will-shape-marketing-in-2025?utm_medium=cpc&utm_source=reddit&utm_campaign=Generate%20%7C%20%7CData_Conversations_Community_Targeting)