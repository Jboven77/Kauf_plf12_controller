#!/usr/bin/env python3
"""Generate YAML components for plugs 9-12"""

def generate_plug_components(plug_num):
    """Generate all YAML components for a single plug"""

    # Binary sensor
    binary_sensor = f"""  # Plug {plug_num} State
  - platform: template
    id: plug{plug_num}_state
    name: "Plug {plug_num} State"
    device_class: power
    lambda: |-
      return false;  // Updated by HTTP response
"""

    # Switch
    switch = f"""  # Plug {plug_num} Schedule
  - platform: template
    id: plug{plug_num}_schedule
    name: "Plug {plug_num} Schedule"
    optimistic: true
    restore_mode: RESTORE_DEFAULT_OFF
    lambda: |-
      return id(plug{plug_num}_schedule_persist);
    turn_on_action:
      - lambda: id(plug{plug_num}_schedule_persist) = true;
    turn_off_action:
      - lambda: id(plug{plug_num}_schedule_persist) = false;
"""

    # Numbers (hour and minute for ON and OFF)
    numbers = f"""  # Plug {plug_num} Timer Hour/Minute Controls
  - platform: template
    id: plug{plug_num}_on_hour
    name: "Plug {plug_num} ON Hour"
    optimistic: true
    min_value: 1
    max_value: 12
    step: 1
    initial_value: 8
    lambda: |-
      return id(plug{plug_num}_on_hour_persist);
    set_action:
      - lambda: id(plug{plug_num}_on_hour_persist) = x;

  - platform: template
    id: plug{plug_num}_on_minute
    name: "Plug {plug_num} ON Minute"
    optimistic: true
    min_value: 0
    max_value: 59
    step: 1
    initial_value: 0
    lambda: |-
      return id(plug{plug_num}_on_minute_persist);
    set_action:
      - lambda: id(plug{plug_num}_on_minute_persist) = x;

  - platform: template
    id: plug{plug_num}_off_hour
    name: "Plug {plug_num} OFF Hour"
    optimistic: true
    min_value: 1
    max_value: 12
    step: 1
    initial_value: 6
    lambda: |-
      return id(plug{plug_num}_off_hour_persist);
    set_action:
      - lambda: id(plug{plug_num}_off_hour_persist) = x;

  - platform: template
    id: plug{plug_num}_off_minute
    name: "Plug {plug_num} OFF Minute"
    optimistic: true
    min_value: 0
    max_value: 59
    step: 1
    initial_value: 0
    lambda: |-
      return id(plug{plug_num}_off_minute_persist);
    set_action:
      - lambda: id(plug{plug_num}_off_minute_persist) = x;
"""

    # Selects (AM/PM)
    selects = f"""  # Plug {plug_num} AM/PM Selects
  - platform: template
    id: plug{plug_num}_on_ampm
    name: "Plug {plug_num} ON AM/PM"
    optimistic: true
    options:
      - "AM"
      - "PM"
    initial_option: "AM"
    lambda: |-
      return id(plug{plug_num}_on_ampm_persist);
    set_action:
      - lambda: id(plug{plug_num}_on_ampm_persist) = x;

  - platform: template
    id: plug{plug_num}_off_ampm
    name: "Plug {plug_num} OFF AM/PM"
    optimistic: true
    options:
      - "AM"
      - "PM"
    initial_option: "PM"
    lambda: |-
      return id(plug{plug_num}_off_ampm_persist);
    set_action:
      - lambda: id(plug{plug_num}_off_ampm_persist) = x;
"""

    # Buttons
    buttons = f"""  # Plug {plug_num} Control Buttons
  - platform: template
    name: "Plug {plug_num} Turn On"
    id: plug{plug_num}_turn_on
    on_press:
      - script.execute: plug{plug_num}_turn_on

  - platform: template
    name: "Plug {plug_num} Turn Off"
    id: plug{plug_num}_turn_off
    on_press:
      - script.execute: plug{plug_num}_turn_off
"""

    # Scripts
    scripts = f"""  # Plug {plug_num} Scripts
  - id: plug{plug_num}_turn_on
    then:
      - http_request.post:
          url: !lambda |-
            return std::string("http://") + id(plug{plug_num}_ip).state + std::string("/switch/kauf_plug/turn_on");

  - id: plug{plug_num}_turn_off
    then:
      - http_request.post:
          url: !lambda |-
            return std::string("http://") + id(plug{plug_num}_ip).state + std::string("/switch/kauf_plug/turn_off");
"""

    # Timer check lambda snippet
    timer_check = f"""          // Plug {plug_num} Schedule Check
          if (id(plug{plug_num}_schedule_persist)) {{
            int on_h = to_24h(id(plug{plug_num}_on_hour_persist), id(plug{plug_num}_on_ampm_persist));
            int off_h = to_24h(id(plug{plug_num}_off_hour_persist), id(plug{plug_num}_off_ampm_persist));

            if (current_hour == on_h && current_minute == id(plug{plug_num}_on_minute_persist)) {{
              ESP_LOGI("Timer", "Turning ON Plug {plug_num}");
              id(plug{plug_num}_turn_on).execute();
            }}
            if (current_hour == off_h && current_minute == id(plug{plug_num}_off_minute_persist)) {{
              ESP_LOGI("Timer", "Turning OFF Plug {plug_num}");
              id(plug{plug_num}_turn_off).execute();
            }}
          }}
"""

    return {
        'binary_sensor': binary_sensor,
        'switch': switch,
        'numbers': numbers,
        'selects': selects,
        'buttons': buttons,
        'scripts': scripts,
        'timer_check': timer_check
    }

# Generate for plugs 9-12
print("=" * 80)
print("BINARY SENSORS")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['binary_sensor'])

print("\n" + "=" * 80)
print("SWITCHES")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['switch'])

print("\n" + "=" * 80)
print("NUMBERS")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['numbers'])

print("\n" + "=" * 80)
print("SELECTS")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['selects'])

print("\n" + "=" * 80)
print("BUTTONS")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['buttons'])

print("\n" + "=" * 80)
print("SCRIPTS")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['scripts'])

print("\n" + "=" * 80)
print("TIMER CHECKS (add to interval lambda)")
print("=" * 80)
for i in range(9, 13):
    print(generate_plug_components(i)['timer_check'])
