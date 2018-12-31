#include <ros.h>
#include <Stepper.h>
#include <math.h>
#include <geometry_msgs/Point.h> // type of message   
//change this to the number of steps on your motor
#define STEPS 200
#define STEPS1 513
float theta1;
float theta2;
float X ;
float Y ;
double L2 = 76.2; // length of the link arms
double L1 = 177.8; // in mm

Stepper stepper(STEPS, 4, 5, 6, 7); // defining motor phases pins
Stepper stepper2(STEPS2, 8, 10, 9, 11);

ros::NodeHandle  nh;

void messageCb( const geometry_msgs::Point& toggle_msg){
      X = toggle_msg.x;
      Y = toggle_msg.y;
      theta2 = 2*atan(sqrt(((L1+L2)*(L1+L2)-((X*X)+(Y*Y)))/(((X*X)+(Y*Y))-((L1-L2)*(L1-L2)))));
      theta1 = atan2(Y,X)+atan2(L2*sin(theta2),(L1+(L2*cos(theta2)))); // get theta in radians
      STEPS = (theta1*200)/(2*3.14159); //convert theta1 (radians) to steps
      STEPS2 = (theta2*513)/(2*3.14159); //convert theta2 (radians) to steps
      stepper.step(STEPS);
      stepper2.step(STEPS2);
      delay(5000);
      stepper.step(-STEPS);
      stepper2.step(-STEPS2);
      delay(5000);
}

ros::Subscriber<std_msgs::Empty> sub("vision_node", &messageCb);// name of the topic to suscribe to

void setup()
{ 
 
 
 stepper.setSpeed(10);
 stepper2.setSpeed(30);
 nh.initNode();
 nh.subscribe(sub);

}

void loop()
{  
  nh.spinOnce(); // may need to be changed to spin  for continuous listening 
  delay(1);
  
}
