void setup() {
    shutdown_manager_setup();
    peak_detector_setup();
}

void loop() {
    shutdown_manager_loop();
    peak_detector_loop();
}
