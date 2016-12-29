#include <iostream>
#include <fstream>
#include <cassert>
//#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

FILE * in, *out, *dc;
char buff[100000000];
char buff2[100000000];
int buff3[100000000];
char buff4[100000000];

int getnum(int start, int len) {
	int res = 0, mn = 1;
	for (int i = start; i<start + len; ++i) {
		res += (unsigned char)buff[i] * mn;
		mn *= 256;
	}
	return res;
}

int sample, sampleDC, size, size2;
int a, b;

int main() {

	FILE * f = fopen("440_square.wav", "r+"); fseek(f, 0, SEEK_END); assert(f); size = ftell(f); fclose(f);
	ifstream in("440_square.wav", ios::in | ios::binary);		//input file
	in.read(buff, size);										//reading input parameters
	sample = getnum(24, 4);										//the number of samples per second input file
	printf("Czestotliwosc probkowania pliku wejsciowego (probki/sekunde): %d \n", sample);

	for (int c = 0; c < 100000000; c++)
	{
		buff2[c] = buff[c];										//duplication buffer
	}

	for (int s = 0; s < 100000000; s++)
	{
		buff[s] = 0;											//cleaning buffer
	}

	FILE * DC = fopen("DC-6dBFS-3s.wav", "r+"); fseek(DC, 0, SEEK_END); assert(DC); size2 = ftell(DC); fclose(DC);
	ifstream dc("DC-6dBFS-3s.wav", ios::in | ios::binary);		//input DC file
	dc.read(buff, size2);										//reading input DC parameters
	sampleDC = getnum(24, 4);									//the number of samples per second DC file
	printf("Czestotliwosc probkowania pliku wejsciowego DC(probki/sekunde): %d \n", sampleDC);


	if (sample == sampleDC)
	{

		printf("\n\nPlik wejsciowy: \n\n");


		for (b = 0; b < 1000; b++)
		{
			printf("%d,", buff2[b]);							//print few value of input file to prove proper job
		}
		printf("\n\nPlik DC: \n\n");


		for (a = 0; a < 1000; a++)								//print few value of input DC file to prove proper job
		{

			printf("%d,", buff[a]);

		}

		printf("\n\nPlik koncowy: \n\n");

		for (int i = 0; i < 100000000; i++)
		{
			buff3[i] = (int)buff2[i] + (int)buff[i];			//adding buffer parameters and generate shift
		}

		for (int i = 0; i < 1000; i++)
		{
			printf("%d,", buff3[i]);							//print few value of output file to prove proper job
		}
		
		for (int k = 0; k < 100000000; k++)
		{
			//buff3[k] +"0"; 								//retrieve the integer value from the array to char array
			buff4[k] = (char)buff3[k];						//but it doesn't work :(

			//	buff4[k] = buff3[k] & 0xff;
			//_itoa(buff3[k], buff4[k], 10);
		}

		printf(" \n");
		printf(" \n\nCzy to samo po zamianie na char\n\n");

		for (int i = 0; i < 1000; i++)
		{
			printf("%d,", buff4[i]);							//print few value of output file to prove proper job
		}
		printf(" \n");
	}

	else
	{
		printf("\n\nZle dobrana czestotliwosc probkowania\n\n");
	}

	ofstream out("out.wav", ios::out | ios::binary);			//output file

	out.write(buff4, size);										//generate output file
	dc.close();													//closing DC file
	in.close();													//closing input file
	out.close();												//closing output file

	system("pause");											//waiting for pressing button 
	return 0;
}

/*
Program takes input file and the input DC file combines them and generates output file.
Program doing proper job when quantity of samples per second is to same for input file and input DC file.
Program shows the sample values DC,sample values input file and output file.
The folder contains the files to testing applications.
Program with signal-441000.wav file, 440_square.wav file and with sin_440Hz_44100.wav doing a proper job.
Progam with piano-46000.wav file don't doing a proper job becouse that file have 46000 samples per second and DC file have 44100 samples per second.
*/