#ifndef PREMIUM_UI_H
#define PREMIUM_UI_H

/*
 * ═══════════════════════════════════════════════════════════════════════
 * BLACKROAD PREMIUM UI SYSTEM
 * ═══════════════════════════════════════════════════════════════════════
 *
 * Advanced visual effects for ESP32 CEO Hub:
 * - Vertical gradients
 * - Glow effects with soft edges
 * - Glass-morphism cards
 * - Animated pulse effects
 * - Premium shadows with depth
 * - Golden Ratio spacing
 */

#include <TFT_eSPI.h>

// ─────────────────────────────────────────────────────────────────────
// COLOR UTILITIES
// ─────────────────────────────────────────────────────────────────────

// Blend two RGB565 colors with alpha (0-255)
uint16_t blendColor(uint16_t fg, uint16_t bg, uint8_t alpha) {
  uint8_t fgR = (fg >> 11) & 0x1F;
  uint8_t fgG = (fg >> 5) & 0x3F;
  uint8_t fgB = fg & 0x1F;

  uint8_t bgR = (bg >> 11) & 0x1F;
  uint8_t bgG = (bg >> 5) & 0x3F;
  uint8_t bgB = bg & 0x1F;

  uint8_t r = ((fgR * alpha) + (bgR * (255 - alpha))) / 255;
  uint8_t g = ((fgG * alpha) + (bgG * (255 - alpha))) / 255;
  uint8_t b = ((fgB * alpha) + (bgB * (255 - alpha))) / 255;

  return (r << 11) | (g << 5) | b;
}

// Darken a color by percentage (0-100)
uint16_t darkenColor(uint16_t color, uint8_t percent) {
  uint8_t r = ((color >> 11) & 0x1F) * (100 - percent) / 100;
  uint8_t g = ((color >> 5) & 0x3F) * (100 - percent) / 100;
  uint8_t b = (color & 0x1F) * (100 - percent) / 100;
  return (r << 11) | (g << 5) | b;
}

// Lighten a color by percentage (0-100)
uint16_t lightenColor(uint16_t color, uint8_t percent) {
  uint8_t r = ((color >> 11) & 0x1F);
  uint8_t g = ((color >> 5) & 0x3F);
  uint8_t b = (color & 0x1F);

  r = r + ((31 - r) * percent / 100);
  g = g + ((63 - g) * percent / 100);
  b = b + ((31 - b) * percent / 100);

  return (r << 11) | (g << 5) | b;
}

// ─────────────────────────────────────────────────────────────────────
// GRADIENT EFFECTS
// ─────────────────────────────────────────────────────────────────────

// Draw vertical gradient (top to bottom)
void drawVerticalGradient(TFT_eSPI &tft, int x, int y, int w, int h,
                          uint16_t colorTop, uint16_t colorBottom) {
  for (int i = 0; i < h; i++) {
    uint16_t color = blendColor(colorBottom, colorTop, (i * 255) / h);
    tft.drawFastHLine(x, y + i, w, color);
  }
}

// Draw radial gradient (center glow)
void drawRadialGlow(TFT_eSPI &tft, int cx, int cy, int radius, uint16_t color) {
  for (int r = radius; r > 0; r -= 2) {
    uint8_t alpha = (r * 60) / radius;  // Fade from center
    uint16_t glowColor = blendColor(color, COLOR_BLACK, alpha);
    tft.drawCircle(cx, cy, r, glowColor);
  }
}

// Premium screen background with subtle gradient
void drawPremiumBackground(TFT_eSPI &tft) {
  // Dark gradient from top (slightly lighter) to bottom (pure black)
  uint16_t topColor = 0x0841;  // Very dark gray
  drawVerticalGradient(tft, 0, 0, 240, 320, topColor, COLOR_BLACK);
}

// ─────────────────────────────────────────────────────────────────────
// GLOW EFFECTS
// ─────────────────────────────────────────────────────────────────────

// Draw soft glow circle (for icons)
void drawIconGlow(TFT_eSPI &tft, int cx, int cy, int radius, uint16_t color) {
  // Outer glow rings (3 layers)
  for (int i = 3; i >= 1; i--) {
    uint16_t glowColor = darkenColor(color, 60 + (i * 10));
    tft.drawCircle(cx, cy, radius + i * 2, glowColor);
  }
}

