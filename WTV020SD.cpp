#include <Arduino.h>
#include "WTV020SD.h"

WTV020SD::WTV020SD(int resetPin, int clockPin, int dataPin, int busyPin)
  : resetPin(resetPin)
  , clockPin(clockPin)
  , dataPin(dataPin)
  , busyPin(busyPin)
{
  init();
}

void WTV020SD::reset()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(clockPin, HIGH);
  delay(1);

  digitalWrite(resetPin, LOW);
  delay(10);
  digitalWrite(resetPin, HIGH);
  delay(600);
}

void WTV020SD::triggerVoice(int fileNumber, bool waitForBusy)
{
  sendData(fileNumber);

  if (waitForBusy)
  {
    delay(40);
    while (isBusy()) ;
  }
}

void WTV020SD::setVolume(int level)
{
  sendData(0xFFF0 | level);
}

void WTV020SD::pauseResume()
{
  sendData(0xFFFE);
}

void WTV020SD::stop()
{
  sendData(0xFFFF);
}

bool WTV020SD::isBusy()
{
  return digitalRead(busyPin) == HIGH;
}

void WTV020SD::init()
{
  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(busyPin, INPUT);
}

void WTV020SD::sendData(unsigned int data)
{
  digitalWrite(clockPin, LOW);
  delay(4);

  for (int i = 8 * sizeof(data) - 1; i >= 0; i--)
  {
    digitalWrite(dataPin, (data & (1 << i)) ? HIGH : LOW);
    digitalWrite(clockPin, LOW);
    delayMicroseconds(200);

    digitalWrite(clockPin, HIGH);
    delayMicroseconds(200);
  }

  delay(4);
}
