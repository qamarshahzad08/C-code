#include <Servo.h>
#include <L298.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <IntegerDoublyLinkedList.h>
#include <Keypad.h>

int jugaad = 0;

//------------------------- Servo ---------------------------

int pos = 0;
int s1_min = 70;
int s1_max = 160;

int s2_min = 30;
int s2_max = 60;
//------------------------Ultrasonic--------------------------

const int pingPin = 5;
long duration; 
int inches, cm;
Servo servo1, servo2;

//--------------------------KEYPAD----------------------------
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A8, A9, A10, A11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A12, A13, A14}; //connect to the column pinouts of the keypad
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char customKey = ' ';
//---------------- deque_to_array ----------------------
const int fwd = 0;
const int rev = 1;
const int lt = 2;
const int rt = 3;
const int bfwd = 10;
const int brev = 11;
const int blt = 12;
const int brt = 13;
const int pfwd = 20;
const int prev = 21;
const int plt = 22;
const int prt = 23;

int convention_set = 0;

int ignore_stop_move = 0;

//-------------------------------------------------------

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(22, 24, 26,28, 30,32,34,36,38,40,42);
HMC5883L compass;

L298 robot(8,10,9,12,11,13,1);
int l_limit,h_limit;
int left_sensors, right_sensors, mid_sensor;
int sensor[7];
int s[7];
int ir_sensitivity = 160;
int gap_count=1;
#define MS 255 //Speed
//Movements

int grid[8][4];
int down_grid[4][4];
int up_grid[4][4];
int write_to_EEPROM;
//----------------------

//Magneto_turn variables
float before_turn, goal;

int forward_before_turn = 300;
int magneto_tolerance = 10;
int angle = 100;
int show_lcd_magneto = 0;

//EEPROM
int addr=0;
byte u;
//----------------------

//------------------------------------------------------ PATHFINDER ------------------------------------------------------
struct node
{
  int x,y,g,h,f;
  node& operator =(const node& a)
  {
    this->x = a.x;
    this->y = a.y;
    this->g = a.g;
    this->h = a.h;
    this->f = a.f;
    return *this;
  }
}temp,next,te;

IntegerDoublyLinkedList<node> openn;
IntegerDoublyLinkedList<int> moves;

int box[2];
int h=8;
int w=4;        //Remember to update Search() prototype as well

//------------------------------------------------------------------------------------------------------------------------




void setup() {
  Serial.begin(9600);

  servo1.attach(2);
  servo2.attach(3);


  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  for(int i=53, j=0; j<7; j++, i-=2)
    pinMode(i, OUTPUT);
  
   
  lcd.begin(16, 4);
  lcd.print("TEAM TECHIES!!");
  delay(1000);
  Blink();
  lcd.clear();
  
  compass.magneto_setup();
  compass.magneto_loop();
  read_sensors();
  print_sensors();
}

//------------------------------------------------------------------- PRACTICE ROUND ------------------------------------------------------------------------------------------------------------
void Write(int i)
{
  EEPROM.write(addr, i);
  addr = addr + 1;
  if (addr == 512)
    addr = 0;
  
  delay(100);
}

void print_degrees()
{
  Serial.print(compass.headingDegrees);
  Serial.println(" Degrees   \t");
}