// Draw pulsing glow effect (call with millis() for animation)
void drawPulsingGlow(TFT_eSPI &tft, int cx, int cy, int baseRadius,
                     uint16_t color, unsigned long time) {
  // Pulse between 0.9x and 1.1x radius
  float pulse = 1.0 + 0.1 * sin(time / 300.0);
  int radius = (int)(baseRadius * pulse);

  // Draw expanding rings
  for (int i = 0; i < 4; i++) {
    uint8_t alpha = 80 - (i * 20);
    uint16_t ringColor = blendColor(color, COLOR_BLACK, alpha);
    tft.drawCircle(cx, cy, radius + i * 3, ringColor);
  }
}

// ─────────────────────────────────────────────────────────────────────
// GLASS-MORPHISM CARDS
// ─────────────────────────────────────────────────────────────────────

// Draw frosted glass card with border glow
void drawGlassCard(TFT_eSPI &tft, int x, int y, int w, int h,
                   uint16_t accentColor) {
  // Outer glow (2px)
  uint16_t glowColor = darkenColor(accentColor, 70);
  tft.drawRoundRect(x - 1, y - 1, w + 2, h + 2, 10, glowColor);

  // Card background (semi-transparent dark)
  uint16_t cardBg = 0x1082;  // Dark with slight transparency effect
  tft.fillRoundRect(x, y, w, h, 8, cardBg);

  // Top highlight (glass reflection)
  uint16_t highlight = 0x2104;
  tft.drawFastHLine(x + 8, y + 1, w - 16, highlight);

  // Accent border (thin, colored)
  tft.drawRoundRect(x, y, w, h, 8, darkenColor(accentColor, 40));

  // Inner shadow (bottom-right)
  tft.drawFastHLine(x + 8, y + h - 2, w - 16, 0x0000);
}

// Premium card with gradient fill
void drawPremiumCard(TFT_eSPI &tft, int x, int y, int w, int h,
                     uint16_t color, bool selected = false) {
  // Shadow layers (depth effect)
  tft.fillRoundRect(x + 4, y + 4, w, h, 8, 0x0000);  // Deep shadow
  tft.fillRoundRect(x + 2, y + 2, w, h, 8, 0x0841);  // Mid shadow

  // Card gradient fill
  uint16_t topColor = lightenColor(color, 20);
  uint16_t bottomColor = darkenColor(color, 30);

  for (int i = 0; i < h; i++) {
    uint16_t lineColor = blendColor(bottomColor, topColor, (i * 255) / h);
    int cornerRadius = 8;
    int lineY = y + i;

    // Simple approximation for rounded corners
    if (i < cornerRadius || i > h - cornerRadius) {
      int inset = (i < cornerRadius) ? (cornerRadius - i) : (i - (h - cornerRadius));
      inset = inset * inset / cornerRadius;  // Curved inset
      tft.drawFastHLine(x + inset, lineY, w - inset * 2, lineColor);
    } else {
      tft.drawFastHLine(x, lineY, w, lineColor);
    }
  }

  // Highlight edge (top)
  tft.drawFastHLine(x + 10, y + 1, w - 20, lightenColor(color, 40));

  // Selection glow
  if (selected) {
    tft.drawRoundRect(x - 2, y - 2, w + 4, h + 4, 10, COLOR_HOT_PINK);
    tft.drawRoundRect(x - 1, y - 1, w + 2, h + 2, 9, COLOR_HOT_PINK);
  }
}

// ─────────────────────────────────────────────────────────────────────
// PREMIUM APP ICONS
// ─────────────────────────────────────────────────────────────────────

