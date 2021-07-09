#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Adafruit_NeoPixel.h>

#if DEBUG == 1
#define LOG_DEBUG(msg) \
  Serial.println("\e[;90m[DEBUG]\t" + String(msg) + "\e[0m")
#else
#define LOG_DEBUG(msg)
#endif

#define LOG_INFO(msg) Serial.println("[INFO]\t" + String(msg))
#define LOG_ERROR(msg) \
  Serial.println("\e[1;91m[ERROR]\t" + String(msg) + "\e[0m")

namespace hardware {
namespace interface {

extern hd44780_I2Cexp lcd;

extern Adafruit_NeoPixel grid;

// clang-format off
#define BRIGHTNESS 20
#define G_RED {BRIGHTNESS, 0, 0}
#define G_GRE {0, BRIGHTNESS, 0}
#define G_BLU {0, 0, BRIGHTNESS}
#define G_YEL {BRIGHTNESS, BRIGHTNESS, 0}
#define G_CYA {0, BRIGHTNESS, BRIGHTNESS}
#define G_MAG {BRIGHTNESS, 0, BRIGHTNESS}
#define G_WHI {BRIGHTNESS, BRIGHTNESS, BRIGHTNESS}
#define G_BLK {0, 0, 0}
#define G_KIC {255, 255, 255}

const uint8_t RED_UP[25][3] PROGMEM = {G_BLK, G_BLK, G_RED, G_BLK, G_BLK,
                                       G_BLK, G_RED, G_RED, G_RED, G_BLK,
                                       G_RED, G_BLK, G_RED, G_BLK, G_RED,
                                       G_BLK, G_BLK, G_RED, G_BLK, G_BLK,
                                       G_BLK, G_BLK, G_RED, G_BLK, G_BLK};

const uint8_t BLU_UP[25][3] PROGMEM = {G_BLK, G_BLK, G_BLU, G_BLK, G_BLK,
                                       G_BLK, G_BLU, G_BLU, G_BLU, G_BLK,
                                       G_BLU, G_BLK, G_BLU, G_BLK, G_BLU,
                                       G_BLK, G_BLK, G_BLU, G_BLK, G_BLK,
                                       G_BLK, G_BLK, G_BLU, G_BLK, G_BLK};

const uint8_t RED_UP_LEFT[25][3] PROGMEM = {G_RED, G_RED, G_RED, G_RED, G_RED,
                                           G_RED, G_RED, G_BLK, G_BLK, G_BLK,
                                           G_BLK, G_BLK, G_RED, G_BLK, G_RED,
                                           G_RED, G_BLK, G_BLK, G_RED, G_BLK,
                                           G_RED, G_BLK, G_BLK, G_BLK, G_RED};

const uint8_t BLU_UP_LEFT[25][3] PROGMEM = {G_BLU, G_BLU, G_BLU, G_BLU, G_BLU,
                                           G_BLU, G_BLU, G_BLK, G_BLK, G_BLK,
                                           G_BLK, G_BLK, G_BLU, G_BLK, G_BLU,
                                           G_BLU, G_BLK, G_BLK, G_BLU, G_BLK,
                                           G_BLU, G_BLK, G_BLK, G_BLK, G_BLU};

const uint8_t RED_UP_LEFT_RETURN[25][3] PROGMEM = {G_RED, G_RED, G_RED, G_RED, G_RED,
                                                  G_RED, G_RED, G_BLK, G_BLK, G_BLK,
                                                  G_GRE, G_BLK, G_RED, G_BLK, G_RED,
                                                  G_RED, G_BLK, G_BLK, G_RED, G_GRE,
                                                  G_GRE, G_GRE, G_GRE, G_BLK, G_RED};

const uint8_t BLU_UP_LEFT_RETURN[25][3] PROGMEM = {G_BLU, G_BLU, G_BLU, G_BLU, G_BLU,
                                                  G_BLU, G_BLU, G_BLK, G_BLK, G_BLK,
                                                  G_GRE, G_BLK, G_BLU, G_BLK, G_BLU,
                                                  G_BLU, G_BLK, G_BLK, G_BLU, G_GRE,
                                                  G_GRE, G_GRE, G_GRE, G_BLK, G_BLU};

const uint8_t RED_R[25][3] PROGMEM = {G_BLK, G_RED, G_RED, G_RED, G_RED,
                                      G_RED, G_BLK, G_BLK, G_BLK, G_RED,
                                      G_BLK, G_RED, G_RED, G_RED, G_RED,
                                      G_RED, G_BLK, G_RED, G_BLK, G_BLK,
                                      G_BLK, G_RED, G_BLK, G_BLK, G_RED};

const uint8_t BLU_R[25][3] PROGMEM = {G_BLK, G_BLU, G_BLU, G_BLU, G_BLU,
                                      G_BLU, G_BLK, G_BLK, G_BLK, G_BLU,
                                      G_BLK, G_BLU, G_BLU, G_BLU, G_BLU,
                                      G_BLU, G_BLK, G_BLU, G_BLK, G_BLK,
                                      G_BLK, G_BLU, G_BLK, G_BLK, G_BLU};

const uint8_t RED_M[25][3] PROGMEM = {G_RED, G_BLK, G_BLK, G_BLK, G_RED,
                                      G_RED, G_RED, G_BLK, G_RED, G_RED,
                                      G_RED, G_BLK, G_RED, G_BLK, G_RED,
                                      G_RED, G_BLK, G_BLK, G_BLK, G_RED,
                                      G_RED, G_BLK, G_BLK, G_BLK, G_RED};

const uint8_t BLU_M[25][3] PROGMEM = {G_BLU, G_BLK, G_BLK, G_BLK, G_BLU,
                                      G_BLU, G_BLU, G_BLK, G_BLU, G_BLU,
                                      G_BLU, G_BLK, G_BLU, G_BLK, G_BLU,
                                      G_BLU, G_BLK, G_BLK, G_BLK, G_BLU,
                                      G_BLU, G_BLK, G_BLK, G_BLK, G_BLU};

const uint8_t RED_DOWNRIGHT[25][3] PROGMEM = {G_BLK, G_BLK, G_BLK, G_BLK, G_RED,
                                              G_BLK, G_RED, G_BLK, G_BLK, G_RED,
                                              G_RED, G_BLK, G_RED, G_BLK, G_BLK,
                                              G_BLK, G_BLK, G_BLK, G_RED, G_RED,
                                              G_RED, G_RED, G_RED, G_RED, G_BLK};

const uint8_t BLU_DOWNRIGHT[25][3] PROGMEM = {G_BLK, G_BLK, G_BLK, G_BLK, G_BLU,
                                              G_BLK, G_BLU, G_BLK, G_BLK, G_BLU,
                                              G_BLU, G_BLK, G_BLU, G_BLK, G_BLK,
                                              G_BLK, G_BLK, G_BLK, G_BLU, G_BLU,
                                              G_BLU, G_BLU, G_BLU, G_BLU, G_BLK};

const uint8_t BLU_DOWNRIGHT_RETURN[25][3] PROGMEM = {G_BLU, G_BLK, G_GRE, G_GRE, G_GRE,
                                                     G_GRE, G_BLU, G_BLK, G_BLK, G_BLU,
                                                     G_BLU, G_BLK, G_BLU, G_BLK, G_GRE,
                                                     G_BLK, G_BLK, G_BLK, G_BLU, G_BLU,
                                                     G_BLU, G_BLU, G_BLU, G_BLU, G_BLU};

const uint8_t RED_DOWNRIGHT_RETURN[25][3] PROGMEM = {G_RED, G_BLK, G_GRE, G_GRE, G_GRE,
                                                     G_GRE, G_RED, G_BLK, G_BLK, G_RED,
                                                     G_RED, G_BLK, G_RED, G_BLK, G_GRE,
                                                     G_BLK, G_BLK, G_BLK, G_RED, G_RED,
                                                     G_RED, G_RED, G_RED, G_RED, G_RED};

const uint8_t BLU_DOWNLEFT[25][3] PROGMEM = {G_BLU, G_BLK, G_BLK, G_BLK, G_BLK,
                                             G_BLU, G_BLK, G_BLK, G_BLU, G_BLK,
                                             G_BLK, G_BLK, G_BLU, G_BLK, G_BLU,
                                             G_BLU, G_BLU, G_BLK, G_BLK, G_BLK,
                                             G_BLK, G_BLU, G_BLU, G_BLU, G_BLU};

const uint8_t RED_DOWNLEFT[25][3] PROGMEM = {G_RED, G_BLK, G_BLK, G_BLK, G_BLK,
                                             G_RED, G_BLK, G_BLK, G_RED, G_BLK,
                                             G_BLK, G_BLK, G_RED, G_BLK, G_RED,
                                             G_RED, G_RED, G_BLK, G_BLK, G_BLK,
                                             G_BLK, G_RED, G_RED, G_RED, G_RED};

const uint8_t BLU_DOWNLEFT_RETURN[25][3] PROGMEM = {G_GRE, G_GRE, G_GRE, G_BLK, G_BLU,
                                                    G_BLU, G_BLK, G_BLK, G_BLU, G_GRE,
                                                    G_GRE, G_BLK, G_BLU, G_BLK, G_BLU,
                                                    G_BLU, G_BLU, G_BLK, G_BLK, G_BLK,
                                                    G_BLU, G_BLU, G_BLU, G_BLU, G_BLU};

const uint8_t RED_DOWNLEFT_RETURN[25][3] PROGMEM = {G_GRE, G_GRE, G_GRE, G_BLK, G_RED,
                                                    G_RED, G_BLK, G_BLK, G_RED, G_GRE,
                                                    G_GRE, G_BLK, G_RED, G_BLK, G_RED,
                                                    G_RED, G_RED, G_BLK, G_BLK, G_BLK,
                                                    G_RED, G_RED, G_RED, G_RED, G_RED};

const uint8_t RED_KICK[25][3] PROGMEM = {G_RED, G_WHI, G_RED, G_RED, G_WHI,
                                         G_WHI, G_RED, G_WHI, G_RED, G_RED,
                                         G_RED, G_RED, G_RED, G_WHI, G_WHI,
                                         G_WHI, G_RED, G_WHI, G_RED, G_RED,
                                         G_RED, G_WHI, G_RED, G_RED, G_WHI};

const uint8_t BLU_KICK[25][3] PROGMEM = {G_BLU, G_WHI, G_BLU, G_BLU, G_WHI,
                                         G_WHI, G_BLU, G_WHI, G_BLU, G_BLU,
                                         G_BLU, G_BLU, G_BLU, G_WHI, G_WHI,
                                         G_WHI, G_BLU, G_WHI, G_BLU, G_BLU,
                                         G_BLU, G_WHI, G_BLU, G_BLU, G_WHI};

const uint8_t BLU_STANDING_BY[25][3] PROGMEM = {G_BLU, G_BLU, G_BLU, G_BLU, G_BLK,
                                               G_BLU, G_BLK, G_BLK, G_BLK, G_BLK,
                                               G_BLK, G_BLU, G_BLU, G_BLU, G_BLK,
                                               G_BLK, G_BLK, G_BLK, G_BLK, G_BLU,
                                               G_BLK, G_BLU, G_BLU, G_BLU, G_BLU};

const uint8_t RED_STANDING_BY[25][3] PROGMEM = {G_RED, G_RED, G_RED, G_RED, G_BLK,
                                               G_RED, G_BLK, G_BLK, G_BLK, G_BLK,
                                               G_BLK, G_RED, G_RED, G_RED, G_BLK,
                                               G_BLK, G_BLK, G_BLK, G_BLK, G_RED,
                                               G_BLK, G_RED, G_RED, G_RED, G_RED};

const uint8_t DEBUG_1[25][3] PROGMEM = {G_BLK, G_BLK, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_GRE, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK};

const uint8_t DEBUG_2[25][3] PROGMEM = {G_BLK, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_BLK,
                                        G_GRE, G_GRE, G_GRE, G_GRE, G_GRE};

const uint8_t DEBUG_3[25][3] PROGMEM = {G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK};

const uint8_t DEBUG_4[25][3] PROGMEM = {G_GRE, G_BLK, G_BLK, G_GRE, G_BLK,
                                        G_BLK, G_GRE, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_GRE, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_BLK};

const uint8_t DEBUG_5[25][3] PROGMEM = {G_GRE, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_BLK,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_GRE};

const uint8_t DEBUG_6[25][3] PROGMEM = {G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_BLK,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK};

const uint8_t DEBUG_7[25][3] PROGMEM = {G_GRE, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_BLK, G_BLK, G_BLK, G_GRE, G_BLK,
                                        G_BLK, G_BLK, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_GRE, G_BLK, G_BLK,
                                        G_BLK, G_BLK, G_GRE, G_BLK, G_BLK};

const uint8_t DEBUG_8[25][3] PROGMEM = {G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK};

const uint8_t DEBUG_9[25][3] PROGMEM = {G_GRE, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_GRE, G_GRE, G_GRE, G_GRE,
                                        G_BLK, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_BLK};

const uint8_t DEBUG_0[25][3] PROGMEM = {G_BLK, G_GRE, G_GRE, G_GRE, G_BLK,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_GRE, G_BLK, G_BLK, G_BLK, G_GRE,
                                        G_BLK, G_GRE, G_GRE, G_GRE, G_BLK};
// clang-format on

void init();

void gridDisplayPattern(const uint8_t pattern[25][3]);

}  // namespace interface
}  // namespace hardware