void magneto_left()
{
  robot.Speed=100;
  robot.forward();
  delay(forward_before_turn);
  
  compass.magneto_loop();
  
  goal = compass.headingDegrees - angle ;//right turn
 l_limit=goal - magneto_tolerance;
 h_limit=goal + magneto_tolerance;
 if(l_limit>=360)
 {
   l_limit=l_limit-360;
 }
 else if(l_limit<=0)
 {
  l_limit=l_limit+360; 
 }
 if(h_limit>=360)
 {
   h_limit=h_limit-360;
 }
 else if(h_limit<=0)
 {
  h_limit=h_limit+360; 
 }
  robot.Speed = 200;
  robot.right();
  int k=0;  
  while(1)
  {
    robot.right();
    k=k+1;
    Serial.println(k);
    if(k == 30)
    {  robot.Speed = 150;
    robot.right();
   }
    if(h_limit-l_limit==20)
    {
    if ( (compass.headingDegrees >= l_limit && compass.headingDegrees <= h_limit))         //Goal tolerance
      break;
    }
    else
    {
    if ( (compass.headingDegrees >= l_limit || compass.headingDegrees <= h_limit))         //Goal tolerance
      break;
    }
    compass.magneto_loop();
    if(show_lcd_magneto == 1)
      show_magneto();
    print_degrees();
  }
  
  robot.stopp();
}
void magneto_right()
{
  robot.Speed=100;
  robot.forward();
  delay(forward_before_turn);
  
  compass.magneto_loop();
  
  goal = compass.headingDegrees + angle ;//right turn
 l_limit=goal - magneto_tolerance;
 h_limit=goal + magneto_tolerance;
 if(l_limit>=360)
 {
   l_limit=l_limit-360;
 }
 else if(l_limit<=0)
 {
  l_limit=l_limit+360; 
 }
 if(h_limit>=360)
 {
   h_limit=h_limit-360;
 }
 else if(h_limit<=0)
 {
  h_limit=h_limit+360; 
 }
  robot.Speed = 200;
  robot.left();
  int k=0;  
  while(1)
  {
    robot.left();
    k=k+1;
    Serial.println(k);
    if(k == 30)
    {  robot.Speed = 150;
    robot.left();
   }
   if(h_limit-l_limit==20)
    {
    if ( (compass.headingDegrees >= l_limit )&&( compass.headingDegrees <= h_limit))         //Goal tolerance
      break;
      
    }
    else
    {
      if ( (compass.headingDegrees >= l_limit )||( compass.headingDegrees <= h_limit))         //Goal tolerance
      break;
    }
    compass.magneto_loop();
    print_degrees();
    if(show_lcd_magneto == 1)
      show_magneto();
  }
  
  robot.stopp();
}


void read_sensors()
{
  sensor[0] = analogRead(A0);
  sensor[1] = analogRead(A1);
  sensor[2] = analogRead(A2);
  sensor[3] = analogRead(A3);
  sensor[4] = analogRead(A4);
  sensor[5] = analogRead(A5);
  sensor[6] = analogRead(A6);
for (int i = 0, j=53 ; i < 7; i++, j-=2)
  {
    (sensor[i] < ir_sensitivity) ? s[i] = 0 : s[i] = 1;
    digitalWrite(j, s[i]);
  }  
  right_sensors = s[4]||s[5]||s[6] ;
  left_sensors = s[0]||s[1]||s[2];
  mid_sensor = s[3];
}

//---------------------------------------------------------------------------------MOVEMENT-------------------------------------------------------------------------------------


void practice_round()
{
  char moves[] = {'f','f','f','f','f','f','f','f','r','f','r','f','f','f','f','f','f','f','l','f','l','f','f','f','f','f','f','f','r','f','r','f','f','f','f','f','f','f','s'};
  int sizee=sizeof(moves);

  ir_sensitivity = 240;
  for(int i=0; i<sizee; i++)
  {
    if(i==9)
    {
      lcd.setCursor(7,1);
      lcd.rightToLeft();
    }
  if(i==19)
  {
    lcd.setCursor(0,2);
    lcd.leftToRight();
  }
  if(i==29)
  {
    lcd.setCursor(7,3);
    lcd.rightToLeft();
  }
    switch(moves[i])
    {
      case 'f':
      {
        while(!(s[1] == 1 && s[5] == 1))
        {
          if(left_sensors == 0 && mid_sensor == 1 && right_sensors == 0)
          {
            robot.Speed= MS;
            robot.forward();
          }
          else if(left_sensors == 1 && right_sensors == 0)
          {
            robot.Speed= MS;
            robot.right(); 
          }
          else if(left_sensors == 0 && right_sensors == 1)
          {
            robot.Speed= MS;
            robot.left();
          }
          else if(left_sensors == 1 && right_sensors == 1)
          {
            robot.Speed= MS;
            robot.forward();
          }
          else if(left_sensors == 0 && right_sensors == 0 && mid_sensor == 0)
          {
            if(i==31)
            {
              robot.forward();
              delay(1000);
              write_to_EEPROM=0;
              lcd.print("0");
              Write(write_to_EEPROM);
              break;
            }
           else if(i==4||i==14||i==24||i==34)//5gaps 
           {
            robot.forward();
            delay(200);
           }
           else
            robot.stopp();
          }
          read_sensors();
        }
        if(i==31)
          break;
        robot.forward();
        delay(100);
        read_sensors();
          
        if(s[4]==1 && s[3] ==1 && s[5] == 1)
        {
          write_to_EEPROM=0;
          lcd.print("0");
          Write(write_to_EEPROM);
        }
        else
        {
          robot.forward();
          delay(150);
          read_sensors();
          if((s[2]==1 && s[3] ==0 && s[5] == 1))
          {
            write_to_EEPROM=2;
            lcd.print("2");
            Write(write_to_EEPROM);
            robot.forward();
            delay(600);
            
          }
          else
          {
            write_to_EEPROM=1;
            lcd.print("1");
            Write(write_to_EEPROM);
          }
        }
        robot.Speed= MS;
        robot.forward();
        delay(300);
        read_sensors();
        print_sensors();
        robot.stopp();
        break;
      }
      case 'l':
      {
        magneto_left();        
        break;
      }
      case 'r':
      {
        magneto_right();
        break;
      }
      case 's':
      {
        robot.stopp();
        break;
      } 
    }
  }
}

