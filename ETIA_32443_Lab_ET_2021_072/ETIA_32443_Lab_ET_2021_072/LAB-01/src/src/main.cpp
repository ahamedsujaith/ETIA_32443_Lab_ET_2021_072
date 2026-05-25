#include <Arduino.h>

// Function declaration
int myFunction(int x, int y);

// External task functions
void task1();
void task2();

void setup() {
  Serial.begin(9600);

  int result = myFunction(2, 3);

  Serial.print("Result = ");
  Serial.println(result);
}

void loop() {
  task1();
  task2();
}

// Function definition
int myFunction(int x, int y) {
  return x + y;
}