# VL53L1X Local Component Setup

## Problem
ESPHome can't clone from GitHub due to authentication issues.

## Solution
Use the downloaded component as a LOCAL component instead!

---

## Setup Steps

### 1. Extract the Downloaded Component

From the downloaded repo: https://github.com/cptkirki/TOF400C-VL53L1X-esphome

Extract the files to your ESPHome config directory.

### 2. Create This Folder Structure

In your ESPHome config folder (usually `/config/esphome/`):

```
/config/esphome/
├── tof-top-steps-cptkirki.yaml  (this config file)
└── components/
    └── vl53l1x/
        ├── __init__.py
        ├── sensor.py
        └── vl53l1x.cpp (and any other files from the repo)
```

### 3. Copy Files

From the downloaded `TOF400C-VL53L1X-esphome` repo:
- Copy the **entire `vl53l1x` folder** to `/config/esphome/components/`

### 4. Upload the Config

Use `tof-top-steps-cptkirki.yaml` to compile and upload.

---

## Alternative: Different Path

If you want to put the component somewhere else, update the config:

```yaml
external_components:
  - source:
      type: local
      path: /config/custom_components  # Change this path
    components: [ vl53l1x ]
```

---

## Wiring

- **VL53L1X VIN** → ESP32-C3 **3.3V**
- **VL53L1X GND** → ESP32-C3 **GND**
- **VL53L1X SDA** → ESP32-C3 **GPIO20**
- **VL53L1X SCL** → ESP32-C3 **GPIO21**

---

## If This Still Fails

Check the downloaded repo structure - the component folder should contain:
- `__init__.py` - Component initialization
- `sensor.py` - Sensor platform definition
- Other `.cpp` or `.h` files

Make sure you're copying the **component folder**, not the entire repo!
