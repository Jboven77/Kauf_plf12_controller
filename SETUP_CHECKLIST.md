# TotalSense Setup Checklist

## Pre-Installation

- [ ] Waveshare ESP32-S3 Touch LCD 7" hardware in hand
- [ ] Kauf PLF12 smart plug installed and working
- [ ] Home Assistant running and accessible
- [ ] Kauf plug added to Home Assistant
- [ ] ESPHome installed (Home Assistant add-on or standalone)

## Configuration Steps

### 1. Identify Your Kauf Plug Entities

In Home Assistant, find your Kauf plug and note these entity IDs:

- [ ] Main switch: `____________________` (e.g., `switch.kauf_plug_1`)
- [ ] Voltage sensor: `____________________` (e.g., `sensor.kauf_plug_1_voltage`)
- [ ] Current sensor: `____________________` (e.g., `sensor.kauf_plug_1_current`)
- [ ] Power sensor: `____________________` (e.g., `sensor.kauf_plug_1_power`)

### 2. Update totalsense.yaml

If your entity IDs are different from the defaults, update these lines:

**Line 347 & 382** - Switch entity (plug state import and control)
```yaml
entity_id: switch.kauf_plug_1  # ← Change this
```

**Line 298** - Voltage sensor
```yaml
entity_id: sensor.kauf_plug_1_voltage  # ← Change this
```

**Line 308** - Current sensor
```yaml
entity_id: sensor.kauf_plug_1_current  # ← Change this
```

**Line 318** - Power sensor
```yaml
entity_id: sensor.kauf_plug_1_power  # ← Change this
```

### 3. Verify Network Settings

- [ ] WiFi SSID is correct (currently: "JEREMY")
- [ ] WiFi password is correct (currently: "605506Jdb")
- [ ] Plug IP address is correct (currently: 192.168.68.77)
- [ ] Timezone is correct (currently: America/Detroit)

### 4. Compile & Flash

```bash
# Validate config
esphome config totalsense.yaml
```
- [ ] No errors in validation

```bash
# Compile firmware
esphome compile totalsense.yaml
```
- [ ] Compilation successful

```bash
# Flash to device (USB required for first flash)
esphome upload totalsense.yaml
```
- [ ] Flash successful
- [ ] Device boots up
- [ ] Splash screen appears (2 seconds)
- [ ] Main page loads

### 5. First Boot Checks

- [ ] **Display working** - Can see splash screen then main page
- [ ] **Touch working** - Can tap buttons and they respond
- [ ] **Backlight working** - Screen is bright and visible
- [ ] **WiFi connected** - Check Home Assistant for device
- [ ] **Time synced** - Time and date display correctly (may take 1-2 min)

### 6. Test Plug Control

- [ ] **View state** - Plug button shows correct state (green/red)
- [ ] **Turn ON** - Tap plug button, plug turns on, button turns green
- [ ] **Turn OFF** - Tap plug button, plug turns off, button turns red
- [ ] **Physical toggle** - Turn plug off at wall, display updates to red
- [ ] **State sync** - Display matches actual plug state

### 7. Test Plug Info Page

- [ ] Tap "Plug Info" button
- [ ] Voltage displays correctly (~120V for US)
- [ ] Current displays correctly (matches actual load)
- [ ] Values update periodically
- [ ] "Back" button returns to main page

### 8. Test Timer Page

- [ ] Tap "Timer" button
- [ ] Current time displays correctly
- [ ] Can scroll hour roller (00-23)
- [ ] Can scroll minute roller (00, 15, 30, 45)
- [ ] Toggle switch enables/disables timer
- [ ] "Save" button saves settings
- [ ] "Back" button returns to main page

### 9. Test IP Settings Page

- [ ] Tap "IP Settings" button
- [ ] Current IP displays in text field
- [ ] Numeric keyboard appears
- [ ] Can enter new IP address
- [ ] "Save" button stores IP (check logs)
- [ ] "Back" button returns to main page

### 10. Test Backlight Control

- [ ] "Auto (5m)" mode is default
- [ ] Screen dims after 5 minutes of inactivity
- [ ] Touch wakes screen
- [ ] Tap backlight button to switch to "ON" mode
- [ ] Screen stays on continuously in ON mode
- [ ] Tap again to return to "Auto" mode

### 11. Test Timer Automation

- [ ] Set timer for ON in 2 minutes
- [ ] Wait for timer to trigger
- [ ] Plug turns on automatically
- [ ] Set timer for OFF in 2 minutes
- [ ] Wait for timer to trigger
- [ ] Plug turns off automatically

## Common Issues & Solutions

### Display shows nothing
- Check power supply (5V, 2A minimum)
- Verify USB-C cable is plugged in
- Try manual backlight ON mode
- Check serial logs for errors

### Touch not responding
- Verify I2C scan detects GT911 in logs
- Check for loose connections
- Try reflashing firmware
- Touch may be inverted - check coordinates in logs

### Plug control doesn't work
- Verify Home Assistant connection (check ESPHome integration)
- Confirm entity IDs match your plug
- Check API encryption key
- Ensure plug is online in HA

### Time not displaying
- Wait 1-2 minutes for NTP sync
- Check WiFi connection
- Verify internet access
- Check timezone setting

### Voltage/Current shows 0.0
- Check Home Assistant entity IDs
- Verify plug has power monitoring
- Ensure sensors are publishing data
- Check Home Assistant connection

### Timer doesn't trigger
- Verify timer is enabled (toggle switch ON)
- Check current time is correct
- Ensure time has synced (not "00:00")
- Review logs for timer trigger messages

## Home Assistant Integration

After first boot, add to Home Assistant:

1. Go to **Settings** → **Devices & Services**
2. Look for "ESPHome" discovered device
3. Click **Configure**
4. Enter encryption key: `+6lkh+FkWq3HVFh6+NukfmN188wGMQap7sw2RK1p9Gg=`
5. Device should show as "TotalSense Controller"

## Final Verification

- [ ] All pages load correctly
- [ ] All buttons respond to touch
- [ ] Plug control works both directions
- [ ] Timer automation works
- [ ] Backlight auto-off works
- [ ] Real-time monitoring updates
- [ ] No errors in logs

## Ready for Production!

- [ ] Device mounted in desired location
- [ ] All features tested and working
- [ ] Timer schedules configured
- [ ] Backlight preference set

---

**Need help?** Check the README.md for detailed troubleshooting steps.

**Note:** After initial USB flash, all future updates can be done wirelessly via OTA (Over-The-Air).
