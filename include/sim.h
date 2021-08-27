#ifndef SIM_H
#define SIM_H


typedef struct {
	float x;
	float y;
} Vec2;

typedef struct Worker {
	char name[100];
	float wage;
} Worker;

typedef struct Good {
	char name[100];
} Good;

typedef struct Recipe {
	char name[100];
	int input_num;
	int *inputs;
	float *input_amts;
	float *input_prop; //proportions
	int output_num;
	int *outputs;
	float *output_amts;
	int labour_num;
	int *labour_types;
	float *labour_amts;
} Recipe;

float get_fmin(float a, float b) {
	if(a < b) {
		return a;
	} else {
		return b;
	}
}

float get_fmax(float a, float b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

#endif












