#ifndef LTC2185_H
#define LTC2185_H
#include <rf-ps_damper-lib/rf_ps_damper_driver.hpp>

class ltc2185{
  private:
  rf_ps_damper_driver* pdrv;

  int adc_sel;
  int delay_t [4] = {0};
  int rst_d;
  int rst;
  char to_do;
  unsigned int microsecond = 1000000;

  void set_delay();
  void set_adc();
  void rst_delay();
  void rst_adc();

  public:
    explicit ltc2185(rf_ps_damper_driver* pdrv);
    explicit ltc2185(const std::string& edge_drv_name,
                    const std::string& instance_name,
                    const int lun,
                    const std::string& expert_edge_drv_path);

    void run();
};

#endif