#include "lib/ang_loc.h"
#include "lib/led.h"
#include "lib/svm.h"
#include "lib/dcm.h"
#include "lib/rot_enc.h"
#include "lib/ult_snc.h"
#include "lib/mag.h"
#include "sd/ver1.cpp"


void setup_sensors(){
    Serial.begin(9600);
    // set_ang_loc();
    set_led();
    set_svm();
    // set_dcm();
    setup_motor();
    set_rot_enc();
    set_ult_snc();
    setup_qmc5883();
    setup_sd();
}