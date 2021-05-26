#ifndef PID_H
#define PID_H

class PID {
 public:
  enum CODES { NO_ERROR, ERROR_TARGET_EXCEEDS_LIMIT };

  double Kp;
  double Ki;
  double Kd;

 protected:
  double m_target;
  double m_allowedError = 0;
  bool m_isTargetReached = true;

  bool m_isTargetLimitEnabled = false;
  double m_targetLowerLimit = 0;
  double m_targetUpperLimit = 0;

  double m_min;
  double m_max;

  double m_cumError;
  double m_prevError;

 public:
  PID(const double Kp, const double Ki, const double Kd, const double min,
      const double max);
  ~PID();

  double calculatePID(double reading);

  bool isTargetReached();
  void setAllowedError(double allowedError);

  void setTargetLimitEnabled(const bool isTargetLimitEnabled);
  void setTargetLimit(const double targetLowerLimit,
                      const double targetUpperLimit);

  double getTarget();
  CODES setTarget(const double target);

 protected:
  virtual double calculateError(double reading);
};

#endif  // PID_H
