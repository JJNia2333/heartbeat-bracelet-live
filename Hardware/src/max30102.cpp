#include "max30102.h"
#include "printToPC.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 20; // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];    // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; // Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
int beat_temp;
void MAX30102_Init()
{
    // Initialize sensor
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // Use default I2C port, 400kHz speed
        printf("[ERROR]: MAX30102 was not found. Please check wiring/power. \n");
    else
        printf("[SUCCESS]: MAX30102 found. \n");

    particleSensor.setup();                    // Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0);  // Turn off Green LED
}

void getHeartRate_task(void *pvParameters)
{
    long irValue;
    while (1)
    {
        irValue = particleSensor.getIR();

        if (irValue < 50000)
        {
            print_msg_t print_msg;
            print_msg.enable_print = PRINT_ENABLE;
            print_msg.heart_rate = 0;
            xQueueSend(print_msg_queue, &print_msg, portMAX_DELAY);
            continue;
        }

        if (checkForBeat(irValue) == true)
        {
            // We sensed a beat!
            long delta = millis() - lastBeat;
            lastBeat = millis();

            beatsPerMinute = 60 / (delta / 1000.0);

            if (beatsPerMinute < 255 && beatsPerMinute > 20)
            {
                rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
                rateSpot %= RATE_SIZE;                    // Wrap variable

                // Take average of readings
                beatAvg = 0;
                for (byte x = 0; x < RATE_SIZE; x++)
                    beatAvg += rates[x];
                beatAvg /= RATE_SIZE;

                if (beat_temp != beatAvg)
                {
                    beat_temp = beatAvg;
                    print_msg_t print_msg;
                    print_msg.enable_print = PRINT_ENABLE;
                    print_msg.heart_rate = beatAvg;
                    xQueueSend(print_msg_queue, &print_msg, portMAX_DELAY);
                }
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}