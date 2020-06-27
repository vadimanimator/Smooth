#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

string filename = "";
int smoothArgument = 0;
vector <double> sourceData;
vector <double> copiedData;

int main(int argc, char** argv) {

	if (argc != 3) {
		cout << "Example: programm file.txt 10" << endl;
		return 0;
	}
	else {
		filename = argv[1];
		smoothArgument = atoi(argv[2]);
	}
	
	cout << "reading..." << endl;
	//read data
	std::ifstream file(filename);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			sourceData.push_back(stof(line));
		}
		file.close();
	}
	else {
		cout << "File " << filename << " not found" << endl;
		return 0;
	}
	
	copiedData = sourceData;
	
	cout << "working..." << endl;
	//smooth
	if (smoothArgument > 0) {
		for (int i = 0; i < copiedData.size(); i++) {
			int min = i - smoothArgument > 0 ? i - smoothArgument : 0;
			int max = i + smoothArgument < copiedData.size() - 1 ? i + smoothArgument : copiedData.size() - 1;
			double sum = 0;
			for (int j = min; j <= max; j++) {
				sum += copiedData[j];
			}
			sourceData[i] = sum / (max - min + 1);
		}
	}
	cout << "saving..." << endl;
	//save new data
	ofstream fout("output(" + filename + ").txt"); 

	for (int i = 0; i < sourceData.size(); i++) {
		if (i < sourceData.size() - 1)
			fout << sourceData[i] << endl;
		else 
			fout << sourceData[i];
	}
	
	fout.close(); 
	
	cout << "Smoothed data saved to \"output(" + filename + ").txt\"" << endl;

	return 0;
}