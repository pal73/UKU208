extern char snmp_community[10];

//Информация об устройстве
extern signed short snmp_device_code;
extern signed 	   snmp_sernum;
extern signed short snmp_sernum_lsb;
extern signed short snmp_sernum_msb;
extern char 	   snmp_location[100];
extern signed short snmp_numofbat;
extern signed short snmp_numofbps;
extern signed short snmp_numofinv;
extern signed short snmp_numofavt;
extern signed short snmp_numofdt;
extern signed short snmp_numofsk;
extern signed short snmp_numofevents;

//Состояние первичной сети
extern signed short snmp_mains_power_voltage;
extern signed short snmp_mains_power_frequency;
extern signed short snmp_mains_power_status;
extern signed short snmp_mains_power_alarm;
extern signed short snmp_mains_power_voltage_phaseA;
extern signed short snmp_mains_power_voltage_phaseB;
extern signed short snmp_mains_power_voltage_phaseC;

//Состояние нагрузки
extern signed short snmp_load_voltage;
extern signed short snmp_load_current;

//Состояние БПСов
extern signed short snmp_bps_number[8];
extern signed short snmp_bps_voltage[8];
extern signed short snmp_bps_current[8];
extern signed short snmp_bps_temperature[8];
extern signed short snmp_bps_stat[8];

//Состояние инверторов
extern signed short snmp_inv_number[3];
extern signed short snmp_inv_voltage[3];
extern signed short snmp_inv_current[3];
extern signed short snmp_inv_temperature[3];
extern signed short snmp_inv_stat[3];

//Состояние Батарей
extern signed short snmp_bat_number[2];
extern signed short snmp_bat_voltage[2];
extern signed short snmp_bat_part_voltage[2];
extern signed short snmp_bat_current[2];
extern signed short snmp_bat_temperature[2];
extern signed short snmp_bat_capacity[2];
extern signed short snmp_bat_charge[2];
extern signed short snmp_bat_status[2];

//Мониторы состояния Батарей
extern signed short snmp_makb_number[4];
extern signed short snmp_makb_connect_status[4];
extern signed short snmp_makb_voltage0[4];
extern signed short snmp_makb_voltage1[4];
extern signed short snmp_makb_voltage2[4];
extern signed short snmp_makb_voltage3[4];
extern signed short snmp_makb_voltage4[4];
extern signed short snmp_makb_temper0[4];
extern signed short snmp_makb_temper1[4];
extern signed short snmp_makb_temper2[4];
extern signed short snmp_makb_temper3[4];
extern signed short snmp_makb_temper4[4];
extern signed short snmp_makb_temper0_stat[4];
extern signed short snmp_makb_temper1_stat[4];
extern signed short snmp_makb_temper2_stat[4];
extern signed short snmp_makb_temper3_stat[4];
extern signed short snmp_makb_temper4_stat[4];
extern signed short snmp_bat_voltage[2];
extern signed short snmp_bat_current[2];
extern signed short snmp_bat_temperature[2];
extern signed short snmp_bat_capacity[2];
extern signed short snmp_bat_charge[2];
extern signed short snmp_bat_status[2]; 

//Спецфункции
//Спецфункции
extern signed short snmp_spc_stat;
extern char snmp_spc_trap_message[100];
extern signed short snmp_spc_trap_value_0,snmp_spc_trap_value_1,snmp_spc_trap_value_2;

//Состояние силовых вводов
extern signed short snmp_energy_vvod_phase_a;
extern signed short snmp_energy_vvod_phase_b;
extern signed short snmp_energy_vvod_phase_c;
extern signed short snmp_energy_pes_phase_a;
extern signed short snmp_energy_pes_phase_b;
extern signed short snmp_energy_pes_phase_c;

//Показания счетчика
extern signed long snmp_energy_total_energy;
extern signed short snmp_energy_current_energy;

//Состояние сухих контактов
extern signed char snmp_sk_number[4];
extern signed char snmp_sk_aktiv[4];
extern signed char snmp_sk_alarm_aktiv[4];
extern signed char snmp_sk_alarm[4];
extern char snmp_sk_name[4][20];

//Состояние датчиков температур
extern signed char snmp_dt_number[3];
extern signed short snmp_dt_temper[3];
extern signed char snmp_dt_error[3];

//Состояние автоматов
extern signed char snmp_avt_number[12];
extern signed char snmp_avt_stat[12];

//Команды
extern signed short snmp_command;
extern signed short snmp_command_parametr;

//Журнал аварий
extern char snmp_log[64][128];

//Установочные параметры
extern signed short snmp_main_bps;
extern signed short snmp_zv_en;
extern signed short snmp_alarm_auto_disable;
extern signed short snmp_bat_test_time;
extern signed short snmp_u_max;
extern signed short snmp_u_min;
extern signed short snmp_u_0_grad;
extern signed short snmp_u_20_grad;
extern signed short snmp_u_sign;
extern signed short snmp_u_min_power;
extern signed short snmp_u_withouth_bat;
extern signed short snmp_control_current;
extern signed short snmp_max_charge_current;
extern signed short snmp_max_current;
extern signed short snmp_min_current;
extern signed short snmp_uvz;
extern signed short snmp_max_current_koef;
extern signed short snmp_max_current_koef;
extern signed short snmp_up_charge_koef;
extern signed short snmp_powerup_psu_timeout;
extern signed short snmp_max_temperature;
extern signed short snmp_tsign_bat; 
extern signed short snmp_tmax_bat;
extern signed short snmp_tsign_bps;
extern signed short snmp_tmax_bps;
extern signed short snmp_bat_part_alarm;
extern signed short snmp_power_cnt_adress;

