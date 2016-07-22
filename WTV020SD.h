#ifndef WTV020SD_h
#define WTV020SD_h

class WTV020SD
{
public:
  WTV020SD(int resetPin, int clockPin, int dataPin, int busyPin);

  void reset();
  void triggerVoice(int fileNumber, bool waitForBusy);
  void setVolume(int level);
  void pauseResume();
  void stop();
  bool isBusy();

private:
  void init();
  void sendData(unsigned int data);

  int resetPin;
  int clockPin;
  int dataPin;
  int busyPin;
};

#endif
