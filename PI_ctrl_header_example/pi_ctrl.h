/*
Author: Omer Ikram ul haq
Date: 2014-05-28
Location: Multan, Pakistan
Ver: 0.2 beta
*/

/* --------------- Comment
    I dont like Derivative part of a controller,
    They are noisy and require filtering and are a burden on the processor

*/

#ifndef pi_ctrl.h
  #define pi_ctrl.h
  
  // Porpotional and Integral controller class
  class pi_controller{
   
    private:
      float output,out_ctrl;
      
  /*----- Integration function using foward euler integration method ----- */
      float integrate(float input, float old_output){
        output = input*dt + old_output;
        return output;
      }
           
    public:
      float kp,tn,dt,IC,lim_max,lim_min;
 
      
/*----- The control output function ----- */
      
      
      float control(float error){
        /* ----- Setting up the initial contion ----- */
        if (IC != 0) {
          out_ctrl = IC;
          IC = 0;
        }
        
        /* ----- Calculating the output ----- */
        out_ctrl = kp*error+integrate(kp*dt/tn*error,out_ctrl);
        
        
        /* ----- Anti-Roll and Output limits ----- */ 
        if (out_ctrl <= lim_min && error <= 0){
          out_ctrl = lim_min;
          
        }else if (out_ctrl >= lim_max && error >= 0){
          out_ctrl = lim_max;
        }
        
        /* ----- Returning the controller output ----- */
        return (out_ctrl);
      }
  
  };
    
#endif
