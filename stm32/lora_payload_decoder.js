function decodeUplink(input) {
  if(input.bytes.length <= 4) {
   
    RX = new Array(4);
    for (let iter_i6 = 0; iter_i6 < 4; iter_i6++) {
      
      RX[iter_i6] = input.bytes[iter_i6];
    }
      RX_ASC = String.fromCharCode.apply(null, RX);
      RX_ASC = RX_ASC.replace("\u0000", "");
    
    let power = RX_ASC[0] == "1" ? "measure_receiver_one_rx" : "measure_receiver_two_rx";  
    let object = {};
    object[power] = RX_ASC.substring(1);
      return {
        data: object
      }
  } else {  
     
gyro_rawY = new Array(8);
gyro_rawZ = new Array(8);
acc_rawY = new Array(8);
acc_rawZ = new Array(8);
acc_total_vector = new Array(8);
 
for (let iter_i1 = 0; iter_i1 < 9; iter_i1++) {
  
  gyro_rawY[iter_i1] = input.bytes[iter_i1];
}
for (let iter_i2 = 0; iter_i2 < 9; iter_i2++) {
  
  gyro_rawZ[iter_i2] = input.bytes[iter_i2+9];
}
for (let iter_i3 = 0; iter_i3 < 9; iter_i3++) {
  
  acc_rawY[iter_i3] = input.bytes[iter_i3+19];
}
for (let iter_i4 = 0; iter_i4 < 9; iter_i4++) {
  
  acc_rawZ[iter_i4] = input.bytes[iter_i4+29];
}
for (let iter_i5 = 0; iter_i5 < 9; iter_i5++) {
  
  acc_total_vector[iter_i5] = input.bytes[iter_i5+39];
}


 
gyro_YASC = String.fromCharCode.apply(null, gyro_rawY);
gyro_ZASC = String.fromCharCode.apply(null, gyro_rawZ);
acc_YASC = String.fromCharCode.apply(null, acc_rawY);
acc_ZASC = String.fromCharCode.apply(null, acc_rawZ);
acc_totalASC = String.fromCharCode.apply(null, acc_total_vector);
//RX1_ASC = String.fromCharCode.apply(null, RX1);
//RX2_ASC = String.fromCharCode.apply(null, RX2);
gyro_YASC = gyro_YASC.replace("\u0000", "");
gyro_ZASC = gyro_ZASC.replace("\u0000", "");
acc_YASC = acc_YASC.replace("\u0000", "");
acc_ZASC = acc_ZASC.replace("\u0000", "");
acc_totalASC = acc_totalASC.replace("\u0000", "");
//RX1_ASC = RX1_ASC.replace("\u0000", "");
//RX2_ASC = RX2_ASC.replace("\u0000", "");
//acc_totalASC = String.fromCharCode.apply(null, acc_total_vector);
//gyro_YASC = String.fromCharCode.apply(null, gyro_rawY);
//gyro_ZASC = String.fromCharCode.apply(null, gyro_rawZ);
 

 
return {
  data: {
    measure_angle_pitch: gyro_YASC,
    measure_angle_yaw: gyro_ZASC,
    measure_acceleration_pitch: acc_YASC, 
    measure_acceleration_yaw: acc_ZASC,
    measure_acceleration_total_vector: acc_totalASC,
//    odb_1: RX1_ASC,
//    odb_2: RX2_ASC
        },
warnings: [],
errors: []
};
}
}
