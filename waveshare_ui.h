#pragma once

static const char WAVESHARE_UI_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart-Home Controller</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(180deg, #0A1929 0%, #0F2847 100%);
            color: white;
            min-height: 100vh;
            padding: 10px;
        }
        .page { display: none; max-width: 800px; margin: 0 auto; }
        .page.active { display: block; }
        .header {
            background: linear-gradient(180deg, #1E3A5F 0%, #0F2847 100%);
            padding: 15px;
            text-align: center;
            border-radius: 8px;
            margin-bottom: 20px;
        }
        .header h1 { font-size: 24px; font-weight: normal; }
        .plug-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 20px;
            padding: 20px;
        }
        .plug-row { display: flex; gap: 10px; align-items: center; }
        .plug-btn {
            flex: 2;
            height: 60px;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            color: white;
            cursor: pointer;
            transition: all 0.3s;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .plug-btn.off {
            background: linear-gradient(135deg, #FF0000 0%, #CC0000 100%);
        }
        .plug-btn.on {
            background: linear-gradient(135deg, #00FF00 0%, #00CC00 100%);
        }
        .plug-btn:active { transform: scale(0.98); }
        .timer-btn {
            flex: 1;
            height: 60px;
            background: linear-gradient(135deg, #444444 0%, #333333 100%);
            border: none;
            border-radius: 8px;
            color: white;
            font-size: 14px;
            cursor: pointer;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .timer-btn:active { transform: scale(0.98); }

        /* Timer Page Styles */
        .timer-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 20px;
            background: rgba(30, 58, 95, 0.5);
            border-radius: 8px;
            margin-bottom: 20px;
        }
        .timer-title h2 { font-size: 22px; margin-bottom: 5px; }
        .timer-title .ip { color: #00FF00; font-size: 14px; }
        .back-btn {
            padding: 15px 30px;
            background: #333333;
            border: none;
            border-radius: 8px;
            color: white;
            font-size: 16px;
            cursor: pointer;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .back-btn:active { transform: scale(0.98); }
        .timer-controls { padding: 20px; }
        .timer-toggle {
            width: 100%;
            padding: 20px;
            background: #555555;
            border: none;
            border-radius: 8px;
            color: white;
            font-size: 18px;
            cursor: pointer;
            margin-bottom: 30px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .timer-toggle.enabled {
            background: linear-gradient(135deg, #228B22 0%, #1a6b1a 100%);
        }
        .time-section { margin-bottom: 30px; }
        .time-label {
            font-size: 18px;
            margin-bottom: 15px;
            padding-left: 5px;
        }
        .time-controls { display: flex; gap: 10px; flex-wrap: wrap; }
        .time-btn {
            padding: 15px 20px;
            background: #444444;
            border: none;
            border-radius: 8px;
            color: white;
            font-size: 16px;
            cursor: pointer;
            min-width: 80px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .time-btn:active { transform: scale(0.98); }

        @media (max-width: 600px) {
            .plug-grid { grid-template-columns: 1fr; }
            .header h1 { font-size: 20px; }
            .time-controls { justify-content: center; }
        }
    </style>
</head>
<body>
    <!-- Main Page -->
    <div id="mainPage" class="page active">
        <div class="header">
            <h1>Smart-Home Controller</h1>
        </div>
        <div class="plug-grid">
            <div class="plug-row">
                <button id="plug1Btn" class="plug-btn off" onclick="togglePlug(1)">PLUG 1</button>
                <button class="timer-btn" onclick="showTimerPage(1)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug5Btn" class="plug-btn off" onclick="togglePlug(5)">PLUG 5</button>
                <button class="timer-btn" onclick="showTimerPage(5)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug2Btn" class="plug-btn off" onclick="togglePlug(2)">PLUG 2</button>
                <button class="timer-btn" onclick="showTimerPage(2)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug6Btn" class="plug-btn off" onclick="togglePlug(6)">PLUG 6</button>
                <button class="timer-btn" onclick="showTimerPage(6)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug3Btn" class="plug-btn off" onclick="togglePlug(3)">PLUG 3</button>
                <button class="timer-btn" onclick="showTimerPage(3)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug7Btn" class="plug-btn off" onclick="togglePlug(7)">PLUG 7</button>
                <button class="timer-btn" onclick="showTimerPage(7)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug4Btn" class="plug-btn off" onclick="togglePlug(4)">PLUG 4</button>
                <button class="timer-btn" onclick="showTimerPage(4)">Timer</button>
            </div>
            <div class="plug-row">
                <button id="plug8Btn" class="plug-btn off" onclick="togglePlug(8)">PLUG 8</button>
                <button class="timer-btn" onclick="showTimerPage(8)">Timer</button>
            </div>
        </div>
    </div>

    <!-- Timer Page Template (will be cloned for each plug) -->
    <div id="timerPage1" class="page">
        <div class="timer-header">
            <div class="timer-title">
                <h2 id="timer1Title">PLUG 1 TIMER</h2>
                <div class="ip" id="timer1IP">IP: Loading...</div>
            </div>
            <button class="back-btn" onclick="showMainPage()">BACK</button>
        </div>
        <div class="timer-controls">
            <button id="timer1Toggle" class="timer-toggle" onclick="toggleTimer(1)">Timer: OFF</button>

            <div class="time-section">
                <div class="time-label" id="timer1OnTime">ON: 08:00 AM</div>
                <div class="time-controls">
                    <button class="time-btn" onclick="adjustTime(1, 'on', 'hour', -1)">H-</button>
                    <button class="time-btn" onclick="adjustTime(1, 'on', 'hour', 1)">H+</button>
                    <button class="time-btn" onclick="adjustTime(1, 'on', 'minute', -1)">M-</button>
                    <button class="time-btn" onclick="adjustTime(1, 'on', 'minute', 1)">M+</button>
                    <button class="time-btn" onclick="toggleAMPM(1, 'on')">AM/PM</button>
                </div>
            </div>

            <div class="time-section">
                <div class="time-label" id="timer1OffTime">OFF: 06:00 PM</div>
                <div class="time-controls">
                    <button class="time-btn" onclick="adjustTime(1, 'off', 'hour', -1)">H-</button>
                    <button class="time-btn" onclick="adjustTime(1, 'off', 'hour', 1)">H+</button>
                    <button class="time-btn" onclick="adjustTime(1, 'off', 'minute', -1)">M-</button>
                    <button class="time-btn" onclick="adjustTime(1, 'off', 'minute', 1)">M+</button>
                    <button class="time-btn" onclick="toggleAMPM(1, 'off')">AM/PM</button>
                </div>
            </div>
        </div>
    </div>

    <script>
        // Create timer pages for plugs 2-8
        for (let i = 2; i <= 8; i++) {
            const page1 = document.getElementById('timerPage1');
            const newPage = page1.cloneNode(true);
            newPage.id = `timerPage${i}`;
            newPage.querySelector('h2').id = `timer${i}Title`;
            newPage.querySelector('.ip').id = `timer${i}IP`;
            newPage.querySelector('.timer-toggle').id = `timer${i}Toggle`;
            newPage.querySelector('.timer-toggle').setAttribute('onclick', `toggleTimer(${i})`);
            newPage.querySelectorAll('.time-label')[0].id = `timer${i}OnTime`;
            newPage.querySelectorAll('.time-label')[1].id = `timer${i}OffTime`;

            const timeButtons = newPage.querySelectorAll('.time-btn');
            timeButtons[0].setAttribute('onclick', `adjustTime(${i}, 'on', 'hour', -1)`);
            timeButtons[1].setAttribute('onclick', `adjustTime(${i}, 'on', 'hour', 1)`);
            timeButtons[2].setAttribute('onclick', `adjustTime(${i}, 'on', 'minute', -1)`);
            timeButtons[3].setAttribute('onclick', `adjustTime(${i}, 'on', 'minute', 1)`);
            timeButtons[4].setAttribute('onclick', `toggleAMPM(${i}, 'on')`);
            timeButtons[5].setAttribute('onclick', `adjustTime(${i}, 'off', 'hour', -1)`);
            timeButtons[6].setAttribute('onclick', `adjustTime(${i}, 'off', 'hour', 1)`);
            timeButtons[7].setAttribute('onclick', `adjustTime(${i}, 'off', 'minute', -1)`);
            timeButtons[8].setAttribute('onclick', `adjustTime(${i}, 'off', 'minute', 1)`);
            timeButtons[9].setAttribute('onclick', `toggleAMPM(${i}, 'off')`);

            document.body.appendChild(newPage);
        }

        // State management
        const plugStates = {};
        const timerStates = {};

        for (let i = 1; i <= 8; i++) {
            plugStates[i] = { name: `PLUG ${i}`, ip: '', state: false };
            timerStates[i] = {
                enabled: false,
                onHour: 8,
                onMinute: 0,
                onAMPM: 'AM',
                offHour: 6,
                offMinute: 0,
                offAMPM: 'PM'
            };
        }

        // Navigation
        function showMainPage() {
            document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
            document.getElementById('mainPage').classList.add('active');
        }

        function showTimerPage(plugNum) {
            document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
            document.getElementById(`timerPage${plugNum}`).classList.add('active');
            updateTimerDisplay(plugNum);
        }

        // Plug control
        async function togglePlug(plugNum) {
            const btn = document.getElementById(`plug${plugNum}Btn`);
            btn.disabled = true;

            try {
                const action = plugStates[plugNum].state ? 'turn_off' : 'turn_on';
                await fetch(`/button/plug${plugNum}_${action}/press`, { method: 'POST' });

                plugStates[plugNum].state = !plugStates[plugNum].state;
                updatePlugButton(plugNum);

                setTimeout(() => updatePlugStates(), 500);
            } catch (error) {
                console.error('Error toggling plug:', error);
            } finally {
                btn.disabled = false;
            }
        }

        function updatePlugButton(plugNum) {
            const btn = document.getElementById(`plug${plugNum}Btn`);
            const state = plugStates[plugNum];
            btn.textContent = state.name;
            btn.className = `plug-btn ${state.state ? 'on' : 'off'}`;
        }

        // Timer control
        async function toggleTimer(plugNum) {
            const enabled = !timerStates[plugNum].enabled;
            timerStates[plugNum].enabled = enabled;

            try {
                await fetch(`/switch/plug${plugNum}_schedule/turn_${enabled ? 'on' : 'off'}`, { method: 'POST' });
                updateTimerDisplay(plugNum);
            } catch (error) {
                console.error('Error toggling timer:', error);
            }
        }

        async function adjustTime(plugNum, type, unit, delta) {
            const state = timerStates[plugNum];
            const prefix = type === 'on' ? 'on' : 'off';

            if (unit === 'hour') {
                let hour = state[`${prefix}Hour`];
                hour += delta;
                if (hour < 1) hour = 12;
                if (hour > 12) hour = 1;
                state[`${prefix}Hour`] = hour;

                await fetch(`/number/plug${plugNum}_${type}_hour/set?value=${hour}`, { method: 'POST' });
            } else {
                let minute = state[`${prefix}Minute`];
                minute += delta;
                if (minute < 0) minute = 59;
                if (minute > 59) minute = 0;
                state[`${prefix}Minute`] = minute;

                await fetch(`/number/plug${plugNum}_${type}_minute/set?value=${minute}`, { method: 'POST' });
            }

            updateTimerDisplay(plugNum);
        }

        async function toggleAMPM(plugNum, type) {
            const state = timerStates[plugNum];
            const prefix = type === 'on' ? 'on' : 'off';
            const current = state[`${prefix}AMPM`];
            const newVal = current === 'AM' ? 'PM' : 'AM';
            state[`${prefix}AMPM`] = newVal;

            await fetch(`/select/plug${plugNum}_${type}_ampm/set?option=${newVal}`, { method: 'POST' });
            updateTimerDisplay(plugNum);
        }

        function updateTimerDisplay(plugNum) {
            const state = timerStates[plugNum];

            document.getElementById(`timer${plugNum}Title`).textContent = `${plugStates[plugNum].name} TIMER`;
            document.getElementById(`timer${plugNum}IP`).textContent = `IP: ${plugStates[plugNum].ip || 'Not Set'}`;

            const toggleBtn = document.getElementById(`timer${plugNum}Toggle`);
            toggleBtn.textContent = `Timer: ${state.enabled ? 'ON' : 'OFF'}`;
            toggleBtn.className = `timer-toggle ${state.enabled ? 'enabled' : ''}`;

            document.getElementById(`timer${plugNum}OnTime`).textContent =
                `ON: ${String(state.onHour).padStart(2, '0')}:${String(state.onMinute).padStart(2, '0')} ${state.onAMPM}`;
            document.getElementById(`timer${plugNum}OffTime`).textContent =
                `OFF: ${String(state.offHour).padStart(2, '0')}:${String(state.offMinute).padStart(2, '0')} ${state.offAMPM}`;
        }

        // Fetch states from ESPHome
        async function updatePlugStates() {
            try {
                const response = await fetch('/text');
                const data = await response.json();

                for (let i = 1; i <= 8; i++) {
                    const nameObj = data.find(t => t.id === `plug${i}_name`);
                    const ipObj = data.find(t => t.id === `plug${i}_ip`);

                    if (nameObj) plugStates[i].name = nameObj.value || `PLUG ${i}`;
                    if (ipObj) plugStates[i].ip = ipObj.value || '';

                    updatePlugButton(i);
                }
            } catch (error) {
                console.error('Error fetching states:', error);
            }

            try {
                const response = await fetch('/binary_sensor');
                const data = await response.json();

                for (let i = 1; i <= 8; i++) {
                    const stateObj = data.find(s => s.id === `plug${i}_state`);
                    if (stateObj) {
                        plugStates[i].state = stateObj.value === 'ON';
                        updatePlugButton(i);
                    }
                }
            } catch (error) {
                console.error('Error fetching binary sensor states:', error);
            }
        }

        async function updateTimerSettings() {
            try {
                const [switches, numbers, selects] = await Promise.all([
                    fetch('/switch').then(r => r.json()),
                    fetch('/number').then(r => r.json()),
                    fetch('/select').then(r => r.json())
                ]);

                for (let i = 1; i <= 8; i++) {
                    const scheduleSwitch = switches.find(s => s.id === `plug${i}_schedule`);
                    if (scheduleSwitch) {
                        timerStates[i].enabled = scheduleSwitch.value === 'ON';
                    }

                    const onHour = numbers.find(n => n.id === `plug${i}_on_hour`);
                    const onMinute = numbers.find(n => n.id === `plug${i}_on_minute`);
                    const offHour = numbers.find(n => n.id === `plug${i}_off_hour`);
                    const offMinute = numbers.find(n => n.id === `plug${i}_off_minute`);

                    if (onHour) timerStates[i].onHour = parseInt(onHour.value);
                    if (onMinute) timerStates[i].onMinute = parseInt(onMinute.value);
                    if (offHour) timerStates[i].offHour = parseInt(offHour.value);
                    if (offMinute) timerStates[i].offMinute = parseInt(offMinute.value);

                    const onAMPM = selects.find(s => s.id === `plug${i}_on_ampm`);
                    const offAMPM = selects.find(s => s.id === `plug${i}_off_ampm`);

                    if (onAMPM) timerStates[i].onAMPM = onAMPM.value;
                    if (offAMPM) timerStates[i].offAMPM = offAMPM.value;
                }
            } catch (error) {
                console.error('Error fetching timer settings:', error);
            }
        }

        // Initialize
        async function init() {
            await updatePlugStates();
            await updateTimerSettings();

            for (let i = 1; i <= 8; i++) {
                updatePlugButton(i);
                updateTimerDisplay(i);
            }

            setInterval(updatePlugStates, 5000);
            setInterval(updateTimerSettings, 10000);
        }

        init();
    </script>
</body>
</html>
)rawliteral";
