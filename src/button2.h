#define noOfButtons 2
#define bounceDelay 20
#define minButtonPress 3
#include <Arduino.h>

const int buttonPins[] = {A2, A3};
uint32_t previousMillis[noOfButtons];
uint8_t pressCount[noOfButtons];
uint8_t counter[noOfButtons]; //2 nilai, 

uint8_t tab = 0;
int control[4] = {0, 0, 0, 0}; // tab, size, operation
float size[6] = {0.1, 0.5,  1, 5, 10, 100};
String operation[2] = {"+", "-"};
String mulai[2] = {"OP", "GO!"};


int select_tab()
{
    long currentMillis = millis();

    // If select tab not pressed
    if (digitalRead(buttonPins[1]))
    {
        previousMillis[1] = currentMillis;
        pressCount[1] = 0;
    }
    // If select tab pressed
    else
    {
        if (currentMillis - previousMillis[1] > bounceDelay)
        {
            previousMillis[1] = currentMillis;
            ++pressCount[1];
            if (pressCount[1] == minButtonPress)
            {
                control[0]++; 
            }
        }
    }
    if (control[0] > 1)
    {
        control[0] = 0;
     }
    
    return control[0];
}

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
    if (counter[0] > 5)
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
    }
    // If plus button pressed
    else
    {
        //Serial.println(digitalRead(buttonPins[1]));
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
                control[1] = control[1] + 1;
            }
        }
    }

    if (control[1] > 6)
    {
        control[1] = 0;
    }
    else if (control[1] < 0)
    {
        control[1] = 0;
    }
    return size[control[1]];
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
                control[2] = control[2] + 1;
            }
        }
    }
    if (control[2] > 1)
    {
        control[2] = 0;
    }
    else if (control[2] < 0)
    {
        control[2] = 0;
    }
    return operation[control[2]];
}

/*String move_tab()
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
                control[3] = control[3] + 1;
            }
        }
    }
    if (control[3] > 1)
    {
        control[3] = 0;
    }
    else if (control[3] < 0)
    {
        control[3] = 0;
    }
    return tab_symbol[control[3]];
}*/