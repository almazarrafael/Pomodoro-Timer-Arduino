#include <LiquidCrystal.h>

int modeButton = 7;
int pauseButton = 6;

int currentSec = 0;
int modeSec[] = {1500, 300, 600};

int currentMode = 0;
String mode[] = {"Study", "Short Break", "Long Break"};

int timer = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int i = 0;
int reading = LOW;

boolean pause = false;
int pausedTime;

int ledPins[] = {10, 9, 8};

void setup()
{
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(modeButton, INPUT);
    pinMode(pauseButton, INPUT);
    lcd.begin(16, 2);
}

void loop()
{
    while(true) {

        delay(1000);

        if (pause) {
            if (digitalRead(pauseButton) == HIGH) {
                pause = false;
                currentSec = pausedTime;
                timer = pausedTime;
            }
            else {
                lcd.clear();
                lcd.print("Paused");
                lcd.setCursor(0, 1);
                lcd.print(pausedTime);
                break;
            }
        }
        else {
            currentSec = modeSec[currentMode];
            timer = currentSec;
        }

        lcd.setCursor(0, 0);
        lcd.print(mode[currentMode]);
        for (i = 0; i < sizeof(ledPins); i++) {
            digitalWrite(ledPins[i], LOW); 
        }
        digitalWrite(ledPins[currentMode], HIGH);
        lcd.setCursor(0, 1);

        delay(1000);

        for (i = 0; i < currentSec; i++) {
            reading = digitalRead(modeButton);
          	lcd.print(timer);
            delay(1000);
            timer--;
            lcd.clear();
            lcd.print(mode[currentMode]);
            lcd.setCursor(0, 1);
            if (digitalRead(pauseButton) == HIGH) {
                pause = true;
                pausedTime = timer;
                break;
            }
            if (reading == HIGH) {
                if (currentMode == 2) {
                    currentMode = 0;
                    break;
                }
                else {
                    currentMode++;
                    break;
                }
                break;
            } 
        }
    }
}