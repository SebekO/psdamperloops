#include <iostream>

#include <rf-ps_damper-lib/rf_ps_damper_driver.hpp>


int main() 
{
  rf_ps_damper_driver* pdrv = rf_ps_damper_driver::instance("rf_ps_damper", "top_regs", 0, "/user/sowarzan/drivers/rf-ps_damper/rf_ps_damper/");

  pdrv->eda_adc.adc0cr.idelay_rst.set(1);


  std::cout << "Hello World";
  return 0;
}