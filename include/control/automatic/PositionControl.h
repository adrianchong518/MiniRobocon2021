#pragma once

#include <stdint.h>

#include <PID.h>

namespace control {
namespace automatic {

class PositionControl : public PID {
 public:
  PositionControl();

  void update();
  void stop();

  void setTarget(double targetPosX, double targetPosY);

  bool isEnabled() const;
  void setIsEnabled(bool isEnabled);

 protected:
  double calculateError(double reading) override { return reading; }

 private:
  bool m_isEnabled = false;

  double m_targetPosX;
  double m_targetPosY;
};

}  // namespace automatic
}  // namespace control