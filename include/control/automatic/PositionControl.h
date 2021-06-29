#pragma once

#include <stdint.h>

#include <PID.h>

namespace control {
namespace automatic {

class PositionControl : public PID {
 public:
  PositionControl();

  void update(int16_t posX, int16_t posY);
  void stop();

  void setTarget(int16_t targetPosX, int16_t m_targetPosY);
  void setTargetMM(double targetPosXMM, double targetPosYMM);

  bool isEnabled() const;
  void setIsEnabled(bool isEnabled);

 protected:
 private:
  bool m_isEnabled = false;

  int16_t m_targetPosX;
  int16_t m_targetPosY;
};

}  // namespace automatic
}  // namespace control