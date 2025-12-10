# AVR Frequency/Period Counter

This project implements a frequency/period counter on the **ATmega328P** microcontroller using **Timer1 in input capture mode**. It precisely measures the time interval between consecutive rising edges of an external digital signal applied to the ICP1 pin (PD6). Timer overflows are counted to accurately handle long periods, and the total timer tick count (with /64 prescaler) is displayed on a 16×2 character LCD.

The system uses interrupt-driven input capture and overflow handling for reliable, real-time measurements—ideal for embedded instrumentation or signal analysis tasks.

> ⚠️ **Note**: A known bug exists in the period calculation logic when the timer wraps between captures. The line `result += 65536 - tmp - tmp_old;` should be corrected to `result += 65536 - tmp_old + tmp;` for accurate results.

---

**Features**  
- Input capture on rising edge (ICP1 pin)  
- Timer1 overflow handling  
- LCD display of raw period in timer ticks  
- Written for CodeVisionAVR (uses `interrupt [vector]` syntax)

**Hardware**  
- ATmega328P  
- 16×2 Alphanumeric LCD (connected via standard parallel interface)  
- External signal source on PD6 (ICP1)

**Usage**  
Compile with CodeVisionAVR and upload to ATmega328P. Apply a digital signal (e.g., square wave) to PD6 to see the measured period (in timer ticks) on the LCD.

