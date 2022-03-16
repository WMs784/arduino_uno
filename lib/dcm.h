#define motor11 3
#define motor12 4
#define motor21 5
#define motor22 6

void set_dcm(){
  pinMode(motor11, OUTPUT);
  pinMode(motor12, OUTPUT);
  pinMode(motor21, OUTPUT);
  pinMode(motor22, OUTPUT);
}