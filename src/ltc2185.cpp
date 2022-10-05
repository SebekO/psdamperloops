#include "ltc2185.h"
#include <rf-ps_damper-lib/rf_ps_damper_driver.hpp>
#include <iostream>
#include <unistd.h>

// ltc2185 constructor
ltc2185::ltc2185(rf_ps_damper_driver* pdrv){
  if(pdrv == NULL)
    throw std::runtime_error("ERROR: rf_ps_damper_driver cannot be NULL!");
  this->pdrv = pdrv;
  adc_sel    = 0;
  rst        = 0;
  set_adc();
}

// ltc2185 user menu function
void ltc2185::run() {
  std::cout << "what to do[d=set dealy value, r=reset dealy value, s=change adc, g=reset ADC's, e=exit]: ";
  std::cin >> to_do;

  switch(to_do) {
    case 's'  :
      set_adc();
      break;
    case 'r'  :
      rst_delay();
      break;
    case 'd'  :
      set_delay();
      break;
    case 'g'  :
      rst_adc();
      break;
    case 'e'  :
      std::cout << "You set: "                       << std::endl;
      std::cout << "ADC0 delay = " << delay_t[0]     << std::endl;
      std::cout << "ADC1 delay = " << delay_t[1]     << std::endl;
      std::cout << "ADC2 delay = " << delay_t[2]     << std::endl;
      std::cout << "ADC3 delay = " << delay_t[3]     << std::endl;
      std::cout << "Press 'e' one more time to exit" << std::endl;
      break;
    default :
      std::cout << "Error, you can olny choose [d, r, s, g, e]" << std::endl;
      run();
    }
}

// ltc2185 adc selector function
void ltc2185::set_adc() {
  std::cout << "select adc[0-3]: ";
  std::cin >> adc_sel;

  while(std::cin.fail() || (adc_sel < 0 || adc_sel > 3)) {
    std::cout << "Error, please put int value in range [0-3]" << std::endl;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> adc_sel;
  }

  std::cout << "you selected: adc" << adc_sel << std::endl;
  rst_delay();
}

// ltc2185 delay setter function
void ltc2185::set_delay() {
  std::cout << "put delay value for adc" << adc_sel <<" [0-31]: ";
  std::cin >> delay_t[adc_sel];

  while(std::cin.fail() || (delay_t[adc_sel] < 0 || delay_t[adc_sel] > 31)) {
    std::cout << "Error, please put int value in range [0-31]" << std::endl;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> delay_t[adc_sel];
  }

  for (int i = 0; i < delay_t[adc_sel] ; i++){
    switch(adc_sel) {
      case 0  :
        pdrv->eda_adc.adc0cr.idelay_inc.set(1);
        break;
      case 1  :
        pdrv->eda_adc.adc1cr.idelay_inc.set(1);
        break;
      case 2  :
        pdrv->eda_adc.adc2cr.idelay_inc.set(1);
        break;
      case 3  :
        pdrv->eda_adc.adc3cr.idelay_inc.set(1);
        break;
      default :
        std::cout << "Error, wrong adc selected" << std::endl;
        run();
        break;
    }
    usleep(microsecond);
    std::cout << "now adc" << adc_sel << " delay is: " << (i+1) << std::endl;
  }

  run();
}

// ltc2185 adc reset function
void ltc2185::rst_adc() {
  std::cout << "reset all adc's [1/0]?: ";
  std::cin >> rst;

  while(std::cin.fail() || (rst < 0 || rst > 1)) {
    std::cout << "Error, please put int value[0/1]" << std::endl;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> rst;
  }

  if(rst){
    pdrv->eda_adc.adc_gcr.sw_reset.set(1);
    usleep(microsecond);
    pdrv->eda_adc.adc_gcr.sw_reset.set(0);
    std::cout << "reset all adc's: DONE" << std::endl;;
  } else {
    std::cout << "nothing done" << std::endl;;
  }

  run();
}

// ltc2185 adc delay reset function
void ltc2185::rst_delay() {
  std::cout << "reset dealy value for adc" << adc_sel << " [1/0]?: ";
  std::cin >> rst_d;
  while(std::cin.fail() || (rst_d < 0 || rst_d > 1)) {
    std::cout << "Error, please put int value[0/1]" << std::endl;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> rst_d;
  }
  if(rst_d){
    switch(adc_sel) {
      case 0  :
        pdrv->eda_adc.adc0cr.idelay_rst.set(1);
        break;
      case 1  :
        pdrv->eda_adc.adc1cr.idelay_rst.set(1);
        break;
      case 2  :
        pdrv->eda_adc.adc2cr.idelay_rst.set(1);
        break;
      case 3  :
        pdrv->eda_adc.adc3cr.idelay_rst.set(1);
        break;
      default :
        std::cout << "Error, wrong adc selected" << std::endl;
        run();
        break;
    }
    usleep(microsecond);
    std::cout << "reset adc" << adc_sel << " dealy value: DONE"  << std::endl;;
  } else {
    std::cout << "nothing done" << std::endl;;
  }
  run();
}