
#include <time.h>
#include <stdbool.h>

#ifndef IMPLEMENTATION_CSC_H
#define IMPLEMENTATION_CSC_H

typedef struct tm tm;
typedef struct position {float latitude; float longitude; float hauteur;}position;
typedef struct dimension {float hauteur; float largeur; float profondeur;} dimension;
typedef struct type_urgence{
    short deteted;
	dimension object_dim;
    float distance;
} type_urgence;



typedef struct message{
    bool recieved;
    bool send;
    struct position car_position;
	float vitesse;
	tm actual_time; // tm est une structure de la librairie <time.h>
	type_urgence detected_object;
	float intensite_freinage;
	tm expiration_time;
	char num_serie[]; // constante
} message;

struct output_csc{
    struct message message_sent;
    float ordre_freinage;
} ;
typedef struct output_csc output_csc;
extern output_csc  Chassis_Safety_Controller(type_urgence obstacle_detected, message message_received,
                                                float vitesse_vehicule,position current_position);
#endif