//Климат-контроль
extern signed short snmp_klimat_box_temper;
extern signed short snmp_klimat_settings_box_alarm;
extern signed short snmp_klimat_settings_vent_on;
extern signed short snmp_klimat_settings_vent_off;
extern signed short snmp_klimat_settings_warm_on;
extern signed short snmp_klimat_settings_warm_off;
extern signed short snmp_klimat_settings_load_on;
extern signed short snmp_klimat_settings_load_off;
extern signed short snmp_klimat_settings_batt_on;
extern signed short snmp_klimat_settings_batt_off;

//Внешние датчики температуры
extern signed short snmp_dt_ext;
extern signed short snmp_dt_msan;
extern signed short snmp_dt_epu;

//Литиевые батареи
extern short snmp_lakb_number[7];				//Номер ЛАКБ
extern short snmp_lakb_voltage[7];				//Напряжение ЛАКБ
extern short snmp_lakb_max_cell_voltage[7];		//Максимальное напряжение ячейки ЛАКБ
extern short snmp_lakb_min_cell_voltage[7];		//Минимальное напряжение ячейки ЛАКБ
extern short snmp_lakb_max_cell_temperature[7];	//Максимальная температура ячейки ЛАКБ
extern short snmp_lakb_min_cell_temperature[7];	//Минимальная температура ячейки ЛАКБ
extern short snmp_lakb_ch_curr[7];				//Ток заряда ЛАКБ
extern short snmp_lakb_dsch_curr[7];			//Ток разряда ЛАКБ
extern short snmp_lakb_rat_cap[7];				//Номинальная емкость ЛАКБ
extern short snmp_lakb_soh[7];				//Остаточная емкость ЛАКБ
extern short snmp_lakb_soc[7];				//Заряд ЛАКБ
extern short snmp_lakb_cclv[7];  				//Максимальный ток заряда ЛАКБ
extern short snmp_lakb_rbt[7];				//Оцениваемое время работы ЛАКБ
extern short snmp_lakb_flags1[7];				//Первый флаг состояния ЛАКБ
extern short snmp_lakb_flags2[7];				//Второй флаг состояния ЛАКБ
extern char snmp_lakb_damp1[3][150];				//Первая строка передаваемого дампа
extern char snmp_lakb_damp2[100];				//Первая строка передаваемого дампа
extern signed char	snmp_lakb_cell_temperature_1[3];		//Температура 1-й ячейки ЛАКБ(ZTT)
extern signed char	snmp_lakb_cell_temperature_2[3];		//Температура 2-й ячейки ЛАКБ(ZTT)
extern signed char	snmp_lakb_cell_temperature_3[3];		//Температура 3-й ячейки ЛАКБ(ZTT)
extern signed char	snmp_lakb_cell_temperature_4[3];		//Температура 4-й ячейки ЛАКБ(ZTT)
extern signed char	snmp_lakb_cell_temperature_ambient[3];	//Температура окружающая ЛАКБ(ZTT)
extern signed char	snmp_lakb_cell_temperature_power[3];	//Температура силовой части ЛАКБ(ZTT)


  
//-----------------------------------------------
void snmp_data (void);
void snmp_sernum_write (int mode); 
void snmp_location_write (int mode);
void snmp_command_execute (int mode);
void event2snmp(char num);
void snmp_main_bps_write (int mode);
void snmp_zv_on_write (int mode);
void snmp_alarm_auto_disable_write (int mode);
void snmp_bat_test_time_write (int mode);
void snmp_u_max_write (int mode);
void snmp_u_min_write (int mode);
void snmp_u_0_grad_write (int mode);
void snmp_u_20_grad_write (int mode);
void snmp_u_sign_write (int mode);
void snmp_u_min_power_write (int mode);
void snmp_u_withouth_bat_write (int mode);
void snmp_control_current_write (int mode);
void snmp_max_charge_current_write (int mode);
void snmp_max_current_write (int mode);
void snmp_min_current_write (int mode);
void snmp_up_charge_koef_write (int mode);
void snmp_powerup_psu_timeout_write (int mode);
void snmp_max_temperature_write (int mode);
void event2snmp(char num);
void snmp_trap_send(char* str, signed short in0, signed short in1, signed short in2);
void snmp_alarm_aktiv_write1(void);
void snmp_alarm_aktiv_write2(void);
void snmp_alarm_aktiv_write3(void);
void snmp_alarm_aktiv_write4(void);
void snmp_klimat_settings_box_alarm_write(int mode);
void snmp_klimat_settings_vent_on_write(int mode);
void snmp_klimat_settings_vent_off_write(int mode);
void snmp_klimat_settings_warm_on_write(int mode);
void snmp_klimat_settings_warm_off_write(int mode);
void snmp_klimat_settings_load_on_write(int mode);
void snmp_klimat_settings_load_off_write(int mode);
void snmp_klimat_settings_batt_on_write(int mode);
void snmp_klimat_settings_batt_off_write(int mode);
void snmp_tsign_bat_write(int mode);
void snmp_tmax_bat_write(int mode);
void snmp_tsign_bps_write(int mode);
void snmp_tmax_bps_write(int mode);
void snmp_bat_part_alarm_write(int mode);
void snmp_power_cnt_adress_write(int mode);
void snmp_uvz_write(int mode);





 