// Draw premium app icon with glow and gradient
void drawPremiumAppIcon(TFT_eSPI &tft, int cx, int cy, int radius,
                        uint16_t color, const char* label, int badge = 0,
                        bool pressed = false) {
  // Glow effect (behind icon)
  if (!pressed) {
    drawIconGlow(tft, cx, cy, radius, color);
  }

  // Shadow
  tft.fillCircle(cx + 2, cy + 2, radius, 0x0000);

  // Icon fill with gradient effect
  uint16_t topColor = pressed ? darkenColor(color, 20) : lightenColor(color, 15);
  uint16_t bottomColor = pressed ? darkenColor(color, 40) : darkenColor(color, 20);

  // Draw gradient circle (approximation with rings)
  for (int r = radius; r > 0; r--) {
    int progress = ((radius - r) * 255) / radius;
    uint16_t ringColor = blendColor(bottomColor, topColor, progress);
    tft.drawCircle(cx, cy, r, ringColor);
  }
  tft.fillCircle(cx, cy, radius - 1, blendColor(topColor, bottomColor, 128));

  // Highlight arc (top reflection)
  if (!pressed) {
    uint16_t highlightColor = lightenColor(color, 50);
    for (int i = -45; i <= 45; i += 5) {
      float angle = i * 3.14159 / 180.0;
      int hx = cx + (radius - 4) * sin(angle);
      int hy = cy - (radius - 4) * cos(angle);
      tft.drawPixel(hx, hy, highlightColor);
    }
  }

  // Outer ring
  tft.drawCircle(cx, cy, radius, pressed ? COLOR_WHITE : darkenColor(color, 10));

  // Label
  tft.setTextColor(pressed ? color : COLOR_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(label, cx, cy, 2);

  // Notification badge
  if (badge > 0) {
    int bx = cx + radius - 6;
    int by = cy - radius + 6;

    // Badge glow
    tft.fillCircle(bx, by, 10, darkenColor(COLOR_HOT_PINK, 50));
    tft.fillCircle(bx, by, 8, COLOR_HOT_PINK);

    // Badge text
    tft.setTextColor(COLOR_WHITE);
    tft.setTextDatum(MC_DATUM);
    if (badge > 99) {
      tft.drawString("99+", bx, by, 1);
    } else {
      tft.drawString(String(badge), bx, by, 1);
    }
  }
}

// ─────────────────────────────────────────────────────────────────────
// PREMIUM LOCK SCREEN
// ─────────────────────────────────────────────────────────────────────

// Draw animated lock screen with premium effects
void drawPremiumLockScreen(TFT_eSPI &tft, unsigned long time,
                           const char* timeStr, const char* dateStr) {
  // Background gradient (dark blue to black)
  uint16_t topColor = 0x0010;  // Very dark blue
  drawVerticalGradient(tft, 0, 0, 240, 320, topColor, COLOR_BLACK);

  // Ambient glow orbs (animated positions)
  float t = time / 5000.0;

  // Pink orb (top right area)
  int orb1X = 180 + 20 * sin(t);
  int orb1Y = 80 + 15 * cos(t * 0.7);
  drawRadialGlow(tft, orb1X, orb1Y, 40, darkenColor(COLOR_HOT_PINK, 70));

  // Blue orb (bottom left area)
  int orb2X = 60 + 15 * sin(t * 0.5 + 2);
  int orb2Y = 240 + 20 * cos(t * 0.8);
  drawRadialGlow(tft, orb2X, orb2Y, 50, darkenColor(COLOR_CYBER_BLUE, 75));

  // Time display with glow
  tft.setTextDatum(MC_DATUM);

  // Time glow (behind text)
  tft.setTextColor(darkenColor(COLOR_WHITE, 80));
  tft.drawString(timeStr, 121, 101, 7);
  tft.drawString(timeStr, 119, 99, 7);

  // Time text
  tft.setTextColor(COLOR_WHITE);
  tft.drawString(timeStr, 120, 100, 7);

  // Date with subtle styling
  tft.setTextColor(COLOR_SUNRISE);
  tft.drawString(dateStr, 120, 150, 2);

  // Divider line with gradient effect
  for (int i = 0; i < 120; i++) {
    uint8_t alpha = (i < 60) ? (i * 4) : ((120 - i) * 4);
    uint16_t lineColor = blendColor(COLOR_HOT_PINK, COLOR_BLACK, alpha);
    tft.drawPixel(60 + i, 175, lineColor);
  }

  // Branding with glow
  tft.setTextColor(COLOR_HOT_PINK);
  tft.drawString("OPERATOR", 120, 200, 4);

  tft.setTextColor(darkenColor(COLOR_CYBER_BLUE, 30));
  tft.drawString("by BlackRoad OS", 120, 230, 2);

  // Unlock button with pulsing border
  int pulseAlpha = 128 + 127 * sin(time / 400.0);
  uint16_t pulseColor = blendColor(COLOR_WHITE, COLOR_BLACK, pulseAlpha);

  // Button glow
  tft.drawRoundRect(58, 268, 124, 44, 22, darkenColor(COLOR_WHITE, 70));
  tft.drawRoundRect(59, 269, 122, 42, 21, darkenColor(COLOR_WHITE, 50));

  // Button border (pulsing)
  tft.drawRoundRect(60, 270, 120, 40, 20, pulseColor);

  // Button text
  tft.setTextColor(COLOR_WHITE);
  tft.drawString("TAP TO UNLOCK", 120, 290, 2);

  // Status indicators
  if (WiFi.status() == WL_CONNECTED) {
    tft.fillCircle(20, 20, 5, COLOR_CYBER_BLUE);
    tft.drawCircle(20, 20, 7, darkenColor(COLOR_CYBER_BLUE, 50));
  }

  tft.setTextColor(COLOR_SUNRISE);
  tft.setTextDatum(TR_DATUM);
  tft.drawString("100%", 225, 15, 2);
}

// ─────────────────────────────────────────────────────────────────────
// PREMIUM STATUS BAR
// ─────────────────────────────────────────────────────────────────────

void drawPremiumStatusBar(TFT_eSPI &tft, bool wifiConnected,
                          const char* timeStr, int batteryPercent) {
  // Gradient background
  drawVerticalGradient(tft, 0, 0, 240, 22, 0x1082, 0x0841);

  // Bottom border with accent
  tft.drawFastHLine(0, 21, 240, 0x2104);

  // WiFi indicator with glow
  if (wifiConnected) {
    tft.fillCircle(12, 11, 4, COLOR_CYBER_BLUE);
    tft.drawCircle(12, 11, 6, darkenColor(COLOR_CYBER_BLUE, 60));
    tft.setTextColor(COLOR_CYBER_BLUE);
    tft.setTextDatum(TL_DATUM);
    tft.drawString("WiFi", 20, 4, 2);
  } else {
    tft.setTextColor(COLOR_HOT_PINK);
    tft.setTextDatum(TL_DATUM);
    tft.drawString("Offline", 8, 4, 2);
  }

  // Time (center)
  tft.setTextColor(COLOR_WHITE);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(timeStr, 120, 4, 2);

  // Battery with color coding
  uint16_t battColor = (batteryPercent > 50) ? COLOR_SUNRISE :
                       (batteryPercent > 20) ? COLOR_AMBER : COLOR_HOT_PINK;
  tft.setTextColor(battColor);
  tft.setTextDatum(TR_DATUM);
  char battStr[8];
  sprintf(battStr, "%d%%", batteryPercent);
  tft.drawString(battStr, 235, 4, 2);

  // Battery icon
  tft.drawRect(195, 5, 16, 10, battColor);
  tft.fillRect(211, 7, 2, 6, battColor);
  int fillWidth = (batteryPercent * 14) / 100;
  tft.fillRect(196, 6, fillWidth, 8, battColor);
}

// ─────────────────────────────────────────────────────────────────────
// PREMIUM BOTTOM NAV
// ─────────────────────────────────────────────────────────────────────

void drawPremiumBottomNav(TFT_eSPI &tft, int activeIndex = 0) {
  // Background with gradient
  drawVerticalGradient(tft, 0, 270, 240, 50, 0x0841, 0x1082);

  // Top border accent
  for (int i = 0; i < 240; i++) {
    uint16_t lineColor = blendColor(COLOR_HOT_PINK, COLOR_VIVID_PUR, (i * 255) / 240);
    tft.drawPixel(i, 270, darkenColor(lineColor, 50));
  }

  // Home button (left) - with glow if active
  if (activeIndex == 0) {
    drawIconGlow(tft, 50, 295, 18, COLOR_VIVID_PUR);
  }
  tft.fillRoundRect(10, 275, 80, 40, 8, activeIndex == 0 ? COLOR_VIVID_PUR : 0x1082);
  tft.drawRoundRect(10, 275, 80, 40, 8, COLOR_VIVID_PUR);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("HOME", 50, 295, 2);

  // Center indicator (animated dot)
  tft.fillCircle(120, 295, 6, COLOR_CYBER_BLUE);
  tft.drawCircle(120, 295, 8, darkenColor(COLOR_CYBER_BLUE, 50));

  // Next button (right)
  if (activeIndex == 1) {
    drawIconGlow(tft, 190, 295, 18, COLOR_HOT_PINK);
  }
  tft.fillRoundRect(150, 275, 80, 40, 8, activeIndex == 1 ? COLOR_HOT_PINK : 0x1082);
  tft.drawRoundRect(150, 275, 80, 40, 8, COLOR_HOT_PINK);
  tft.setTextColor(COLOR_WHITE);
  tft.drawString("NEXT", 190, 295, 2);
}

#endif // PREMIUM_UI_H