//------------------------------------------------------------------------// PRACTICE ROUND //-----------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------- DEQUE TO ARRAY -----------------------------------------------------------------------------------------------------

char* deque_to_array()
{ 
  int sizee;
  //if(ignore_stop_move)
    //sizee = moves.GetSize();    
  //else
    sizee = moves.GetSize()+1;
  char* m = new char[sizee+1];
  int s,k;

  for(int i=0; i<sizee; i++)
  {
    s = moves.Retrievee(i);
    if(i!=0)
      k = moves.Retrievee(i-1);

    switch(s)
    {
      case 0:               //forward
      {
        if(i==0)
          m[i] = 'f';
        else if(k == lt)
          m[i] = 'l';
        else if(k == rt)
          m[i] = 'r';
        else if(k == fwd)
          m[i] = 'f';
        else if(k == rev)
          m[i] = 's'; 
        else if(k == blt)
          m[i] = 'l';
        else if(k == brt)
          m[i] = 'r';
        else if(k == bfwd)
          m[i] = 'u';
        else if(k == brev)
          m[i] = 'u'; 
        else if(k == plt)
          m[i] = 'l';
        else if(k == prt)
          m[i] = 'r';
        else if(k == pfwd)
          m[i] = 'f';
        else if(k == prev)
          m[i] = 's'; 
        
        break;
      }
      case 1:               //Back
      {
        
        if(i==0)
          m[i] = 'f';
        else if(k == lt)
          m[i] = 'r';
        else if(k == rt)
          m[i] = 'l';
        else if(k == fwd)
          m[i] = 's';
        else if(k == rev)
          m[i] = 'f';
        else if(k == blt)
          m[i] = 'r';
        else if(k == brt)
          m[i] = 'l';
        else if(k == bfwd)
          m[i] = 's';
        else if(k == brev)
          m[i] = 'f'; 
        else if(k == plt)
          m[i] = 'r';
        else if(k == prt)
          m[i] = 'l';
        else if(k == pfwd)
          m[i] = 's';
        else if(k == prev)
          m[i] = 'f';  
        break;
      }
      case 2:               //Left
      {
        if(i==0)
          m[i] = 'l';
        else if(k == lt)
          m[i] = 'f';
        else if(k == rt)
          m[i] = 's';
        else if(k == fwd)
          m[i] = 'r';
        else if(k == rev)
          m[i] = 'l';
        else if(k == blt)
          m[i] = 'f';
        else if(k == brt)
          m[i] = 's';
        else if(k == bfwd)
          m[i] = 'r';
        else if(k == brev)
          m[i] = 'l';
        else if(k == plt)
          m[i] = 'f';
        else if(k == prt)
          m[i] = 's';
        else if(k == pfwd)
          m[i] = 'r';
        else if(k == prev)
          m[i] = 'l'; 
        break;
      }
      case 3:               //Right              
      {
        if(i==0)
          m[i] = 'r';
        else if(k == lt)
          m[i] = 's';
        else if(k == rt)
          m[i] = 'f';
        else if(k == fwd)
          m[i] = 'l';
        else if(k == rev)
          m[i] = 'lr'; 
        else if(k == blt)
          m[i] = 's';
        else if(k == brt)
          m[i] = 'f';
        else if(k == bfwd)
          m[i] = 'l';
        else if(k == brev)
          m[i] = 'r'; 
        else if(k == plt)
          m[i] = 's';
        else if(k == prt)
          m[i] = 'f';
        else if(k == pfwd)
          m[i] = 'l';
        else if(k == prev)
          m[i] = 'r'; 
        break;
      }
      
      case 10:               //pick-block-forward
      {
        if(i==0)
          m[i] = 'u';
        else if(k == lt)
          m[i] = 'l';
        else if(k == rt)
          m[i] = 'r';
        else if(k == fwd)
          m[i] = 'f';
        else if(k == rev)
          m[i] = 's'; 
        else if(k == blt)
          m[i] = 'l';
        else if(k == brt)
          m[i] = 'r';
        else if(k == bfwd)
          m[i] = 'f';
        else if(k == brev)
          m[i] = 's'; 
        else if(k == plt)
          m[i] = 'r';
        else if(k == prt)
          m[i] = 'l';
        else if(k == pfwd)
          m[i] = 'f';
        else if(k == prev)
          m[i] = 's'; 
        
        break;
      }
      case 11:               //pick-block-Back
      {
        
        if(i==0)
          m[i] = 'u';
        else if(k == lt)
          m[i] = 'l';
        else if(k == rt)
          m[i] = 'r';
        else if(k == fwd)
          m[i] = 's';
        else if(k == rev)
          m[i] = 'u';
        else if(k == blt)
          m[i] = 'l';
        else if(k == brt)
          m[i] = 'r';
        else if(k == bfwd)
          m[i] = 's';
        else if(k == brev)
          m[i] = 'u'; 
        else if(k == plt)
          m[i] = 'l';
        else if(k == prt)
          m[i] = 'r';
        else if(k == pfwd)
          m[i] = 's';
        else if(k == prev)
          m[i] = 'u';  
        break;
      }
      case 12:               //pick-block-Left
      {
        if(i==0)
          m[i] = 'i';
        else if(k == lt)
          m[i] = 'u';
        else if(k == rt)
          m[i] = 's';
        else if(k == fwd)
          m[i] = 'u';
        else if(k == rev)
          m[i] = 'l';
        else if(k == blt)
          m[i] = 'u';
        else if(k == brt)
          m[i] = 's';
        else if(k == bfwd)
          m[i] = 'l';
        else if(k == brev)
          m[i] = 'l';
        else if(k == plt)
          m[i] = 'u';
        else if(k == prt)
          m[i] = 's';
        else if(k == pfwd)
          m[i] = 'l';
        else if(k == prev)
          m[i] = 'l'; 
        break;
      }
      case 13:               //pick-block-Right              
      {
        if(i==0)
          m[i] = 'o';
        else if(k == lt)
          m[i] = 's';
        else if(k == rt)
          m[i] = 'u';
        else if(k == fwd)
          m[i] = 'r';
        else if(k == rev)
          m[i] = 'l'; 
        else if(k == blt)
          m[i] = 's';
        else if(k == brt)
          m[i] = 'u';
        else if(k == bfwd)
          m[i] = 'r';
        else if(k == brev)
          m[i] = 'l'; 
        else if(k == plt)
          m[i] = 's';
        else if(k == prt)
          m[i] = 'u';
        else if(k == pfwd)
          m[i] = 'r';
        else if(k == prev)
          m[i] = 'l'; 
        break;
      }
      case 20:               //place-block-forward
      {
        if(i==0)
          m[i] = 'g';
        else if(k == lt)
          m[i] = 'r';
        else if(k == rt)
          m[i] = 'l';
        else if(k == fwd)
          m[i] = 'u';
        else if(k == rev)
          m[i] = 's'; 
        else if(k == blt)
          m[i] = 'r';
        else if(k == brt)
          m[i] = 'l';
        else if(k == bfwd)
          m[i] = 'u';
        else if(k == brev)
          m[i] = 's'; 
        else if(k == plt)
          m[i] = 'r';
        else if(k == prt)
          m[i] = 'l';
        else if(k == pfwd)
          m[i] = 'u';
        else if(k == prev)
          m[i] = 's'; 
        
        break;
      }
      case 21:               //place-block-Back
      {
        
        if(i==0)
          m[i] = 'g';
        else if(k == lt)
          m[i] = 'l';
        else if(k == rt)
          m[i] = 'r';
        else if(k == fwd)
          m[i] = 's';
        else if(k == rev)
          m[i] = 'f';
        else if(k == blt)
          m[i] = 'l';
        else if(k == brt)
          m[i] = 'r';
        else if(k == bfwd)
          m[i] = 's';
        else if(k == brev)
          m[i] = 'f'; 
        else if(k == plt)
          m[i] = 'l';
        else if(k == prt)
          m[i] = 'r';
        else if(k == pfwd)
          m[i] = 's';
        else if(k == prev)
          m[i] = 'f';  
        break;
      }
      case 22:               //place-block-Left
      {
        if(i==0)
          m[i] = 'h';
        else if(k == lt)
          m[i] = 'f';
        else if(k == rt)
          m[i] = 's';
        else if(k == fwd)
          m[i] = 'l';
        else if(k == rev)
          m[i] = 'l';
        else if(k == blt)
          m[i] = 'f';
        else if(k == brt)
          m[i] = 's';
        else if(k == bfwd)
          m[i] = 'l';
        else if(k == brev)
          m[i] = 'l';
        else if(k == plt)
          m[i] = 'f';
        else if(k == prt)
          m[i] = 's';
        else if(k == pfwd)
          m[i] = 'l';
        else if(k == prev)
          m[i] = 'l'; 
        break;
      }
      case 23:               //place-block-Right              
      {
        if(i==0)
          m[i] = 'j';
        else if(k == lt)
          m[i] = 's';
        else if(k == rt)
          m[i] = 'f';
        else if(k == fwd)
          m[i] = 'r';
        else if(k == rev)
          m[i] = 'l'; 
        else if(k == blt)
          m[i] = 's';
        else if(k == brt)
          m[i] = 'f';
        else if(k == bfwd)
          m[i] = 'r';
        else if(k == brev)
          m[i] = 'l'; 
        else if(k == plt)
          m[i] = 's';
        else if(k == prt)
          m[i] = 'f';
        else if(k == pfwd)
          m[i] = 'r';
        else if(k == prev)
          m[i] = 'l'; 
        break;
      }
    }
  }
  //if(ignore_stop_move)      
    m[sizee] = 's';
  
  return m;
}

