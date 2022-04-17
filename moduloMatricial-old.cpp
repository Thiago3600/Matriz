#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cell{
	int i;
	int j;
	double value;
	struct matrix *started;
	struct cell *inicio;
};

struct matrix{
	int lines;
	int columns;
	double det;
	struct cell *start;
};

void insertElement(struct matrix *mat, int i, int j, double val);
struct matrix *createMatrix(int i, int j);
struct matrix *sumMatrix(struct matrix *matA, struct matrix *matB);
struct matrix *minusMatrix(struct matrix *matA, struct matrix *matB);
struct matrix *divMatrix(struct matrix *matA, struct matrix *matB);
struct matrix *inverseMat(struct matrix *mat);
struct matrix *multMatrix(struct matrix *matA, struct matrix *matB);
struct matrix *multiplyBy(struct matrix *mat, double val);
struct matrix *exponentsMat(struct matrix *mat, int n);
struct matrix *transposedMat(struct matrix *mat);
struct matrix *createCopyMatrix(struct matrix *mat);


double returnValue(struct matrix *mat, int i, int j);
double determinant(struct matrix *mat);

void insertValues(double vector[], int n, struct matrix *mat);
void insertRandValMat(struct matrix *mat);
void printfMatrix(struct matrix *mat); 
void printVector(struct matrix *mat);
void copyMatrix(struct matrix *matA, struct matrix *matB);

/*Cria uma matriz de acordo com a dimensão fornecida pelas
	variaveis do tipo int e retorna uma nova matriz*/
struct matrix *createMatrix(int i, int j){
	struct matrix *matriz = (struct matrix*) malloc(sizeof(struct matrix));
	struct cell *celulas = (struct cell*) malloc((i*j)*sizeof(struct cell));
	struct cell *address = celulas;				/* 8 */
	
	matriz->lines = i;//4
	matriz->columns = j;//2
	matriz->start = celulas;
	celulas->started = matriz;
	
	int m, n;
	for(m = 0; m < i; m++){
		for(n = 0; n < j; n++){
			celulas->i = m;
			celulas->j = n;						
			celulas->value = 0;	
			celulas->inicio = address;
			celulas++;			
		}
	}
	
	celulas = matriz->start;
	return matriz;
}

/*Insere valores a partir de um vetor, tendo que informar o tamanho do vetor
	e qual variavel matrix.*/
void insertValues(double vector[], int n, struct matrix *mat){
	if(n == ((mat->columns)*(mat->lines))){
		int count = 0;
		while(count < n){
			mat->start->value = vector[count];
			mat->start++;
			count++; 
		}
		mat->start = mat->start - count;
	}else{
		printf("Vetores de tamanho diferentes\n");
	}
}

void insertRandValMat(struct matrix *mat){
	int i, j;
	srand(time(NULL));
	for(i = 0; i < mat->lines; i++){
		for(j = 0; j < mat->columns; j++){
			insertElement(mat, i, j, ((double)(rand()%1000)/1000));
		}
	}
}

