# TotalSense Controller
**Professional Smart Plug Controller for Waveshare ESP32-S3 Touch LCD 7"**

*By Jeremy Boven & Peter Olundtu*

---

## Overview

TotalSense is a sophisticated control interface for Kauf PLF12 smart plugs, featuring a beautiful LVGL-based touchscreen UI with real-time monitoring, timer scheduling, and professional animations.

## Features

### ✨ Main Features
- **Real-time State Monitoring** - Instantly see plug status (Green=ON, Red=OFF)
- **Power Monitoring** - Live voltage and current readings
- **Daily Timer Scheduling** - Set automatic ON/OFF times
- **IP Configuration** - Easily configure plug IP addresses
- **Auto Backlight** - 5-minute auto-off with manual override
- **Professional UI** - Smooth animations and modern design
- **Splash Screen** - 2-second branded startup animation

### 📱 User Interface

#### Main Page
- **Large Time Display** - Current time and date prominently displayed
- **Plug Control Button** - Color-coded state button (Green/Red)
- **Timer Button** - Quick access to scheduling
- **Navigation Buttons** - IP Settings, Plug Info, Backlight control

#### IP Settings Page
- **Numeric Keyboard** - Easy IP address input
- **Save Configuration** - Persistent storage of plug IP addresses

#### Plug Info Page
- **Voltage Display** - Real-time voltage monitoring
- **Current Display** - Real-time amperage monitoring
- **Large, Clear Readouts** - Easy to read from a distance

#### Timer Page
- **Daily Schedule** - Set recurring ON/OFF times
- **15-minute Intervals** - Hour and minute rollers
- **Enable/Disable Toggle** - Quick timer activation
- **Current Time Display** - Reference for scheduling

## Hardware Requirements

### Components
1. **Waveshare ESP32-S3 Touch LCD 7"** (800x480)
   - Model: ESP32-S3-Touch-LCD-7.0
   - Wiki: https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-7

2. **Kauf PLF12 Smart Plug**
   - Must have ESPHome firmware installed
   - Must be connected to Home Assistant

3. **WiFi Network**
   - 2.4GHz WiFi required
   - Stable connection recommended

### Pin Configuration (Pre-configured)
- **Display:** RGB Parallel Interface
- **Touch:** GT911 I2C (SDA: GPIO08, SCL: GPIO09, INT: GPIO18)
- **Backlight:** GPIO38 (PWM controlled)

## Software Requirements

- **ESPHome** 2024.11.0 or newer
- **Home Assistant** (for plug communication)
- **Kauf Plug** with ESPHome firmware

## Installation

### Step 1: Configure Home Assistant

1. Ensure your Kauf PLF12 plug is added to Home Assistant
2. Note the entity IDs (default: `switch.kauf_plug_1`)
3. Find sensor entity IDs:
   - `sensor.kauf_plug_1_voltage`
   - `sensor.kauf_plug_1_current`
   - `sensor.kauf_plug_1_power`

### Step 2: Update Configuration

Edit `totalsense.yaml` if your Kauf plug has different entity IDs:

```yaml
# Find and replace these entity IDs if different
entity_id: switch.kauf_plug_1          # Line 336, 347, 374, 382
entity_id: sensor.kauf_plug_1_voltage  # Line 298
entity_id: sensor.kauf_plug_1_current  # Line 308
entity_id: sensor.kauf_plug_1_power    # Line 318
```

### Step 3: Compile and Flash

```bash
# Validate configuration
esphome config totalsense.yaml

# Compile firmware
esphome compile totalsense.yaml

# Flash to device (first time, USB required)
esphome upload totalsense.yaml

# After first flash, OTA updates work wirelessly
esphome upload totalsense.yaml --device totalsense-controller.local
```

### Step 4: Add to Home Assistant

The device will automatically appear in Home Assistant's ESPHome integration.

## Configuration

### WiFi Settings
Located in `totalsense.yaml`:
```yaml
wifi:
  ssid: "JEREMY"
  password: "605506Jdb"
```

### Timezone
Default: `America/Detroit` (EST/EDT)
Change in `substitutions` section if needed.

### Plug IP Address
Default: `192.168.68.77`
- Can be changed via the touchscreen IP Settings page
- Stored persistently in flash memory

## Usage Guide

### Main Screen

**Time Display**
- Top of screen shows current time (large) and date (small)

**Plug Control Button** (Center)
- Tap to toggle plug ON/OFF
- **Green** = Plug is ON
- **Red** = Plug is OFF
- State updates automatically if plug is turned off physically

**Timer Button** (Right of plug button)
- Opens timer scheduling page
- Shows clock icon

**Navigation Buttons** (Bottom)
- **IP Settings** - Configure plug IP address
- **Plug Info** - View voltage and current
- **Backlight** - Toggle between Auto (5min) and ON

### IP Settings Page

1. Tap **IP Settings** button on main page
2. Current IP address appears in text field
3. Use numeric keyboard to enter new IP
4. Tap **Save** to store configuration
5. Tap **Back** to return to main page

### Plug Info Page

- Displays real-time monitoring data
- **Voltage** - Line voltage (typically 120V)
- **Current** - Current draw in Amps
- Updates automatically every few seconds

