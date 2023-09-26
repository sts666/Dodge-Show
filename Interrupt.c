/** Initialize the banked stack pointer register for IRQ mode
*/
#define INT_DISABLE 0b11000000
#define INT_ENABLE 0b01000000
#define IRQ_MODE 0b10010
#define SVC_MODE 0b10011
#define KEY_BASE 0xff200050
#define MPCORE_GIC_CPUIF 0xfffec100
#define ICCICR 0x000
#define ICCPMR 0x004
#define MPCORE_GIC_DIST 0xFFFED000
#define ICDDCR 0x000
#define ENABLE 0x1



	
void set_A9_IRQ_stack(void);
void config_KEYs(void);
void enable_A9_interrupts(void);
void config_GIC(void);
void __attribute__((interrupt)) __cs3_isr_irq(void);
void key_ISR();
void key0_ISR();
void key1_ISR();
void key2_ISR();
void key3_ISR();

int main(void){
	set_A9_IRQ_stack(); // initialize the stack pointer for IRQ mode
	config_GIC(); // configure the general interrupt controller
	config_KEYs(); // configure pushbutton KEYs to generate interrupts
	enable_A9_interrupts(); // enable interrupts
	while(1){
		
	}
	
}
	
void config_KEYs(){
	volatile int * KEY_ptr = (int *)KEY_BASE; // pushbutton KEY address
	*(KEY_ptr + 2) = 0x3; // enable interrupts for KEY[1]
}

void set_A9_IRQ_stack(void) {
	int stack, mode;
	stack = 0x40000;
	mode = INT_DISABLE | IRQ_MODE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
	/* set banked stack pointer */
	asm("mov sp, %[ps]" : : [ps] "r"(stack));
	/* go back to SVC mode before executing subroutine return! */
	mode = INT_DISABLE | SVC_MODE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
}

void enable_A9_interrupts(void) {
	int status = SVC_MODE | INT_ENABLE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

void config_GIC(void) {
	int address; // used to calculate register addresses
	/* configure the HPS timer interrupt */ *((int *)0xFFFED8C4) = 0x01000000;
	*((int *)0xFFFED118) = 0x00000080;
	/* configure the FPGA interval timer and KEYs interrupts */ *((int *)0xFFFED848) = 0x00000101;
	*((int *)0xFFFED108) = 0x00000300;
	// Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all
	// priorities
	address = MPCORE_GIC_CPUIF + ICCPMR;
	*((int *)address) = 0xFFFF;
	// Set CPU Interface Control Register (ICCICR). Enable signaling of
	// interrupts
	address = MPCORE_GIC_CPUIF + ICCICR;
	*((int *)address) = ENABLE;
	// Configure the Distributor Control Register (ICDDCR) to send pending
	// interrupts to CPUs
	address = MPCORE_GIC_DIST + ICDDCR;
	*((int *)address) = ENABLE;
}

void __attribute__((interrupt)) __cs3_isr_irq(void) {
	// Read the ICCIAR from the processor interface
	int address = MPCORE_GIC_CPUIF + 0xc;
	int int_ID = *((int *)address);
	if (int_ID == 73) // check if interrupt is from the KEYs
		key_ISR();
	else
		while (1); // if unexpected, then stay here
	// Write to the End of Interrupt Register (ICCEOIR)
	address = MPCORE_GIC_CPUIF + 0x10;
	*((int *)address) = int_ID;
	return; 
}

void key_ISR(){
	volatile int *push_button_ptr = (int *)0xff200050;
	int push=*push_button_ptr;
	if(push==0b0001)
		key0_ISR();
	if(push==0b0010)
		key1_ISR();
	if(push==0b0100)
		key2_ISR();
	if(push==0b1000)
		key3_ISR();	
}

void key0_ISR(){
	volatile int * led_ptr= (int*) 0xff200000;
	*led_ptr=0b0001;
}
	
void key1_ISR(){
	volatile int * led_ptr= (int*) 0xff200000;
	*led_ptr=0b0010;
}

void key2_ISR(){
	volatile int * led_ptr= (int*) 0xff200000;
	*led_ptr=0b0100;
}

void key3_ISR(){
	volatile int * led_ptr= (int *) 0xff200000;
	*led_ptr=0b1000;
}