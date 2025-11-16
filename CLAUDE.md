# CLAUDE.md - AI Assistant Documentation

## Project Overview

This repository contains an ESPHome configuration for a **Waveshare ESP32-S3 7-inch touchscreen display** that serves as a smart home controller for managing 8 Kauf smart plugs. The project uses LVGL (Light and Versatile Graphics Library) to create an interactive touchscreen interface for controlling, scheduling, and monitoring the smart plugs.

### Key Information
- **Device**: Waveshare ESP32-S3 7-inch display (800x480 resolution)
- **Framework**: ESPHome with ESP-IDF
- **UI Framework**: LVGL (version with 16-bit color depth)
- **Target Devices**: 8 Kauf smart plugs controlled via HTTP API
- **Communication**: Wi-Fi network communication using HTTP requests

## Repository Structure

```
Kauf_plf12_controller/
├── esp32-s3-waveshare-7in.yaml    # Main ESPHome configuration (5346 lines)
├── logs (13).txt                  # Debug/diagnostic logs
└── CLAUDE.md                      # This file
```

### File Purposes

**esp32-s3-waveshare-7in.yaml**
- Single comprehensive configuration file containing:
  - Hardware configuration (ESP32-S3, display, touchscreen)
  - Network configuration (Wi-Fi credentials and settings)
  - UI definitions using LVGL
  - Script logic for plug control and scheduling
  - Global variables and state management
  - Font and time configuration

## Architecture & Components

### Hardware Configuration

**ESP32-S3 Settings** (lines 11-48):
- Board: esp32-s3-devkitc-1
- CPU: 240MHz
- Flash: 8MB
- PSRAM: Octal mode, 120MHz, 524KB
- Framework: ESP-IDF with experimental features enabled
- Optimizations: Performance-focused with PSRAM instruction/data caching

**Display** (lines 1410-1443):
- Platform: RPI DPI RGB
- Resolution: 800x480
- Pixel clock: 16MHz
- Color order: RGB
- Interface: Parallel RGB with specific timing parameters

**Touchscreen** (lines 1444-1452):
- Platform: GT911
- Interrupt pin: GPIO4
- Reset pin: CH422G hub #1

**I2C Bus** (lines 79-83):
- SDA: GPIO08
- SCL: GPIO09
- Connected to CH422G I/O expander

### Software Architecture

#### 1. Substitutions (lines 1-9)
Defines IP addresses for 8 smart plugs:
```yaml
plug1_ip: "192.168.68.79"
plug2_ip: "192.168.68.77"
# ... through plug8
```

#### 2. Global Variables (lines 103-201)
- **Backlight control**: `last_activity`, `bl_level`, `bl_mode`
- **Plug IP storage**: `plug1_ip_str` through `plug8_ip_str` (std::string)
- Each stored as string for HTTP request construction

#### 3. Switches (lines 203-256)
- **lcd_backlight_sw**: Hardware backlight control via CH422G
- **plug1_schedule_enabled through plug8_schedule_enabled**: Enable/disable timers for each plug

#### 4. Scripts (lines 258-963)
Key automation scripts:
- **register_activity**: Resets inactivity timer, turns on backlight
- **bl_auto_off_check**: Auto-off backlight after 5 minutes of inactivity
- **plug[1-8]_turn_on/off**: Execute HTTP requests to control plugs
- **plug[1-8]_update_state**: Poll plug status and update UI indicators
- **schedule_check**: Check all plug schedules every minute

#### 5. LVGL UI (lines 1453-5057)
**Pages**:
- **main_page**: Overview with all 8 plugs and quick controls
- **timer1_page through timer8_page**: Individual timer configuration for each plug
- **plug_info_page**: IP address configuration and status monitoring

**UI Elements**:
- Buttons for plug on/off control
- Timer enable/disable toggles
- Time pickers (hour, minute, AM/PM selectors)
- Status labels showing plug state and connectivity
- On-screen keyboard for IP address input (lines 4826-4832)

#### 6. Number Inputs (lines 976-1280)
For each plug (1-8):
- `plug[N]_on_hour`: 1-12 (12-hour format)
- `plug[N]_on_minute`: 0-59
- `plug[N]_off_hour`: 1-12
- `plug[N]_off_minute`: 0-59

#### 7. Select Inputs (lines 1281-1408)
For each plug (1-8):
- `plug[N]_on_ampm`: "AM" or "PM"
- `plug[N]_off_ampm`: "AM" or "PM"

#### 8. Intervals (lines 5058+)
- **schedule_check**: Runs every 60 seconds to check and execute schedules
- **bl_auto_off_check**: Runs every 30 seconds to check for backlight timeout
- **plug state updates**: Periodic polling of plug states

## Development Workflows

