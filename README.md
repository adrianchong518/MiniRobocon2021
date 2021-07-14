# Mini Robocon 2021

This repo contains the code for the Arduino built on the robot, which is participating in the HK Mini Robocon 2021

The project is coded on VSCode with the extension PlatformIO installed.

## Todo

- [x] ~~Implement controller interfaces (switches, LCD)~~
- [x] ~~Implement interfaces (NeoPixel) & Refactor~~
- [x] ~~Implement sensors~~
  - [x] ~~Collision detection~~
  - [x] ~~Encoders (PCINT, INT)~~
  - [x] ~~TF-Mini~~
- [ ] Implement ball hitting
- [ ] Implement automatic path following

## Build Environments

**Debug LCD**: Builds with serial and LCD debug outputs
**Debug No Controller**: Builds version for when no controller is plugged in
**Debug**: Builds with serial debug output
**Release**: Builds without all debug outputs

## LCD Display

```monospace
| -------------------- |
|                      |
|                      |
| Sq:ID            L R |
| [    State    ] MG__ |
| -------------------- |
```

## Control over Serial

### Hardware

```monospace
> h c
Run hardware::calibrate()

> h h
Run hardware::startingPosition();

> h cont
Re-enable the hardware loop
```

### Mecanum

```monospace
> m s [speed]
Set the speed of movement (0.0 ~ 1.0)

> m d [direction]
Set the direction of movement (-180 ~ 180 degrees)

> m r [degrees]
Set the target direction the robot is facing (-180 ~ 180 degrees)

> m rsd [difference in speed]
Set the difference in speed of the F/B or L/R motors for rotation (-510 ~ 510)

> m ms
Return the speeds of the motors
("FL | FR | BL | BR")

> m rr
Return the direction the robot is facing currently

> m gt
Toggle whether gyroscope feedback rotation PID is enabled

> m c
Calibrates the gyroscope (Finds the offset)

> m pid
Return the value of the PID constants

> m kp [value]
Set the Kp constant of rotation control

> m ki [value]
Set the Ki constant of rotation control

> m kd [value]
Set the Kd constant of rotation control

> m t
Toggle whether the mecanum is enabled
```

### Servos

```monospace
> s ru [degree]
Set the right upper servo to [degree] (0 ~ 180)

> s rl [degree]
Set the right lower servo to [degree] (0 ~ 180)

> s lu [degree]
Set the left upper servo to [degree] (0 ~ 180)

> s ll [degree]
Set the left lower servo to [degree] (0 ~ 180)

> s r[0|1|2]
Set the right servos the state [0|1|2]

> s l[0|1|2]
Set the left servos to state [0|1|2]

State 0: Normal retracted position
State 1: Holding ball position
State 2: Putting ball position
```

### Encoders

```monospace
> e r
Return the counts and error counts of x, y, ball hitter encoders

> e rx
Return the counts and error counts of x encoder

> e ry
Return the counts and error counts of y encoder

> e rbh
Return the counts and error counts of ball hitter encoder

> e c
Clear the counts of x, y, ball hitter encoders

> e cx
Clear the counts of x encoder

> e cy
Clear the counts of y encoder

> e cbh
Clear the counts of ball hitter encoder
```

### Distance Sensors (TFMini-S)

```monospace
> dist vr
Return the value of all distance sensors

> dist enable
Enable all distance sensors

> dist disable
Disable all distance sensors

> dist [index] vr
Return the value of the distance sensor at [index]

> dist [index] enable
Enable the distance sensor at [index]

> dist [index] disable
Disable the distance sensors at [index]
```

### Manual Control

```monospace
> manual t
Toggles whether manual control is enabled
```

### Automatic Control

```monospace
> auto t
Toggles whether auto control is enabled
```

### Position Control

```monospace
> pos set [x-pos] [y-pos]
Set the position target to ([x-pos], [y-pos]) (mm)

> pos kp [value]
Set the Kp constant of position control

> pos ki [value]
Set the Ki constant of position control

> pos kd [value]
Set the Kd constant of position control

> pos t
Toggle whether position control is enabled
```

### Run

```monospace
> run routine [routine-name]
Run routine with the name [routine-name]

> run seq [seq-id]
Run the sequence of routines with ID [seq-id]
```
