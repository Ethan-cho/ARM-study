.text
.global main

main:
    mov x0, #1       // x0 <- 상수 1 값 넣기 (1의미: stdout)
    ldr x1, =message // x1 <- message(hello world 문자열) 주소값 넣기
    ldr x2, =len     // x2 <- len 값(hello world 문자열 길이) 넣기
                     // x0: 첫번째 인자
                     // x1: 두번째 인자
                     // x2: 세번째 인자
    mov x8, 0x40     // x8 <- 시스템콜 write() 번호넣기: 0x40 (64)
    svc 0            // 시스템콜 발생시키는 명령어
    ret              // 함수 리턴

.data
// .ascii 에서 마지막에 zero(NULL)로 끝나는 문자열로 선언
message: .asciz "hello world\n"

// 현재 position(.)에서 message 주소를 뺀값으로 문자열 길이 구하기
len= . - message
