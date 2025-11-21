#pragma once
#include "esphome.h"

namespace esphome {

class CustomWebDashboard : public Component {
 public:
  void setup() override {
    ESP_LOGI("custom_web", "Custom dashboard component initialized");
  }

  void loop() override {}

  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }

  static const char* get_dashboard_html() {
    return R"html(<!DOCTYPE html>
<html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>Smart-Home Controller</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:Arial,sans-serif;background:linear-gradient(180deg,#0A1929 0%,#1E3A5F 100%);color:#fff;min-height:100vh;padding:20px}
.header{text-align:center;padding:15px;background:linear-gradient(180deg,#1E3A5F 0%,#0F2847 100%);border-radius:15px;margin-bottom:30px;box-shadow:0 4px 15px rgba(0,0,0,.3)}
.header h1{font-size:28px;margin:0}
.grid{display:grid;grid-template-columns:repeat(2,1fr);gap:20px;max-width:900px;margin:0 auto}
.plug-row{display:flex;gap:10px;align-items:center}
.plug-btn{flex:2;height:70px;border:none;border-radius:15px;font-size:20px;font-weight:700;color:#fff;cursor:pointer;transition:all .3s ease;box-shadow:0 4px 8px rgba(0,0,0,.4);position:relative}
.plug-btn.off{background:#f00}
.plug-btn.on{background:#228B22}
.plug-btn:active{transform:translateY(2px);box-shadow:0 2px 4px rgba(0,0,0,.4)}
.timer-btn{flex:1;height:70px;border:none;border-radius:15px;font-size:16px;font-weight:700;color:#fff;cursor:pointer;transition:all .3s ease;box-shadow:0 4px 8px rgba(0,0,0,.4);background:#444}
.timer-btn:active{transform:translateY(2px);box-shadow:0 2px 4px rgba(0,0,0,.4)}
.status{font-size:14px;position:absolute;bottom:5px;right:10px;opacity:.8}
.loading{opacity:.6;pointer-events:none}
@media (max-width:768px){.grid{grid-template-columns:1fr}.plug-btn{font-size:18px}.header h1{font-size:24px}}
</style></head><body>
<div class="header"><h1>Smart-Home Controller</h1></div>
<div class="grid">
<div class="plug-row"><button class="plug-btn off" id="p1" onclick="t(1)">PLUG 1<span class="status" id="s1">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p5" onclick="t(5)">PLUG 5<span class="status" id="s5">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p2" onclick="t(2)">PLUG 2<span class="status" id="s2">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p6" onclick="t(6)">PLUG 6<span class="status" id="s6">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p3" onclick="t(3)">PLUG 3<span class="status" id="s3">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p7" onclick="t(7)">PLUG 7<span class="status" id="s7">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p4" onclick="t(4)">PLUG 4<span class="status" id="s4">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
<div class="plug-row"><button class="plug-btn off" id="p8" onclick="t(8)">PLUG 8<span class="status" id="s8">OFF</span></button><button class="timer-btn" onclick="location.href='/config'">Timer</button></div>
</div>
<script>
const ips={1:'192.168.68.79',2:'192.168.68.77',3:'192.168.68.76',4:'192.168.68.75',5:'192.168.68.203',6:'192.168.68.204',7:'192.168.68.205',8:'192.168.68.206'};
async function t(n){const b=document.getElementById('p'+n),s=document.getElementById('s'+n),o=b.classList.contains('on');b.classList.add('loading');
try{await fetch(`http://${ips[n]}/switch/kauf_plug/${o?'turn_off':'turn_on'}`,{method:'POST',mode:'no-cors'});
b.classList.toggle('on');b.classList.toggle('off');s.textContent=o?'OFF':'ON'}catch(e){console.error(e)}finally{b.classList.remove('loading')}}
async function c(n){try{const r=await fetch(`http://${ips[n]}/switch/kauf_plug`),d=await r.json(),b=document.getElementById('p'+n),s=document.getElementById('s'+n);
if(d.state==='ON'){b.classList.remove('off');b.classList.add('on');s.textContent='ON'}else{b.classList.remove('on');b.classList.add('off');s.textContent='OFF'}}catch(e){}}
window.addEventListener('load',()=>{for(let i=1;i<=8;i++)c(i)});
setInterval(()=>{for(let i=1;i<=8;i++)c(i)},5000);
</script>
</body></html>)html";
  }
};

}  // namespace esphome
