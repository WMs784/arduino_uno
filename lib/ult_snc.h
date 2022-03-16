#define rep(i,n) for (int i = 0;i < (int)n;i++)
#define trigPin 11
#define echoPin 12
float duration = 0;
float res_distance = 0;

void set_ult_snc(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
float dis(){
  rep(i,6) {
        rep(j,100) {
            digitalWrite(trigPin, LOW);
            digitalWrite(echoPin, LOW);
            delayMicroseconds(1);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration = pulseIn(echoPin, HIGH);
            res_distance += duration * 0.000001 * 34000 / 2;
        }
        digitalWrite(trigPin, LOW);
        digitalWrite(echoPin, LOW);
        res_distance = res_distance * 0.01;//１００個の平均を取る
    }
    return res_distance;
}