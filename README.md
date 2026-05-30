# Air Quality Monitoring System 

A low-cost air quality monitoring system built with Arduino, using an MQ-135 gas sensor and a DHT11 temperature & humidity sensor. The goal was simple — build something that actually works without spending a ton of money on commercial AQI monitors.

This project is part of a research paper on cost-efficient air quality monitoring. You can find the paper in the `/paper` folder.

---

## Why I Built This

Air quality monitors are expensive. The good ones cost thousands of rupees and most people, especially in residential areas, don't have access to real-time AQI data. This project is an attempt to fix that using components that cost a fraction of the price — the entire hardware setup comes under ₹[your cost here].

It's not perfect. It won't match a CPCB-grade sensor. But it gives you a solid approximate reading and honestly, that's good enough for most everyday use cases.

---

## Hardware Used

| Component | Purpose |
|-----------|---------|
| Arduino Uno (or Nano) | Microcontroller |
| MQ-135 Gas Sensor | Detects gases like NH3, CO2, benzene, NOx |
| DHT11 Sensor | Measures temperature and humidity |
| 16x2 I2C LCD (0x27) | Displays live readings |
| Green LED | Safe air quality indicator |
| Yellow LED | Moderate air quality indicator |
| Red LED | Danger / high temp indicator |
| Buzzer | Alert when air quality is dangerous |
| Jumper wires + breadboard | Connections |

---

## Pin Configuration

| Component | Arduino Pin |
|-----------|------------|
| MQ-135 | A0 |
| DHT11 | D4 |
| Buzzer | D8 |
| Green LED | D9 |
| Yellow LED | D10 |
| Red LED | D11 |
| LCD | SDA / SCL (I2C) |

---

## How It Works

- The **MQ-135** reads gas concentration from the surrounding air and outputs a raw analog value (0–1023). This value is used to classify air quality into three levels.
- The **DHT11** reads temperature and humidity. If temperature crosses 35°C, the system automatically escalates to a danger alert regardless of gas readings.
- **LEDs and buzzer** give instant visual and audio feedback based on the current air quality level.
- AQI categories are loosely based on **India's National Air Quality Index (NAQI)** standard by CPCB:

| Raw Analog Value | Status | Indicator |
|-----------------|--------|-----------|
| < 300 | SAFE | Green LED |
| 300 – 499 | MODERATE | Yellow LED |
| ≥ 500 | DANGER | Red LED + Buzzer |

> **Note:** This system uses raw analog sensor values for classification, not converted PPM readings. It provides a directional air quality estimate, not a certified NAQI reading. PM2.5 and PM10 are not measured.

---

## Circuit Setup

### Schematic
![Fritzing Diagram](https://github.com/user-attachments/assets/19c5f52e-73e3-43cc-aa38-e6cae7ef902d)

### Actual Build
![Hardware Prototype](https://github.com/user-attachments/assets/cfc69da5-4b8a-4954-a16e-1693d7065c85 )

---

## Getting Started

### Prerequisites

Install these libraries in the Arduino IDE before uploading:

- `DHT.h` — for the DHT11 temperature & humidity sensor
- `LiquidCrystal_I2C.h` — for the I2C LCD display
- `Wire.h` — comes pre-installed with Arduino IDE

### Important: Sensor Warm-Up

The MQ-135 needs to warm up for **at least 24–48 hours** before readings stabilize. Skipping this will give inaccurate baseline values. This is not optional.

### Upload

1. Clone this repo
2. Open `aqi_monitor.ino` in Arduino IDE
3. Install the required libraries
4. Select your board and COM port, then upload

---

## Sample Output

Serial monitor output (9600 baud):
```
AQ: 214 | Temp: 28.4C | Hum: 62%
AQ: 231 | Temp: 28.5C | Hum: 61%
```

LCD display:
```
AQ:214 SAFE
T:28.4C H:62%
```

---

## Research Paper

This project is documented in a research paper focused on the feasibility of low-cost AQI monitoring systems. The paper covers sensor analysis, limitations of budget hardware, and real-world testing.

📄 Find it here: [`/paper`](finalreport_digital.pdf)

---

## Limitations

Being upfront about this:

- MQ-135 uses raw analog values for classification, not calibrated PPM readings. Thresholds may need adjustment based on your environment.
- PM2.5 and PM10 are not measured (would need a separate dust sensor like the GP2Y1010AU0F).
- DHT11 has limited accuracy (±2°C, ±5% RH) — DHT22 would be better if you want more precision.
- Readings can drift with humidity and temperature changes.
- Results should be treated as approximate, not absolute.

---

## Future Improvements

- Add a dust/particulate sensor for PM2.5 and PM10
- Convert raw MQ-135 values to actual PPM using a proper calibration formula
- Replace DHT11 with DHT22 for better accuracy
- Log data to an SD card or send it to a cloud dashboard (Firebase / ThingSpeak)

---

## License

Open source — feel free to use, modify, and build on this. If you use it in your own project or paper, a credit would be appreciated.

---

*Built as part of a research project on affordable air quality monitoring.*
