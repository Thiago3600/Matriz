#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED


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
		struct cell *start;
	};


#endif
