
#pragma once

class DataGrabber {
public:

	float load, temp;
	string source;

	float readProcess(int x){
		ofBuffer buffer = ofBufferFromFile(source); // reading into the buffer

		string lastLine = "";
		do {
			lastLine = buffer.getNextLine();
		} while (!buffer.isLastLine());

		vector<string> tokens = ofSplitString(lastLine, ",", true);

		if (tokens.size() >= 11) {
			// this parces the last line into separate arrays
			load = ofToInt(tokens[5]);
			temp = ofToInt(tokens[10]);

			if (x == 0){
				return temp;
			}

			if (x == 1){
				return load;
			}
			//cout << "load = " << load;
			/*cout << " - temp  = " << temp << "\n";*/

		}
	}


	//----------------------------------------------
	void getSource(){
		int year = ofGetYear();
		int month = ofGetMonth();
		int day = ofGetDay();
		string monthO;
		string dayO;
		stringstream mm;
		stringstream dd;
		mm << month;
		mm >> monthO;
		dd << day;
		dd >> dayO;

		if (month < 10){
			monthO = "0" + monthO;
		}
		if (day < 10){
			dayO = "0" + dayO;
		}

		stringstream tt;
		tt << "OpenHardwareMonitorLog-2015-" << monthO << "-" << dayO << ".csv";
		source = tt.str();

	}
};
