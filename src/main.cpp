#include <rf-ps_damper-lib/rf_ps_damper_driver.hpp>
#include "ltc2185.h"

int main(){
  rf_ps_damper_driver* pdrv = rf_ps_damper_driver::instance("rf_ps_damper", "psDamperLoops", 0, "/user/sowarzan/drivers/rf-ps_damper/rf_ps_damper/");
  ltc2185 adc(pdrv);
  adc.run();
  return 0;
}