#include "head.h"

int main(void)
{
	app_init();

	while(1)
	{
		display_adc_and_voltage(adc_value);
	}
}