//---------------------------------------------------------------------------------- DEQUE TO ARRAY -----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------- MOVEMENTS -----------------------------------------------------------------------------------------------------------

void movement()
{
  char* m = deque_to_array();
  int sizee;
  if(ignore_stop_move)
    sizee = moves.GetSize();    
  else
    sizee = moves.GetSize()+1;
    
  
  for(int i=0; i<sizee; i++)
  {
    switch(m[i])
    {
      case 'f':
      {
        forward();
        break;
      }
      case 'l':
      {
        magneto_left();
        forward();
        break;
      }
      case 'r':
      {
        magneto_right();
        forward();
        break;
      }
      case 's':
      {
        robot.stopp();
        break;
      } 
      case 'u':
      {
        robot.forward();
        delay(300);
        robot.right();
        delay(100);
        pick_box();
        break;
      }
    }
  }
}

//---------------------------------------------------------------------------------// MOVEMENTS //-----------------------------------------------------------------------------------------------------------


void Blink()
{
      robot.stopp();
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,LOW);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,HIGH);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,LOW);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,HIGH);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,LOW);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,HIGH);
      delay(200);
      for(int i=53, j=0; j<7; j++, i-=2)
          digitalWrite(i,LOW);
}
void make_grid()
{
  int z=0;
  addr=0;
  for(int i=0;i<8;i++)
  {
     u = EEPROM.read(z);
     z = z + 1;
     if (z == 512)
        z = 0;
      grid[i][0]=u;
  }
  for(int i=7;i>=0;i--)
  {
     u = EEPROM.read(z);
     z = z + 1;
     if (z == 512)
        z = 0;
      grid[i][1]=u;
  }
  for(int i=0;i<8;i++)
  {
     u = EEPROM.read(z);
     z = z + 1;
     if (z == 512)
        z = 0;
     grid[i][2]=u;
  }
  for(int i=7;i>=0;i--)
  {
     u = EEPROM.read(z);
     z = z + 1;
     if (z == 512)
        z = 0;
      grid[i][3]=u;
  }

  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)
    {
      if(i<4)
        down_grid[i][j] = grid[i][j];
      else
        up_grid[i-4][j] = grid[i][j];
    }
  }
  
  
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(down_grid[i][j] == 2)
      {
        box[0] = i;
        box[1] = j;
      }
    }
  }
}
void print_sensors()
{
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print(sensor[2]);
  Serial.print("\t");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print(sensor[4]);
  Serial.print("\t");
  Serial.print(sensor[5]);
  Serial.print("\t");
  Serial.print(sensor[6]);
  Serial.println("\t");
}

