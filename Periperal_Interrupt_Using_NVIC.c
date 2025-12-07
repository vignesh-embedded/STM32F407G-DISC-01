#include <stdint.h>
#include <stdio.h>

#define USART_IRQNO 39

int main(void)
{
	//Manually Pend the Pending Bit for USART3
	uint32_t *pISPR1 = (uint32_t*)0xE000E204;
	*pISPR1 |= (1<<(USART_IRQNO % 32));

	//Enable the USART3 IRQNO in NVIC
	uint32_t *pISER1 = (uint32_t*)0xE000E104;
	*pISER1 |= (1<<(USART_IRQNO % 32));
}

// USART3 IRQ Handler
void USART3_IRQHandler (void)
{
	printf("In USART3 ISR \n");
}