/*Realiza a soma de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
struct matrix *sumMatrix(struct matrix *matA, struct matrix *matB){
	if((matA->lines) == (matB->lines) && (matA->columns) == (matB->columns)){
		struct matrix *matC = createMatrix(matA->lines, matA->columns);
		int count = 0, i, j;		
		for(i = 0; i < matA->lines; i++){
			for(j = 0; j < matA->columns; j++){
				insertElement(matC, i, j, (returnValue(matA, i, j)+returnValue(matB, i, j)));
			}	
		}
	return matC;
	}else{
		printf("Nao foi possivel somar\n");
		return NULL;
	}
	
}

/*Realiza a subtração de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
struct matrix *minusMatrix(struct matrix *matA, struct matrix *matB){
	if((matA->lines) == (matB->lines) && (matA->columns) == (matB->columns)){
		struct matrix *matC = createMatrix(matA->lines, matA->columns);
		int count = 0, i, j;		
		for(i = 0; i < matA->lines; i++){
			for(j = 0; j < matA->columns; j++){
				insertElement(matC, i, j, (returnValue(matA, i, j)-returnValue(matB, i, j)));
			}	
		}
	return matC;
	}else{
		printf("Nao foi possivel subtrair\n");
		return NULL;
	}
	
}

/*Realiza a divisão de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
struct matrix *divMatrix(struct matrix *matA, struct matrix *matB){
	if((matA != NULL) && (matB != NULL) && (matA->columns) == (matB->lines) && (matB->lines) == (matB->columns)){
		struct matrix *matC = inverseMat(matB);
		struct matrix *matD = multMatrix(matA, matC);
		free(matC);
	return matD;
	}else{
		printf("Nao foi possivel dividir\n");
		return NULL;
	}
	
}

/*Calcula a matriz inversa da matriz fornecida e retorna uma nova com o resultado*/
struct matrix *inverseMat(struct matrix *mat){
	if(mat != NULL && mat->lines == mat->columns){
		
		struct matrix *inverse = createMatrix(mat->lines, mat->columns*2);
		struct matrix *temp = createMatrix(mat->lines, mat->columns*2);
		
		double det = 1;
		int i, j, k, l = 0, c = 0;
		
		for(i=0; i<mat->lines; i++){
			for(j=0; j<mat->columns; j++){
				insertElement(temp, i, j, returnValue(mat, i, j));
			}	
		}
		for(i=0; i<temp->lines; i++){
			for(j=temp->lines; j<temp->columns; j++){
				if(i==j-temp->lines){
					insertElement(temp, i, j, 1);
				}	
			}	
		}
		copyMatrix(inverse, temp);
		
		for(k=0; k<temp->lines; k++){	
			for(i=0; i<temp->lines; i++){
				for(j=0; j<temp->columns; j++){
					if(i!=l){
						insertElement(inverse, i, j, (returnValue(temp, l, c)*returnValue(temp, i, j)-returnValue(temp, c, j)*returnValue(temp, i, l))/det);
					}	
				}
			}
			copyMatrix(temp, inverse);
			det = returnValue(temp, l, c);
			l++;		
			c++;			
		}
		if(det==0){
			printf("\nA matriz nao tem inversa a determinante = %i\n", det);
			return NULL;
		}else{
			//printVector(inverse);
			free(temp);
			temp = createMatrix(mat->lines, mat->columns);
			for(i = 0; i < inverse->lines; i++){
				for(j = 0; j < inverse->columns; j++){
					insertElement(temp, i, j, returnValue(inverse, i, j + mat->columns)/det);		
				}	
			}
			free(inverse);
			return temp;				
		}
	}else{
		return NULL;
	}
}

/*Realiza a multiplicação de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
struct matrix *multMatrix(struct matrix *matA, struct matrix *matB){
	if((matA->columns)==(matB->lines)){
		struct matrix *matC = createMatrix(matA->lines, matB->columns);
		int i, j, k;
		for(i = 0; i < matA->lines;i++){
			for(j = 0; j < matB->columns; j++){
				for(k = 0; k < matA->columns; k++){
					insertElement(matC, j, i, (returnValue(matC, j, i)+returnValue(matA, j, k)*returnValue(matB, k, i)));
				}
			}
		}
		return matC;
	}else{
		printf("As matrizes nao estao de acordo com a multiplicacao.\n");
		printf("Matriz A %dx%d.\n", matA->lines, matA->columns);
		printf("Matriz B %dx%d.\n", matB->lines, matB->columns);
		return NULL;		
	}
}

/*Multiplica uma matriz por um valor*/
struct matrix *multiplyBy(struct matrix *mat, double val){
	if(mat != NULL){
		struct matrix *result = createMatrix(mat->lines, mat->columns);
		int i, j;
		for(i = 0; i < mat->lines; i++){
			for(j = 0; j < mat->columns; j++){
				insertElement(result, i, j, returnValue(mat, i, j)*val);
			}
		}
		return result;	
	}
}

/*Eleva a matriz a um valor*/
struct matrix *exponentsMat(struct matrix *mat, int n){
	if(mat != NULL){
		struct matrix *result = createCopyMatrix(mat);
		int i = 1;
		while(i < n){
			result = multMatrix(result, mat);
			i++;
		}
		return result;
	}
}

/*E fornecida uma matriz e retorna uma nova transposta.*/
struct matrix *transposedMat(struct matrix *mat){
	if(mat != NULL){
		struct matrix *result = createMatrix(mat->columns, mat->lines);
		//printfMatrix(result);
		
		int i, j;
		for(i = 0; i < result->lines; i++){
			for(j = 0; j < result->columns; j++){
				insertElement(result, i, j, returnValue(mat, j, i));
				//printf("matriz[%d][%d] = %.0lf Result[%d][%d] = %.0lf\n", j, i, returnValue(mat, j, i), i, j, returnValue(result, i, j));
			}
		}
		return result;
	}
}

