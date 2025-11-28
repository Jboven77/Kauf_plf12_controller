# VL53L1X Setup Instructions for Linux Server

## Files Created
- `tof-upper.yaml` - ESPHome configuration for ESP32-C3 with VL53L1X sensor

## Setup Steps

### 1. Download the VL53L1X Component

From your Linux server, download the component:

```bash
cd /home/user/Kauf_plf12_controller
git clone https://github.com/cptkirki/TOF400C-VL53L1X-esphome.git temp-component
```

### 2. Copy Component Files

Extract just the component folder:

```bash
# Copy the vl53l1x component to the current directory
cp -r temp-component/components/vl53l1x ./
# Clean up
rm -rf temp-component
```

### 3. Verify Folder Structure

Your folder should look like this:

```
/home/user/Kauf_plf12_controller/
├── tof-upper.yaml
└── vl53l1x/
    ├── __init__.py
    ├── sensor.py
    └── (other component files)
```

### 4. Compile and Upload

```bash
esphome compile tof-upper.yaml
esphome upload tof-upper.yaml
```

## Wiring

Connect the VL53L1X sensor to your ESP32-C3:

- **VL53L1X VIN** → ESP32-C3 **3.3V**
- **VL53L1X GND** → ESP32-C3 **GND**
- **VL53L1X SDA** → ESP32-C3 **GPIO20**
- **VL53L1X SCL** → ESP32-C3 **GPIO21**

## Configuration Details

- **Device Name**: tof-upper
- **WiFi SSID**: BOVENS-MESH
- **WiFi Password**: 605506Jdb
- **Framework**: Arduino (required for VL53L1X)
- **I2C Pins**: GPIO20 (SDA), GPIO21 (SCL)
- **Update Interval**: 500ms (can be reduced once stable)

## Troubleshooting

If you get component errors:
1. Check that the vl53l1x folder exists
2. Verify __init__.py is inside vl53l1x/
3. Try absolute path in YAML: `path: /home/user/Kauf_plf12_controller/vl53l1x`
