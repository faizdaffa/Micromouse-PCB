#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
uint8_t KP_X = 0;
uint8_t KI_X = 0;
uint8_t KD_X = 0;
uint8_t OP_X = 30;
uint8_t S_X  = 20;
uint8_t START_X = 87;
uint8_t Swipe_TAB_X = 110;
uint8_t KP_Y = 0;
uint8_t KI_Y = 20;
uint8_t KD_Y = 40;
uint8_t OP_Y = 0;
uint8_t S_Y  = 20;
uint8_t START_Y = 0;
uint8_t Swipe_TAB_Y = 48;

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

void display_selector(uint16_t tab, uint16_t select, float kp, float ki, float kd, String operation, float size_number, String Swipe_TAB, String START)
{
    if (tab == 0)
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
            display.setCursor(Swipe_TAB_X,Swipe_TAB_Y);
            display.print(Swipe_TAB);
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
            display.setCursor(KD_X, KD_Y);
            display.print(String(kd, 1));
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
        }
        else if (select == 3)
        {
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(KP_X, KP_Y);
            display.print(String(kp, 1));
            display.setCursor(KI_X, KI_Y);
            display.print(String(ki, 1));
            display.setTextColor(BLACK, WHITE);
            display.setCursor(KD_X, KD_Y);
            display.print(String(kd, 1));
            display.setTextColor(WHITE);
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
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
            display.setTextColor(BLACK, WHITE);
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
        }
    }
    else if (tab == 1)
    {
        if (select == 1)
        {
            display.setTextSize(2);
            display.setTextColor(BLACK, WHITE);
            display.setCursor(OP_X, OP_Y);
            display.print(operation);
            display.setTextColor(WHITE);
            display.setCursor(S_X, S_Y);
            display.print(String(size_number, 1));
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
            display.setCursor(START_X, START_Y);
            display.print(START);
        }
        else if (select == 2)
        {
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(OP_X, OP_Y);
            display.print(operation);
            display.setTextColor(BLACK, WHITE);
            display.setCursor(S_X, S_Y);
            display.print(String(size_number, 1));
            display.setTextColor(WHITE);
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
            display.setCursor(START_X, START_Y);
            display.print(START);
        }
        else if (select == 3)
        {
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(OP_X, OP_Y);
            display.print(operation);
            display.setCursor(S_X, S_Y);
            display.print(String(size_number, 1));
            display.setTextColor(BLACK, WHITE);
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
            display.setTextColor(WHITE);
            display.setCursor(START_X, START_Y);
            display.print(START);
        }
        else
        {
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(OP_X, OP_Y);
            display.print(operation);
            display.setCursor(S_X, S_Y);
            display.print(String(size_number, 1));
            display.setCursor(Swipe_TAB_X, Swipe_TAB_Y);
            display.print(Swipe_TAB);
            display.setTextColor(BLACK, WHITE);
            display.setCursor(START_X, START_Y);
            display.print(START);
        }
    }
}