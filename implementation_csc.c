#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "implementation_csc.h"

//gcc -Wall -L../CUnit-2.1-3/CUnit/Sources/.Libs -I../CUnit-2.1-3/CUnit/Headers -o csc_test csc_test.c implementation_csc.o -lcunit

tm current_time_tm(){
    time_t timestamp = time( NULL );
    return *localtime( & timestamp );
}

tm addMinuts(tm time ,int min){
    if (time.tm_min+min>=60){
        time.tm_hour++;
    }
    time.tm_min=(time.tm_min+min )%60;
    return time;
}

output_csc  Chassis_Safety_Controller(type_urgence obstacle_detected, message message_received,
                                                float vitesse_vehicule,position current_position){
    
    char numSerie[] ="abcd";
    while (1){
        type_urgence obstacle =obstacle_detected;
        float ordre_freinage;
        message message_sent;

       
        if (obstacle.object_dim.hauteur>8 && obstacle.object_dim.largeur>5 && obstacle.object_dim.profondeur>5 && obstacle.distance<=100){
                ordre_freinage = vitesse_vehicule/(obstacle.distance*2);

                message_sent.car_position = current_position;
                message_sent.vitesse = vitesse_vehicule;
                message_sent.actual_time = current_time_tm() ; 
                message_sent.detected_object=obstacle;
                message_sent.intensite_freinage=ordre_freinage;
                message_sent.expiration_time=addMinuts( message_sent.actual_time,5 );
                message_sent.num_serie[0]='a';
        } 
        else if( message_received.recieved==true){
                message_sent=message_received;
                message_sent.send = true;
                ordre_freinage=message_received.intensite_freinage;
        }
        else{
                message_sent.send=false;
                ordre_freinage=0;
        }
        output_csc o ={message_sent, ordre_freinage};
        return o;
        
    }

}