//----------------------------------------------------------------------------------------------- PATHFINDER ---------------------------------------------------------------------------------

void search(int h, int w, int a, int b, int c, int d, int grid[][4])
{
    int initial[2] = {a,b};
    int goal[2] = {c,d};
    moves.MakeNULL();
    Serial.println();
    Serial.print("Initial: ");
    Serial.println(grid[a][b]);
    Serial.print("Goal: ");
    Serial.println(grid[c][d]);

    int closed[h][w];
    for(int i=0; i<h; i++)
    {
      for(int j=0; j<w; j++)                    //closed initialization
        closed[i][j]=0;
    }

    int heuristic[h][w];
    for(int i=0; i<h; i++)
    {
      for(int j=0; j<w; j++)                    //heuristic initialization
        heuristic[i][j]= abs(i-goal[0]) + abs(j-goal[1]);
    }

    int expand[h][w];
    for(int i=0; i<h; i++)
    {
      for(int j=0; j<w; j++)                    //expand initialization
        expand[i][j]=-1;
    }

    int action[h][w];
    for(int i=0; i<h; i++)
    {
      for(int j=0; j<w; j++)                    //action initialization
        action[i][j]=-1;
    }
    
    int movee[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    char move_sign[6] = {'^','v','<','>','B','P'};                  //movements & costs
    int cost[4] = {1,1,1,1};
   
    temp.x=initial[0];
    temp.y=initial[1];
    temp.g=0;
    temp.h= heuristic[temp.x][temp.y];
    temp.f = temp.g + temp.h;
    
    openn.push__front(temp);
    
    bool found = false;
    bool resign = false;
    int countt = 0;
  
    int k,sizee;
    
    while(found == false && resign == false)
    { 
        if(openn.GetSize()==0)
        {
          resign = true;
          Serial.print("\nSearch failed\n");
        }
        else
        {
            sizee = openn.GetSize();
            k=0;

            
            next.x = openn.Retrievee(0).x;
            next.y = openn.Retrievee(0).y;
            next.g = openn.Retrievee(0).g;
            next.h = openn.Retrievee(0).h;
            next.f = openn.Retrievee(0).f;

            for(int i=0; i<sizee ; i++)
            {
              for(int j=0; j<sizee-1; j++)
              {
                if(openn.Retrievee(j).f < openn.Retrievee(j+1).f)
                {
                   next.x = openn.Retrievee(j).x;
                   next.y = openn.Retrievee(j).y;
                   next.g = openn.Retrievee(j).g;
                   next.h = openn.Retrievee(j).h;
                   next.f = openn.Retrievee(j).f;

                    k=j;
                }  
              }
            }
            
            sizee = openn.GetSize();
            openn.Delete(k);
            expand[next.x][next.y] = countt;
            countt++;

        if(next.x == goal[0] && next.y == goal[1])
        {
            found = true;
            Serial.print("\nSearch Success\n");
        }
        else
        {
            for(int i=0; i<4; i++)
            {
              temp.x = next.x + movee[i][0];
              temp.y = next.y + movee[i][1];    
              if(temp.x >= 0 && temp.x < h && temp.y >= 0 && temp.y < w)
              {
                  if(closed[temp.x][temp.y] == 0 &&  grid[temp.x][temp.y] == 0)   // Path
                  {           
                    temp.g = next.g + cost[i];
                    temp.h = heuristic[temp.x][temp.y];
                    temp.f = temp.g + temp.h;
                    openn.push__front(temp);                
                    closed[temp.x][temp.y] = 1;
                    action[temp.x][temp.y] = i;
                  }
                  if(closed[temp.x][temp.y] == 0 &&  grid[temp.x][temp.y] == 2)   // Box
                  {           
                    temp.g = next.g + cost[i];
                    temp.h = heuristic[temp.x][temp.y];
                    temp.f = temp.g + temp.h;
                    openn.push__front(temp);                
                    closed[temp.x][temp.y] = 1;
                    action[temp.x][temp.y] = i+10;
                  } 
                  if(closed[temp.x][temp.y] == 0 &&  grid[temp.x][temp.y] == 3)   // Place Box
                  {           
                    temp.g = next.g + cost[i];
                    temp.h = heuristic[temp.x][temp.y];
                    temp.f = temp.g + temp.h;
                    openn.push__front(temp);                
                    closed[temp.x][temp.y] = 1;
                    action[temp.x][temp.y] = i+20;
                  }
              } 
            }
        }
      }
  }      

    
    char policy[h][w];
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)                        //policy initialization
        policy[i][j]=' ';
    } 
    policy[goal[0]][goal[1]] = '*';

    bool box_flag = false;
    bool place_box_flag = false;
    int q,o;
    while(temp.x != initial[0] || temp.y != initial[1])
    {
      if(action[next.x][next.y] >= 20)
      {
          q = action[next.x][next.y] - 20;
          action[next.x][next.y] -= 20; 
          temp.x = next.x - movee[q][0];
          temp.y = next.y - movee[q][1];
          place_box_flag = true;
      }
      else if(action[next.x][next.y] >= 10 && action[next.x][next.y] < 20)
      { 
          o = action[next.x][next.y] - 10;
          temp.x = next.x - movee[o][0];
          temp.y = next.y - movee[o][1];
          box_flag = true;
      }
      else
      {
          temp.x = next.x - movee[action[next.x][next.y]][0];
          temp.y = next.y - movee[action[next.x][next.y]][1];
      }
      
      if(box_flag == true)
          policy[temp.x][temp.y] = move_sign[4];
      else if(place_box_flag == true)
          policy[temp.x][temp.y] = move_sign[5];
      else
          policy[temp.x][temp.y] = move_sign[action[next.x][next.y]];
      
      
      if(place_box_flag == true)
      {
          moves.push__front(q+20);
          place_box_flag = false;
      }
      else if(box_flag == true)
      {
          moves.push__front(o+10);
          box_flag = false;
      }
      else
      {
          moves.push__front(action[next.x][next.y]);
      }
      next = temp;
   }
      int s = moves.GetSize();
  
      Serial.println();
      for(int i=0; i<s; i++)
      {
        Serial.print(moves.Retrievee(i));
        Serial.print("\t");
      }

