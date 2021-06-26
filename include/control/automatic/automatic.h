#pragma once

namespace control {
namespace automatic {

extern bool isAutomaticEnabled;

void init();
void loop();

void stop();

void setIsAutomaticEnabled(const bool isAutomaticEnabled);

}  // namespace automatic
}  // namespace control