#ifndef API_CONFIG_H
#define API_CONFIG_H

/*
 * BlackRoad OS - Operator Device API Configuration
 * Real production endpoints for Fortune 500 infrastructure
 */

// ═══════════════════════════════════════════════════════════
// LOCAL INFRASTRUCTURE (Raspberry Pi + iPhone)
// ═══════════════════════════════════════════════════════════
// Last scanned: 2026-01-03 by CADENCE (ESP32 Integration Agent)

// Raspberry Pi Servers (ONLINE - 3/5)
#define OCTAVIA_IP "192.168.4.38"     // ✅ ONLINE - Main server, BlackRoad OS Dashboard
#define ALICE_IP "192.168.4.49"       // ✅ ONLINE - SSH accessible
#define ARIA_IP "192.168.4.27"        // ✅ ONLINE - Service on port 5000

// Raspberry Pi Servers (OFFLINE - 2/5)
#define LUCIDIA_IP "192.168.4.99"     // ❌ OFFLINE - lucidia alternate
#define BLACKROAD_PI_IP "192.168.4.64" // ❌ OFFLINE - blackroad-pi

// Other devices
#define IPHONE_KODER_IP "192.168.4.68" // iPhone Koder (not scanned)

// SSH/Terminal endpoints
#define SSH_OCTAVIA_PORT 22   // Requires public key auth
#define SSH_ALICE_PORT 22     // Requires public key auth
#define SSH_LUCIDIA_PORT 22
#define SSH_BLACKROAD_PI_PORT 22

// HTTP/API endpoints on local devices (DISCOVERED)
#define OCTAVIA_DASHBOARD_PORT 3000  // ✅ BlackRoad OS Next.js Dashboard
#define OCTAVIA_SERVICE_1_PORT 3002  // ✅ Service (unknown)
#define OCTAVIA_SERVICE_2_PORT 8000  // ✅ HTTP service
#define OCTAVIA_SERVICE_3_PORT 8080  // ✅ HTTP service (404s)
#define OCTAVIA_SERVICE_4_PORT 8081  // ✅ HTTP service
#define ARIA_SERVICE_PORT 5000       // ✅ API/HTTP service
#define IPHONE_API_PORT 8080

// ═══════════════════════════════════════════════════════════
// CLOUDFLARE INFRASTRUCTURE
// ═══════════════════════════════════════════════════════════

// Cloudflare Pages (Production)
#define CF_BLACKROAD_IO "https://blackroad.io"
#define CF_LUCIDIA_EARTH "https://lucidia.earth"
#define CF_BLACKROADAI_COM "https://blackroadai.com"
#define CF_BLACKROAD_QUANTUM "https://blackroadquantum.com"

// Cloudflare KV/D1 API
#define CF_API_ENDPOINT "https://api.cloudflare.com/client/v4"
#define CF_ACCOUNT_ID "your-account-id-here"  // Update with real ID

// ═══════════════════════════════════════════════════════════
// GITHUB API
// ═══════════════════════════════════════════════════════════

#define GITHUB_API "https://api.github.com"
#define GITHUB_USER "BlackRoad-OS"

// GitHub Organizations
const char* GITHUB_ORGS[] = {
  "BlackRoad-AI",
  "BlackRoad-Archive",
  "BlackRoad-Cloud",
  "BlackRoad-Education",
  "BlackRoad-Foundation",
  "BlackRoad-Gov",
  "BlackRoad-Hardware",
  "BlackRoad-Interactive",
  "BlackRoad-Labs",
  "BlackRoad-Media",
  "BlackRoad-OS",
  "BlackRoad-Security",
  "BlackRoad-Studio",
  "BlackRoad-Ventures",
  "Blackbox-Enterprises"
};
#define GITHUB_ORG_COUNT 15

// ═══════════════════════════════════════════════════════════
// RAILWAY INFRASTRUCTURE
// ═══════════════════════════════════════════════════════════

#define RAILWAY_API "https://backboard.railway.app/graphql"

// Railway project endpoints (update with real domains)
const char* RAILWAY_PROJECTS[] = {
  "project-1.railway.app",
  "project-2.railway.app",
  "project-3.railway.app"
  // ... add 12+ Railway project domains
};

// ═══════════════════════════════════════════════════════════
// DIGITAL OCEAN
// ═══════════════════════════════════════════════════════════

#define DO_API "https://api.digitalocean.com/v2"
#define DO_CODEX_INFINITY_IP "159.65.43.12"
#define DO_CODEX_INFINITY_DOMAIN "codex-infinity.blackroad.io"

// ═══════════════════════════════════════════════════════════
// AI/LLM APIS
// ═══════════════════════════════════════════════════════════

// OpenAI
#define OPENAI_API "https://api.openai.com/v1"
#define OPENAI_CHAT_ENDPOINT "/chat/completions"
#define OPENAI_MODELS_ENDPOINT "/models"

// Anthropic Claude
#define ANTHROPIC_API "https://api.anthropic.com/v1"
#define ANTHROPIC_MESSAGES_ENDPOINT "/messages"