### Timer Page

1. Tap **Timer** button on main page
2. Toggle switch (top right) to enable/disable timer
3. Set **Turn ON** time using hour/minute rollers
4. Set **Turn OFF** time using hour/minute rollers
5. Tap **Save** to activate schedule
6. Timer runs daily at configured times

**Time Selection**
- Hours: 00-23 (24-hour format)
- Minutes: 00, 15, 30, 45

### Backlight Control

**Auto Mode** (Default)
- Display dims after 5 minutes of inactivity
- Wakes on touch

**Manual ON Mode**
- Backlight stays on continuously
- Tap button to toggle mode

## Scaling to 8 Plugs

This configuration is designed for **one plug** as a proof of concept. To scale to 8 plugs:

### Recommended Changes

1. **Reduce Font Sizes**
   - `roboto_72` → `roboto_48` for time
   - `roboto_48` → `roboto_32` for titles
   - `roboto_24` → `roboto_18` for buttons

2. **Grid Layout**
   - Main page: 4x2 grid of plug buttons
   - Each button: ~180x100px
   - Include plug number labels

3. **Add Variables**
   ```yaml
   globals:
     - id: plug2_state
     - id: plug2_voltage
     # ... etc for plugs 2-8
   ```

4. **Duplicate Sensors**
   - Copy sensor blocks for each plug
   - Update entity IDs and variable names

5. **Sub-pages per Plug**
   - Tap plug button → opens dedicated info/timer page
   - Or use a selector/dropdown to choose active plug

## Troubleshooting

### Display Not Working
- Check RGB pin connections match hardware
- Verify PSRAM is enabled
- Check backlight is on (manual mode)

### Touch Not Responding
- Verify I2C pins (SDA/SCL)
- Check interrupt pin (GPIO18)
- Look for GT911 in I2C scan logs

### Plug Not Responding
- Verify Home Assistant connection
- Check entity IDs match your Kauf plug
- Ensure plug is online in HA
- Check API encryption key matches

### No Time Display
- Wait for NTP sync (may take 1-2 minutes after boot)
- Check WiFi connection
- Verify timezone setting

### Backlight Stuck Off
- Tap screen to wake
- Switch to Manual ON mode
- Check backlight PWM pin (GPIO38)

## Technical Specifications

### Display
- Resolution: 800x480 pixels
- Color Depth: 16-bit RGB
- Interface: 16-bit RGB parallel
- Touch: GT911 capacitive (I2C)

### Performance
- CPU: 240MHz ESP32-S3
- PSRAM: 8MB Octal SPI @ 120MHz
- Flash: 16MB
- Framework: ESP-IDF

### Power Monitoring Update Rate
- Voltage/Current: ~2 seconds (via Home Assistant)
- Plug State: Real-time (event-driven)

### Timer Accuracy
- Check interval: 60 seconds
- Triggers at exact hour:minute match
- Resolution: 15-minute intervals

## API Encryption

**ESPHome API Key:**
```
+6lkh+FkWq3HVFh6+NukfmN188wGMQap7sw2RK1p9Gg=
```

**OTA Password:**
```
48170f28ed94e6fe392d67906b01ff74
```

## Customization

### Colors

Edit style definitions in `totalsense.yaml`:

```yaml
style_button_on:
  bg_color: 0x27AE60  # Green when ON

style_button_off:
  bg_color: 0xE74C3C  # Red when OFF

style_time_large:
  text_color: 0x3498DB  # Blue time display
```

### Fonts

Change Google Fonts in font definitions:
```yaml
font:
  - file: "gfonts://Roboto"  # Change to any Google Font
    id: custom_font
    size: 24
```

### Splash Screen

Edit splash page text in LVGL configuration:
```yaml
- label:
    text: "TotalSense"  # Change branding
```

## Support & Development

### Entity ID Discovery

To find your Kauf plug's entity IDs:

1. Open Home Assistant
2. Go to **Settings** → **Devices & Services**
3. Find your Kauf plug
4. Click on the device
5. Note all entity IDs

Common entity patterns:
- `switch.kauf_plf10_*` or `switch.kauf_plf12_*`
- `sensor.*_voltage`
- `sensor.*_current`
- `sensor.*_power`

### Logs

View real-time logs:
```bash
esphome logs totalsense.yaml
```

Or in Home Assistant:
- **Settings** → **Devices** → **TotalSense Controller** → **Logs**

## Future Enhancements

- [ ] 8-plug multi-device support
- [ ] Power usage graphs
- [ ] Energy cost calculator
- [ ] Multiple timer schedules per plug
- [ ] Vacation/random mode
- [ ] Plug grouping
- [ ] Custom plug names
- [ ] Dark/light theme toggle

## Credits

**Developed by:**
- Jeremy Boven
- Peter Olundtu

**Built with:**
- ESPHome (https://esphome.io)
- LVGL (https://lvgl.io)
- Kauf Smart Plugs (https://kaufha.com)
- Waveshare ESP32-S3 (https://waveshare.com)

## License

This project is provided as-is for personal use.

---

**Version:** 1.0.0
**Last Updated:** November 2024
