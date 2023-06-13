#include "bluetooth.h"

void printArray(float arr[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        Serial.println(arr[i]);
    }
    Serial.println();
}

float *parse_data(float values[], int arraySize)
{
    int index = 0;
    String receivedData = bluetooth.readStringUntil('\n'); // Read the received data until newline character

    char charBuffer[receivedData.length() + 1];               // Create a character array to store the parsed values
    receivedData.toCharArray(charBuffer, sizeof(charBuffer)); // Convert the received data to a character array

    char *token = strtok(charBuffer, ","); // Split the string using the comma delimiter

    while (token != NULL && index < arraySize)
    {
        float value = atof(token); // Convert the token to a float

        // Store the value in the array
        values[index] = value;

        index++;                   // Increment the index
        token = strtok(NULL, ","); // Get the next token
    }

    if (index >= arraySize)
    {
        Serial.println("Values:");
        index = 0;
        printArray(values, arraySize);
        memset(values, 0, sizeof(float) * arraySize);
    }

    return values;
}