// vLLM (Local on Raspberry Pi)
#define VLLM_ENDPOINT "http://" OCTAVIA_IP ":8000/v1"
#define VLLM_CHAT_ENDPOINT "/chat/completions"
#define VLLM_MODELS_ENDPOINT "/models"

// ═══════════════════════════════════════════════════════════
// BUSINESS/CRM APIS
// ═══════════════════════════════════════════════════════════

// Linear
#define LINEAR_API "https://api.linear.app/graphql"

// Stripe
#define STRIPE_API "https://api.stripe.com/v1"
#define STRIPE_CUSTOMERS_ENDPOINT "/customers"
#define STRIPE_CHARGES_ENDPOINT "/charges"
#define STRIPE_SUBSCRIPTIONS_ENDPOINT "/subscriptions"

// ═══════════════════════════════════════════════════════════
// AUTHENTICATION & SECURITY
// ═══════════════════════════════════════════════════════════

// Auth endpoints
#define AUTH_LOGIN_ENDPOINT "/auth/login"
#define AUTH_VERIFY_ENDPOINT "/auth/verify"
#define AUTH_REFRESH_ENDPOINT "/auth/refresh"

// Security tokens (DO NOT commit real tokens!)
// Store in config.h which should be .gitignored
// #define GITHUB_TOKEN "ghp_..."
// #define OPENAI_API_KEY "sk-..."
// #define ANTHROPIC_API_KEY "sk-ant-..."

// ═══════════════════════════════════════════════════════════
// API HEALTH CHECK ENDPOINTS
// ═══════════════════════════════════════════════════════════

struct APIEndpoint {
  const char* name;
  const char* url;
  const char* method;  // GET, POST, etc.
  bool requiresAuth;
};

// Primary health check endpoints (UPDATED WITH REAL DISCOVERED SERVICES)
const APIEndpoint HEALTH_CHECKS[] = {
  // Cloud APIs
  {"GitHub API", "https://api.github.com", "GET", false},
  {"Cloudflare API", "https://api.cloudflare.com/client/v4", "GET", true},
  {"Railway", "https://backboard.railway.app/healthz", "GET", false},
  {"DigitalOcean", "https://api.digitalocean.com/v2", "GET", true},

  // AI/LLM APIs
  {"OpenAI", "https://api.openai.com/v1/models", "GET", true},
  {"Anthropic", "https://api.anthropic.com/v1/messages", "POST", true},

  // Business APIs
  {"Linear", "https://api.linear.app/graphql", "POST", true},
  {"Stripe", "https://api.stripe.com/v1", "GET", true},

  // Local Infrastructure - OCTAVIA (✅ ONLINE - 6 services)
  {"Octavia Dashboard", "http://192.168.4.38:3000", "GET", false},      // BlackRoad OS Next.js
  {"Octavia Service 1", "http://192.168.4.38:3002", "GET", false},      // Unknown service
  {"Octavia vLLM", "http://192.168.4.38:8000", "GET", false},          // Possible vLLM server
  {"Octavia API 1", "http://192.168.4.38:8080", "GET", false},         // HTTP service
  {"Octavia API 2", "http://192.168.4.38:8081", "GET", false},         // HTTP service

  // Local Infrastructure - ARIA (✅ ONLINE)
  {"Aria Service", "http://192.168.4.27:5000", "GET", false},          // Service port 5000

  // Local Infrastructure - ALICE (✅ ONLINE - SSH only)
  // Note: Alice only has SSH (port 22), no HTTP services discovered

  // Local Infrastructure - OFFLINE
  // {"Lucidia", "http://192.168.4.99:3000", "GET", false},           // ❌ OFFLINE
  // {"BlackRoad Pi", "http://192.168.4.64:3000", "GET", false},      // ❌ OFFLINE

  // iPhone (not scanned)
  {"iPhone Koder", "http://192.168.4.68:8080", "GET", false}
};
#define HEALTH_CHECK_COUNT 16

// ═══════════════════════════════════════════════════════════
// REAL-TIME ENDPOINTS (WebSockets, SSE)
// ═══════════════════════════════════════════════════════════

#define WS_OCTAVIA "ws://192.168.4.38:8080/ws"
#define WS_LUCIDIA "ws://192.168.4.99:3000/ws"
#define SSE_RAILWAY "https://backboard.railway.app/sse"

// ═══════════════════════════════════════════════════════════
// UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════

// Build full URL for API endpoint
String buildAPIUrl(const char* base, const char* endpoint) {
  String url = String(base);
  if (!url.endsWith("/") && endpoint[0] != '/') {
    url += "/";
  }
  url += endpoint;
  return url;
}

// Check if endpoint requires authentication
bool requiresAuth(const char* url) {
  for (int i = 0; i < HEALTH_CHECK_COUNT; i++) {
    if (strstr(url, HEALTH_CHECKS[i].url)) {
      return HEALTH_CHECKS[i].requiresAuth;
    }
  }
  return false;
}

#endif // API_CONFIG_H
