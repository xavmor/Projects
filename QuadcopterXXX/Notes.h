/*

Function: int mpu_init(struct int_param_s *int_param) does the following
     *  Gyro FSR: +/- 2000DPS\n
     *  Accel FSR +/- 2G\n
     *  DLPF: 42Hz\n
     *  FIFO rate: 50Hz\n
     *  Clock source: Gyro PLL\n
     *  FIFO: Disabled.\n
     *  Data ready interrupt: Disabled, active low, unlatched.
     *  @param[in]  int_param   Platform-specific parameters to interrupt API.



Struct: reg =
    .who_am_i       = 0x75,
    .rate_div       = 0x19,
    .lpf            = 0x1A,
    .prod_id        = 0x0C,
    .user_ctrl      = 0x6A,
    .fifo_en        = 0x23,
    .gyro_cfg       = 0x1B,
    .accel_cfg      = 0x1C,
    .accel_cfg2     = 0x1D,
    .lp_accel_odr   = 0x1E,
    .motion_thr     = 0x1F,
    .motion_dur     = 0x20,
    .fifo_count_h   = 0x72,
    .fifo_r_w       = 0x74,
    .raw_gyro       = 0x43,
    .raw_accel      = 0x3B,
    .temp           = 0x41,
    .int_enable     = 0x38,
    .dmp_int_status = 0x39,
    .int_status     = 0x3A,
    .accel_intel    = 0x69,
    .pwr_mgmt_1     = 0x6B,
    .pwr_mgmt_2     = 0x6C,
    .int_pin_cfg    = 0x37,
    .mem_r_w        = 0x6F,
    .accel_offs     = 0x77,
    .i2c_mst        = 0x24,
    .bank_sel       = 0x6D,
    .mem_start_addr = 0x6E,
    .prgm_start_h   = 0x70






 */
