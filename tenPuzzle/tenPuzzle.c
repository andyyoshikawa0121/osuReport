#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define e pow(10,-6)


//構造体

typedef struct{

	char formula_data[200];
	char operater[2];

}Formula;


typedef struct{

	double two_data[2];
	Formula formula[2];
	int priority[2];

}Two_data;


typedef struct{

	double three_data[3];
	Formula formula[3];
	int priority[3];

}Three_data;


//関数

Two_data swap_data_two(Two_data old_data){

	char save_formula[100];
	int save_priority;
	double save_data;
	char save_operater[2];

	strcpy(save_formula,old_data.formula[0].formula_data);
	strcpy(old_data.formula[0].formula_data,old_data.formula[1].formula_data);
	strcpy(old_data.formula[1].formula_data,save_formula);

	save_priority = old_data.priority[0];
	old_data.priority[0] = old_data.priority[1];
	old_data.priority[1] = save_priority;

	save_data = old_data.two_data[0];
	old_data.two_data[0] = old_data.two_data[1];
	old_data.two_data[1] = save_data;

	strcpy(save_operater,old_data.formula[0].operater);
	strcpy(old_data.formula[0].operater,old_data.formula[1].operater);
	strcpy(old_data.formula[1].operater,save_operater);

	return old_data;

}

Three_data swap_data_three(Three_data old_data){

	char save_formula[100];
	int save_priority;
	double save_data;
	char save_operater[2];

	strcpy(save_formula,old_data.formula[1].formula_data);
	strcpy(old_data.formula[1].formula_data,old_data.formula[2].formula_data);
	strcpy(old_data.formula[2].formula_data,save_formula);

	save_priority = old_data.priority[1];
	old_data.priority[1] = old_data.priority[2];
	old_data.priority[2] = save_priority;

	save_data = old_data.three_data[1];
	old_data.three_data[1] = old_data.three_data[2];
	old_data.three_data[2] = save_data;

	strcpy(save_operater,old_data.formula[1].operater);
	strcpy(old_data.formula[1].operater,old_data.formula[2].operater);
	strcpy(old_data.formula[2].operater,save_operater);

	return old_data;

}

double *swap_data_double(double old_data[4],int k,int q){

	double save_data;
	save_data = old_data[k];
	old_data[k] = old_data[q];
	old_data[q] = save_data;
	return old_data;

}


