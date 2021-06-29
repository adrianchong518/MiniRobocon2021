#pragma once

#include <stdint.h>

#include <PID.h>

namespace control {
namespace automatic {

class PositionControl : public PID {
 public:
  PositionControl();

  void update(int32_t posX, int32_t posY);
  void stop();

  void setTarget(int32_t targetPosX, int32_t m_targetPosY);
  void setTargetMM(double targetPosXMM, double targetPosYMM);

  bool isEnabled() const;
  void setIsEnabled(bool isEnabled);

 protected:
  double calculateError(double reading) override { return reading; }

 private:
  bool m_isEnabled = false;

  int32_t m_targetPosX;
  int32_t m_targetPosY;
};

}  // namespace automatic
}  // namespace control