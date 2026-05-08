{
  "name": "k501_simulate_run",
  "description": "Simulate a SoftK501Dev run from a compiled K501 spec. No filesystem required; uses an optional virtual file index.",
  "parameters": {
    "type": "object",
    "required": ["spec"],
    "properties": {
      "spec": { "type": "object", "description": "Normalized K501 spec (output of k501_compile)." },
      "virtual_files": {
        "type": "array",
        "description": "Optional virtual file listing for mobile/no-terminal environments.",
        "items": {
          "type": "object",
          "required": ["path", "size"],
          "properties": {
            "path": { "type": "string" },
            "size": { "type": "integer" },
            "mtime": { "type": "string" },
            "type": { "type": "string" },
            "content_preview": { "type": "string" }
          }
        }
      }
    }
  }
}