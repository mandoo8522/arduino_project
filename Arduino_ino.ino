int levelSensor = 8; // 수위 센서의 핀 번호 선언
int yellowLED = 7; // 노란색 LED의 핀 번호 선언
int greenLED = 6; // 녹색 LED의 핀 번호 선언
int buzzer = 5; // 부저의 핀 번호 선언

int previousState = -1;   // 이전 상태를 저장할 변수 (-1로 초기화하여 처음에는 반드시 상태가 변경되도록 함)

void setup() {
               // 각 핀의 모드 설정
  pinMode(levelSensor, INPUT);   // 수위 센서 핀을 입력 모드로 설정
  pinMode(yellowLED, OUTPUT);    // 노란색 LED 핀을 출력 모드로 설정
  pinMode(greenLED, OUTPUT);     // 녹색 LED 핀을 출력 모드로 설정
  pinMode(buzzer, OUTPUT);       // 부저 핀을 출력 모드로 설정
}

void loop() {
  int currentState = digitalRead(levelSensor); // 수위 센서에서 디지털 값을 읽어들임

  if (currentState != previousState) {      // 현재 상태가 이전 상태와 다를 때 (상태 변경 발생)
    if (currentState == 1) {                // 상태 값이 1인 경우 (물이 감지된 경우)
      digitalWrite(yellowLED, HIGH);        // 노란색 LED 켜기
      digitalWrite(greenLED, LOW);          // 녹색 LED 끄기
    } else {                                // 상태 값이 0인 경우 (물이 감지되지 않은 경우)
      digitalWrite(yellowLED, LOW);         // 노란색 LED 끄기
      digitalWrite(greenLED, HIGH);         // 녹색 LED 켜기
      if (previousState == 1) {             // 이전 상태가 1인 경우 (노란색 LED가 켜져 있던 경우)
        tone(buzzer, 1000, 500);            // 부저를 1000Hz로 500ms 동안 울리기
        delay(500);                         // 부저 소리가 끝난 후 약간의 지연을 추가하여 반복 울림 방지
        noTone(buzzer);                     // 부저 소리를 끄기
      }
    }
    previousState = currentState;           // 이전 상태를 현재 상태로 업데이트
  }
}