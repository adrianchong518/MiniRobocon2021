#pragma once

#include <Arduino.h>

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

extern Adafruit_NeoPixel grid;

// clang-format off
#define BRIGHTNESS 20
#define RED {BRIGHTNESS, 0, 0}
#define GRE {0, BRIGHTNESS, 0}
#define BLU {0, 0, BRIGHTNESS}
#define YEL {BRIGHTNESS, BRIGHTNESS, 0}
#define CYA {0, BRIGHTNESS, BRIGHTNESS}
#define MAG {BRIGHTNESS, 0, BRIGHTNESS}
#define WHI {BRIGHTNESS, BRIGHTNESS, BRIGHTNESS}
#define BLK {0, 0, 0}
#define KIC {255, 255, 255}

const uint8_t RED_UP[25][3] PROGMEM = {BLK, BLK, RED, BLK, BLK,
                                       BLK, RED, RED, RED, BLK,
                                       RED, BLK, RED, BLK, RED,
                                       BLK, BLK, RED, BLK, BLK,
                                       BLK, BLK, RED, BLK, BLK};

const uint8_t BLU_UP[25][3] PROGMEM = {BLK, BLK, BLU, BLK, BLK,
                                       BLK, BLU, BLU, BLU, BLK,
                                       BLU, BLK, BLU, BLK, BLU,
                                       BLK, BLK, BLU, BLK, BLK,
                                       BLK, BLK, BLU, BLK, BLK};

const uint8_t RED_UP_LEFT[25][3] PROGMEM = {RED, RED, RED, RED, RED,
                                           RED, RED, BLK, BLK, BLK,
                                           BLK, BLK, RED, BLK, RED,
                                           RED, BLK, BLK, RED, BLK,
                                           RED, BLK, BLK, BLK, RED};

const uint8_t BLU_UP_LEFT[25][3] PROGMEM = {BLU, BLU, BLU, BLU, BLU,
                                           BLU, BLU, BLK, BLK, BLK,
                                           BLK, BLK, BLU, BLK, BLU,
                                           BLU, BLK, BLK, BLU, BLK,
                                           BLU, BLK, BLK, BLK, BLU};

const uint8_t RED_UP_LEFT_RETURN[25][3] PROGMEM = {RED, RED, RED, RED, RED,
                                                  RED, RED, BLK, BLK, BLK,
                                                  GRE, BLK, RED, BLK, RED,
                                                  RED, BLK, BLK, RED, GRE,
                                                  GRE, GRE, GRE, BLK, RED};

const uint8_t BLU_UP_LEFT_RETURN[25][3] PROGMEM = {BLU, BLU, BLU, BLU, BLU,
                                                  BLU, BLU, BLK, BLK, BLK,
                                                  GRE, BLK, BLU, BLK, BLU,
                                                  BLU, BLK, BLK, BLU, GRE,
                                                  GRE, GRE, GRE, BLK, BLU};

const uint8_t RED_R[25][3] PROGMEM = {BLK, RED, RED, RED, RED,
                                      RED, BLK, BLK, BLK, RED,
                                      BLK, RED, RED, RED, RED,
                                      RED, BLK, RED, BLK, BLK,
                                      BLK, RED, BLK, BLK, RED};

const uint8_t BLU_R[25][3] PROGMEM = {BLK, BLU, BLU, BLU, BLU,
                                      BLU, BLK, BLK, BLK, BLU,
                                      BLK, BLU, BLU, BLU, BLU,
                                      BLU, BLK, BLU, BLK, BLK,
                                      BLK, BLU, BLK, BLK, BLU};

const uint8_t RED_M[25][3] PROGMEM = {RED, BLK, BLK, BLK, RED,
                                      RED, RED, BLK, RED, RED,
                                      RED, BLK, RED, BLK, RED,
                                      RED, BLK, BLK, BLK, RED,
                                      RED, BLK, BLK, BLK, RED};

