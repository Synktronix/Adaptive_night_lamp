 
#define LDR_PIN A0
#define LED_PIN 9

#define DARK_THRESHOLD   800
#define BRIGHT_THRESHOLD 200

int ldrValue = 0;
int brightness = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(LDR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    analogWrite(LED_PIN, 0);

    Serial.println("Adaptive Light System Started");
}

void loop()
{
    // Read LDR: 0 to 1023 on Arduino UNO
    ldrValue = analogRead(LDR_PIN);

    // Higher reading means darker conditions
    if (ldrValue <= BRIGHT_THRESHOLD)
    {
        brightness = 0;
    }
    else if (ldrValue >= DARK_THRESHOLD)
    {
        brightness = 255;
    }
    else
    {
        brightness = map(
            ldrValue,
            BRIGHT_THRESHOLD,
            DARK_THRESHOLD,
            0,
            255
        );
    }

    // Generate PWM output on D9
    analogWrite(LED_PIN, brightness);

    // Display readings
    Serial.print("LDR ADC: ");
    Serial.print(ldrValue);

    Serial.print(" | LED Brightness: ");
    Serial.print((brightness * 100L) / 255);
    Serial.println("%");

    delay(100);
}