### ESPHome Build Process

1. **Compilation**: ESPHome compiles the YAML to C++ code
2. **Platform.IO**: Builds the firmware using ESP-IDF framework
3. **Output**: Generates `.bin` firmware file
4. **Deployment**: OTA (Over-The-Air) updates or serial flash

### Common Development Tasks

#### Adding a New Plug
1. Add IP to substitutions section
2. Create global string variable for IP storage
3. Add schedule_enabled switch
4. Create turn_on, turn_off, and update_state scripts
5. Add number inputs for on/off times
6. Add select inputs for AM/PM
7. Create button and UI elements on main_page
8. Create dedicated timer configuration page
9. Add schedule check logic in schedule_check script
10. Add IP configuration field in plug_info_page

#### Modifying UI Layout
1. Locate the relevant page in LVGL pages section
2. Modify widget properties (x, y, width, height, bg_color)
3. Update click handlers (on_click) as needed
4. Adjust label texts and fonts
5. Test on actual hardware (800x480 display)

#### Adjusting Schedules
- Schedule logic is in the `schedule_check` script
- Uses SNTP time (id: sntp_time)
- Compares current time against number/select inputs
- Checks schedule_enabled switch state before executing

#### Network Configuration
- Wi-Fi credentials in wifi section (lines 53-62)
- API encryption key (line 68)
- OTA password (line 73)
- HTTP request timeout: 300ms (line 77)

## Key Conventions for AI Assistants

### Code Organization

1. **Single File Architecture**
   - Everything is in one YAML file
   - No separate components or packages
   - Keep related elements together (e.g., all plug1 configurations near each other)

2. **Naming Conventions**
   - IDs: `snake_case` (e.g., `plug1_turn_on`, `lbl_main_title`)
   - Names (user-facing): Title Case with spaces (e.g., "Plug 1 Schedule Enabled")
   - LVGL widget IDs: prefix with type (`btn_`, `lbl_`, `ip1_text`, etc.)

3. **Repetitive Patterns**
   - The configuration for plugs 1-8 follows identical patterns
   - When modifying one plug's logic, consider if all 8 need updating
   - Use consistent spacing and indentation across similar sections

### LVGL Specific

1. **Color Format**: Hexadecimal 0xRRGGBB
   - Background: 0x101830 (dark blue)
   - Red: 0xFF0000 (plug off)
   - Green: 0x00FF00 (plug on)
   - Gray: 0x444444 (inactive/disabled)

2. **Coordinate System**
   - Origin (0,0) is top-left
   - Display dimensions: 800x480
   - Manual positioning required (no auto-layout)

3. **Widget Hierarchy**
   - Pages contain widgets
   - Widgets can contain child widgets
   - Buttons often contain labels

4. **Event Handlers**
   - Use `on_click`, `on_value`, `on_ready` for events
   - Lambda expressions for complex logic
   - Script calls for reusable actions

### HTTP Communication

1. **API Endpoints**
   - Toggle: `/switch/kauf_plug/toggle`
   - Turn on: `/switch/kauf_plug/turn_on`
   - Turn off: `/switch/kauf_plug/turn_off`
   - Status: `/switch/kauf_plug` (GET request)

2. **Request Pattern**
   ```yaml
   - http_request.post:
       url: !lambda |-
         return std::string("http://") + id(plug1_ip_str) + std::string("/switch/kauf_plug/toggle");
   - delay: 500ms
   - script.execute: plug1_update_state
   ```

3. **Error Handling**
   - Timeouts set to 300ms
   - Status labels show "unreachable" on failure
   - No retry logic implemented

### State Management

1. **Global Variables**
   - Use `id(variable_name)` to access in lambdas
   - String types for IP addresses
   - Integer types for timing/state tracking

2. **Switches for Toggles**
   - Template switches for boolean states
   - `optimistic: true` for local-only state
   - `entity_category: "config"` for configuration items

3. **Number/Select for User Input**
   - Number inputs for numeric values with min/max
   - Select inputs for choice-based options
   - `initial_value`/`initial_option` for defaults

### Testing & Debugging

1. **Logger Levels**
   - Global level: WARN (line 51)
   - LVGL level: INFO (line 1454)
   - Use ESP_LOGI, ESP_LOGW for custom logging

2. **Serial Monitoring**
   - Connect via USB serial during development
   - Monitor ESPHome logs for debugging
   - Check HTTP request responses

3. **Common Issues**
   - **Plug unreachable**: Check IP address, network connectivity
   - **Backlight not working**: Check CH422G initialization, GPIO pins
   - **Touch not responding**: Verify GT911 interrupt/reset pins
   - **Schedule not firing**: Check SNTP time sync, schedule_check interval
   - **Keyboard not appearing**: Verify keyboard widget ID and textarea linkage

