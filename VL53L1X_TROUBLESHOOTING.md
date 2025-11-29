# VL53L1X Sensor Troubleshooting Guide

## Error 0x0D: RANGE_PHASE_CHECK_FAIL

This error means the sensor can't get a valid distance measurement.

### Quick Fixes to Try (in order):

1. **Remove protective film** from sensor lens (if present)
2. **Point sensor at a valid target** (white/matte surface works best)
3. **Try MEDIUM mode** instead of LONG (use `vl53l1x-updated.yaml`)
4. **Try SHORT mode** if MEDIUM fails (use `vl53l1x-short-range.yaml`)
5. **Check sensor mounting** - ensure it's not vibrating or moving

### Configuration Files (Try in this order):

1. **vl53l1x-cptkirki.yaml** - Uses cptkirki's TOF400C component (TRY THIS FIRST!)
2. **vl53l1x-official.yaml** - Official ESPHome component (limited to 2m)
3. **vl53l1x-ultra-conservative.yaml** - Ultra-slow settings, SHORT mode, 50kHz I2C
4. **vl53l1x-updated.yaml** - MEDIUM range mode (up to 3m, balanced)
5. **vl53l1x-short-range.yaml** - SHORT range mode (up to 1.3m, most reliable)

### Distance Modes Explained:

| Mode | Range | Timing Budget | Reliability | Use Case |
|------|-------|---------------|-------------|----------|
| SHORT | 0-1.3m | 20-100ms | ⭐⭐⭐⭐⭐ | Indoor, close range |
| MEDIUM | 0-3m | 33-200ms | ⭐⭐⭐⭐ | General purpose |
| LONG | 0-4m | 140-500ms | ⭐⭐⭐ | Outdoor, max range needed |

### Testing Steps:

1. **CRITICAL: Check for protective film on sensor lens!** This is the #1 cause of 0x0D errors.

2. **Flash the cptkirki component** first (best compatibility):
   ```bash
   esphome run vl53l1x-cptkirki.yaml
   ```

3. **Point sensor at a white wall or cardboard box** about 50cm-1m away

4. **Watch the logs** - you should see distance values instead of `nan`

5. **If still getting 0x0D errors**, try the official component:
   ```bash
   esphome run vl53l1x-official.yaml
   ```

6. **Still failing?** Try ultra-conservative settings:
   ```bash
   esphome run vl53l1x-ultra-conservative.yaml
   ```

### Hardware Checklist:

⚠️ **BEFORE ANYTHING ELSE:**
- [ ] **Protective film removed from sensor lens** (peel it off!)
- [ ] **Point sensor at a valid target** (white wall, cardboard, paper)
- [ ] **Sensor is getting 3.3V power** (check with multimeter if possible)

**Wiring:**
- [ ] SDA to GPIO20
- [ ] SCL to GPIO21
- [ ] VCC to 3.3V (NOT 5V!)
- [ ] GND to GND
- [ ] Wires are short and not loose (< 20cm ideal)
- [ ] I2C pullup resistors present (usually built into sensor module)

**Environment:**
- [ ] Sensor firmly mounted (not vibrating)
- [ ] No bright sunlight hitting the sensor directly
- [ ] Target is 20cm-100cm away (for initial testing)
- [ ] Target is not transparent, black velvet, or mirror-like

### Signal Quality Tips:

**Good targets:**
- White matte surfaces
- Cardboard boxes
- Painted walls
- Light-colored objects

**Bad targets:**
- Mirrors or shiny metal (too reflective)
- Black velvet (too absorptive)
- Glass or transparent materials
- Very thin objects

### Your Application: Step Detection

For detecting people on steps at 4ft (1.22m):

- **MEDIUM mode** is ideal (up to 3m range)
- **SHORT mode** will work but is very close to its 1.3m limit
- Consider using **MEDIUM mode with 100ms timing budget** (in vl53l1x-updated.yaml)

### If Nothing Works:

**You're seeing the sensor at 0x29 but getting constant 0x0D errors. This usually means:**

1. **Protective film is STILL on the lens** - Look very carefully, sometimes it's clear and hard to see
2. **Sensor is defective** - The VL53L1X chip might be damaged
3. **Power supply issue** - ESP32-C3 might not provide enough current

**Try these hardware fixes:**

1. ✓ I2C bus scan shows `0x29` address (sensor is detected - confirmed in your logs)
2. **Take a photo of your sensor module** - check if there's a clear film on the black lens
3. **Measure voltage** at sensor VCC pin - should be 3.3V (not 2.8V or less)
4. **Try external I2C pullups** - Add 4.7kΩ resistors from SDA/SCL to 3.3V
5. **Try different I2C pins** - Use GPIO2 for SDA, GPIO3 for SCL instead
6. **Test with another ESP32** or Arduino to rule out sensor defect
7. **Try a different VL53L1X module** - Current one might be faulty

**Component Library Priority:**
1. **cptkirki/TOF400C** (vl53l1x-cptkirki.yaml) ← Try this first!
2. **Official ESPHome** (vl53l1x-official.yaml) ← Try this second
3. **soldierkam** (all other configs) ← Original attempt

### Advanced Tuning (if needed):

Uncomment and adjust in the sensor config:
```yaml
sensor:
  - platform: vl53l1x_sensor
    # ... other settings ...
    signal_rate_limit: 0.25  # Lower = more sensitive (0.1-0.5 MCPS)
    sigma_threshold: 15      # Measurement quality (15-50)
    pre_range_timeout: 14    # Timeout in ms
    final_range_timeout: 14  # Timeout in ms
```

## Next Steps:

Flash `vl53l1x-updated.yaml` and see if MEDIUM mode resolves your 0x0D errors!
