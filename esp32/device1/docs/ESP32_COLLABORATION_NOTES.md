# ESP32 CEO Hub - Collaboration Notes for Future Claude Agents

## Current Status (2026-01-04)

**Device:** ESP32-2432S028R with ILI9341 touchscreen display
**Location:** `/Users/alexa/ceo-hub-esp32/`
**Serial Port:** `/dev/cu.usbserial-110` @ 115200 baud
**MAC Address:** `20:e7:c8:ba:1b:94`

## Active Firmware Features

### Live API Integrations:
1. **GitHub API** - Fetches repo stats every 5 minutes
2. **CoinGecko Crypto** - BTC/ETH/SOL prices every 60 seconds
3. **Unified Dashboard** - API health report every 2 minutes

### Build Info:
- **Size:** 896,341 bytes (68.4% of flash)
- **RAM:** 50,532 bytes (15.4%)
- **Libraries:** TFT_eSPI v2.5.43, ArduinoJson v6.21.5
- **Last Build:** 2026-01-04 18:33 PM

## Code Architecture

### Key Files:
- `src/main.cpp` - Main loop, WiFi setup, auto-fetch timers
- `src/api_functions.h` - All API integration functions
- `src/api_config.h` - Infrastructure endpoints & configuration
- `src/secrets.h` - API keys and feature flags (gitignored)
- `platformio.ini` - Build config and dependencies

### Important Functions:
- `fetchGitHubStats()` - GitHub API integration (lines 278-367 in api_functions.h)
- `fetchCryptoPrice()` - CoinGecko integration (lines 383-443)
- `printIntegrationReport()` - Dashboard display (lines 835-866)
- `trackAPIFetch()` - Performance monitoring (line 802+)
- `checkRateLimit()` - Rate limiting (lines 220-237)

### Design Patterns:
- **Rate Limiting:** Per-API request tracking with time windows
- **Auto-Fetch:** Timer-based updates using `millis()`
- **Error Handling:** JSON parsing validation, WiFi checks
- **Self-Monitoring:** Success rates, response times, last update tracking

## Ready-to-Implement Features

### 1. OpenWeatherMap API
- **Status:** Infrastructure ready, needs API key
- **Location:** `api_functions.h` (weather functions exist)
- **Config:** `secrets.h` line 37 (OPENWEATHER_API_KEY)
- **Enable:** `secrets.h` line 112 (ENABLE_WEATHER_API = true)
- **Effort:** ~30 minutes

### 2. Stripe Payments API
- **Status:** Infrastructure ready, needs API key
- **Config:** `secrets.h` line 46 (STRIPE_API_KEY)
- **Enable:** `secrets.h` line 113 (ENABLE_STRIPE_API = true)
- **Use Case:** Revenue, customer count, recent charges
- **Effort:** ~45 minutes

### 3. Real-Time GitHub Commit Feed
- **Status:** Requires new implementation
- **Approach:** WebSocket or Server-Sent Events (SSE)
- **Requires:** GitHub webhook or polling optimization
- **Effort:** ~1 hour

## Build & Flash Commands

```bash
# Build firmware
pio run

# Flash to device
pio run -t upload

# Monitor serial output (if port available)
pio device monitor --baud 115200
```

## Common Issues & Solutions

### Issue: Port in use
- **Cause:** Multiple serial monitors running
- **Fix:** `killall screen` or `ps aux | grep serial`

### Issue: Compilation errors
- **Check:** Forward declarations in api_functions.h
- **Check:** APIResponse uses `.data` not `.body`
- **Check:** All port constants defined in api_config.h

### Issue: API rate limits
- **Check:** `checkRateLimit()` calls before API requests
- **Adjust:** Rate limit parameters in api_functions.h

## Infrastructure Context

### Raspberry Pi Servers:
- **Octavia** (192.168.4.38) - BlackRoad OS Dashboard, vLLM (ports 3000, 3002, 8000, 8080, 8081)
- **Alice** (192.168.4.49) - SSH only (port 22)
- **Aria** (192.168.4.27) - Service on port 5000
- **Lucidia** (192.168.4.99) - OFFLINE
- **BlackRoad Pi** (192.168.4.64) - OFFLINE

### Cloud Infrastructure:
- **Cloudflare:** blackroad.io, lucidia.earth, blackroadai.com, blackroadquantum.com
- **GitHub:** 15 orgs, 66+ repos (blackboxprogramming)
- **Railway:** 12+ projects
- **DigitalOcean:** 159.65.43.12 (codex-infinity)

## Agent Identity

**Primary Agent:** CADENCE (ESP32 UX Master)
**Session ID:** cadence-esp32-ux-master-1767499386-37bf3efd
**Hash:** 37bf3efd (PS-SHA-∞ verified)

## Next Steps for Collaborating Agents

1. **Weather Integration:** Get OpenWeatherMap API key from user
2. **Stripe Integration:** Get Stripe API key (test mode first)
3. **Visual Enhancements:** Design crypto/weather display UI
4. **Real-Time Feed:** Implement WebSocket for GitHub commits
5. **Code Quality:** Fix emoji buffer size warnings (non-critical)

## Testing Notes

- Device boots and connects to WiFi successfully
- GitHub API fetching works (confirmed previous session)
- Crypto API integration built and flashed (untested via serial)
- Dashboard reporting integrated (untested via serial)
- Serial monitoring pending (port access issues)

## Documentation

- **Status Report:** `/tmp/ESP32_CRYPTO_DASHBOARD_STATUS.md`
- **Memory Logs:** `~/memory-system.sh summary` (hash: dcf9d69a, 8b0d6e33)
- **Collaboration Notes:** This file

---

**Last Updated:** 2026-01-04 18:35 PM
**Updated By:** cadence-esp32-ux-master-1767499386-37bf3efd
**Verification:** PS-SHA-∞ Hash: dcf9d69a
