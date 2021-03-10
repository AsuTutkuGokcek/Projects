#include <stdio.h>
int secret_pin=12345;

void transfer_money() {
	printf("$1000 was transferred to your account.\n");
}

void check_password() {
	struct{
	char username[100];
	int check_pin;
	int local_secret_pin;	
	}my;
	my.local_secret_pin=secret_pin;

	printf("Enter username:\n");
	scanf("%s",my.username);

	printf("Your username was: %s\n",my.username);

	printf("Enter pin:\n");
	scanf("%d",&my.check_pin);
	
	if (my.check_pin==my.local_secret_pin)
	{
		printf("You entered the right pin!\n");
		transfer_money();
	}
	else
		printf("Invaild pin. bye.\n");
}

int main() {
	check_password();
	return 0;
}
