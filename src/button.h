#define noOfButtons 2
#define bounceDelay 20
#define minButtonPress 3
#include <Arduino.h>

const int buttonPins[] = {A2, A3};
uint32_t previousMillis[noOfButtons];
uint8_t pressCount[noOfButtons];
uint8_t counter[noOfButtons];
float size[6] = {0.1, 0.5,  1, 5, 10, 100};
String operation[2] = {"+", "-"};
String pid_status[2] = {"PID", "..."};
int select_size = 0;

int select_channel()
{
    long currentMillis = millis();

    // If select channel not pressed
    if (digitalRead(buttonPins[0]))
    {
        previousMillis[0] = currentMillis;
        pressCount[0] = 0;
    }
    // If select channel pressed
    else
    {
        if (currentMillis - previousMillis[0] > bounceDelay)
        {
            previousMillis[0] = currentMillis;
            ++pressCount[0];
            if (pressCount[0] == minButtonPress)
            {
                counter[0]++;
            }
        }
    }
    if (counter[0] > 6)
    {
        counter[0] = 1;
    }
    else if (counter[0] == 0)
    {
        counter[0] = 1;
    }
    // Serial.println(counter[0]);
    return counter[0];
}

float control_value(float val, float size, String operation_status)
{
    // If plus button not pressed
    long currentMillis = millis();
    if (digitalRead(buttonPins[1]))
    {
        previousMillis[1] = currentMillis;
        pressCount[1] = 0;
        Serial.println(digitalRead(buttonPins[1]));
    }
    // If plus button pressed
    else
    {
        Serial.println(digitalRead(buttonPins[1]));
        if (currentMillis - previousMillis[1] > bounceDelay)
        {
            previousMillis[1] = currentMillis; // Set previousMillis to millis to reset timeout
            ++pressCount[1];
            if (pressCount[1] == minButtonPress)
            // add size
            {
                if (operation_status == "+")
                {

                    val = val + size;
                }
                else
                {
                    val = val - size;
                }
            }
        }
    }
    return val;
}

float change_size()
{
    // If plus button not pressed
    long currentMillis = millis();
    if (digitalRead(buttonPins[1]))
    {
        previousMillis[1] = currentMillis;
        pressCount[1] = 0;
    }
    // If plus button pressed
    else
    {
        if (currentMillis - previousMillis[1] > bounceDelay)
        {
            previousMillis[1] = currentMillis; // Set previousMillis to millis to reset timeout
            ++pressCount[1];
            if (pressCount[1] == minButtonPress)
            // add size
            {
                select_size = select_size + 1;
            }
        }
    }

    if (select_size > 6)
    {
        select_size = 0;
    }
    else if (select_size < 0)
    {
        select_size = 0;
    }
    return size[select_size];
}

String changeOperation()
{
    long currentMillis = millis();
    if (digitalRead(buttonPins[1]))
    {
        previousMillis[1] = currentMillis;
        pressCount[1] = 0;
    }
    // If plus button pressed
    else
    {
        if (currentMillis - previousMillis[1] > bounceDelay)
        {
            previousMillis[1] = currentMillis; // Set previousMillis to millis to reset timeout
            ++pressCount[1];
            if (pressCount[1] == minButtonPress)
            // add size
            {
                select_size = select_size + 1;
            }
        }
    }
    if (select_size > 1)
    {
        select_size = 0;
    }
    else if (select_size < 0)
    {
        select_size = 0;
    }
    return operation[select_size];
}

String doPID()
{
    long currentMillis = millis();
    if (digitalRead(buttonPins[1]))
    {
        previousMillis[1] = currentMillis;
        pressCount[1] = 0;
    }
    // If plus button pressed
    else
    {
        if (currentMillis - previousMillis[1] > bounceDelay)
        {
            previousMillis[1] = currentMillis; // Set previousMillis to millis to reset timeout
            ++pressCount[1];
            if (pressCount[1] == minButtonPress)
            // add size
            {
                select_size = select_size + 1;
            }
        }
    }
    if (select_size > 1)
    {
        select_size = 0;
    }
    else if (select_size < 0)
    {
        select_size = 0;
    }
    return pid_status[select_size];
}