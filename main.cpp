#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstring>
#include"MeshSimplifier.h"

int main(int argc, char** argv)
{
	if (argc < 5)
	{
		cout << "ERROR" << endl;
		cout << "Please input: [input filename] [output filename] [alpha] [adjust]" << endl;
		return 0;
	}
	time_t start, end;
	start = clock();
	cout << "start " << start << endl;
	string in = argv[1];
	string out = argv[2];
	double alpha = atof(argv[3]);
	double adjust = atof(argv[4]);
	MeshSimplifier simplifier;
	simplifier.readin(in);
	time_t readin = clock();
	cout << "input time:" << (double)(readin - start) / CLOCKS_PER_SEC << "sec" << endl;
	simplifier.run(alpha);
	time_t run = clock();
	cout << "run time:" << (double)(run - start) / CLOCKS_PER_SEC << "sec" << endl;
	
	simplifier.output(out);
	time_t output = clock();
	cout << "output time:" << (double)(output - start) / CLOCKS_PER_SEC << "sec" << endl;
	system("pause");
	return 0;
}
