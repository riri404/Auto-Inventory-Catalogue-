#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node for maker-level structures
 struct node {
   char *maker; //pointer to car maker
   struct node *next; //pointer to next maker
   struct model *below; //pointer to model structure
 };

//node for model-level structures, include 12 attributes
struct model {
  char *car_maker;
  char *car_model;
  char *trim;
  char *km;
  char *year;
  char *type;
  char *drivetrain;
  char *transmission;
  char *stock;
  char *status;
  char *fuel_eco;
  char *set_of_features;
  char *attrs;//for show all attributes
  struct model *next;//pointer to next model
};

//this method is to get all features of vehicle
void getfeatures(char *line, struct model *head_car_model )
{
  // firstly split {set_features} of line, then split other attributes
  const char s[] = "{"; 
  char *arr_f; //for store set_features {features}
  char *arr_o; //store first split other attributes
  //store split other 11 attributes of car
  char *arr0, *arr1, *arr2, *arr3, *arr4, *arr5, *arr6, *arr7, *arr8, *arr9, *arr10;
  char *token;
  //set attrs of struct model
  char attributes[3000];//store all atttrs, to keep the data, not use pointer.
  strcpy(attributes, line);
  ((head_car_model)->attrs) = attributes; 
  //printf(" %s\n", head_car_model->attrs);

  //use strtok to split {set_features} of line, store in att_f[]
  token = strtok(line, s);
  arr_o = token;
  while(token != NULL){
    arr_f =  token;
    token = strtok(NULL, s);  
  }
  //move all elements in arr_f to arr_ff
  char arr_ff[strlen(arr_f)+1]; 
  for(int i = 0; i<strlen(arr_f)-1; i++){
    arr_ff[i+1] = arr_f[i];
  }
  //add '{' before features
  arr_ff[0] = '{'; 
  //assign set_features to arr_f
  arr_f = arr_ff;
  //split other attributes in arr_o
  //need to split ',' in arr_o
  int n = 0;
  while( n < 11){
    token = strtok(arr_o, ",");
    //assign other attributes to arr[0-10] in order of output file
    switch(n){
      case 1:
        arr1 = token;
        break;
      case 2:
        arr2 = token;
        break;
      case 3:
        arr3 = token;
        break;
      case 4:
        arr4 = token;
        break;
      case 5:
        arr5 = token;
        break;  
      case 6:
        arr6 = token;
        break; 
      case 7:
        arr7 = token;
        break; 
      case 8:
        arr8 = token;
        break; 
      case 9:
        arr9 = token; 
        break;
      case 10:
        arr10 = token;
        break;              
      default:
        arr0 = token;
        break;  
    }
    while(token != NULL){
      arr_o = token;
      token = strtok(NULL, s);  
    }
    n += 1;
  }
    //assign attributes to structures
    head_car_model->car_maker = arr0;
    head_car_model->car_model = arr1;
    head_car_model->trim = arr2;
    head_car_model->km = arr3;
    head_car_model->year = arr4;
    head_car_model->type = arr5;
    head_car_model->drivetrain = arr6;
    head_car_model->transmission = arr7;
    head_car_model->stock = arr8;
    head_car_model->status = arr9;
    head_car_model->fuel_eco = arr10;
    head_car_model->set_of_features = arr_f;

}

//this method is to given a reference (pointer to pointer) to the head of a list and a char, inserts a new node on the front of the list.
void push( struct node** head_ref, char *new_data)
{
  struct node *new_maker = malloc(sizeof(struct node));
  new_maker->maker = new_data;
  new_maker->next = (*head_ref);
  (*head_ref) = new_maker; 
  new_maker->below = NULL;
  printf("Create the maker node is %s \n", ((new_maker)->maker));
}
//this method is to insert model
void insertModel( struct model *prev_model, struct model *model_below)
{
  model_below->next = prev_model->next;
  prev_model = model_below; 
}


//this method is to insert a new model node in given maker node
void pushModel(struct node** prev_ref,  struct model *new_below)
{
  if(prev_ref == NULL){
    printf("the given previous node cannot be null");
    return;
  }
  if(((*prev_ref)->below) == NULL){
    ((*prev_ref)->below) = new_below;
    new_below->next = NULL;
  }
  else{
    new_below->next = ((*prev_ref)->below);
    ((*prev_ref)->below) = new_below;
  }
  printf("Show multi linked list:\n");
  printf("the node of (%s) (maker->below) is: %s\n\n", ((*prev_ref)->maker) , (*prev_ref)->below->car_model);

}

