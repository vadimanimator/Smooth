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
	
	
	cout << "working..." << endl;
	//smooth
	if (smoothArgument > 0) {
		double sum = 0;
		int tempCount = 0;
		for (int i = 0; i < sourceData.size() + smoothArgument; i++) {
			
			if (i < smoothArgument) {
				sum += sourceData[i];
			}
			else {
				if (i < sourceData.size()) {
					sum += sourceData[i];
				}
				if (tempCount > smoothArgument) {
					sum -= sourceData[i - (smoothArgument*2+1)];
				}
				//size wnd for this element
				int min = tempCount - smoothArgument > 0 ? tempCount - smoothArgument : 0;
				int max = tempCount + smoothArgument < sourceData.size() - 1 ? tempCount + smoothArgument : sourceData.size() - 1;
				
				copiedData.push_back(sum/(max - min + 1));
				tempCount++;
			}			
		}
	}
	else {
		cout << "Smooth argument is less than 0" << endl;
		return 0;
	}

	cout << "saving..." << endl;
	//save new data
	ofstream fout("output(" + filename + ").txt");

	for (int i = 0; i < copiedData.size(); i++) {
		if (i < copiedData.size() - 1)
			fout << copiedData[i] << endl;
		else 
			fout << copiedData[i];
	}
	
	fout.close(); 
	
	cout << "Smoothed data saved to \"output(" + filename + ").txt\"" << endl;

	return 0;
}