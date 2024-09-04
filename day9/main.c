#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE* fptr;

void strstrip(char* str);

typedef struct Road road_t;
typedef struct City city_t;

struct Road {
    int length;
    city_t* targets[2];
};

struct City {
    char name[30];
    road_t* roads[10];
    int road_counter;
};


city_t* appendCity(city_t* cities, int* cc,  char* name){
   city_t newcity;
   strcpy(newcity.name, name);
   newcity.road_counter = 0;
   cities[*cc] = newcity;
   *cc += 1;
   return &(cities[*cc - 1]);
}

city_t* findCity(city_t* cities, int* cc, char* name){
    for(int i=0; i<*cc; i++){
        if(strcmp(name, cities[i].name) == 0){
            return &(cities[i]);
        }
    }
    return appendCity(cities, cc, name);
}

bool hasVisited(city_t* visited[], int* vc, road_t* current_road, city_t* current_city){
    for(int i=0; i<*vc; i++){
        if(strcmp(visited[i]->name, current_city->name) == 0){
            continue;
        }else if(strcmp(visited[i]->name, current_road->targets[0]->name) == 0){
            return true;
        }else if(strcmp(visited[i]->name, current_road->targets[1]->name) == 0){
            return true;
        }
    }
    return false;
}

int findShortestRoute(city_t *cities, int *cc, city_t *visited[], int *vc,
                      char *home_name) {
  city_t *current_city = findCity(cities, cc, home_name);
  int total_length = 0;
  while (*vc < *cc) {
    visited[*vc] = current_city;
    *vc += 1;
    road_t *shortest_road;
    int shortest_length = 100000;
    for (int i = 0; i < current_city->road_counter; i++) {
      road_t *current_road = current_city->roads[i];
      if (current_road->length < shortest_length && !hasVisited(visited, vc, current_road, current_city)) {
        shortest_road = current_road;
        shortest_length = shortest_road->length;
      }
    }
    total_length += shortest_length;
    if(strcmp(current_city->name, shortest_road->targets[0]->name) == 0){
        current_city = shortest_road->targets[1];
    }else{
        current_city = shortest_road->targets[0];
    }
  }
  printf("Shortest length was: %u\n", total_length);
  return total_length;
}

void addRoadToCity(city_t* cities, int *cc, road_t* roads, int *rc,  char* city_name, char* dest_name, int road_length){
    road_t newroad;
    city_t* home_city = findCity(cities, cc, city_name);
    city_t* dest_city = findCity(cities, cc, dest_name);
    newroad.targets[0] = home_city;
    newroad.targets[1] = dest_city;
    newroad.length = road_length;
    
    roads[*rc] = newroad;
    
    home_city->roads[home_city->road_counter] = &roads[*rc];
    home_city->road_counter += 1;
    dest_city->roads[dest_city->road_counter] = &roads[*rc];
    dest_city->road_counter += 1;
    *rc += 1; 

}

int main(){
    road_t* roads = malloc(sizeof(road_t) * 100);
    int road_counter = 0;
    city_t* cities = malloc(sizeof(city_t) * 20);
    int city_counter = 0;
    city_t** already_visited = malloc(sizeof(city_t) * 20);
    int visited_counter = 0;
    
    fptr = fopen("../in.txt", "r");
    char buffer[120] = {0};
    char* token;
    while(fgets(buffer, 120, fptr) != NULL){
        strstrip(buffer);
        token = strtok(buffer, " ");
        int arg_counter = 0;
        char target1[30] = {0};
        char target2[30] = {0};
        int length = 0;
        while(token != NULL){
            if(arg_counter == 0){
                strcpy(target1, token);
            }else if(arg_counter == 2){
                strcpy(target2, token);
            }else if(arg_counter == 4){
                length = atoi(token);
            }
            arg_counter++;
            token = strtok(NULL, " ");
        }
        printf("%s to %s is %u\n", target1, target2, length);
        addRoadToCity(cities, &city_counter, roads, &road_counter, target1, target2, length);
    }
    for(int i=0;i<city_counter;i++){
        
        findShortestRoute(cities, &city_counter, already_visited, &visited_counter, cities[i].name);
    }
    return 0;
    
}
void strstrip(char* str){
    str[strcspn(str, "\n")] = 0;
}
