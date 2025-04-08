//---Giao tiếp cảm biến siêu âm
#define trigPin 12
#define echoPin 13
int distance = 0;
//---Giao tiếp bánh xe
//OUT1,2 Nối với bánh bên trái,
//OUT3,4 Nối với bánh bên phải
#define in1 8  //điều khiển OUT1
#define in2 7  //điều khiển OUT2
#define in3 6  //điều khiển OUT3
#define in4 5  //điều khiển OUT4
#define ena 9  //Thay đổi tốc độ của bánh bên trái
#define enb 3  //Thay đổi tốc độ của bánh bên phải
int tocdo = 200;
//---Giao tiếp cảm biến
#define cbt A0  //cảm biến bên trái
#define cbg A1  //Cảm biến ở giữa
#define cbp A2  //Cảm biến bên phải
//---giao tiếp bluetooth
int command = 0;  //biến chứa giá trị nhận được từ bluetooth
int a = 1;  //biến chọn chế độ hoạt động. a=1:chạy dò line, a=2: chạy theo điều khiển từ xa

void setup() {
  Serial.begin(9600);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(cbt, INPUT_PULLUP);
  pinMode(cbg, INPUT_PULLUP);
  pinMode(cbp, INPUT_PULLUP);
  // digitalWrite(ena,1);
  // digitalWrite(enb,1);
  analogWrite(ena, tocdo);
  analogWrite(enb, tocdo);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop() {
  if (a == 1) {
    DoLineDigital();
  } else if (a == 2) {
    Remote();
  } else if (a == 3) {
    Remote_internet();
  }

  //TranhVatCan();
}
void Remote_internet() {
  int i = digitalRead(A3);
  int j = digitalRead(A4);
  int k = digitalRead(A5);
  if((i==0)&&(j==1)&&(k==0)){
    Tien();
  }
  else if((i==1)&&(j==0)&&(k==0)){
    Trai();
  }
  else if((i==0)&&(j==0)&&(k==1)){
    Phai();
  }
  else if((i==0)&&(j==0)&&(k==0)){
    Lui();
  }
  else if((i==1)&&(j==1)&&(k==1)){
    Dung();
  }
}

void Remote() {
  if (Serial.available() > 0) {
    command = (char)Serial.read();
    switch (command) {
      case 'F':
        Tien();
        break;
      case 'B':
        Lui();
        break;
      case 'L':
        Trai();
        break;
      case 'R':
        Phai();
        break;
      case 'S':
        Dung();
        break;
      default:;
    }
  }
}
void DoLineDigital() {
  if ((digitalRead(cbg) == 1) && (digitalRead(cbt) == 1) && (digitalRead(cbp) == 1)) {
    Dung();
    Serial.println("Dung");
  } else if ((digitalRead(cbg) == 1) && (digitalRead(cbt) == 1)) {
    XoayTrai();
    Serial.println("Xoay Trai");
  } else if ((digitalRead(cbg) == 1) && (digitalRead(cbp) == 1)) {
    XoayPhai();
    Serial.println("Xoay Phai");
  } else if (digitalRead(cbt) == 1) {
    Phai();
    Serial.println("Phai");
  } else if (digitalRead(cbp) == 1) {
    Trai();
    Serial.println("Trai");
  } else if (digitalRead(cbg) == 1) {
    Tien();
    Serial.println("Tien");
  }
}

void TranhVatCan() {
  KhoangCach();
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 40) {
    Dung();
    Xoay();
    delay(1000);
  } else {
    Tien();
  }
}

void XoayTrai() {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void XoayPhai() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void Tien() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void Lui() {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void Trai() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}
void Phai() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void Dung() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}
void Xoay() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void KhoangCach() {
  int duration = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}