void print_formula(Two_data old_data,char operater[2]){

	int i;
	char new_formula[100] = "(";

	if(strcmp(operater,"+") == 0) {

		printf("%s+%s\n",old_data.formula[0].formula_data,old_data.formula[1].formula_data);

	}else if(strcmp(operater,"-") == 0){

		if(old_data.two_data[1] < 0){

			strcat(new_formula,old_data.formula[1].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[1].formula_data,new_formula);

		}else if(strcmp(old_data.formula[1].operater,"-") == 0 | strcmp(old_data.formula[1].operater,"+") == 0){

			strcat(new_formula,old_data.formula[1].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[1].formula_data,new_formula);
			strcpy(new_formula,"(");

		}


		printf("%s-%s\n",old_data.formula[0].formula_data,old_data.formula[1].formula_data);

	}else if(strcmp(operater,"*") == 0){

		for(i=0;i<2;i++){

			if( (old_data.priority[i] != 0) & (old_data.priority[i] < 2 ) ){

				strcat(new_formula,old_data.formula[i].formula_data);
				strcat(new_formula,")");

			}else{

				strcpy(new_formula,old_data.formula[i].formula_data);

			}

			strcpy(old_data.formula[i].formula_data,new_formula);
			strcpy(new_formula,"(");
		}

		printf("%s*%s\n",old_data.formula[0].formula_data,old_data.formula[1].formula_data);

	}else{

		for(i=0;i<2;i++){

			if( (old_data.priority[i] != 0) & (old_data.priority[i] < 2 ) ){

				strcat(new_formula,old_data.formula[i].formula_data);
				strcat(new_formula,")");

			}else{

				strcpy(new_formula,old_data.formula[i].formula_data);

			}

			strcpy(old_data.formula[i].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		if(strcmp(old_data.formula[1].operater,"/") == 0){

			strcat(new_formula,old_data.formula[1].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[1].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		printf("%s/%s\n",old_data.formula[0].formula_data,old_data.formula[1].formula_data);

	}

}


Two_data update_two_formulas(Three_data old_data,Two_data new_data,char operater[2]){

	int i;
	char new_formula[100] = "(";
	char link_formula[100] = "";

	if(strcmp(operater,"+") == 0){

		//足し算部分のデータの更新
		new_data.two_data[1] = old_data.three_data[1] + old_data.three_data[2];

		//文字式の更新
		//第1式の更新
		strcpy(new_data.formula[0].formula_data,old_data.formula[0].formula_data);
		strcpy(new_data.formula[0].operater,old_data.formula[0].operater);
		//第2式の更新
		strcpy(link_formula,old_data.formula[1].formula_data);
		strcat(link_formula,operater);
		strcat(link_formula,old_data.formula[2].formula_data);
		strcpy(new_data.formula[1].formula_data,link_formula);
		new_data.priority[1] = 1;
		strcpy(new_data.formula[1].operater,operater);

	}else if(strcmp(operater,"-") == 0){

		//引き算部分のデータの更新
		new_data.two_data[1] = old_data.three_data[1] - old_data.three_data[2];

		if(old_data.three_data[2] < 0){

			strcat(new_formula,old_data.formula[2].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[2].formula_data,new_formula);
			strcpy(new_formula,"(");

		}else if(strcmp(old_data.formula[2].operater,"-") == 0 | strcmp(old_data.formula[2].operater,"+") == 0){

			strcat(new_formula,old_data.formula[2].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[2].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		//文字式の更新
		strcpy(new_data.formula[0].formula_data,old_data.formula[0].formula_data);
		strcpy(new_data.formula[0].operater,old_data.formula[0].operater);
		//第１式の更新
		strcpy(link_formula,old_data.formula[1].formula_data);
		//第2式の更新
		strcat(link_formula,operater);
		strcat(link_formula,old_data.formula[2].formula_data);
		strcpy(new_data.formula[1].formula_data,link_formula);
		new_data.priority[1] = 1;
		strcpy(new_data.formula[1].operater,operater);

	}else if(strcmp(operater,"*") == 0){

		//掛け算部分のデータの更新
		new_data.two_data[1] = old_data.three_data[1] * old_data.three_data[2];

		//文字式の更新
		//第１式の更新
		strcpy(new_data.formula[0].formula_data,old_data.formula[0].formula_data);
		strcpy(new_data.formula[0].operater,old_data.formula[0].operater);

		for(i=1;i<3;i++){

			if( (old_data.priority[i] != 0) & (old_data.priority[i] < 2) ){

				strcat(new_formula,old_data.formula[i].formula_data);
				strcat(new_formula,")");

			}else{

				strcpy(new_formula,old_data.formula[i].formula_data);


			}

			strcpy(old_data.formula[i].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		//第2式の更新
		strcpy(link_formula,old_data.formula[1].formula_data);
		strcat(link_formula,operater);
		strcat(link_formula,old_data.formula[2].formula_data);
		strcpy(new_data.formula[1].formula_data,link_formula);
		//priorityの更新
		new_data.priority[1] = 2;
		strcpy(new_data.formula[1].operater,operater);


	}else{

		//割算部分のデータの更新
		new_data.two_data[1] = old_data.three_data[1] / old_data.three_data[2];

		//文字式の更新
		//第１式の更新
		strcpy(new_data.formula[0].formula_data,old_data.formula[0].formula_data);
		strcpy(new_data.formula[0].operater,old_data.formula[0].operater);
		//カッコをつけるかどうかの判断
		for(i=1;i<3;i++){

			if( (old_data.priority[i] != 0) & (old_data.priority[i] < 2) ){

				strcat(new_formula,old_data.formula[i].formula_data);
				strcat(new_formula,")");

			}else{

				strcpy(new_formula,old_data.formula[i].formula_data);

			}

			strcpy(old_data.formula[i].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		if(strcmp(old_data.formula[2].operater,"/") == 0){

			strcat(new_formula,old_data.formula[2].formula_data);
			strcat(new_formula,")");
			strcpy(old_data.formula[2].formula_data,new_formula);
			strcpy(new_formula,"(");

		}

		//第2式の更新
		strcpy(link_formula,old_data.formula[1].formula_data);
		strcat(link_formula,operater);
		strcat(link_formula,old_data.formula[2].formula_data);
		strcpy(new_data.formula[1].formula_data,link_formula);
		//priorityの更新
		new_data.priority[1] = 2;
		//operaterの更新
		strcpy(new_data.formula[1].operater,operater);


	}

	return new_data;

}


Three_data update_three_formulas(double old_data[4],Three_data new_data,char operater[2],int k,int q){

	int i;
	char new_formula[100];
	char string_data[100];

	if(strcmp(operater,"+") == 0){

		//足し算部分の更新
		new_data.three_data[2] = old_data[k] + old_data[q];
		//優先度の更新
		new_data.priority[2] = 1;

	}else if(strcmp(operater,"-") == 0){

		//足し算部分の更新
		new_data.three_data[2] = old_data[k] - old_data[q];
		//優先度の更新
		new_data.priority[2] = 1;

	}else if(strcmp(operater,"*") == 0){

		//掛け算部分の更新
		new_data.three_data[2] = old_data[k] * old_data[q];
		//優先度の更新
		new_data.priority[2] = 2;

	}else{

		//割算部分の更新
		new_data.three_data[2] = old_data[k] / old_data[q];
		//優先度の更新
		new_data.priority[2] = 2;

	}

	//文字式の更新
	sprintf(string_data,"%d",(int)old_data[k]);
	strcpy(new_formula,string_data);
	strcat(new_formula,operater);
	sprintf(string_data,"%d",(int)old_data[q]);
	strcat(new_formula,string_data);
	strcpy(new_data.formula[2].formula_data,new_formula);
	strcpy(new_data.formula[2].operater,operater);
	strcpy(new_data.formula[0].operater,"");
	strcpy(new_data.formula[1].operater,"");

	return new_data;

}

Three_data shift_three_array(Three_data array){

	int save_data = array.three_data[0];
	int save_priority = array.priority[0];
	char save_formula[100];
	char save_operater[2];
	int i;

	strcpy(save_formula,array.formula[0].formula_data);
	strcpy(save_operater,array.formula[0].operater);

	for(i=0;i<2;i++){
		array.three_data[i] = array.three_data[i+1];
		array.priority[i] = array.priority[i+1];
		strcpy(array.formula[i].formula_data,array.formula[i+1].formula_data);
		strcpy(array.formula[i].operater,array.formula[i+1].operater);
	}

	array.three_data[i] = save_data;
	array.priority[i] = save_priority;
	strcpy(array.formula[i].formula_data,save_formula);
	strcpy(array.formula[i].operater,save_operater);

	return array;

}


int check_ans(double a){

	if( (10.0-a) < e & (10.0-a) >= 0 ){
		//printf("clear%lf\n",a);
		return 1;

	}

	return 0;

}


void two_to_one(Two_data old_data){

	if(check_ans(old_data.two_data[0]+old_data.two_data[1])){

		print_formula(old_data,"+");

	}else if(check_ans(old_data.two_data[0]-old_data.two_data[1])){

		print_formula(old_data,"-");

	}else if(check_ans(old_data.two_data[0]-old_data.two_data[1])){

		//引き算の順番が変わっているので、shiftをする作業が必要
		old_data = swap_data_two(old_data);
		print_formula(old_data,"-");

	}else if(check_ans(old_data.two_data[0]*old_data.two_data[1])){

		print_formula(old_data,"*");

	}else if(check_ans(old_data.two_data[0]/old_data.two_data[1])){

		print_formula(old_data,"/");

	}else if(check_ans(old_data.two_data[0]/old_data.two_data[1])){

		old_data = swap_data_two(old_data);
		print_formula(old_data,"/");

	}

}

void three_to_two(Three_data old_data){

	Two_data new_data;
	int i;

	for(i=0;i<3;i++){

		new_data.two_data[0] = old_data.three_data[0];
		new_data.priority[0] = old_data.priority[0];

		//足し算
		new_data = update_two_formulas(old_data,new_data,"+");

		two_to_one(new_data);

		//引き算
		new_data = update_two_formulas(old_data,new_data,"-");

		two_to_one(new_data);

		//old_dataのformula[1]とformula[2]を入れ替える作業が必要
		//引き算その2
		old_data = swap_data_three(old_data);
		new_data = update_two_formulas(old_data,new_data,"-");

		two_to_one(new_data);
		//入れ替えたold_dataのformulaを元に戻す
		old_data = swap_data_three(old_data);

		//掛け算
		new_data = update_two_formulas(old_data,new_data,"*");

		two_to_one(new_data);

		//割り算
		new_data = update_two_formulas(old_data,new_data,"/");

		two_to_one(new_data);

		//割り算その２
		old_data = swap_data_three(old_data);
		new_data = update_two_formulas(old_data,new_data,"/");

		two_to_one(new_data);
		//入れ替えたold_dataのformulaを元に戻す
		old_data = swap_data_three(old_data);

		old_data = shift_three_array(old_data);

	}

}

void four_to_three(double old_data[4]){

	Three_data new_data;
	char string_data[100];
	int i,j,k,q;

	for(i=0;i<4;i++){
		for(j=i+1;j<4;j++){
			new_data.three_data[0] = old_data[i];
			new_data.priority[0] = 0;
			sprintf(string_data,"%d",(int)old_data[i]);
			strcpy(new_data.formula[0].formula_data,string_data);

			new_data.three_data[1] = old_data[j];
			new_data.priority[1] = 0;
			sprintf(string_data,"%d",(int)old_data[j]);
			strcpy(new_data.formula[1].formula_data,string_data);

			if(i==0 & j==3){
				k = 1;
				q = 2;
			}else if(i==1 & j==2){
				k = 0;
				q = 3;
			}else{
				k = 3 - i;
				q = 3 - j;
			}

			//足し算
			new_data = update_three_formulas(old_data,new_data,"+",k,q);
			three_to_two(new_data);

			//引き算
			new_data = update_three_formulas(old_data,new_data,"-",k,q);
			three_to_two(new_data);

			//引き算その2
			old_data = swap_data_double(old_data,k,q);
			new_data = update_three_formulas(old_data,new_data,"-",k,q);
			three_to_two(new_data);
			old_data = swap_data_double(old_data,k,q);

			//掛け算
			new_data = update_three_formulas(old_data,new_data,"*",k,q);
			three_to_two(new_data);

			//割り算
			new_data = update_three_formulas(old_data,new_data,"/",k,q);
			three_to_two(new_data);

			//割り算その2
			old_data = swap_data_double(old_data,k,q);
			new_data = update_three_formulas(old_data,new_data,"/",k,q);
			three_to_two(new_data);
			old_data = swap_data_double(old_data,k,q);
		}
	}

}

int main (void){

	int i;
	double data[4];

	for(i=0;i<4;i++){
		printf("input data[%d] : ",i);
		scanf("%lf",&data[i]);
	}


	four_to_three(data);


	return 0;

}
