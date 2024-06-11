#include <Servo.h>
#include <Keypad.h>

Servo servoMotor;

const int servoPin = 12;          // 서보 모터 핀
const int buzzerPin = 13;         // 부저 핀
const int servoOpenAngle = 80;    // 서보 모터가 열린 상태의 각도
const int servoCloseAngle = 0;    // 서보 모터가 닫힌 상태의 각도
        
int numOperations = 0;            // 입력된 작동 횟수
bool startOperation = false;      // 작동 시작 여부
bool isCancelled = false;         // 작업 취소 여부

const byte ROWS = 4;              // 키패드의 행 수
const byte COLS = 4;              // 키패드의 열 수

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 6, 7, 8};   // 행에 연결된 Arduino 핀
byte colPins[COLS] = {9, 10, 11, 4}; // 열에 연결된 Arduino 핀

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  servoMotor.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);       // 부저 핀을 출력으로 설정
  Serial.begin(9600);
}

void loop() {                      //메인작동함수
  char keyPressed = keypad.getKey();
  if (keyPressed) {
    Serial.print("Key Pressed: ");
    Serial.println(keyPressed);

    if (keyPressed >= '0' && keyPressed <= '9') {
      numOperations = numOperations * 10 + (keyPressed - '0'); // 입력된 숫자를 작동 횟수로 변환
      Serial.print("Number of Operations: ");
      Serial.println(numOperations);
    }
    if (keyPressed == '*') { // '*' 버튼이 눌렸을 때
      startOperation = true; // 작동 시작
    }
    if (keyPressed == 'D') { // 'D' 버튼이 눌렸을 때
      isCancelled = true;    // 작업 취소 설정
      Serial.println("Operation Cancelled.");
    }
  }

  if (startOperation) {  // 서보모터 각도 초기화
    operateServo(numOperations);
    startOperation = false; // 작동 후 초기화
    numOperations = 0;      // 입력된 숫자 초기화
  }
}

void operateServo(int times) { //서보모터 제어함수
  isCancelled = false; // 작동 시작 시 취소 상태 초기화
  for (int i = 0; i < times; i++) {
    if (isCancelled) { // 루프 중간에 취소 상태를 확인
      Serial.println("Operation Cancelled During Execution.");
      break; // 취소가 설정된 경우 루프 중단
    } 
    openServo();  // 서보 모터를 엽니다.
    delay(500);   // 0.5초 대기
    closeServo(); // 서보 모터를 닫습니다.
    delay(1000);  // 1초 대기
  }
  if (!isCancelled) {
    buzz();  // 모든 작업이 정상적으로 끝난 후 부저를 울립니다.
  }
}

void openServo() {
  servoMotor.write(servoOpenAngle); // 서보 모터를 엽니다.
}

void closeServo() {
  servoMotor.write(servoCloseAngle); // 서보 모터를 닫습니다.
}

void buzz() {
  digitalWrite(buzzerPin, HIGH); // 부저를 울립니다.
  delay(100);                    // 0.1초 동안 울림
  digitalWrite(buzzerPin, LOW);  // 부저를 끕니다.
}