const uint8_t BLU_M[25][3] PROGMEM = {BLU, BLK, BLK, BLK, BLU,
                                      BLU, BLU, BLK, BLU, BLU,
                                      BLU, BLK, BLU, BLK, BLU,
                                      BLU, BLK, BLK, BLK, BLU,
                                      BLU, BLK, BLK, BLK, BLU};

const uint8_t RED_DOWNRIGHT[25][3] PROGMEM = {BLK, BLK, BLK, BLK, RED,
                                              BLK, RED, BLK, BLK, RED,
                                              RED, BLK, RED, BLK, BLK,
                                              BLK, BLK, BLK, RED, RED,
                                              RED, RED, RED, RED, BLK};

const uint8_t BLU_DOWNRIGHT[25][3] PROGMEM = {BLK, BLK, BLK, BLK, BLU,
                                              BLK, BLU, BLK, BLK, BLU,
                                              BLU, BLK, BLU, BLK, BLK,
                                              BLK, BLK, BLK, BLU, BLU,
                                              BLU, BLU, BLU, BLU, BLK};

const uint8_t BLU_DOWNRIGHT_RETURN[25][3] PROGMEM = {BLU, BLK, GRE, GRE, GRE,
                                                     GRE, BLU, BLK, BLK, BLU,
                                                     BLU, BLK, BLU, BLK, GRE,
                                                     BLK, BLK, BLK, BLU, BLU,
                                                     BLU, BLU, BLU, BLU, BLU};

const uint8_t RED_DOWNRIGHT_RETURN[25][3] PROGMEM = {RED, BLK, GRE, GRE, GRE,
                                                     GRE, RED, BLK, BLK, RED,
                                                     RED, BLK, RED, BLK, GRE,
                                                     BLK, BLK, BLK, RED, RED,
                                                     RED, RED, RED, RED, RED};

const uint8_t BLU_DOWNLEFT[25][3] PROGMEM = {BLU, BLK, BLK, BLK, BLK,
                                             BLU, BLK, BLK, BLU, BLK,
                                             BLK, BLK, BLU, BLK, BLU,
                                             BLU, BLU, BLK, BLK, BLK,
                                             BLK, BLU, BLU, BLU, BLU};

const uint8_t RED_DOWNLEFT[25][3] PROGMEM = {RED, BLK, BLK, BLK, BLK,
                                             RED, BLK, BLK, RED, BLK,
                                             BLK, BLK, RED, BLK, RED,
                                             RED, RED, BLK, BLK, BLK,
                                             BLK, RED, RED, RED, RED};

const uint8_t BLU_DOWNLEFT_RETURN[25][3] PROGMEM = {GRE, GRE, GRE, BLK, BLU,
                                                    BLU, BLK, BLK, BLU, GRE,
                                                    GRE, BLK, BLU, BLK, BLU,
                                                    BLU, BLU, BLK, BLK, BLK,
                                                    BLU, BLU, BLU, BLU, BLU};

const uint8_t RED_DOWNLEFT_RETURN[25][3] PROGMEM = {GRE, GRE, GRE, BLK, RED,
                                                    RED, BLK, BLK, RED, GRE,
                                                    GRE, BLK, RED, BLK, RED,
                                                    RED, RED, BLK, BLK, BLK,
                                                    RED, RED, RED, RED, RED};

const uint8_t RED_KICK[25][3] PROGMEM = {RED, WHI, RED, RED, WHI,
                                         WHI, RED, WHI, RED, RED,
                                         RED, RED, RED, WHI, WHI,
                                         WHI, RED, WHI, RED, RED,
                                         RED, WHI, RED, RED, WHI};

const uint8_t BLU_KICK[25][3] PROGMEM = {BLU, WHI, BLU, BLU, WHI,
                                         WHI, BLU, WHI, BLU, BLU,
                                         BLU, BLU, BLU, WHI, WHI,
                                         WHI, BLU, WHI, BLU, BLU,
                                         BLU, WHI, BLU, BLU, WHI};