//this method is searchInventory, using traverse linked list to find all matched key and value
void searchInventory(char *str1, char *str2, struct node *head_search)
{
  printf("Find all matched data:\n ");

  while((head_search->next) != 0){
    if(strcmp((head_search->maker), str2) == 0){
      printf("match maker is: %s\n", (head_search->maker));
        while((head_search->below) != 0){
            printf("%s\n", (head_search->below->attrs));
            head_search->below = head_search->below->next;
        }
        break;
      }
      head_search = (head_search->next);//find next node

  }
}

//this method is to savecatalogue2file( head_maker )
void savecatalogue2file( struct node *head_maker_save)
{
  //create and write an output file
  FILE *ft = NULL;
  ft = fopen("./output.txt", "a+");
  while(head_maker_save->next != NULL){
    //create file output
    while((head_maker_save->below) != NULL){
      printf("%s\n", head_maker_save->below->attrs );
      fputs(head_maker_save->below->attrs,ft);
      head_maker_save->below = head_maker_save->below->next;
    }
    head_maker_save = head_maker_save->next;
  }
//close file
  fclose(ft);

}

//this method is to add2Inventory(data)
void add2Inventory(char* data, struct node *insert_maker)
{
  struct model *add_model = NULL;
  add_model = malloc(sizeof(struct model));
  if (add_model == NULL) { printf("fail to allocate memory!");}    
  getfeatures(data, add_model);

  //push into linked list
  while((insert_maker->next) != 0){
      if(strcmp((insert_maker->maker), (add_model->car_maker)) == 0){
        pushModel(&insert_maker, add_model);
        break;
      }
      insert_maker = (insert_maker->next);//find next node     

  }
  printf("this data has already added into linked list:\n\n");
  printf("%s\n", add_model->attrs);
  
}

int main(void) {
  // read data file
  FILE *fp = NULL; //file pointer
  fp = fopen("./car_data.txt", "r");
  char buff[1024]; 

  if(fp == NULL)
  {
    perror("Fail to read!");
    return -1;
  }
  //create struct node of 5 car makers
  struct node *head_maker = NULL;
  struct node *head_node = NULL; //for additionally head pointer to node of list
  char *data = "Bmw";
  push(&head_maker, data);
  data = "Lexus";
  push(&head_maker, data); 
  data = "Toyota";
  push(&head_maker, data);
  data = "Mercedec";
  push(&head_maker, data);
  data = "Honda";
  push(&head_maker, data);
  head_node = malloc(sizeof(struct node));
  head_node->next = head_maker;

  printf("Already created maker linked list.\n\n");
  printf("creating multi linked list...\n\n");
  //read ordered output file
  while (fgets(buff, sizeof(buff), fp) != NULL)
  {
    struct model *head_model = NULL;
    head_model = malloc(sizeof(struct model));
    if (head_model == NULL) { printf("fail to allocate memory!");}
    //create multi linked list    
    getfeatures(buff, head_model);
    
    //use head_maker to traverse all node maker, to find same maker, then node->below->new model node.
    while((head_maker->next) != 0){
      if(strcmp((head_maker->maker), (head_model->car_maker)) == 0){
        pushModel(&head_maker, head_model);
        break;
      }
      head_maker = (head_maker->next);//find next node
    }
    //recall savecatalogue2file()
    savecatalogue2file(head_maker);
  
  }  

 
  char add_data[500] = "Bmw, X6, SS, 10km, 2018, SUV, AWD, auto, 22AA999A, new, 10L/100km, {Heated Seats, Heated Mirrors, Keyless Entry}";
  // pointer is back to head of the node list
  head_maker = head_node->next;
  add2Inventory(add_data, head_maker);
  
  //recall searchInventory(str_key, str_value, head_maker)
  char *str_key, *str_value;
  str_value = "Mercedec";
  str_key = "car_maker";
  searchInventory(str_key, str_value, head_maker);




  fclose(fp); //close file
  

  return 0;

}



      

       


