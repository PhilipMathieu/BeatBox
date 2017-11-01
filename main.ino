#include "peak_detector.ino"
#include "shutdown_manager.ino"

void setup() {
    shutdown_manager_setup();
    peak_detector_setup();
}

void loop() {
    // Could add code here later to skip shutdown management most of the time
    shutdown_manager_loop();
    peak_detector_loop();
}