/*Imprime no console a matriz desejada.*/
void printfMatrix(struct matrix *mat){
	int i = 0, j = 0;
	if(mat!=NULL){
		printf("\n");
		for(i = 0; i < mat->lines; i++){
			printf("|");
			for(j = 0; j < mat->columns; j++){
				printf("%.4lf|", returnValue(mat, i, j));
				//returnValue(mat, i, j);
			}	
			printf("\n");
		}
	}else{
		printf("Nao foi possivel usar printf");
	}
	
}

/*Retorna o valor de um elemento de uma matriz.*/
double returnValue(struct matrix *mat, int i, int j){
	if(mat != NULL){
		double result = 0;	
		int m, n, count = 0;
		for(m = 0; m < mat->lines; m++){
			for(n = 0; n < mat->columns; n++){
				if((i == mat->start->i)&&(j == mat->start->j)){
					result = mat->start->value;
					m = mat->lines+1;
					n = mat->columns+1;
				}else{
					mat->start++;
					count++;
				}
			}
		}
		mat->start = mat->start - count;
		return result;	
	}else{
		printf("Erro no endereco. i = %d, j = %d\n", i, j);
	}
	return 0;
}

/*Insere um valor em um elemento de uma matriz*/
void insertElement(struct matrix *mat, int i, int j, double val){
	if(mat != NULL){
		double result = 0;	
		int m, n, count = 0;
		for(m = 0; m < mat->lines; m++){
			for(n = 0; n < mat->columns; n++){
				if((i == mat->start->i)&&(j == mat->start->j)){
					mat->start->value = val;
					m = mat->lines+1;
					n = mat->columns+1;
				}else{
					mat->start++;
					count++;
				}
			}
		}
		mat->start = mat->start - count;	
	}else{
		printf("Erro no endereco");
	}
		
}

/*Calcula a determinante de uma matriz*/
double determinant(struct matrix *mat){
	if(mat != NULL && (mat->lines == mat->columns)){
		struct matrix *temp = createCopyMatrix(mat);
		double p = 1;
		int i, j, k, l = 0, c = 0;
		for(k = 0; k < mat->lines; k++){
			for(i = 0; i < mat->lines; i++){
				for(j = 0; j < mat->lines; j++){
					if(i!=l){
						insertElement(temp, i, j, ((returnValue(mat, l, c)*returnValue(mat, i, j)-returnValue(mat, c, j)*returnValue(mat, i, l))/p));
					}
				}
			}
			copyMatrix(mat, temp);
			p = returnValue(temp, l, c);
			l++;
			c++;
		}
		return p;
	}else{
		printf("Erro na funcao determinant\n");
		return 0;
	}
}

/*Cria uma copia de uma matriz fornecida*/
struct matrix *createCopyMatrix(struct matrix *mat){
	if(mat != NULL){
		struct matrix *copyMat = createMatrix(mat->lines, mat->columns);
		int i, j;
		for(i = 0; i < mat->lines; i++){
			for(j = 0; j < mat->columns; j++){
				insertElement(copyMat, i, j, returnValue(mat, i, j));
			}
		}
		return copyMat;	
	}else{
		printf("Matriz nula.\n");
		return NULL;
	}	
}

/*Copia os valores da matrizB para MatrizA*/
void copyMatrix(struct matrix *matA, struct matrix *matB){
	if(matA != NULL && matB != NULL && matA->lines == matB->lines && matA->columns == matB->columns){
		int i, j;
		for(i = 0; i < matB->lines; i++){
			for(j = 0; j < matB->columns; j++){
				insertElement(matA, i, j, returnValue(matB, i, j));
			}
		}	
	}else{
		printf("Erro na copyMatrix.\n");
	}
}

/*Imprime no console a matriz como um vetor*/
void printVector(struct matrix *mat){
	
	int i = 0;
	while(i < mat->lines*mat->columns){
		printf("Matriz[%d][%d] = %.5lf\n", mat->start->i, mat->start->j, mat->start->value);
		mat->start++;
		i++;
	}
	mat->start = mat->start - i;	
}	