//-----------------------------------------------------------------------------------------------------

  Serial.println("\nGrid Display:");
  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)                               //Grid Display
    {
      Serial.print(grid[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  Serial.println("\nHeuristic Display: ");
  for(int i=0; i<h; i++)
        {
          for(int j=0; j<w; j++)                        //Heuristic Display
          {  Serial.print(heuristic[i][j]);
          Serial.print("\t");
          }
          
          Serial.println();
  }
  
  Serial.println("\nClosed Display:");
  for(int i=0; i<h; i++)
        {
          for(int j=0; j<w; j++)                        //Closed Display
          {  Serial.print(closed[i][j]);
          Serial.print("\t");
          }
          
          Serial.println();
  }

 Serial.println("\nAction Display: ");
 for(int i=0; i<h; i++)
        {
          for(int j=0; j<w; j++)                        //Action Display
          {  Serial.print(action[i][j]);
          Serial.print("\t");
          }
          
          Serial.println();
  }
  
 Serial.println("\nExpand Display:");
 for(int i=0; i<h; i++)
        {
          for(int j=0; j<w; j++)                        //Expand Display
          {  Serial.print(expand[i][j]);
          Serial.print("\t");
          }
          
          Serial.println();
  }
  Serial.println("\nPolicy Display: ");
  for(int i=0; i<h; i++)
  {
          for(int j=0; j<w; j++)                        //Policy Display
            Serial.print(policy[i][j]);
          Serial.println();
  }
  delay(1000);
  
  Serial.println("\n");
}

void show_down_grid()
{
  Serial.println();
  Serial.println("Down Grid Display: ");
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            Serial.print(down_grid[i][j]);
          }
         Serial.println();
        }
}

