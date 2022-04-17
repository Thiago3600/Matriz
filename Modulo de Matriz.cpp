#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>



using namespace std;

struct cell;
struct matStruct;

class moduloMatriz{

		struct cell{
			int i;
			int j;
			double value;
			struct matStruct *started;
			struct cell *inicio;
		};

		struct matStruct{
			int lines;
			int columns;
			double determinant;
			bool det;
			struct cell *start;
		};

	private:
		struct matStruct *matriz = NULL;
		struct cell *celulas = NULL;
		struct cell *init = NULL;

		bool setProxEndCell(){
			if(true){
				this->matriz->start ++;
				return true;
			}else{
				return false;
			}
		}
		
		


		void setMatrixStart(int i){
			//printf("antes setMatrixStart %lf\n", matriz->start->value);
			this->matriz->start = matriz->start - i;
			//printf(" depois setMatrixStart %lf\n", matriz->start->value);
		}
		
		

		bool setDetermMatrix(){
			if(matriz != NULL){
				this->matriz->determinant = this->determinant();
				if(this->matriz->determinant == 0){
					this->matriz->det = false;
					return false;
				}else{
					this->matriz->det = true;
					return true;
				}
			}
			
			
		}
    public:
		double getDetermMatrix(){
			if(matriz != NULL){
				if(!this->matriz->det){
	                this->setDetermMatrix();
	            }else{
	            	return this->matriz->determinant;
				}	
			}else{
				printf("Matriz Null\n");
				return 0;
			}
            
		}
    private:

		bool setCellValue(double val){
			if(sizeof(val) == sizeof(double)){

				matriz->start->value = val;
				//printf("inserindo %lf\n", getCellVal());
				return true;
			}else{
				return false;
			}
		}

		bool verificaConfigEnder(int a){
			if((celulas != NULL) && (matriz != NULL) && (a >= 0)){
				return true;
			}else{
				return false;
			}
		}

		bool setCellLine(int i){
			if(verificaConfigEnder(i)){
				celulas->i = i;
				//printf("%d line cell\n", celulas->i);
				return true;
			}else{
				return false;
			}
		}
		bool setCellCol(int j){
			if(verificaConfigEnder(j)){
				celulas->j = j;
				return true;
			}else{
				return false;
			}
		}

		bool setMatrixLines(int i){
			if(verificaConfigEnder(i)){
				matriz->lines = i;
				return true;
			}else{
				return false;
			}
		}
		bool setMatrixCols(int j){
			if(verificaConfigEnder(j)){
				matriz->columns = j;
				return true;
			}else{
				return false;
			}
		}

		void clearMatrix(){
			if(matriz != NULL){
				free(matriz);
				matriz = NULL;
			}
			if(celulas != NULL){
				free(celulas);
				celulas = NULL;
			}
			if(init != NULL){
				free(init);
				init = NULL;
			}
		}


		double getCellVal(){
			return matriz->start->value;
		}
		int getCellLine(){
			if(verificaConfigEnder(matriz->start->i)){
				return matriz->start->i;

			}else{
				return -1;
			}
		}
		int getCellCol(){
			if(verificaConfigEnder(matriz->start->j)){
				return matriz->start->j;
			}else{
				return -1;
			}
		}

		int getMatrixLines(){
			if(verificaConfigEnder(matriz->lines)){
				return matriz->lines;
			}else{
				return -1;
			}
		}
		int getMatrixCols(){
			if(verificaConfigEnder(matriz->columns)){
				return matriz->columns;
			}else{
				return -1;
			}
		}

	public:

