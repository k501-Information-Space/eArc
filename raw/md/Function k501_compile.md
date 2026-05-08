{
  "name": "k501_compile",
  "description": "Compile and validate a K501 DSL document into a normalized K501 spec.",
  "parameters": {
    "type": "object",
    "required": ["dsl"],
    "properties": {
      "dsl": { "type": "string", "description": "K501 DSL as YAML or JSON text." }
    }
  }
}