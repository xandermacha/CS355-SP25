#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void override_sigint(int);
int interupt_count = 0;
void loop() {
    for(int i=0; i<10; i++) {
        printf("Hello %d\n", i);
        sleep(1);
    }
}
int main(){
	signal(SIGINT, override_sigint);
	loop();
	return 0;
}
void override_sigint(int signum) {
	interupt_count++;
	printf("ctrl+c pressed %d/10 times\n", interupt_count);
	if(interupt_count >= 10) {
		printf("sigint is now back to default");
		signal(SIGINT, SIG_DFL);
	}
}