void show_up_grid()
{
  Serial.println();
  Serial.println("Up Grid Display: ");
  
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            Serial.print(up_grid[i][j]);
          }
         Serial.println();
        }
}

void show_grid()
{
  Serial.println();
  Serial.println("Grid Display: ");
  
        for(int i=0;i<8;i++)
        {
          for(int j=0;j<4;j++)
          {
            Serial.print(grid[i][j]);
          }
         Serial.println();
        }
}
void show_box()
{
  Serial.println();
  Serial.print("Box[0]: ");
  Serial.println(box[0]);
  Serial.print("Box[1]: ");
  Serial.println(box[1]);
}

void forward()
{
  
        read_sensors();
        print_sensors();
        while(!(s[1] == 1 && s[5] == 1))
        {
          if(left_sensors == 0 && mid_sensor == 1 && right_sensors == 0)
          {
            robot.forward();
          }
          else if(left_sensors == 1 && right_sensors == 0)
          {
            robot.right(); 
          }
          else if(left_sensors == 0 && right_sensors == 1)
          {
            robot.left();
          }
          else if(left_sensors == 1 && right_sensors == 1)
          {
            robot.forward();
          }
          else
          {
            if(jugaad == 1)//5gaps 
            {
              robot.forward();
              delay(700);
              Blink();
              jugaad=0;
            }
            else
              robot.stopp();
          }
          read_sensors();
        }       
        robot.forward();
        delay(500);
        read_sensors();
        print_sensors();
        robot.stopp();
}

void show_movement()
{
  char* m = deque_to_array();
  int sizee;
  if(ignore_stop_move)
    sizee = moves.GetSize();    
  else
    sizee = moves.GetSize()+1;
    
  for(int i=0; i<sizee; i++)
  {
    Serial.print(m[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void show_magneto()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Degrees: ");
  lcd.print(compass.headingDegrees);
  lcd.setCursor(0,1);
  lcd.print("Goal: ");
  lcd.print(goal);
  lcd.setCursor(0,2);
  lcd.print("High limit: ");
  lcd.print(h_limit);
  lcd.setCursor(0,3);
  lcd.print("Low Limit: ");
  lcd.print(l_limit);
}

void show_lcd_grid()
{
  lcd.clear();
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<8;j++)
    {
       lcd.print(grid[j][i]);
    }
    lcd.setCursor(0,i+1);
  }
}


//---------------------------------------------------------------------------------------------- ULTRASONIC -------------------------------------------------------------------------------------------------

void measure_distance()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
}

