#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

const int hall0 = 2;
const int hall1 = 3;
const int hall2 = 4;
const int hall3 = 5;
bool flag0 = false;
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;
const int maglock =  12;
int halls[4] = {hall0, hall1, hall2, hall3};
bool flags[4] = {flag0, flag1, flag2, flag3};
int hallsLen = arr_len(halls);
bool penalty1 = false;
bool penalty2 = false;
bool penalty3 = false;
bool unlock = false;
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < hallsLen; i++){
    pinMode(halls[i], INPUT);
  }
  pinMode(maglock, OUTPUT);
}

void loop(){
  //Hall 0 = Diamond
  //Hall 1 = Trap
  //Hall 2 = Square
  //Hall 3 = Triangle
  for(int i = 0; i < hallsLen; i++){
    Serial.print("Hall");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(digitalRead(halls[i]));
  }
  bool sw0 = !digitalRead(hall0);
  bool sw1 = !digitalRead(hall1);
  bool sw2 = !digitalRead(hall2);
  bool sw3 = !digitalRead(hall3);
  if (sw0 && !penalty1 && !penalty2 && !penalty3) {
    flag0 = true;
  }
  else {
    flag0 = false;
  }
  if (sw1 && flag0 && !penalty1 && !penalty2 && !penalty3) {
    flag1 = true;
  }
  else if (sw1 && !flag0) {
    flag1 = false;
    penalty1 = true;
  }
  else if (!sw1) {
    flag1 = false;
    penalty1 = false;
  }
  if (sw2 && flag1 && !penalty1 && !penalty2 && !penalty3) {
    flag2 = true;
  }
  else if (sw2 && !flag1) {
    flag2 = false;
    penalty2 = true;
  }
  else if (!sw2) {
    flag2 = false;
    penalty2 = false;
  }
  if (sw3 && flag2 && !penalty1 && !penalty2 && !penalty3) {
    flag3 = true;
    unlock = true;
  }
  else if (sw3 && !flag2) {
    flag3 = false;
    penalty3 = true;
  }
  else if (!sw3) {
    flag3 = false;
    penalty3 = false;
  }

  if (!unlock) {
    digitalWrite(maglock, LOW);
  }
  else{
    digitalWrite(maglock, HIGH);
    delay(30000);
    digitalWrite(maglock, LOW);
    unlock = false;
  }
}
