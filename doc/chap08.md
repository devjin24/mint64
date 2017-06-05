# 8. A20 게이트를 활성화하여 1MB 이상 영역에 접근해보자
## 8.1 IA-32e 모드 커널과 메모리 맵
IA-32e 모드 커널을 실행하기 위한 준비작업으로 PC에 설치된 메모리가 64MB 이상인지 검사하고 커널이 위치할 영역을 모두 0으로 초기화하는 작업을 수행한다.
그리고 부팅과정을 완료하고 1MB 이상의 메모리에 정상적으로 접근되는지 확인한다.  
미리 초기화하는 이유는 IA-32e 커널 이미지가 초기화되지 않은 영역을 포함하고 있지 않기 때문이다.

## 8.2 IA-32e 모드 커널을 위한 메모리 초기화

## 8.3 1MB 어드레스와 A20 게이트
### 8.3.1 A20 게이트의 의미와 용도
A20 게이트에서 A20의 의미는 어드레스의 20번째 비트를 뜻하며, A20의 역할은 어드레스 20번째 비트를 활성화하거나 비활성화하여 
XT PC의 어드레스 계산 방식과 호환성을 유지시킵니다.

### 8.3.2 A20 게이트 활성화 방법
* 키보드 컨트롤러로 활성화하는 방법
* 시스템 컨트롤 포트로 활성화하는 방법
* BIOS 서비스로 활성화하는 방법
#### 시스템 컨트롤 포트로 A20 게이트 활성화하기

#### BIOS 서비스로 A20 게이트 활성화 방법
## 8.4 A20 게이트 적용과 메모리 크기 검사
### 8.4.1 A20 게이트 활성화 코드 적용
### 8.4.2 메모리 크기 검사 기능 추가

