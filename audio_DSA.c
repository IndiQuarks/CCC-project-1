#include <Arduino.h>

#define BUZZER_PIN 18
#define BUZZER_CH  0

struct Song {
  const uint16_t* freqs;
  const uint16_t* durs;
  uint8_t length;
  Song* next;
};

const uint16_t dhoom_freqs[] = {
  392, 392, 392, 440, 392, 392, 349,
  392, 392, 392, 440, 392, 349, 330
};

const uint16_t dhoom_durs[] = {
  200, 200, 200, 300, 300, 200, 400,
  200, 200, 200, 300, 300, 200, 500
};

const uint16_t hb_freqs[] = {
  392, 392, 440, 392, 523, 494,
  392, 392, 440, 392, 587, 523,
  392, 392, 784, 659, 523, 494, 440,
  698, 698, 659, 523, 587, 523
};

const uint16_t hb_durs[] = {
  250, 250, 500, 500, 500, 1000,
  250, 250, 500, 500, 500, 1000,
  250, 250, 500, 500, 500, 500, 1000,
  250, 250, 500, 500, 500, 1000
};

const uint16_t nokia_freqs[] = {
  659, 622, 494, 523,
  587, 349, 392, 523,
  659, 622, 494, 523,
  587, 523, 392, 349
};

const uint16_t nokia_durs[] = {
  200, 200, 200, 400,
  400, 200, 200, 400,
  200, 200, 200, 400,
  400, 400, 400, 600
};

const uint16_t snake_freqs[] = {
  392, 440, 466, 440, 392, 349,
  330, 349, 392, 330, 294, 262
};

const uint16_t snake_durs[] = {
  150, 150, 150, 150, 150, 200,
  150, 150, 150, 150, 150, 400
};

const uint16_t customSong_freqs[] = {
  330,494,440,494,440,494,392,440,494,440,392,349,
  330,494,440,494,440,494,392,440,494,440,
  330,494,440,494,440,494,392,440,494,440,392,349,
  294,330,349,392,349,330,
  294,349,330,349,330,
  330,494,440,494,440,494,392,440,494,440,392,349,
  330,494,440,494,440,494,392,440,494,440,
  330,494,440,494,440,494,392,440,494,440,392,349,
  294,330,349,392,349,330,
  294,349,330,349,330
};

const uint16_t customSong_durs[] = {
  250,250,250,250,250,250,250,250,250,250,250,250,
  250,250,250,250,250,250,250,250,250,500,
  250,250,250,250,250,250,250,250,250,250,250,250,
  500,250,250,500,250,250,
  500,250,250,250,250,
  250,250,250,250,250,250,250,250,250,250,250,250,
  250,250,250,250,250,250,250,250,250,500,
  250,250,250,250,250,250,250,250,250,250,250,250,
  250,250,250,250,250,250,
  500,250,250,250,250
};

Song songDhoom = {
  dhoom_freqs,
  dhoom_durs,
  (uint8_t)(sizeof(dhoom_freqs) / sizeof(uint16_t)),
  nullptr
};

Song songHB = {
  hb_freqs,
  hb_durs,
  (uint8_t)(sizeof(hb_freqs) / sizeof(uint16_t)),
  nullptr
};

Song songNokia = {
  nokia_freqs,
  nokia_durs,
  (uint8_t)(sizeof(nokia_freqs) / sizeof(uint16_t)),
  nullptr
};

Song songSnake = {
  snake_freqs,
  snake_durs,
  (uint8_t)(sizeof(snake_freqs) / sizeof(uint16_t)),
  nullptr
};

Song songCustom = {
  customSong_freqs,
  customSong_durs,
  (uint8_t)(sizeof(customSong_freqs) / sizeof(uint16_t)),
  nullptr
};

Song* currentSong = &songDhoom;
uint8_t currentIndex = 0;
unsigned long noteStart = 0;
bool notePlaying = false;

void playNote(uint16_t freq) {
  if (freq == 0) {
    ledcWrite(BUZZER_CH, 0);
  } else {
    ledcWriteTone(BUZZER_CH, freq);
    ledcWrite(BUZZER_CH, 128);
  }
}

void setup() {
  songDhoom.next = &songHB;
  songHB.next = &songNokia;
  songNokia.next = &songSnake;
  songSnake.next = &songCustom;
  songCustom.next = &songDhoom;

  ledcSetup(BUZZER_CH, 2000, 8);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);
}

void loop() {
  if (!notePlaying) {
    uint16_t f = currentSong->freqs[currentIndex];
    playNote(f);
    noteStart = millis();
    notePlaying = true;
  } else {
    uint16_t d = currentSong->durs[currentIndex];
    if (millis() - noteStart >= d) {
      ledcWrite(BUZZER_CH, 0);
      currentIndex++;
      if (currentIndex >= currentSong->length) {
        currentIndex = 0;
        currentSong = currentSong->next;
      }
      notePlaying = false;
    }
  }
}
