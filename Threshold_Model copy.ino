//Threshold Model with Greater than or equal to condition


#include <math.h>
#include <TN.h>






// Define range of in/out variables.  This range is mapped on to the full input/output range, 
// and anything outside of this is clipped.
boolean SWstateOld, SWstateNew;
const float range_max = 4;
const float range_min = 0;
boolean stubborn;

// Required variables
int ins[2] = {0,0};
float fsum= 0.0;
int state;


TN Tn = TN(-1.0,1.0);




void setup () {
 
  //Set initial state via dip switch, option A is 0, option B is 1
  startvalue();
}

void loop() {
  //Read the inputs, set so 0=not connected, 1=Option A, 4=Option B
 
 ins[0]=0;
 ins[1]=0;
 if (Tn.sw()==false){
 
   for (int input=1; input<4; input++ ){
   
     if (Tn.isConnected(input)==true){
       
       ins[0]=ins[0]++;
       
       if (Tn.digitalRead(input)==true){
 
              ins[1] = ins[1]++ ;
              
       }
       
     }
     
   }
            
        
        
  
  
  fsum=(float)ins[1]/(float)ins[0];
  
  
  if (stubborn==false){
  
    if (state==1) {
    
      if (fsum<=0.5) {
    
          state=0;
        
      }
    
    }
  
     else{
    
      if (fsum>=0.5) {
    
          state=1;
        
      }
    
    }
    
  }
  else{
    if (state==1) {
    
      if (fsum<0.5) {
    
          state=0;
        
      }
    
    }
  
     else {
    
      if (fsum>0.5) {
    
          state=1;
        
      }
    
    }
  }
  updateOutputs();
 }
 else{ 
   
      switchHold();
       
     
     
 }
   
     
  
  for (int reps=1; reps<1000; reps++ ){
   
       if (Tn.masterSw()==true){
    
          startvalue();
          updateOutputs();
    
       }
       
       if (Tn.sw()==true){
        
          switchHold();
         
       }
       
       delay(1);
       
                    
  } 
}
  
  

void startvalue(){
  
  if (Tn.pot()<0.5){
    
    stubborn=true;
    
  }
  else{
    
    stubborn=false;
  }
  
  if(Tn.pot()<0.25){
    
    state=0;
    
  }
  
 else if(Tn.pot()<0.5){
   
   state=1;
   
 }
 
 else if(Tn.pot()<0.75){
   
   state=0;
   
 }
 
 else{
   
   state=1;
   
 }
  
}


void updateOutputs(){
  
  
  if (state==1){
    Tn.colour(0,255,0);
    Tn.digitalWrite(1,true);
    Tn.digitalWrite(2,true);
    Tn.digitalWrite(3,true);
  }
  
  
 else {
    Tn.colour(0,0,255);
    Tn.digitalWrite(1,false);
    Tn.digitalWrite(2,false);
    Tn.digitalWrite(3,false);
    
  }
  
  
  
}
  
void switchHold(){
  
       state=1-state;
       updateOutputs();
    int test=0;
   while(test==0){
     delay(2);
     
     if(Tn.sw()==false){
       
       test=1;
     }
   }
   
}
