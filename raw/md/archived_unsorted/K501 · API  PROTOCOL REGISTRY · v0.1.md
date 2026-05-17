# K501 · API / PROTOCOL REGISTRY · v0.1
Mode: REFERENCE_ONLY · APPEND_ONLY
Scope: Verified Public Interfaces + Phantom Audit
Last Audit: 2026-02-23

────────────────────────────────────────────────────────

- name: OpenAI API
  family: LLM Platform
  transport: HTTPS
  protocol: REST + Streaming + Realtime
  payload: JSON
  auth: API Key
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://developers.openai.com/api/reference/overview/
    - https://developers.openai.com/api/reference/
    - https://developers.openai.com/api/docs/quickstart/

────────────────────────────────────────────────────────

- name: Google Gemini API
  family: LLM Platform
  transport: HTTPS
  protocol: REST + Streaming + Realtime
  payload: JSON
  auth: Google API credentials
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://ai.google.dev/api
    - https://ai.google.dev/api/all-methods

────────────────────────────────────────────────────────

- name: GitHub REST API
  family: Developer Platform
  transport: HTTPS
  protocol: REST (versioned)
  payload: JSON
  auth: Bearer token (PAT / OAuth / GitHub App)
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://docs.github.com/en/rest
    - https://docs.github.com/en/rest/about-the-rest-api/api-versions
    - https://docs.github.com/rest/authentication/authenticating-to-the-rest-api

────────────────────────────────────────────────────────

- name: GitHub GraphQL API
  family: Developer Platform
  transport: HTTPS
  protocol: GraphQL
  payload: JSON
  auth: Bearer token
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://docs.github.com/en/graphql/guides/forming-calls-with-graphql
    - https://api.github.com/graphql

────────────────────────────────────────────────────────

- name: DuckDuckGo Instant Answer API
  family: Search / Knowledge
  transport: HTTPS
  protocol: REST (Instant Answer only)
  payload: JSON
  auth: none (public endpoint)
  official_status: OFFICIAL_LIMITED
  risk_flags:
    - not full search API
    - limited data scope
  urls:
    - https://www.postman.com/api-evangelist/search/documentation/bdkqiym/duckduckgo-instant-answer-api

────────────────────────────────────────────────────────

- name: Duck.ai API
  family: AI Chat
  transport: UNKNOWN
  protocol: UNKNOWN
  payload: UNKNOWN
  auth: UNKNOWN
  official_status: NOT_AVAILABLE
  risk_flags:
    - no official public API
    - product UI only
  urls:
    - https://duckduckgo.com/duckduckgo-help-pages/duckai/

────────────────────────────────────────────────────────

- name: Duck.ai OpenAI-compatible wrappers
  family: AI Chat (third-party)
  transport: HTTPS (varies)
  protocol: OpenAI-compatible (unofficial)
  payload: JSON
  auth: varies
  official_status: THIRD_PARTY
  risk_flags:
    - unofficial proxy
    - not endorsed by DuckDuckGo
    - stability uncertain
  urls:
    - https://github.com/dhiaaeddine16/duckduckgo-ai-openai-api

────────────────────────────────────────────────────────

- name: Chrome Extensions API
  family: Browser Platform
  transport: internal (browser JS)
  protocol: Chrome Extension Messaging
  payload: structured JS objects
  auth: extension permissions model
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://developer.chrome.com/docs/extensions/reference/api

────────────────────────────────────────────────────────

- name: Chrome Native Messaging
  family: Browser ↔ Local Bridge
  transport: stdio (IPC)
  protocol: Native Messaging host protocol
  payload: JSON messages
  auth: host manifest + extension permissions
  official_status: OFFICIAL
  risk_flags:
    - local host dependency
  urls:
    - https://developer.chrome.com/docs/extensions/develop/concepts/native-messaging

────────────────────────────────────────────────────────

- name: Chrome DevTools Protocol (CDP)
  family: Browser Instrumentation
  transport: WebSocket (typical)
  protocol: DevTools Protocol
  payload: JSON
  auth: debugger / remote debugging context
  official_status: OFFICIAL
  risk_flags:
    - debugging surface
  urls:
    - https://chromedevtools.github.io/devtools-protocol/

────────────────────────────────────────────────────────

- name: Chrome Web Store Publish API
  family: Distribution / Store
  transport: HTTPS
  protocol: REST
  payload: JSON
  auth: OAuth / Google credentials
  official_status: OFFICIAL
  risk_flags: none
  urls:
    - https://developer.chrome.com/docs/webstore/api

────────────────────────────────────────────────────────

- name: Chrome Management API
  family: Enterprise Management
  transport: HTTPS
  protocol: REST
  payload: JSON
  auth: Google enterprise credentials
  official_status: OFFICIAL
  risk_flags:
    - enterprise scope required
  urls:
    - https://developers.google.com/chrome/management

────────────────────────────────────────────────────────

END OF REGISTRY
Status: CANONICAL BASELINE · PHANTOM AUDIT COMPLETE