# ESP32 CEO Hub - Device 1

**Production-Grade IoT Operator Device for BlackRoad OS**

## Device Specifications

- **Model:** ESP32-2432S028R (ESP32-D0WD-V3)
- **Display:** 2.4" ILI9341 TFT (240x320 pixels)
- **Touch:** Resistive touchscreen
- **WiFi:** 802.11 b/g/n
- **MAC Address:** 20:e7:c8:ba:1b:94
- **Flash:** 1,310,720 bytes (896,341 bytes used - 68.4%)
- **RAM:** 327,680 bytes (50,532 bytes used - 15.4%)

## Features

### 🔌 Live API Integrations
- **GitHub** - Real-time repository stats, commit counts, issue tracking
- **CoinGecko Crypto** - Live BTC/ETH/SOL prices with 24h changes
- **Unified Dashboard** - Comprehensive API status reporting every 2 minutes

### 📱 Applications
1. **AI Inference** - Real-time ML metrics dashboard
2. **VPN Monitor** - Network bandwidth and connection status
3. **CRM Pipeline** - Sales pipeline and customer metrics
4. **Messages** - Notification center for all communications
5. **GitHub** - Repository analytics and commit activity
6. **Crypto** - Live cryptocurrency price tracking

### 🎯 Navigation System
- **Bottom Navigation Bar** (available on all app screens)
  - **LEFT Button** (x: 10-80, y: 278-313) - BACK/HOME navigation
  - **RIGHT Button** (x: 160-230, y: 278-313) - RECENT APPS switcher
- **Navigation History** - Stack-based history (max 10 screens)
- **Touch Gestures** - Tap anywhere to launch apps from home

## Build & Flash

### Prerequisites
```bash
# Install PlatformIO
pip3 install platformio

# Install required libraries (auto-installed via platformio.ini)
# - TFT_eSPI@^2.5.43
# - ArduinoJson@^6.21.3
```

### Build Commands
```bash
cd /Users/alexa/ceo-hub-esp32

# Build firmware
pio run

# Upload to device
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
```

### Quick Flash
```bash
# All-in-one: build + upload + monitor
pio run -t upload && pio device monitor
```

## Configuration

### WiFi Setup
Edit `src/secrets.h`:
```cpp
#define WIFI_SSID "your-network-name"
#define WIFI_PASSWORD "your-password"
```

### API Keys
**GitHub API** (Optional - higher rate limits):
```cpp
#define GITHUB_TOKEN "ghp_your_token_here"
```

**Weather API** (Not yet enabled - needs OpenWeatherMap key):
```cpp
#define OPENWEATHER_API_KEY "your_key_here"
#define ENABLE_WEATHER_API true
```

**Stripe API** (Not yet enabled):
```cpp
#define STRIPE_API_KEY "sk_test_your_key_here"
#define ENABLE_STRIPE_API true
```

### API Feature Flags
```cpp
#define ENABLE_GITHUB_API true   // ✅ ACTIVE
#define ENABLE_CRYPTO_API true   // ✅ ACTIVE
#define ENABLE_WEATHER_API false // ⏳ READY (needs API key)
#define ENABLE_STRIPE_API false  // ⏳ READY (needs API key)
```

## Auto-Fetch System

The device automatically refreshes data:
- **GitHub Stats:** Every 5 minutes (300s)
- **Crypto Prices:** Every 60 seconds
- **API Dashboard:** Every 2 minutes (120s)

All updates run in the background without blocking the UI.

## Serial Output

Connect at **115200 baud** to see:
- WiFi connection status
- API request/response logs
- Touch event coordinates
- Navigation state changes
- Auto-fetch updates
- Performance metrics

### Example Output
```
✅ Connected to WiFi: YourNetwork
🔄 Auto-fetching crypto prices...
💰 Fetching crypto prices...
✅ Crypto: BTC $45,234.56 (+2.34%), ETH $2,876.23 (-1.12%), SOL $98.45 (+5.67%)

📊 Printing API Status Dashboard...
┌─────────────────────────────────────────────────────────────┐
│         BLACKROAD OS - OPERATOR DEVICE                      │
│         API INTEGRATION REPORT                              │
└─────────────────────────────────────────────────────────────┘

API #0: GitHub           🟢 ACTIVE   | Requests: 24 | Success: 100% | Avg: 234ms | Last: 45s ago
API #1: OpenAI           ⚪ SETUP    | Requests: 0  | Success: N/A  | Avg: N/A   | Last: Never
API #2: Crypto (CoinGecko)🟢 ACTIVE | Requests: 56 | Success: 98%  | Avg: 187ms | Last: 12s ago
```

## Documentation

- **[Build Status & Features](docs/ESP32_CRYPTO_DASHBOARD_STATUS.md)** - Complete integration status
- **[Navigation Guide](docs/ESP32_NAVIGATION_GUIDE.md)** - How to use bottom nav bar
- **[Collaboration Notes](docs/ESP32_COLLABORATION_NOTES.md)** - Architecture for Claude agents

## Troubleshooting

### Device Not Responding
1. Check serial output for errors
2. Verify WiFi credentials in `secrets.h`
3. Press physical RESET button on ESP32 board
4. Re-flash firmware: `pio run -t upload`

### Navigation Stuck
- Tap **LEFT button** (bottom-left corner) to go BACK or HOME
- If frozen, press physical RESET button

### API Errors
- Check WiFi connection (device auto-reconnects)
- Verify API keys in `secrets.h` (GitHub, Weather, Stripe)
- Check serial output for HTTP status codes
- Rate limits: GitHub 60/hr, Crypto 50/min

### Build Errors
```bash
# Clean build
pio run -t clean

# Re-install libraries
pio lib install
```

## Production Quality Features

✅ **Rate Limiting** - Per-API request tracking with time windows
✅ **Error Handling** - JSON parse validation, HTTP status checks
✅ **Self-Monitoring** - Automatic performance metrics tracking
✅ **Memory Efficient** - DynamicJsonDocument with proper sizing
✅ **Network Resilient** - WiFi reconnection + connection checks
✅ **Non-Blocking** - Timer-based updates using `millis()`
✅ **Production Logging** - Comprehensive serial output for debugging

## Next Steps

### Ready to Implement (Infrastructure Complete)
1. **Weather API** - Just needs OpenWeatherMap API key (~30 min)
2. **Stripe API** - Needs Stripe key, will show revenue/customers (~45 min)
3. **Real-time Visualizations** - Display crypto/weather/GitHub on screen (~1 hour)
4. **GitHub WebSocket** - Live commit feed via SSE/WebSocket (~1 hour)

## GitHub Repository

**Location:** https://github.com/BlackRoad-OS/blackroad-os-iot-devices/tree/main/esp32/device1

**Verification:** cadence-esp32-ux-master-1767499386-37bf3efd
**Build Hash:** 896341 bytes @ 2026-01-04T18:33:00Z

---

**Last Updated:** 2026-01-04
**Agent:** CADENCE (ESP32 UX Master)
**Session:** cadence-esp32-ux-master-1767499386-37bf3efd
