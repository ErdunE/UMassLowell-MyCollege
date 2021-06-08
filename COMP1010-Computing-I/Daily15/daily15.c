/*
 Program: <Final iteration>
 Author: <Erdun E>
 Date: <03-30-2018>
 Time spent: <2days>
 Sources of Help: <tutors, web sites, friends>
 Purpose:this program let us know how to do unit conversion
 */
#include <stdio.h>

void main_menu();
void convert_lengths(int *choice);//
void convert_weights(int *choice);
void clear_keyboard_buffer();
void input_length_metric(); 
void conversion_length_metric(int *p_feet, double *p_inches); 
void output_length_metric(int *p_feet, double *p_inches, int result_meters, double centimeters_result);
void input_length_usa();
void conversion_length_usa(int *p_meters, double *p_centimeters);
void output_length_usa(int *p_meters, double *p_centimeters, int result_feet, double inches_result);
void input_weight_metric();
void conversion_weight_metric(int *p_lbs, double *p_oz);
void output_weight_metric(int *p_lbs, double *p_oz, int result_kg, double result_g);
void input_weight_usa();
void conversion_weight_usa(int *p_kg, double *p_g);
void output_weight_usa(int *p_kg, double *p_g, int result_lbs, double result_oz); 




int main (int argc, char * argv[])
{
    int choice;
    do
    {
        main_menu(&choice);
    }
    while (choice != 0);
    return 0;
}

void main_menu(int *choice)
{
    printf("Would you like to convert lengths or weights?:");
    printf("Enter 1 for lengths, 2 for weights, or 0 to end program.\n");
    scanf("%d", choice);
    clear_keyboard_buffer();
    while (*choice != 1 && *choice != 2 && *choice != 0)
    {
        printf(" Wrong order, pls try again. \n");
        printf("Enter 1 for lengths, 2 for weights, or 0 to end program.\n");
        printf("Enter 1 for lengths or 2 for weights\n");
        scanf("%d", choice);
        clear_keyboard_buffer();
        if (*choice !=0 && *choice != 1 && *choice != 2 )
        {
            printf("Wrong order, pls try again. \n");
            printf("Enter 1 for lengths, 2 for weights, or 0 to end program.\n");
            printf("Enter 1 for lengths or 2 for weights\n");
            scanf("%d", choice);
            clear_keyboard_buffer();
        }
        
    }
    if (*choice==1)
    {
        convert_lengths(choice);
    }
    if (*choice==2)
    {
        convert_weights(choice);
    }
    if (choice==0)
    {
        choice = 0;
    }
}

void convert_lengths(int *choice)
{
    printf("You chose to convert to lengths\nDo you want to (1) 1convert from feet/inches to meters/centimeters? \nor (2) from meters to centimeters to feet/inches? \nOr (0)exit?:\n");
    
    scanf("%d", choice);
    
    if (*choice==1)
    {
        length_to_metric();
        *choice = 1;
    }
    if (*choice==2)
    {
        length_to_usa();
        *choice = 1;
    }
    
    if (*choice==0)
    {
        *choice = 0;
    }
}

