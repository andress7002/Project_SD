#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// Initialize the OLED using hardware I2C (PB6=SCL, PB7=SDA)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0);

void drawBatteryIcon(int x, int y, int level) {
    // Battery outline
    oled.drawFrame(x, y, 30, 12);   // outer battery frame
    oled.drawBox(x + 30, y + 3, 3, 6); // battery terminal

    // Battery fill (level from 0–100)
    int filledWidth = (level * 28) / 100;
    oled.drawBox(x + 1, y + 1, filledWidth, 10);
}

void setup() {
    // Initialize I2C on PB6/PB7
    Wire.setSCL(PB6);
    Wire.setSDA(PB7);
    Wire.begin();

    // Initialize the OLED
    oled.begin();
}

void loop() {
    // Example sensor values (replace later with real data)
    int batteryLevel = 70;      // %
    float voltage = 3.92;       // V
    float temperature = 28.4;   // °C

    oled.clearBuffer();

    // Title
    oled.setFont(u8g2_font_6x10_tf);
    oled.drawStr(0, 10, "Battery %");

    // Draw battery UI icon
    drawBatteryIcon(90, 2, batteryLevel);

    // Display voltage
    oled.setCursor(0, 28);
    oled.print("Voltage: ");
    oled.print(voltage, 2);
    oled.print("V");

    // Display temperature
    oled.setCursor(0, 45);
    oled.print("Temp: ");
    oled.print(temperature, 1);
    oled.print("C");

    oled.sendBuffer();

    delay(200);
}