const uint8_t BLU_STANDING_BY[25][3] PROGMEM = {BLU, BLU, BLU, BLU, BLK,
                                               BLU, BLK, BLK, BLK, BLK,
                                               BLK, BLU, BLU, BLU, BLK,
                                               BLK, BLK, BLK, BLK, BLU,
                                               BLK, BLU, BLU, BLU, BLU};

const uint8_t RED_STANDING_BY[25][3] PROGMEM = {RED, RED, RED, RED, BLK,
                                               RED, BLK, BLK, BLK, BLK,
                                               BLK, RED, RED, RED, BLK,
                                               BLK, BLK, BLK, BLK, RED,
                                               BLK, RED, RED, RED, RED};

const uint8_t DEBUG_1[25][3] PROGMEM = {BLK, BLK, GRE, BLK, BLK,
                                        BLK, GRE, GRE, BLK, BLK,
                                        BLK, BLK, GRE, BLK, BLK,
                                        BLK, BLK, GRE, BLK, BLK,
                                        BLK, GRE, GRE, GRE, BLK};

const uint8_t DEBUG_2[25][3] PROGMEM = {BLK, GRE, GRE, GRE, GRE,
                                        BLK, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK,
                                        GRE, BLK, BLK, BLK, BLK,
                                        GRE, GRE, GRE, GRE, GRE};

const uint8_t DEBUG_3[25][3] PROGMEM = {BLK, GRE, GRE, GRE, BLK,
                                        BLK, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, BLK, BLK,
                                        BLK, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK};

const uint8_t DEBUG_4[25][3] PROGMEM = {GRE, BLK, BLK, GRE, BLK,
                                        BLK, GRE, BLK, BLK, GRE,
                                        GRE, GRE, GRE, BLK, BLK,
                                        BLK, BLK, BLK, BLK, GRE,
                                        GRE, BLK, BLK, BLK, BLK};

const uint8_t DEBUG_5[25][3] PROGMEM = {GRE, GRE, GRE, GRE, GRE,
                                        GRE, BLK, BLK, BLK, BLK,
                                        BLK, GRE, GRE, GRE, GRE,
                                        BLK, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, GRE};

const uint8_t DEBUG_6[25][3] PROGMEM = {BLK, GRE, GRE, GRE, BLK,
                                        GRE, BLK, BLK, BLK, BLK,
                                        BLK, GRE, GRE, GRE, GRE,
                                        GRE, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK};

const uint8_t DEBUG_7[25][3] PROGMEM = {GRE, GRE, GRE, GRE, GRE,
                                        BLK, BLK, BLK, GRE, BLK,
                                        BLK, BLK, GRE, BLK, BLK,
                                        BLK, BLK, GRE, BLK, BLK,
                                        BLK, BLK, GRE, BLK, BLK};

const uint8_t DEBUG_8[25][3] PROGMEM = {BLK, GRE, GRE, GRE, BLK,
                                        GRE, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK,
                                        GRE, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK};

const uint8_t DEBUG_9[25][3] PROGMEM = {GRE, GRE, GRE, GRE, GRE,
                                        GRE, BLK, BLK, BLK, GRE,
                                        GRE, GRE, GRE, GRE, GRE,
                                        BLK, BLK, BLK, BLK, GRE,
                                        GRE, BLK, BLK, BLK, BLK};

const uint8_t DEBUG_0[25][3] PROGMEM = {BLK, GRE, GRE, GRE, BLK,
                                        GRE, BLK, BLK, BLK, GRE,
                                        GRE, BLK, BLK, BLK, GRE,
                                        GRE, BLK, BLK, BLK, GRE,
                                        BLK, GRE, GRE, GRE, BLK};
// clang-format on

void init();

void gridDisplayPattern(const uint8_t pattern[25][3]);

}  // namespace interface
}  // namespace hardware