void input_length_metric()
{
    int feet;
    double inches;
    printf("Please enter a number(feet):\n");
    scanf("%d", &feet);
    while (feet <= 0)
    {
        printf("pls enter positive number: \n");
        scanf("%d", &feet);
        clear_keyboard_buffer();
    }
    
    printf("Please enter the number of inches:\n");
    scanf("%lf", &inches);
    while (inches <= 0)
    {
        printf("pls enter positive number: \n");
        scanf("%lf", &inches);
        clear_keyboard_buffer();
    }
    conversion_length_metric(&feet, &inches);

void conversion_length_metric(int *p_feet, double *p_inches)
{
    double feet_to_meters = *p_feet * 0.3048; 
    
    double inches_to_meters = (*p_inches/12) * 0.3048;
    
    double total_meters = inches_to_meters + feet_to_meters;
    
    int result_meters = inches_to_meters + feet_to_meters;
    
    double centimeters_result = (total_meters-result_meters)*100; 
    
    output_length_metric(p_feet, p_inches, result_meters, centimeters_result);
    
}


void output_length_metric(int *p_feet, double *p_inches, int result_meters, double centimeters_result)
{
    printf("%d (feet) %lf (inche) is equal to %d (meter) %lf (centimeter)\n", *p_feet, *p_inches, result_meters, centimeters_result);
}


void input_length_usa()
{
    int meters;
    double centimeters;
    printf("Please enter the number (meter):\n");
    scanf("%d", &meters);
    clear_keyboard_buffer();
    while (meters <= 0)
    {
        printf("pls enter positive number: \n");
        scanf("%d", &meters);
        clear_keyboard_buffer();
    }
    printf("Please enter the number of centimeters\n");
    scanf("%lf", &centimeters);
    while (centimeters <= 0)
    {
        printf("pls enter positive number: \n");
        scanf("%lf", &centimeters);
        clear_keyboard_buffer();
    }
    
    conversion_length_usa(&meters, &centimeters);
}



void conversion_length_usa(int *p_meters, double *p_centimeters)
{
    double meters_to_feet = *p_meters / 0.3048;
    
    double centimeters_to_feet = (*p_centimeters / 100) / 0.3048;
    
    double total_feet = meters_to_feet + centimeters_to_feet;
    
    int result_feet = meters_to_feet + centimeters_to_feet;
    
    double inches_result = (total_feet-result_feet) * 12; 
    
    output_length_usa(p_meters, p_centimeters, result_feet, inches_result);
}


void weight_to_metric()
{
    printf("You chose to convert from feet/inches to meters/centimeters.\n");
    input_length_metric();
}
void convert_weights(int *choice)
{
    
    printf("You chose to convert to weights\nDo you want to (1) convert from pounds/ounces to KG or G? \nor (2)from KG or G to pounds/ounces? \nOr (0)exit? :\n");
    
    scanf("%d", choice);
    
    if (*choice==1)
    {
        weight_to_metric();
        *choice = 1;
    }
    if (*choice==2)
    {
        weight_to_usa();
        *choice = 1;
    }
    if (*choice==0)
    {
    *choice = 0;
    }
    
}

void input_weight_metric()
{
    int lbs;
    double oz;
    printf("Please enter the number (pound): ");
    scanf("%d", &lbs);
    clear_keyboard_buffer();
    while (lbs <= 0)
    {
        printf("Pls enter a positive weight: \n");
        scanf("%d", &lbs);
        clear_keyboard_buffer();
    }
    
    printf("Please enter the number of (oz): ");
    scanf("%lf", &oz);
    clear_keyboard_buffer();
    while (oz <= 0)
    {
        printf("Please enter a positive weight: \n");
        scanf("%lf", &oz);
        clear_keyboard_buffer();
    }
    conversion_weight_metric(&lbs, &oz);
}



void conversion_weight_metric(int *p_lbs, double *p_oz)
{
    double lbs_to_kg = *p_lbs / 2.2046;
    double oz_to_kg = (*p_oz/16) / 2.2046;
    double amount_total = lbs_to_kg +oz_to_kg;
    int result_kg = lbs_to_kg + oz_to_kg;
    double result_g = (amount_total - result_kg) * 1000;
    output_weight_usa(p_lbs, p_oz, result_kg, result_g);
}

void output_weight_metric(int *p_lbs, double *p_oz, int result_kg, double result_g)
{
    printf("%d (pound) and %f (oz) is equal to %d (KG) and %f (g).\n", *p_lbs, *p_oz, result_kg, result_g);
}


    int kg;
    double g;
    printf("Please enter the number (kg)");
    scanf("%d", &kg);
    clear_keyboard_buffer();
    while (kg <= 0)
    {
        printf("pls enter a positive number: \n");
        scanf("%d", &kg);
        clear_keyboard_buffer();
    }
    printf("Please enter the number grams:");
    scanf("%lf", &g);
    clear_keyboard_buffer();
    while (g <= 0)
    {
        printf("pls enter a positive number: \n");
        scanf("%lf", &g);
        clear_keyboard_buffer();
    }
    conversion_weight_usa(&kg, &g);
}
    


    void conversion_weight_usa(int *p_kg, double *p_g)
    {
    double kg_to_lbs = *p_kg * 2.2046;
    double g_to_lbs = (*p_g/1000) * 2.2046;
    double result_amount = kg_to_lbs + g_to_lbs;
    int result_lbs = kg_to_lbs + g_to_lbs;
    double result_oz = (result_amount - result_lbs) * 16; 
    output_weight_usa(p_kg, p_g, result_lbs, result_oz);
    }


void output_weight_usa (int *p_kg, double *p_g, int result_lbs, double result_oz)
{
    printf("%d (KG) and %f (g) is equivalent to %d (pound) and %f (oz).\n", *p_kg, *p_g, result_lbs, result_oz);
}

        
        
void clear_keyboard_buffer()
{
    char c;
    scanf("%c", &c);
    while(c != '\n')
    {
        scanf("%c", &c);
    }
    return;
}
