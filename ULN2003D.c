#include "ULN2003D.h"

// 步进电机初始化
void Stepper_Init(void) {
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
}

// 步进电机单步转动
void Stepper_Step(int dir) {
    static int step = 0;
    
    if (dir == 1) {  // 正向转动
        step++;
        if (step >= 4) step = 0;
    } else {  // 反向转动
        step--;
        if (step < 0) step = 3;
    }
    
    switch (step) {
        case 0:
            IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
            break;
        case 1:
            IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
            break;
        case 2:
            IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
            break;
        case 3:
            IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
            break;
    }

    while(!stepflag)
        stepflag = 0;
}

// 步进电机转动一定角度
void Stepper_Turn(int steps, int dir) {
    int i;
    for (i = 0; i < steps; i++) {
        Stepper_Step(dir);
    }
}

// 在密码验证成功后开门
void Open_Door(void) {
    Stepper_Turn(STEPS_PER_REV / 4, 1);  // 假设转动1/4圈开门
}
