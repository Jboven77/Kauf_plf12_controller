# VL53L1X Time-of-Flight Sensor Setup for ESPHome

## The Problem
ESPHome can't clone the external component from GitHub due to authentication issues in your environment.

## Solution Options

### Option 1: Fix Git Authentication (Recommended)
Add this to your ESPHome container or installation to allow anonymous GitHub cloning:

```bash
git config --global url."https://".insteadOf git://
```

If using ESPHome in Home Assistant (addon), you may need to:
1. Go to Settings → Add-ons → ESPHome
2. Enable "Show in sidebar"
3. Restart ESPHome addon

### Option 2: Manual Component Installation
1. SSH into your Home Assistant or ESPHome environment
2. Navigate to: `/config/esphome/`
3. Create directory: `mkdir -p custom_components/vl53l1x`
4. Download the component manually from: https://github.com/toyoshim/esphome-vl53l1x
5. Copy files to `custom_components/vl53l1x/`
6. Use this in your YAML:

```yaml
external_components:
  - source:
      type: local
      path: custom_components
    components: [ vl53l1x ]
```

### Option 3: Use Pre-Downloaded Component
Use the `tof-top-steps-alternative.yaml` which tries the ssieb component library (different source).

## Files Provided

1. **tof-top-steps.yaml** - Main config using toyoshim component
2. **tof-top-steps-alternative.yaml** - Alternative using ssieb component
3. **This file** - Setup instructions

## Wiring
- VL53L1X VIN → ESP32-C3 3.3V
- VL53L1X GND → ESP32-C3 GND
- VL53L1X SDA → ESP32-C3 GPIO20
- VL53L1X SCL → ESP32-C3 GPIO21

## Download Links

**Main Config:**
```
https://raw.githubusercontent.com/Jboven77/Kauf_plf12_controller/claude/add-new-code-01M816K38EffHSgTGb9SEJrG/tof-top-steps.yaml
```

**Alternative Config:**
```
https://raw.githubusercontent.com/Jboven77/Kauf_plf12_controller/claude/add-new-code-01M816K38EffHSgTGb9SEJrG/tof-top-steps-alternative.yaml
```

## Troubleshooting

If you still get errors, share the complete error message and we can:
- Try VL53L0X instead (older but more widely supported)
- Use a custom component approach
- Create a fully manual configuration
