void saveAllData() {
//  manager.writeInt(0, position_Y_Axis_MM);
//  manager.writeInt(1, position_Z_Axis_MM);
//  manager.writeInt(2, position_R_Axis_REV);
  manager.writeInt(3, origin_Y_Axis_MM_raw);  // This remains unchanged as it's a float
  manager.writeInt(4, origin_Z_Axis_MM_raw);  // This remains unchanged as it's a float
  manager.writeInt(5, velocity_Y_Axis_MMPerSec_raw);
  manager.writeInt(6, velocity_Z_Axis_MMPerSec_raw);
  manager.writeInt(7, velocity_R_Axis_MMPerSec_raw);
  manager.writeInt(8, acceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(9, acceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(10, acceleration_R_Axis_MMPerSecSq_raw);
  manager.writeInt(11, manualSpeed_Y_Axis_MMPerSec_raw);
  manager.writeInt(12, manualSpeed_Z_Axis_MMPerSec_raw);
  manager.writeInt(13, manualSpeed_R_Axis_MMPerSec_raw);
  manager.writeInt(14, manualAcceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(15, manualAcceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(16, manualAcceleration_R_Axis_MMPerSecSq_raw);
  manager.writeInt(17, homingSpeed_Y_Axis_MMPerSec_raw);
  manager.writeInt(18, homingSpeed_Z_Axis_MMPerSec_raw);
  manager.writeInt(19, homingAcceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(20, homingAcceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(21, numOfHoles_raw);
  manager.writeInt(22, yStep_raw);
  manager.writeInt(23, mGap_raw);
  manager.writeInt(24, zDepth_raw);
  manager.writeInt(25, safeHeight_raw);
  manager.writeInt(26, tolHeight_raw);
  manager.writeInt(27, diameterSelection);
  manager.writeInt(28, stepDown_raw);
  manager.writeInt(29, firstDis_raw);
  manager.writeInt(30, secDis_raw);
}

void loadAllData() {
//  position_Y_Axis_MM = manager.readInt(0);
//  position_Z_Axis_MM = manager.readInt(1);
//  position_R_Axis_REV = manager.readInt(2);
  origin_Y_Axis_MM_raw = manager.readInt(3);  // This remains unchanged as it's a float
  origin_Z_Axis_MM_raw = manager.readInt(4);  // This remains unchanged as it's a float
  velocity_Y_Axis_MMPerSec_raw = manager.readInt(5);
  velocity_Z_Axis_MMPerSec_raw = manager.readInt(6);
  velocity_R_Axis_MMPerSec_raw = manager.readInt(7);
  acceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(8);
  acceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(9);
  acceleration_R_Axis_MMPerSecSq_raw = manager.readInt(10);
  manualSpeed_Y_Axis_MMPerSec_raw = manager.readInt(11);
  manualSpeed_Z_Axis_MMPerSec_raw = manager.readInt(12);
  manualSpeed_R_Axis_MMPerSec_raw = manager.readInt(13);
  manualAcceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(14);
  manualAcceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(15);
  manualAcceleration_R_Axis_MMPerSecSq_raw = manager.readInt(16);
  homingSpeed_Y_Axis_MMPerSec_raw = manager.readInt(17);
  homingSpeed_Z_Axis_MMPerSec_raw = manager.readInt(18);
  homingAcceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(19);
  homingAcceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(20);
  numOfHoles_raw = manager.readInt(21);
  yStep_raw = manager.readInt(22);
  mGap_raw = manager.readInt(23);
  zDepth_raw = manager.readInt(24);
  safeHeight_raw = manager.readInt(25);
  tolHeight_raw = manager.readInt(26);
  diameterSelection = manager.readInt(27);
  stepDown_raw = manager.readInt(28);
  firstDis_raw = manager.readInt(29);
  secDis_raw = manager.readInt(30);
}



void saveAllParameters() {
  // manager.writeInt(0, position_Y_Axis_MM);
  // manager.writeInt(1, position_Z_Axis_MM);
  // manager.writeInt(2, position_R_Axis_REV);
  // manager.writeFloat(3, origin_Y_Axis_MM);  // This remains unchanged as it's a float
  // manager.writeFloat(4, origin_Z_Axis_MM);  // This remains unchanged as it's a float
  manager.writeInt(5, velocity_Y_Axis_MMPerSec_raw);
  manager.writeInt(6, velocity_Z_Axis_MMPerSec_raw);
  manager.writeInt(7, velocity_R_Axis_MMPerSec_raw);
  manager.writeInt(8, acceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(9, acceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(10, acceleration_R_Axis_MMPerSecSq_raw);
  manager.writeInt(11, manualSpeed_Y_Axis_MMPerSec_raw);
  manager.writeInt(12, manualSpeed_Z_Axis_MMPerSec_raw);
  manager.writeInt(13, manualSpeed_R_Axis_MMPerSec_raw);
  manager.writeInt(14, manualAcceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(15, manualAcceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(16, manualAcceleration_R_Axis_MMPerSecSq_raw);
  manager.writeInt(17, homingSpeed_Y_Axis_MMPerSec_raw);
  manager.writeInt(18, homingSpeed_Z_Axis_MMPerSec_raw);
  manager.writeInt(19, homingAcceleration_Y_Axis_MMPerSecSq_raw);
  manager.writeInt(20, homingAcceleration_Z_Axis_MMPerSecSq_raw);
  manager.writeInt(21, numOfHoles_raw);
  manager.writeInt(22, yStep_raw);
  manager.writeInt(23, mGap_raw);
  manager.writeInt(24, zDepth_raw);
  manager.writeInt(25, safeHeight_raw);
  manager.writeInt(26, tolHeight_raw);
  manager.writeInt(27, diameterSelection);
  manager.writeInt(28, stepDown_raw);
  manager.writeInt(29, firstDis_raw);
  manager.writeInt(30, secDis_raw);
}

void loadAllParameters() {
  // position_Y_Axis_MM = manager.readInt(0);
  // position_Z_Axis_MM = manager.readInt(1);
  // position_R_Axis_REV = manager.readInt(2);
  // origin_Y_Axis_MM = manager.readFloat(3);  // This remains unchanged as it's a float
  // origin_Z_Axis_MM = manager.readFloat(4);  // This remains unchanged as it's a float
  velocity_Y_Axis_MMPerSec_raw = manager.readInt(5);
  velocity_Z_Axis_MMPerSec_raw = manager.readInt(6);
  velocity_R_Axis_MMPerSec_raw = manager.readInt(7);
  acceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(8);
  acceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(9);
  acceleration_R_Axis_MMPerSecSq_raw = manager.readInt(10);
  manualSpeed_Y_Axis_MMPerSec_raw = manager.readInt(11);
  manualSpeed_Z_Axis_MMPerSec_raw = manager.readInt(12);
  manualSpeed_R_Axis_MMPerSec_raw = manager.readInt(13);
  manualAcceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(14);
  manualAcceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(15);
  manualAcceleration_R_Axis_MMPerSecSq_raw = manager.readInt(16);
  homingSpeed_Y_Axis_MMPerSec_raw = manager.readInt(17);
  homingSpeed_Z_Axis_MMPerSec_raw = manager.readInt(18);
  homingAcceleration_Y_Axis_MMPerSecSq_raw = manager.readInt(19);
  homingAcceleration_Z_Axis_MMPerSecSq_raw = manager.readInt(20);
  numOfHoles_raw = manager.readInt(21);
  yStep_raw = manager.readInt(22);
  mGap_raw = manager.readInt(23);
  zDepth_raw = manager.readInt(24);
  safeHeight_raw = manager.readInt(25);
  tolHeight_raw = manager.readInt(26);
  diameterSelection = manager.readInt(27);
  stepDown_raw = manager.readInt(28);
  firstDis_raw = manager.readInt(29);
  secDis_raw = manager.readInt(30);
}


void saveOrigin() {
  manager.writeInt(3, origin_Y_Axis_MM_raw);
  manager.writeInt(4, origin_Z_Axis_MM_raw);
}

void saveCurrentPositon() {
  manager.writeInt(0, position_Y_Axis_MM);
  manager.writeInt(1, position_Z_Axis_MM);
}
