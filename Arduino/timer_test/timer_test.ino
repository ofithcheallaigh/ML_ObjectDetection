

#include <Arduino.h>
#include <nrf_timer.h>

// This sketch reads the duration of a pulse on digital pin 2.

void setup() {
  // Set up the Timer1 peripheral.
  nrf_timer_config_t timer_config = {
    .prescaler = 16,
    .mode = NRF_TIMER_MODE_TIMER,
    .bit_width = NRF_TIMER_BIT_WIDTH_16,
    .counter_top = 0xFFFF,
    .irq_priority = NRF_TIMER_IRQ_PRIORITY_LOW,
  };
  nrf_timer_init(&timer_config);

  // Set up digital pin 2 as an input.
  pinMode(2, INPUT);

  // Enable interrupts on the Timer1 peripheral.
  nrf_timer_enable_irq();
}

void loop() {
  // Wait for a pulse on digital pin 2.
  while (digitalRead(2) == LOW);

  // Read the value of the Timer1 counter.
  uint32_t timer_value = nrf_timer_get_counter();

  // Print the duration of the pulse to the Serial Monitor.
  Serial.println(timer_value);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
