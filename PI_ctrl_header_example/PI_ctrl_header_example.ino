/*
Author: Omer Ikram ul haq
Date: 2014-05-28
Documentation webpage:
Location: Multan, Pakistan
Ver: 0.2 beta
*/



#include "pi_ctrl.h"



pi_controller c1;

unsigned long t;
float dt=0.02;
// Mechanical Model parameter
float j = 0.01,ang_accel=0,ang_speed=0; // Moment of Inertia
// Fan curve polynomials
double p1=4.6586e-6, p2=-0.00015319, p3=0.0045347, p4=0.038095;

void setup(){
  Serial.begin(115200);
  c1.kp = 0.001;
  c1.tn = 2;
  c1.dt = dt;
  c1.IC = 5;
  c1.lim_max = 10;
  c1.lim_min = -10;
  
  Serial.print("angular speed ref = ");
  Serial.print("\t");
  Serial.print("angular speed = ");
  Serial.print("\t");
  Serial.print("Ctrl_output = ");
  Serial.print("\t");
  Serial.print("Processor load = ");
  
  
  t=micros();

}


float ctrl_output = 0; 
int w_ref=0;
void loop(){
  
  
  float w=angular_speed(ctrl_output); // Measuring the speed
  
  if (Serial.available()){
    w_ref = Serial.parseInt();
  }
  
  ctrl_output = c1.control(w_ref - w); 
  
  

  Serial.print(w_ref);
  Serial.print("\t");

  Serial.print(w);
  Serial.print("\t");

  Serial.print(ctrl_output);
  Serial.print("\t");

  Serial.println((micros()-t)/(dt*10000));

  while ((micros()-t) < dt*1000000){
    // stay here
  }
  t=micros();  

}

float angular_speed (float torque){
  
        float fan_load = p1*ang_speed*ang_speed*ang_speed + p2*ang_speed*ang_speed + p3*ang_speed + p4;
  
	ang_accel = (torque-fan_load)/j;
	ang_speed = ang_accel*dt + ang_speed;
	return(ang_speed);

}





