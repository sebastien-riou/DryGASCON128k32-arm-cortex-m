#include <mbed.h>
DigitalOut led1(LED1);
void set_led(int state){
    led1 = state;
}
void test(void);
int main(){
    while (true){
        test();
    }
    return 0;
}

