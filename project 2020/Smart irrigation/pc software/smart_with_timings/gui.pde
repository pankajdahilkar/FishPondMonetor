/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void button1_click1(GButton source, GEvent event) { //_CODE_:button1:440738:
  println("button1 - GButton >> GEvent." + event + " @ " + millis());
      Setting_window.setVisible(!Setting_window.isVisible());

} //_CODE_:button1:440738:

public void Manual_OP_click(GButton source, GEvent event) { //_CODE_:Manual_OP:331912:
  println("Manual_OP - GButton >> GEvent." + event + " @ " + millis());
         Manual_window.setVisible(!Manual_window.isVisible());
} //_CODE_:Manual_OP:331912:

synchronized public void win_draw2(PApplet appc, GWinData data) { //_CODE_:Setting_window:236456:
  appc.background(230);
} //_CODE_:Setting_window:236456:

public void Save_button_click1(GButton source, GEvent event) { //_CODE_:Save_button:453932:
  println("Save_button - GButton >> GEvent." + event + " @ " + millis());
  
    V1_On_time_hr=int(Hour1_ON.getText());
   V1_On_time_min=int(min1_ON.getText());
   V1_Off_time_hr=int(hour_off_1.getText());
   V1_Off_time_min=int(MIn1_off.getText());

   V2_On_time_hr=int(Hour2_ON.getText());
   V2_On_time_min=int(Min2_ON.getText());
   V2_Off_time_hr=int(Hour2_OFF.getText());
   V2_Off_time_min=int(Min2_OFF.getText());
  
   V3_On_time_hr=int(Hour3_ON.getText());
   V3_On_time_min=int(Min3_ON.getText());
   V3_Off_time_hr=int(Hour3_OFF.getText());
   V3_Off_time_min=int(Min3_OFF.getText());
   
   println("V1_On_time_hr = "+ V1_On_time_hr);
   println("V1_On_time_min = "+ V1_On_time_min);
   println("V1_Off_time_hr = "+ V1_Off_time_hr);
   println("V1_Off_time_min = "+ V1_Off_time_min);
  
    println("V2_On_time_hr = "+ V2_On_time_hr);
   println("V2_On_time_min = "+ V2_On_time_min);
   println("V2_Off_time_hr = "+ V2_Off_time_hr);
   println("V2_Off_time_min = "+ V2_Off_time_min);
   
    println("V3_On_time_hr = "+ V3_On_time_hr);
   println("V3_On_time_min = "+ V3_On_time_min);
   println("V3_Off_time_hr = "+ V3_Off_time_hr);
   println("V3_Off_time_min = "+ V3_Off_time_min);
   

} //_CODE_:Save_button:453932:

public void close_buttonClick(GButton source, GEvent event) { //_CODE_:close_Button:333072:
  println("close_Button - GButton >> GEvent." + event + " @ " + millis());
   Setting_window.setVisible(!Setting_window.isVisible());
} //_CODE_:close_Button:333072:

public void hour1_On_change1(GTextField source, GEvent event) { //_CODE_:Hour1_ON:339852:
  println("Hour1 - GTextField >> GEvent." + event + " @ " + millis());
  
} //_CODE_:Hour1_ON:339852:

