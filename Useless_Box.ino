#include <Servo.h>
Servo servoUp, servoTurn, servoPush;
int a[6] = {0, 0, 0, 0, 0, 0};
int Pos[6] = {166, 146, 123, 101, 77, 55};
int i, j, pos, degree = 115;
String str = "";
boolean insert = false;
boolean FlagTurnOn = true;
boolean FlagTurnOff = false;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
void setup()
{
  Serial.begin(9600);
  servoPush.attach(8);
  servoTurn.attach(7);
  servoUp.attach(6);
  servoPush.write(180);
  servoTurn.write(115);
  servoUp.write(60);
  for (i = 10; i <= 15; i++)
  {
    pinMode(i, INPUT);
  }
}
void loop()
{
  currentMillis = millis();
  Insert();
  Run();
  Delete();
  //Print();
}
void Print()
{
  for (i = 0; i < 6; i++)
  {
    str += String(a[i]) + " ";
  }
  Serial.println(str);
  str = "";
}
void Insert()
{
  for (i = 10; i <= 15; i++)
  {
    if (digitalRead(i))
    {
      for (j = 0; j < 6; j++)
      {
        if (a[j] == i)
        {
          insert = false;
          break;
        }
        else
        {
          insert = true;
        }
      }
      if (insert)
      {
        for (j = 0; j < 6; j++)
        {
          if (a[j] == 0)
          {
            a[j] = i;
            break;
          }
        }
      }
    }
  }
}
void Delete()
{
  for (i = 10; i <= 15; i++)
  {
    if (!digitalRead(i))
    {
      for (j = 0; j < 6; j++)
      {
        if (a[j] == i)
        {
          pos = j;
          for (j = pos; j < 6; j++)
          {
            if (a[j] != 0)
            {
              a[j] = a[j + 1];
            }
            else
            {
              break;
            }
          }
          break;
        }
      }
    }
  }
}
void Run()
{
  if (a[0] != 0)  //switch on
  {
    FlagTurnOff = false;
    if (FlagTurnOn)
    { 
      servoUp.write(6); //Up
      delay(200);
      servoTurn.write(115);
      delay(150);
      servoPush.write(50);
      delay(150);
      FlagTurnOn = false;
    }
    servoTurn.write(Pos[a[0] - 10]);
    degree = Pos[a[0] - 10];
    delay(150);
    servoPush.write(0); //Push down
    delay(150);
    servoPush.write(50);  //Pull up
    delay(150);
    previousMillis = currentMillis;
  }
  if (a[0] == 0)  //All switch off
  {
    servoTurn.write(degree);
    FlagTurnOff = true;
  }
  if (FlagTurnOff)
  {
    if (currentMillis - previousMillis >= 5000)
    {
      servoTurn.write(115);
      degree = 115;
      delay(150);
      servoPush.write(180); //Down
      delay(150);
      servoUp.write(60);  //Down
      delay(150);
      FlagTurnOn = true;
    }
  }
}
