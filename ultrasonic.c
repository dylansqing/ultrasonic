// Include header file
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

#define TRIG 17
#define ECHO 22

int pulseIn(int pin, int level) {
   struct timeval tn, t0, t1;
   long micros;

   gettimeofday(&t0, NULL);
   micros = 0;

   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
   }

   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
   }

   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);
   }

   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}

// Main function
int main() {
  int i;
  int Duration;
  float Distance;

  if (wiringPiSetupGpio() == -1) return 1;

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  printf("test\n");

  // Repeat LED blinking 10 times
  while (1) {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(1);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(1);
  Duration = pulseIn(ECHO,HIGH);

    if (Duration>0) {
      Distance = Duration/2;
      Distance = Distance*340*100/1000000;

      //printf("Duration: %d us\n", Duration);
      printf("Distance: %lf cm\n", Distance);
    }

    delay(50);
  }

  // Turn off LED
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);

  return 0;
}