long microsecondsToInches(long microseconds)
{
  return microseconds/ 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void show_distance()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("in: ");
  lcd.print(inches);
  lcd.setCursor(0,1);
  lcd.print("cm: ");
  lcd.print(cm);
  delay(10);
}

void test_ultrasonic()
{
  measure_distance();
  show_distance();
}

//---------------------------------------------------------------------------------------- Servos -----------------------------------------------------------------------------------------------------------

void sweep_servos()
{
  /*for(
    pos = s1_min; pos <= s1_max; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }*/
  for(pos = s2_min; pos <= s2_max; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = s2_max; pos>=s2_min; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  
  /*for(pos = s1_max; pos>=s1_min; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }*/ 
}

void pick_box()
{
  test_ultrasonic();
  robot.stopp();
  for(pos = s1_max; pos>=s1_min; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(25);                       // waits 15ms for the servo to reach the position 
  }  
  for(pos = s2_min; pos <= s2_max; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(100);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = s1_min; pos <= s1_max; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(25);                       // waits 15ms for the servo to reach the position 
  } 
}

void place_box()
{
  for(pos = s1_max; pos>=s1_min; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(25);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = s2_max; pos>=s2_min; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(100);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = s1_min; pos <= s1_max; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(25);                       // waits 15ms for the servo to reach the position 
  } 
  
    
}
void pod_box()
{
  test_ultrasonic();
  while(!(cm >= 30))
  {
    if(left_sensors == 0 && mid_sensor == 1 && right_sensors == 0)
          {
            robot.forward();
          }
          else if(left_sensors == 1 && right_sensors == 0)
          {
            robot.right(); 
          }
          else if(left_sensors == 0 && right_sensors == 1)
          {
            robot.left();
          }
          else if(left_sensors == 1 && right_sensors == 1)
          {
            robot.forward();
          }
          else
          {
            
              robot.stopp();
          }
          read_sensors();
    test_ultrasonic();
  }
  robot.stopp();
  place_box();
}


//---------------------------------------------------------------------------------------------// VOID LOOOOOOOOOOOOOOOOOOOP //-------------------------------------------------------------------------------
void loop(){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
    make_grid();
    servo1.write(s1_max);
    servo2.write(s2_min);
    test_ultrasonic();
    //Blink();
    switch(customKey)
    {
      case '1':
      {
        lcd.clear();
        practice_round();
        break;
      }
      case '2':
      {
        show_lcd_grid();
        break;
      }
      case '3':
      {
        lcd.clear();
        forward();
        search(4, 4, 0, 0, box[0], box[1], down_grid);
        movement();
        pick_box();
        search(4, 4, box[0]-1, box[1],1,3, down_grid);
        movement();  
        break;
      }
      case '5':
      {
        lcd.clear();
        robot.forward();
        delay(300);
        magneto_left();
        forward();
        magneto_left();
        forward();
        robot.forward();
        delay(100);
        robot.right();
        delay(1000);        
        forward();
        break;
      }
      case '6':
      {
        lcd.clear();
        robot.forward();
        delay(500);                      
        if(up_grid[1][3] == 1) //right wala one ha
        {
          magneto_left();
          forward();
          magneto_right();
          forward();
          magneto_right(); 
          search(4, 4, 0, 2,2,3, up_grid);
          jugaad = 1;
          search(4, 4, 0,2 ,2,3, up_grid);
          movement();
          ignore_stop_move = 1;
          search(4, 4, 3, 3,3,0, up_grid);
          movement();  
          ignore_stop_move = 0;
        }
        else
        {
          magneto_right();
          forward();
          forward();
        }
        break;
      }
      case '7':
      {
        lcd.clear();
        forward();
        search(4, 4, 3, 3,3,0, up_grid);
        movement();  
        break;
      }
      case '8':
      {
        //sweep_servos();
        pick_box();
        delay(2000);
        place_box();
        break;
      }
      case '9':
      {
        //sweep_servos();
        pick_box();
        delay(4000);
        pod_box();
        break;
      }
      case '#':
      {
        lcd.clear();
        show_grid();
        show_down_grid();
        show_up_grid();
        show_box();
        break;
      }
      case '0':
      {
        lcd.clear();
        search(4, 4, 0, 0, 2, 1, down_grid);
        show_movement();
        break;
      }
    }
}
