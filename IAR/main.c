#include "driverlib.h"
#include "mymsp430.h"

volatile uint32_t MCLK=0;
void main( void )
{
	/* Stop watchdog timer */
	WDT_A_hold(WDT_A_BASE);

	Clk_Using_DCO_Init(20000,4000);

	MCLK=UCS_getMCLK();

	GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN7);//Green led
	GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);//Red led

	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN1|GPIO_PIN6);// Button2 and external button
	GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN1|GPIO_PIN6);
	GPIO_selectInterruptEdge(GPIO_PORT_P1,GPIO_PIN1|GPIO_PIN6,GPIO_HIGH_TO_LOW_TRANSITION);
	GPIO_clearInterrupt(GPIO_PORT_P1,GPIO_PIN1|GPIO_PIN6);

	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,GPIO_PIN1);// Button1
	GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
	GPIO_selectInterruptEdge(GPIO_PORT_P2,GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
	GPIO_clearInterrupt(GPIO_PORT_P2,GPIO_PIN1);



	__enable_interrupt();

	while(1)
	{

	}
}

/* Interrrupt Service Rountie */
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
	if(GPIO_getInterruptStatus(GPIO_PORT_P1,GPIO_PIN1))
	{
		GPIO_toggleOutputOnPin(GPIO_PORT_P4,GPIO_PIN7);// Toogle Green led
		GPIO_clearInterrupt(GPIO_PORT_P1,GPIO_PIN1);
	}
	else if (GPIO_getInterruptStatus(GPIO_PORT_P1,GPIO_PIN6))
	{
		GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);// Toogle Red led
		GPIO_clearInterrupt(GPIO_PORT_P1,GPIO_PIN6);
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
	if(GPIO_getInterruptStatus(GPIO_PORT_P2,GPIO_PIN1))
	{
		GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);// Toogle Red led
		GPIO_clearInterrupt(GPIO_PORT_P2,GPIO_PIN1);
	}
}










