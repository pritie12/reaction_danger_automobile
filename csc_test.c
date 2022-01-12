#include "CUnit.h"
#include "Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "implementation_csc.h"
#include <stdbool.h>
#include <stdio.h> 


/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}



void test_req01_1(void){

    type_urgence obstacle;
    obstacle.object_dim.hauteur= 100;
    obstacle.object_dim.largeur= 50;
    obstacle.object_dim.profondeur=20;
    obstacle.distance=10.2;

    float speed = 50;

    position pos= {10,20,30};

    message msg;
    msg.recieved=false;

    output_csc o = Chassis_Safety_Controller(obstacle, msg,speed,pos);

    CU_ASSERT_EQUAL(o.message_sent.send,true);
    CU_ASSERT(o.ordre_freinage>0);

}

void test_req01_2(void){

    type_urgence obstacle;
    obstacle.object_dim.hauteur= 1;
    obstacle.object_dim.largeur= 0.5;
    obstacle.object_dim.profondeur=0.02;
    obstacle.distance=10.2;

    type_urgence obstacle_d;
    obstacle.object_dim.hauteur= 10;
    obstacle.object_dim.largeur= 50;
    obstacle.object_dim.profondeur=20;

    float speed = 50;

    position pos= {10,20,30};

   message msg;
   msg.recieved=true;
   msg.send=false;
   msg.car_position=pos;
   msg.vitesse=110.5;
   //msg.actual_time=current_time_tm();
   msg.detected_object= obstacle_d;
   msg.detected_object.distance=20.5;
   msg.intensite_freinage=0.7;


    output_csc o = Chassis_Safety_Controller(obstacle, msg,speed,pos);

    CU_ASSERT(o.message_sent.send);
    CU_ASSERT(o.ordre_freinage>0);
}

void test_req02_1(void){

    type_urgence obstacle;
    obstacle.object_dim.hauteur= 1;
    obstacle.object_dim.largeur= 0.5;
    obstacle.object_dim.profondeur=0.02;
    obstacle.distance=10.2;

    float speed = 50;

    position pos= {10,20,30};

    message msg;
    msg.recieved=false;

    output_csc o = Chassis_Safety_Controller(obstacle, msg,speed,pos);

    CU_ASSERT_EQUAL(o.message_sent.send,false);
    CU_ASSERT_EQUAL(o.ordre_freinage,0);
}

void test_req04_1(void){

    type_urgence obstacle;
    obstacle.object_dim.hauteur= 100;
    obstacle.object_dim.largeur= 50;
    obstacle.object_dim.profondeur=20;
    obstacle.distance=10.2;

    float speed = 50;

    position pos= {10,20,30};

    message msg;
    msg.recieved=false;

    output_csc o = Chassis_Safety_Controller(obstacle, msg,speed,pos);

    CU_ASSERT_EQUAL(o.message_sent.send,true);
   //Message contenant latitude, longitude, l’altitude, vitesse, 
   //direction du système à l’origine du message, 
   //l’heure courante, une heure d’expiration de ce message, 
   //le type d’urgence, ainsi que les mesures 

}


/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "req 01 test_1", test_req01_1)) ||
        (NULL == CU_add_test(pSuite, "req 01 test_2", test_req01_2)) ||
        (NULL == CU_add_test(pSuite, "req 02 test_1", test_req02_1)) ||
        (NULL == CU_add_test(pSuite, "req 04 test_1", test_req04_1))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}