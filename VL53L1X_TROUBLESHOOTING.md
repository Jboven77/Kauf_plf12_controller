# VL53L1X Sensor Troubleshooting Guide

## Error 0x0D: RANGE_PHASE_CHECK_FAIL

This error means the sensor can't get a valid distance measurement.

### Quick Fixes to Try (in order):

1. **Remove protective film** from sensor lens (if present)
2. **Point sensor at a valid target** (white/matte surface works best)
3. **Try MEDIUM mode** instead of LONG (use `vl53l1x-updated.yaml`)
4. **Try SHORT mode** if MEDIUM fails (use `vl53l1x-short-range.yaml`)
5. **Check sensor mounting** - ensure it's not vibrating or moving

### Configuration Files:

- **vl53l1x-updated.yaml** - MEDIUM range mode (up to 3m, balanced)
- **vl53l1x-short-range.yaml** - SHORT range mode (up to 1.3m, most reliable)

### Distance Modes Explained:

| Mode | Range | Timing Budget | Reliability | Use Case |
|------|-------|---------------|-------------|----------|
| SHORT | 0-1.3m | 20-100ms | ⭐⭐⭐⭐⭐ | Indoor, close range |
| MEDIUM | 0-3m | 33-200ms | ⭐⭐⭐⭐ | General purpose |
| LONG | 0-4m | 140-500ms | ⭐⭐⭐ | Outdoor, max range needed |

### Testing Steps:

1. **Flash the MEDIUM range config** first:
   ```bash
   esphome run vl53l1x-updated.yaml
   ```

2. **Point sensor at a white wall** about 1 meter away

3. **Watch the logs** - you should see distance values instead of `nan`

4. **If still getting 0x0D errors**, flash SHORT range:
   ```bash
   esphome run vl53l1x-short-range.yaml
   ```

### Hardware Checklist:

- [ ] Protective film removed from sensor lens
- [ ] Sensor powered with 3.3V (NOT 5V!)
- [ ] I2C pullup resistors present (usually on sensor board)
- [ ] Wiring correct: SDA to GPIO20, SCL to GPIO21
- [ ] Sensor firmly mounted (not vibrating)
- [ ] No bright sunlight hitting the sensor

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

1. Check I2C bus scan shows `0x29` address ✓ (confirmed in your logs)
2. Try different I2C speed: Change `frequency: 400kHz` to `frequency: 100kHz`
3. Add I2C pullup resistors (4.7kΩ) if not present on sensor board
4. Test sensor with a different microcontroller to rule out hardware failure
5. Try a different VL53L1X sensor module (might be defective)

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
