{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "earc://schemas/kernel_spec_v1.json",
  "title": "eArc Kernel Spec v1",
  "type": "object",
  "required": ["spec", "kernel", "mode", "principles", "analysis", "metrika", "communication", "canon", "statement"],
  "additionalProperties": false,
  "properties": {
    "spec": {
      "type": "object",
      "required": ["version"],
      "additionalProperties": false,
      "properties": {
        "version": { "type": "string", "pattern": "^[0-9]+\\.[0-9]+$" }
      }
    },
    "kernel": {
      "type": "object",
      "required": ["id", "name", "type", "state"],
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string", "minLength": 3, "maxLength": 128 },
        "name": { "type": "string", "minLength": 1, "maxLength": 128 },
        "type": { "type": "string", "enum": ["monolith"] },
        "state": { "type": "string", "enum": ["dev", "arch", "canonical"] },
        "symbol": { "type": "string", "maxLength": 8 }
      }
    },
    "mode": {
      "type": "object",
      "required": ["current", "dualsystem"],
      "additionalProperties": false,
      "properties": {
        "current": { "type": "string", "enum": ["DEV", "ARCH", "HOLD"] },
        "dualsystem": {
          "type": "object",
          "required": ["DEV", "ARCH"],
          "additionalProperties": false,
          "properties": {
            "DEV": { "type": "string" },
            "ARCH": { "type": "string" }
          }
        }
      }
    },
    "principles": {
      "type": "array",
      "minItems": 1,
      "items": {
        "type": "string",
        "enum": [
          "order_before_content",
          "archive_before_action",
          "perception_before_reaction",
          "memory_before_optimization",
          "limitation_before_expansion",
          "silence_is_valid_signal",
          "display_never_drives_action"
        ]
      }
    },
    "analysis": {
      "type": "object",
      "required": ["pasa", "scope", "automation"],
      "additionalProperties": false,
      "properties": {
        "pasa": { "type": "string", "enum": ["enabled", "disabled"] },
        "scope": {
          "type": "array",
          "items": { "type": "string", "enum": ["patterns", "drift", "stability", "actions", "non_actions"] }
        },
        "automation": { "type": "string", "enum": ["none"] }
      }
    },
    "metrika": {
      "type": "object",
      "required": ["role", "policy", "feedback_loop"],
      "additionalProperties": false,
      "properties": {
        "role": { "type": "string", "enum": ["memory"] },
        "policy": { "type": "string", "enum": ["append_only"] },
        "feedback_loop": { "type": "string", "enum": ["disabled"] }
      }
    },
    "communication": {
      "type": "object",
      "required": ["default", "transmit", "read", "activation"],
      "additionalProperties": false,
      "properties": {
        "default": { "type": "string", "enum": ["OFF", "ON"] },
        "transmit": { "type": "string", "enum": ["OFF", "ON"] },
        "read": { "type": "string", "enum": ["OFF", "ON"] },
        "activation": { "type": "string", "enum": ["explicit_only"] }
      }
    },
    "canon": {
      "type": "object",
      "required": ["status", "mutability"],
      "additionalProperties": false,
      "properties": {
        "status": { "type": "string", "enum": ["active", "inactive"] },
        "mutability": { "type": "string", "enum": ["frozen", "mutable"] }
      }
    },
    "statement": { "type": "string", "minLength": 1 }
  }
}