		/*Cria uma matriz de acordo com a dimensao fornecida pelas
			variaveis do tipo int e retorna uma nova matriz*/
		moduloMatriz(int i, int j){
			setlocale(LC_ALL, "portuguese");
			this->clearMatrix();
			matriz = (struct matStruct*) malloc(sizeof(struct matStruct));
			celulas = (struct cell*) malloc((i*j)*sizeof(struct cell));
			struct cell *address = celulas;				/* 8 */

			//celulas->started = matriz;
			if(setMatrixLines(i) && setMatrixCols(j)){
				matriz->start = celulas;
				int m, n;
				for(m = 0; m < i; m++){
					for(n = 0; n < j; n++){
						this->setCellLine(m);
						this->setCellCol(n);
						this->insertElement(m, n, 0);
						celulas->inicio = address;
						celulas++;
					}
				}
				celulas = matriz->start;
				this->matriz->det = false;
			}else{
				this->clearMatrix();
				free(address);
				printf("N�o foi possivel criar a matriz.\n");
			}
			
		}


		/*Insere valores a partir de um vetor, tendo que informar o tamanho do vetor
			e qual variavel matStruct.*/
		void insertValues(double vector[], int n){
			if(matriz != NULL){
				if(n == ((matriz->columns)*(matriz->lines))){
					int count = 0;
					while(count < n){
						matriz->start->value = vector[count];
						//printf("local = %d || Valor = %.0lf ", matriz->start, matriz->start->value);
						//printf("matriz->start->value = %.0lf == vector[%d] = %.0lf || n = %d\n", matriz->start->value, count, vector[count], n);
						matriz->start++;
						count++;
					}
					matriz->start = matriz->start - count;
					printf("Dados inseridos.\n");
				}else{
					printf("Vetores de tamanho diferentes\n");
				}
			}else{
				printf("Não existe matriz a exibir.\n");
			}

		}

		/*Insere um valor em um elemento de uma matriz*/
		bool insertElement(int i, int j, double val){
			if(matriz != NULL){
				double result = 0;
				int m, n, count = 0;
				for(m = 0; m < this->matriz->lines; m++){
					for(n = 0; n < this->matriz->columns; n++){
						if((i == this->matriz->start->i)&&(j == this->matriz->start->j)){
							this->matriz->start->value = val;
							this->matriz->start = this->matriz->start - count;
							return true;
						}else{
							this->matriz->start++;
							count++;
						}
					}
				}
				return false;
			}else{
				printf("Erro no endereco");
			}
		}

		/*Retorna o valor de um elemento de uma matriz.*/
		double returnValue(int i, int j){
			if(matriz != NULL){
				double result = 0;
				int m, n, count = 0;
				for(m = 0; m < getMatrixLines(); m++){
					for(n = 0; n < getMatrixCols(); n++){
						if((i == matriz->start->i)&&(j == matriz->start->j)){
							result = matriz->start->value;
							m = getMatrixLines()+1;
							n = getMatrixLines()+1;
						}else{
							matriz->start++;
							count++;
						}
					}
				}
				matriz->start = matriz->start - count;
				return result;
			}else{
				printf("Erro no endereco. i = %d, j = %d\n", i, j);
			}
		}
		/*Imprime no console a matriz.*/
		void printfMatrix(){
			if(this->matriz != NULL){
				int i = 0, j = 0;
				printf("\n");
				for(i = 0; i < this->getMatrixLines(); i++){
					printf("|");
					for(j = 0; j < this->getMatrixCols(); j++){
						printf("%.4lf|", this->returnValue(i, j));
					}
					printf("\n");
				}
			}else{
				printf("Nao foi possivel usar printf\n");
			}
		}
		/*Imprime no console a matriz como um vetor*/
		void printVector(){
			if(matriz != NULL){
				int i = 0;
				printf("\nImprimindo...\n");
				while(i < matriz->lines*matriz->columns){
					printf("Matriz[%d][%d] = %.0lf\n", matriz->start->i, matriz->start->j, matriz->start->value);
					matriz->start++;
					i++;
				}
				matriz->start = matriz->start - i;
			}else{
				printf("Erro na fun��o printVector, matriz nula.\n");
			}

		}
	private:
		/*Cria uma matriz de acordo com a dimensão fornecida pelas
			variaveis do tipo int e retorna uma nova matriz*/
		moduloMatriz *createMatrix(int i, int j){
			moduloMatriz *mat = new moduloMatriz(i, j);
			return mat;
		}

