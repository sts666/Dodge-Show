void Timer_ISR(){
	volatile int * Timer_ptr = (int *)0xfffec600;
	printf("Point 1");
	volatile int * Timer_Interrupt_ptr = (int *)0xfffec60c;
	int interrupt=*(Timer_Interrupt_ptr);
	*(Timer_Interrupt_ptr)=interrupt;
}

void config_Timer(){
	volatile int * Timer_ptr = (int *)0xfffec600;
	*Timer_ptr=200000000;
	volatile int * Timer_interrupt_ptr = (int *)0xfffec60c;
	*(Timer_interrupt_ptr)=0b111;
}