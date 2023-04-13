#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
uint8_t KP_X = 0;
uint8_t KI_X = 0;
uint8_t KD_X = 0;
uint8_t S_X = 70;
uint8_t OP_X = 100;
uint8_t PID_X = 75;
uint8_t KP_Y = 0;
uint8_t KI_Y = 20;
uint8_t KD_Y = 40;
uint8_t S_Y = 20;
uint8_t OP_Y = 0;
uint8_t PID_Y = 40;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void start_display()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.display();
    delay(2000);

    display.clearDisplay();
}

void display_selector(uint16_t select, float kp, float ki, float kd, float size_number, String operation, String PID)
{

    if (select == 1)
    {
        display.setTextSize(2);
        display.setTextColor(BLACK, WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setTextColor(WHITE);
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setTextSize(1);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
    }
    else if (select == 2)
    {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setTextColor(BLACK, WHITE);
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setTextColor(WHITE);
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setTextSize(1);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
    }
    else if (select == 3)
    {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setTextColor(BLACK, WHITE);
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
    }
    else if (select == 4)
    {

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setTextColor(BLACK, WHITE);
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
    }

    else if (select == 5)
    {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setTextSize(1);
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
        display.setTextColor(BLACK, WHITE);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
    }
    else
    {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(KP_X, KP_Y);
        display.print(String(kp, 1));
        display.setCursor(KI_X, KI_Y);
        display.print(String(ki, 1));
        display.setCursor(KD_X, KD_Y);
        display.print(String(kd, 1));
        display.setCursor(OP_X, OP_Y);
        display.print(operation);
        display.setTextSize(1);
        display.setCursor(S_X, S_Y);
        display.print(String(size_number, 1));
        display.setTextColor(BLACK, WHITE);
        display.setCursor(PID_X, PID_Y);
        display.print(PID);
    }
}