	public:
		/*Realiza a soma de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
		void sumMatrix(moduloMatriz *matA, moduloMatriz *matB){
			if(matA->matriz != NULL && matB->matriz != NULL){
				if((matA->getMatrixLines()) == (matB->getMatrixLines()) && (matA->getMatrixCols()) == (matB->getMatrixCols())){
					createMatrix(matA->getMatrixLines(), matA->getMatrixCols());
					int count = 0, i, j;
					for(i = 0; i < matA->getMatrixLines(); i++){
						for(j = 0; j < matA->getMatrixCols(); j++){
							insertElement(i, j, (matA->returnValue(i, j)+matB->returnValue(i, j)));
						}
					}
				}else{
					printf("Nao foi possivel realizar a operação\nMatrizes de tamanhos diferentes\n");
				}
			}else{
				if(matA->matriz != NULL){
					printf("Matriz A está nula.\n");
				}
				if(matB->matriz != NULL){
					printf("Matriz B está nula.\n");
				}

			}
		}
		/*Realiza a subtraçãp de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
		void minusMatrix(moduloMatriz *matA, moduloMatriz *matB){
			if(matA->matriz != NULL && matB->matriz != NULL){
				if((matA->getMatrixLines()) == (matB->getMatrixLines()) && (matA->getMatrixCols()) == (matB->getMatrixCols())){
					createMatrix(matA->getMatrixLines(), matA->getMatrixCols());
					int count = 0, i, j;
					for(i = 0; i < matA->getMatrixLines(); i++){
						for(j = 0; j < matA->getMatrixCols(); j++){
							insertElement(i, j, (matA->returnValue(i, j)-matB->returnValue(i, j)));
						}
					}
				}else{
					printf("Nao foi possivel realizar a operação\n");
				}
			}else{
				if(matA->matriz != NULL){
					printf("Matriz A está nula.\n");
				}
				if(matB->matriz != NULL){
					printf("Matriz B está nula.\n");
				}

			}
		}
		/*Copia os valores da matrizB para MatrizA vazia*/
		void copyMatrix(moduloMatriz *matA){
			if(matA != NULL){
				int i, j;
				for(i = 0; i < this->getMatrixLines(); i++){
					for(j = 0; j < this->getMatrixCols(); j++){
						this->insertElement(i, j, matA->returnValue( i, j));
					}
				}
				this->printfMatrix();
			}else{
				printf("Nao � possivel copiar matriz A.\n");
			}
		}
	private:
		/*Cria uma copia de uma matriz fornecida*/
		moduloMatriz *createCopyMatrix(){
			if(matriz != NULL){
				moduloMatriz *copyMat = new moduloMatriz(getMatrixLines(), getMatrixCols());
				int i, j;
				for(i = 0; i < getMatrixLines(); i++){
					for(j = 0; j < getMatrixCols(); j++){
						copyMat->insertElement(i, j, this->returnValue(i, j));
					}
				}
				return copyMat;
			}else{
				return NULL;
			}
		}
	public:
		/*Multiplica uma matriz por um valor*/
		void multiplyBy(double val){
			if(matriz != NULL){
				int i, j;
				for(i = 0; i < getMatrixLines(); i++){
					for(j = 0; j < getMatrixCols(); j++){
						insertElement(i, j, returnValue(i, j)*val);
					}
				}
			}else{
				printf("Erro multiplyBy: A matriz está vazia\n");
			}
		}
		/*Realiza a multiplicação de duas matrizes fornecidas pelo usuario, e retorna uma nova matriz*/
		void multMatrix(moduloMatriz *matA, moduloMatriz *matB){
			if(matA != NULL && matB != NULL){
				if( matA->getMatrixLines() == (matB->getMatrixCols())){
					createMatrix(matA->getMatrixLines(), matB->getMatrixCols());
					int i, j, k;
					for(i = 0; i < matA->getMatrixLines();i++){
						for(j = 0; j < matB->getMatrixCols(); j++){
							for(k = 0; k < matA->getMatrixCols(); k++){
								insertElement( j, i, (returnValue( j, i) + matA->returnValue( j, k)*matB->returnValue( k, i)));
							}
						}
					}
				}else{
					printf("As matrizes nao estao de acordo com a multiplicacao.\n");
					printf("Matriz A %dx%d.\n", matA->getMatrixLines(), matA->getMatrixCols());
					printf("Matriz B %dx%d.\n", matB->getMatrixCols(), matB->getMatrixCols());
				}
			}
		}
    private:
		/*Calcula a determinante de uma matriz*/
		double determinant(){
			if(matriz != NULL && (this->getMatrixLines() == this->getMatrixCols())){
				moduloMatriz *temp = this->createCopyMatrix();
				moduloMatriz *mat = this->createCopyMatrix();
				double p = 1;
				int i, j, k, l = 0, c = 0;
				for(k = 0; k < this->getMatrixLines(); k++){
					for(i = 0; i < this->getMatrixLines(); i++){
						for(j = 0; j < this->getMatrixLines(); j++){
							if(i!=l){
								temp->insertElement(i, j, ((this->returnValue(l, c)*this->returnValue(i, j)-this->returnValue(c, j)*this->returnValue(i, l))/p));
							}
						}
					}
					this->copyMatrix(temp);
					p = temp->returnValue( l, c);
					l++;
					c++;
					//delete temp;
				}
				this->copyMatrix(mat);
				return p;

			}else{
				printf("Erro na funcao determinant\n");
				return 0;
			}
		}
	public:
        /*Calcula a matriz inversa da matriz fornecida e retorna uma nova com o resultado*/
        void inverseMat(moduloMatriz *mat){
            if(mat != NULL && mat->getMatrixLines() == mat->getMatrixCols()){
				
                moduloMatriz *inverse = new moduloMatriz(mat->getMatrixLines(), mat->getMatrixCols()*2);
                moduloMatriz *temp = new moduloMatriz(mat->getMatrixLines(), mat->getMatrixCols()*2);

                double det = 1;
                int i, j, k, l = 0, c = 0;
                //temp->printfMatrix();
                temp->copyMatrix(mat);
                
	
                for(i=0; i<temp->getMatrixLines(); i++){
                    for(j = temp->getMatrixLines(); j<temp->getMatrixCols(); j++){
                        if(i==j-temp->getMatrixLines()){
                            temp->insertElement(i, j, 1);
                        }
                    }
                }
                printf("Pa antes");
                inverse->copyMatrix(temp);
				printf("Pa depois");
                for(k=0; k<temp->getMatrixLines(); k++){
                    for(i=0; i<temp->getMatrixLines(); i++){
                        for(j=0; j<temp->getMatrixCols(); j++){
                            if(i!=l){
                                //insertElement(inverse, i, j, (returnValue(temp, l, c)*returnValue(temp, i, j)-returnValue(temp, c, j)*returnValue(temp, i, l))/det);
                                inverse->insertElement(i, j, (temp->returnValue(l, c)*temp->returnValue(i, j)-temp->returnValue(c, j)*temp->returnValue(i, l))/det);
                            }
                        }
                    }
                    
                    temp->copyMatrix(inverse);
                    //copyMatrix(temp, inverse);
                    //det = returnValue(temp, l, c);
                    det = temp->returnValue(l, c);
                    l++;
                    c++;
                   
                }
                
                if(det==0){
                    printf("\nA matriz nao tem inversa a determinante = %i\n", det);
                }else{
                    //printVector(inverse);
                    this->createMatrix(mat->getMatrixLines(), mat->getMatrixCols());
                    for(i = 0; i < inverse->getMatrixLines(); i++){
                        for(j = 0; j < inverse->getMatrixCols(); j++){
                        	this->insertElement(i, j, inverse->returnValue( i, j + mat->getMatrixCols())/det);
                            //insertElement(temp, i, j, returnValue(inverse, i, j + mat->columns)/det);
                        }
                    }
                    
                    
                    printf("Apos delete\n");
                }
            }else{
            	printf("Erro na fun��o inverseMat\n");                
            }
        }


};