### Performance Considerations

1. **Memory Management**
   - PSRAM enabled for large LVGL buffers
   - Monitor free heap during development
   - Avoid excessive string allocations in hot paths

2. **HTTP Timeouts**
   - Keep timeout at 300ms or adjust based on network
   - Too short = false negatives
   - Too long = UI lag

3. **Update Intervals**
   - Schedule checks: 60 seconds
   - Backlight checks: 30 seconds
   - Plug state updates: as needed (triggered after actions)

### Security Notes

1. **Credentials in Code**
   - Wi-Fi password is hardcoded (line 55)
   - API encryption key is hardcoded (line 68)
   - **For production**: Use secrets file or environment variables

2. **Network Security**
   - No HTTPS for plug communication
   - Plain HTTP API calls
   - Ensure network isolation if needed

## Common Modification Patterns

### Changing Timer Duration
```yaml
# In schedule_check script, find the time comparison logic
# Currently uses direct hour/minute comparison
# Modify the conditional logic to add duration handling
```

### Adding a Status Indicator
```yaml
# 1. Create a label in the appropriate page
- label:
    id: lbl_new_status
    x: <position>
    y: <position>
    text: "Status"
    text_font: font_small

# 2. Update in lambda or script
- lambda: |-
    lv_label_set_text(id(lbl_new_status), "New Value");
```

### Modifying Button Colors
```yaml
# Change bg_color based on state
- lambda: |-
    lv_obj_set_style_bg_color(id(btn_plug1), lv_color_hex(0x00FF00), 0);
```

## Build & Deployment

### Building Firmware
```bash
# Using ESPHome CLI
esphome compile esp32-s3-waveshare-7in.yaml

# Output will be in .esphome/build/waveshare-esp32-s3-7in/
```

### Uploading
```bash
# Serial upload (first time)
esphome upload esp32-s3-waveshare-7in.yaml

# OTA upload (subsequent updates)
esphome upload esp32-s3-waveshare-7in.yaml --device 192.168.x.x
```

### Logs
```bash
# Monitor logs
esphome logs esp32-s3-waveshare-7in.yaml
```

## Known Issues & Limitations

1. **Keyboard Visibility**: The on-screen keyboard may not appear on the plug_info_page
   - Location: lines 4826-4832
   - Triggered by textarea click events (lines 4616-4823)
   - Check keyboard widget z-index and visibility settings

2. **Fixed IP Addresses**: Plug IPs are configured via substitutions
   - Can be changed at runtime via plug_info_page UI
   - Stored in global string variables
   - Not persisted across reboots (resets to substitution values)

3. **No Time Zone Support**: SNTP time uses UTC
   - Schedule comparisons assume local time zone
   - May need adjustment for daylight saving time

4. **Limited Error Recovery**: HTTP failures mark plugs as "unreachable"
   - No automatic retry mechanism
   - Manual intervention required (refresh or re-check)

## ESPHome Version Requirements

- **Minimum version**: 2025.4.2 (specified in line 14)
- Uses relatively recent LVGL features
- ESP-IDF framework with experimental features
- May not be compatible with older ESPHome versions

## Additional Resources

- ESPHome Documentation: https://esphome.io/
- LVGL Documentation: https://docs.lvgl.io/
- ESP32-S3 Datasheet: https://www.espressif.com/en/products/socs/esp32-s3
- Waveshare Display Info: Check manufacturer documentation for specific model

## Git Workflow

### Branch Strategy
- Development work should be done on feature branches with `claude/` prefix
- Branch naming: `claude/claude-md-<session-id>`
- Never push directly to main/master

### Commit Guidelines
1. Use clear, descriptive commit messages
2. Focus on "why" rather than "what"
3. Commit related changes together
4. Example: "Fix keyboard visibility on plug info page" vs "Update YAML"

### Recent Changes
- Binary firmware files (.bin) are not committed to repository
- YAML configuration is the primary tracked file
- Logs are included for debugging reference

## Tips for AI Assistants

1. **Before Modifying**: Always read the relevant section of the YAML file first
2. **Pattern Matching**: Look for existing patterns (e.g., plug1-8 configurations)
3. **Test Considerations**: Changes to UI require hardware testing (can't be fully simulated)
4. **Backup Strategy**: Large changes should preserve original values in comments
5. **LVGL Syntax**: Be careful with LVGL-specific syntax and indentation
6. **Lambda Expressions**: C++ syntax within YAML strings - watch for escaping
7. **Incremental Changes**: Make small, testable changes rather than large rewrites
8. **Documentation**: Update this file when making architectural changes

## Contact & Support

This is a personal project for the Boven household. For issues or questions, refer to ESPHome community forums or documentation.
