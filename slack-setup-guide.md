# BlackRoad OS Inc - Slack Setup Guide

**Workspace:** blackroadosinc.slack.com
**Invite Link:** https://join.slack.com/t/blackroadosinc/shared_invite/zt-3metl392t-67XGU1HBgh3PN2CXHK9PgQ

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Step 1: Join the Workspace

1. Click the invite link above
2. Sign in with amundsonalexa@gmail.com or blackroad.systems@gmail.com
3. Complete the workspace setup

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Step 2: Create Channels

Once you're in the workspace, create these channels:

### Core Operations
- **#general** - Already exists (default)
- **#dev** - `/create #dev` - Development discussions
- **#infrastructure** - Infrastructure & deployment updates
- **#alerts** - Automated system alerts

### API & Services  
- **#ollama-ai** - AI model updates & metrics
- **#headscale-vpn** - VPN connection status
- **#espocrm** - CRM deals & pipeline updates
- **#dashboard** - Dashboard notifications

### Devices
- **#esp32-updates** - ESP32 device status & logs
- **#raspberry-pi** - Raspberry Pi server updates

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Step 3: Install Apps

Go to https://blackroadosinc.slack.com/apps and install:

### 1. GitHub App
- Search for "GitHub"
- Click "Add to Slack"
- Connect to BlackRoad-OS organization
- Subscribe to notifications:
  - `/github subscribe BlackRoad-OS/blackroad-os-iot-devices commits:all`
  - `/github subscribe BlackRoad-OS/blackroad-os-brand commits:all`

### 2. Incoming Webhooks
- Search for "Incoming Webhooks"
- Click "Add to Slack"
- Create webhooks for each channel:
  - #esp32-updates
  - #raspberry-pi
  - #ollama-ai
  - #infrastructure
  - #alerts

**Save the webhook URLs!** You'll need them for integrations.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Step 4: Set Up Webhooks (After Step 3)

Once you have webhook URLs, test them:

### Test ESP32 Webhook
```bash
curl -X POST https://hooks.slack.com/services/YOUR/WEBHOOK/URL \
  -H 'Content-type: application/json' \
  -d '{
    "text": "🤖 ESP32 OTA Bootloader deployed successfully!",
    "username": "ESP32 Bot",
    "icon_emoji": ":robot_face:"
  }'
```

### Test Infrastructure Webhook
```bash
curl -X POST https://hooks.slack.com/services/YOUR/WEBHOOK/URL \
  -H 'Content-type: application/json' \
  -d '{
    "text": "✅ Ollama AI deployed on Octavia (192.168.4.38:11434)",
    "username": "Infrastructure Bot",
    "icon_emoji": ":gear:"
  }'
```

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Step 5: Configure Notifications (Optional)

### Slash Commands
Create custom slash commands:
- `/esp32-status` - Check ESP32 device status
- `/deploy` - Trigger deployments
- `/infra-status` - Check infrastructure health

### Bots
- Name suggestions: "BlackRoad Bot", "Infrastructure Bot", "ESP32 Bot"
- Set profile pictures with BlackRoad branding

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Integration Examples

### ESP32 Status Update
When ESP32 connects to WiFi, send:
```json
{
  "channel": "#esp32-updates",
  "text": "ESP32 Connected!",
  "attachments": [{
    "color": "good",
    "fields": [
      {"title": "IP Address", "value": "192.168.4.xxx", "short": true},
      {"title": "Hostname", "value": "esp32-blackroad-ceo", "short": true},
      {"title": "Firmware", "value": "BlackRoad OS v1.0", "short": true},
      {"title": "Status", "value": "✅ Online", "short": true}
    ]
  }]
}
```

### Ollama AI Update
```json
{
  "channel": "#ollama-ai",
  "text": "AI Model Ready",
  "attachments": [{
    "color": "#2979FF",
    "fields": [
      {"title": "Model", "value": "Qwen2.5:7B", "short": true},
      {"title": "Speed", "value": "150 tokens/sec", "short": true},
      {"title": "Server", "value": "octavia:11434", "short": true},
      {"title": "Status", "value": "✅ Running", "short": true}
    ]
  }]
}
```

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Quick Start Checklist

- [ ] Join workspace via invite link
- [ ] Create channels (#dev, #infrastructure, #alerts, etc.)
- [ ] Install GitHub app
- [ ] Install Incoming Webhooks app  
- [ ] Create webhook for #esp32-updates
- [ ] Create webhook for #infrastructure
- [ ] Test webhooks with curl commands
- [ ] Invite team members (if any)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

**Next:** Once webhooks are set up, I can integrate them into:
- ESP32 firmware (send status updates when device boots)
- Infrastructure monitoring scripts
- GitHub Actions (deployment notifications)
- Raspberry Pi health checks

Let me know when you have the webhook URLs!