public void min1_ON_change1(GTextField source, GEvent event) { //_CODE_:min1_ON:354137:
  println("min1 - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:min1_ON:354137:

public void Hour1_OFF_change2(GTextField source, GEvent event) { //_CODE_:hour_off_1:684476:
  println("hour_off_1 - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:hour_off_1:684476:

public void Min1_OFF_change3(GTextField source, GEvent event) { //_CODE_:MIn1_off:876974:
  println("MIn1_off - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:MIn1_off:876974:

public void Hour2_ON_change(GTextField source, GEvent event) { //_CODE_:Hour2_ON:406011:
  println("Hour2_ON - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Hour2_ON:406011:

public void Min2_ON_change(GTextField source, GEvent event) { //_CODE_:Min2_ON:574722:
  println("Min2_ON - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Min2_ON:574722:

public void Hour2_OFF_change(GTextField source, GEvent event) { //_CODE_:Hour2_OFF:917643:
  println("Hour2_OFF - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Hour2_OFF:917643:

public void Min2_OFF_change2(GTextField source, GEvent event) { //_CODE_:Min2_OFF:678250:
  println("Min2_OFF - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Min2_OFF:678250:

public void Hour3_ON_change(GTextField source, GEvent event) { //_CODE_:Hour3_ON:298193:
  println("Hour3_ON - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Hour3_ON:298193:

public void Min3_ON_change(GTextField source, GEvent event) { //_CODE_:Min3_ON:917260:
  println("Min3_ON - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Min3_ON:917260:

public void Hour3_OFF_change(GTextField source, GEvent event) { //_CODE_:Hour3_OFF:375286:
  println("Hour3_OFF - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Hour3_OFF:375286:

public void Min3_OFF_change1(GTextField source, GEvent event) { //_CODE_:Min3_OFF:359918:
  println("Min3_OFF - GTextField >> GEvent." + event + " @ " + millis());
} //_CODE_:Min3_OFF:359918:

synchronized public void win_draw1(PApplet appc, GWinData data) { //_CODE_:Manual_window:944522:
  appc.background(230);
} //_CODE_:Manual_window:944522:

public void V1_manual_button_click1(GImageToggleButton source, GEvent event) { //_CODE_:V1_manual_button:575506:
  println("imgTogButton1 - GImageToggleButton >> GEvent." + event + " @ " + millis());
  if(V1_flag == 1){ V1_flag=0;
 try{
      myPort.write('2');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }  
}
  else{ V1_flag =1;
   try{
      myPort.write('1');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }
  }
  
  
  
  
} //_CODE_:V1_manual_button:575506:

public void V2_manual_button_click1(GImageToggleButton source, GEvent event) { //_CODE_:V2_manual_button:522809:
  println("imgTogButton2 - GImageToggleButton >> GEvent." + event + " @ " + millis());
 if(V2_flag == 1) {V2_flag=0;
  try{
      myPort.write('4');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }
 }
  else {V2_flag =1;
 try{
      myPort.write('3');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }  
}

} //_CODE_:V2_manual_button:522809:

public void V3_manual_button_click1(GImageToggleButton source, GEvent event) { //_CODE_:V3_manual_button:965847:
  println("imgTogButton3 - GImageToggleButton >> GEvent." + event + " @ " + millis());
 if(V3_flag == 1){ V3_flag=0;
  try{
      myPort.write('6');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }
 
 }
  else{ V3_flag =1;
   try{
      myPort.write('5');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }
  }
} //_CODE_:V3_manual_button:965847:

public void pump_manual_click1(GImageToggleButton source, GEvent event) { //_CODE_:pump_manual:611919:
  println("imgTogButton4 - GImageToggleButton >> GEvent." + event + " @ " + millis());
  if(Pump_flag == 1) {Pump_flag=0;
 try{
      myPort.write('8');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }  
}
  else {Pump_flag =1;
 try{
      myPort.write('7');
      myPort.write('\r');
      myPort.write('\n');
      }catch(Exception e) {
    println(e.toString());
  }  
}
} //_CODE_:pump_manual:611919:

public void Manual_close_click(GButton source, GEvent event) { //_CODE_:Manual_close:281094:
  println("Manual_close - GButton >> GEvent." + event + " @ " + millis());
     Manual_window.setVisible(!Manual_window.isVisible());

} //_CODE_:Manual_close:281094:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  button1 = new GButton(this, 695, 431, 80, 33);
  button1.setText("SETTING");
  button1.addEventHandler(this, "button1_click1");
  Manual_OP = new GButton(this, 794, 431, 80, 33);
  Manual_OP.setText("Manual");
  Manual_OP.addEventHandler(this, "Manual_OP_click");
  Setting_window = GWindow.getWindow(this, "Valve Settings", 0, 0, 480, 320, JAVA2D);
  Setting_window.noLoop();
  Setting_window.setActionOnClose(G4P.CLOSE_WINDOW);
  Setting_window.addDrawHandler(this, "win_draw2");
  label2 = new GLabel(Setting_window, 181, 12, 80, 20);
  label2.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label2.setText("ON TIME");
  label2.setOpaque(false);
  label3 = new GLabel(Setting_window, 330, 12, 80, 20);
  label3.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label3.setText("OFF TIME");
  label3.setOpaque(false);
  label4 = new GLabel(Setting_window, 13, 83, 80, 20);
  label4.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label4.setText("VALVE 1");
  label4.setOpaque(false);
  label5 = new GLabel(Setting_window, 13, 143, 80, 20);
  label5.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label5.setText("VALVE 2");
  label5.setOpaque(false);
  label6 = new GLabel(Setting_window, 13, 203, 80, 20);
  label6.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label6.setText("VALVE3");
  label6.setOpaque(false);
  Save_button = new GButton(Setting_window, 131, 258, 80, 30);
  Save_button.setText("SAVE");
  Save_button.addEventHandler(this, "Save_button_click1");
  close_Button = new GButton(Setting_window, 253, 258, 80, 30);
  close_Button.setText("CLOSE");
  close_Button.addEventHandler(this, "close_buttonClick");
  Hour1_ON = new GTextField(Setting_window, 145, 83, 50, 20, G4P.SCROLLBARS_NONE);
  Hour1_ON.setText("12");
  Hour1_ON.setOpaque(true);
  Hour1_ON.addEventHandler(this, "hour1_On_change1");
  label7 = new GLabel(Setting_window, 165, 52, 80, 20);
  label7.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label7.setText("Hour : Min ");
  label7.setOpaque(false);
  label8 = new GLabel(Setting_window, 329, 52, 80, 20);
  label8.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label8.setText("Hour : Min");
  label8.setOpaque(false);
  label9 = new GLabel(Setting_window, 200, 83, 10, 20);
  label9.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label9.setText(":");
  label9.setOpaque(false);
  min1_ON = new GTextField(Setting_window, 216, 83, 50, 20, G4P.SCROLLBARS_NONE);
  min1_ON.setText("12");
  min1_ON.setOpaque(true);
  min1_ON.addEventHandler(this, "min1_ON_change1");
  hour_off_1 = new GTextField(Setting_window, 307, 83, 50, 20, G4P.SCROLLBARS_NONE);
  hour_off_1.setText("12");
  hour_off_1.setPromptText("12");
  hour_off_1.setOpaque(true);
  hour_off_1.addEventHandler(this, "Hour1_OFF_change2");
  label10 = new GLabel(Setting_window, 362, 83, 10, 20);
  label10.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label10.setText(":");
  label10.setOpaque(false);
  MIn1_off = new GTextField(Setting_window, 378, 83, 50, 20, G4P.SCROLLBARS_NONE);
  MIn1_off.setText("00");
  MIn1_off.setOpaque(true);
  MIn1_off.addEventHandler(this, "Min1_OFF_change3");
  Hour2_ON = new GTextField(Setting_window, 145, 143, 50, 20, G4P.SCROLLBARS_NONE);
  Hour2_ON.setText("12");
  Hour2_ON.setPromptText("12");
  Hour2_ON.setOpaque(true);
  Hour2_ON.addEventHandler(this, "Hour2_ON_change");
  label1 = new GLabel(Setting_window, 200, 143, 10, 20);
  label1.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label1.setText(":");
  label1.setOpaque(false);
  Min2_ON = new GTextField(Setting_window, 216, 143, 50, 20, G4P.SCROLLBARS_NONE);
  Min2_ON.setText("00");
  Min2_ON.setPromptText("00");
  Min2_ON.setOpaque(true);
  Min2_ON.addEventHandler(this, "Min2_ON_change");
  Hour2_OFF = new GTextField(Setting_window, 307, 143, 50, 20, G4P.SCROLLBARS_NONE);
  Hour2_OFF.setText("12");
  Hour2_OFF.setOpaque(true);
  Hour2_OFF.addEventHandler(this, "Hour2_OFF_change");
  label11 = new GLabel(Setting_window, 362, 143, 10, 20);
  label11.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label11.setText(":");
  label11.setOpaque(false);
  Min2_OFF = new GTextField(Setting_window, 378, 143, 50, 20, G4P.SCROLLBARS_NONE);
  Min2_OFF.setText("00");
  Min2_OFF.setPromptText("00");
  Min2_OFF.setOpaque(true);
  Min2_OFF.addEventHandler(this, "Min2_OFF_change2");
  Hour3_ON = new GTextField(Setting_window, 145, 203, 50, 20, G4P.SCROLLBARS_NONE);
  Hour3_ON.setText("12");
  Hour3_ON.setPromptText("12");
  Hour3_ON.setOpaque(true);
  Hour3_ON.addEventHandler(this, "Hour3_ON_change");
  label12 = new GLabel(Setting_window, 200, 203, 10, 20);
  label12.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label12.setText(":");
  label12.setOpaque(false);
  Min3_ON = new GTextField(Setting_window, 217, 201, 50, 20, G4P.SCROLLBARS_NONE);
  Min3_ON.setText("00");
  Min3_ON.setPromptText("00");
  Min3_ON.setOpaque(true);
  Min3_ON.addEventHandler(this, "Min3_ON_change");
  Hour3_OFF = new GTextField(Setting_window, 307, 203, 50, 20, G4P.SCROLLBARS_NONE);
  Hour3_OFF.setText("12");
  Hour3_OFF.setPromptText("12");
  Hour3_OFF.setOpaque(true);
  Hour3_OFF.addEventHandler(this, "Hour3_OFF_change");
  label13 = new GLabel(Setting_window, 362, 203, 10, 20);
  label13.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label13.setText(":");
  label13.setOpaque(false);
  Min3_OFF = new GTextField(Setting_window, 378, 203, 50, 20, G4P.SCROLLBARS_NONE);
  Min3_OFF.setText("00");
  Min3_OFF.setOpaque(true);
  Min3_OFF.addEventHandler(this, "Min3_OFF_change1");
  Manual_window = GWindow.getWindow(this, "Manual operate", 0, 0, 320, 240, JAVA2D);
  Manual_window.noLoop();
  Manual_window.setActionOnClose(G4P.CLOSE_WINDOW);
  Manual_window.addDrawHandler(this, "win_draw1");
  label14 = new GLabel(Manual_window, 82, 15, 180, 20);
  label14.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label14.setText("MANUAL VALVE OPERATION");
  label14.setOpaque(false);
  V1_manual_button = new GImageToggleButton(Manual_window, 42, 56);
  V1_manual_button.addEventHandler(this, "V1_manual_button_click1");
  V2_manual_button = new GImageToggleButton(Manual_window, 112, 56);
  V2_manual_button.addEventHandler(this, "V2_manual_button_click1");
  V3_manual_button = new GImageToggleButton(Manual_window, 181, 56);
  V3_manual_button.addEventHandler(this, "V3_manual_button_click1");
  pump_manual = new GImageToggleButton(Manual_window, 250, 56);
  pump_manual.addEventHandler(this, "pump_manual_click1");
  V1_STATE = new GLabel(Manual_window, 27, 117, 60, 20);
  V1_STATE.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  V1_STATE.setText("V1");
  V1_STATE.setOpaque(false);
  label15 = new GLabel(Manual_window, 101, 117, 60, 20);
  label15.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label15.setText("V2");
  label15.setOpaque(false);
  label16 = new GLabel(Manual_window, 174, 118, 60, 20);
  label16.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label16.setText("V3");
  label16.setOpaque(false);
  label17 = new GLabel(Manual_window, 245, 118, 60, 20);
  label17.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label17.setText("PUMP");
  label17.setOpaque(false);
  Manual_close = new GButton(Manual_window, 116, 163, 80, 30);
  Manual_close.setText("CLOSE");
  Manual_close.setLocalColorScheme(GCScheme.RED_SCHEME);
  Manual_close.addEventHandler(this, "Manual_close_click");
  Setting_window.loop();
  Manual_window.loop();
}

// Variable declarations 
// autogenerated do not edit
GButton button1; 
GButton Manual_OP; 
GWindow Setting_window;
GLabel label2; 
GLabel label3; 
GLabel label4; 
GLabel label5; 
GLabel label6; 
GButton Save_button; 
GButton close_Button; 
GTextField Hour1_ON; 
GLabel label7; 
GLabel label8; 
GLabel label9; 
GTextField min1_ON; 
GTextField hour_off_1; 
GLabel label10; 
GTextField MIn1_off; 
GTextField Hour2_ON; 
GLabel label1; 
GTextField Min2_ON; 
GTextField Hour2_OFF; 
GLabel label11; 
GTextField Min2_OFF; 
GTextField Hour3_ON; 
GLabel label12; 
GTextField Min3_ON; 
GTextField Hour3_OFF; 
GLabel label13; 
GTextField Min3_OFF; 
GWindow Manual_window;
GLabel label14; 
GImageToggleButton V1_manual_button; 
GImageToggleButton V2_manual_button; 
GImageToggleButton V3_manual_button; 
GImageToggleButton pump_manual; 
GLabel V1_STATE; 
GLabel label15; 
GLabel label16; 
GLabel label17; 
GButton Manual_close; 
