#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Patient {
    string name;
    string type;
    int pr;
};
struct Reading {
    int HDL;
    int LDL;
    float ratio;
    int Systolic;
    int Diastolic;
};

Patient createNew(string str){
    Patient current;
    int values_stored = 0;
    int last_space = 0;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' ' && values_stored == 0){
            int len = i - last_space;
            current.name = str.substr(last_space,i);
            last_space = i+1;
            values_stored++;
        }
        else if(str[i] == ' ' && values_stored == 1){
            int len = i - last_space;
            current.type = str.substr(last_space,len);
            last_space = i+1;
            values_stored++;
        }
        else if(i == (str.length()-1)){
            string num = str.substr(last_space,i);
            current.pr = stoi(num);
        }
    }
    return current;
}

Reading storeReadings(string str){
    int lastSpace = 0;
    int values_stored = 0;
    Reading curr_reading;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' ' && values_stored == 0){
            int len = i - lastSpace;
            string HDL = str.substr(lastSpace,len);
            curr_reading.HDL = stoi(HDL);
            values_stored++;
            lastSpace = i+1;
        }
        else if(str[i] == ' ' && values_stored == 1){
            int len = i - lastSpace;
            string LDL = str.substr(lastSpace,len);
            curr_reading.LDL = stoi(LDL);
            values_stored++;
            lastSpace = i+1;
        }
        else if(str[i] == ' ' && values_stored == 2){
            int len = i - lastSpace;
            string Systolic = str.substr(lastSpace,len);
            curr_reading.Systolic = stoi(Systolic);
            values_stored++;
            lastSpace = i+1;
        }
        else if(i == (str.length())-1){
            string Diastolic = str.substr(lastSpace,i);
            curr_reading.Diastolic = stoi(Diastolic);
        }
    }
    curr_reading.ratio = (float) curr_reading.HDL/curr_reading.LDL;
    return curr_reading;
}

void evaluate_cholesterol(Reading curr){
    cout << "Cholesterol Profile" << endl;
    cout << "\t" << "HDL: " << curr.HDL << " LDL: " << curr.LDL << endl;
    cout << "\t" << "Ratio: " << setprecision(4) << curr.ratio << endl;
    string HDL_string;
    string LDL_string;
    if(curr.HDL < 40){HDL_string = "Too low";}
    else if (40 <= curr.HDL < 60){HDL_string = "Okay";}
    else if (curr.HDL >= 60){HDL_string = "Excellent";}
    else{HDL_string = "invalid";}
    cout << "\t" << "HDL is " << HDL_string << endl;
    if(curr.LDL < 100){LDL_string = "Optimal";}
    else if (100 <= curr.LDL < 130){LDL_string = "Near Optimal";}
    else if (130 <= curr.LDL < 160){LDL_string = "Borderline High";}
    else if (160 <= curr.LDL < 190){LDL_string = "High";}
    else if (curr.LDL >= 190){LDL_string = "Very High";}
    else{LDL_string = "invalid";}
    cout << "\t" << "LDL is " << LDL_string << endl;
    string ratio_string;
    if(curr.ratio < 0.3){ratio_string = "is good";}
    else if(curr.ratio >= 0.3){ratio_string = "is not good";}
    else{ratio_string = "invalid";}
    cout << "\t" << "Ratio of HDL to LDL " << ratio_string << endl;
}
void evaluate_blood_pressure(Reading curr){
    cout << "Blood Pressure Profile" << endl;
    cout << "\t" << "Systolic: " << curr.Systolic << " Diastolic: " << curr.Diastolic << endl;
    string systolic_str;
    string diastolic_str;
    if(curr.Systolic < 120) {systolic_str = "Optimal";}
    else if(120 <= curr.Systolic < 130) {systolic_str = "Normal";}
    else if(130 <= curr.Systolic < 140) {systolic_str = "Normal high";}
    else if(140 <= curr.Systolic < 160) {systolic_str = "Stage 1 hypertension";}
    else if(160 <= curr.Systolic < 180) {systolic_str = "Stage 2 hypetension";}
    else if(curr.Systolic >= 180) {systolic_str = "Stage 3 hypertension";}
    else{systolic_str = "invalid";}
    if(curr.Diastolic < 80){diastolic_str = "Optimal";}
    else if(80 <= curr.Diastolic < 85){diastolic_str = "Normal";}
    else if(85 <= curr.Diastolic < 90){diastolic_str = "Normal high";}
    else if(90 <= curr.Diastolic < 100){diastolic_str = "Stage 1 hypertension";}
    else if(100 <= curr.Diastolic < 110){diastolic_str = "Stage 2 hypertension";}
    else if(curr.Diastolic >= 110){diastolic_str = "Stage 3 hypertension";}
    else{diastolic_str = "invalid";}
    cout << "\t" << "Systolic reading is " << systolic_str << endl;
    cout << "\t" << "Diastolic reading is " << diastolic_str << endl;
}

int main ()
{
    string file_path = "infile.txt";
    fstream file;
    file.open(file_path);
    int patients;
    cout << "Enter the number of patient records: ";
    cin >> patients;
    cout << "\n" << endl;
    string curr_name = "";
    string curr_line;
    int read = 0;
    while (read < patients){
        getline(file,curr_line);
        Patient current_patient = createNew(curr_line);
        cout << "Current Patient's Name- " <<current_patient.name << endl;
        int readings = 0;
        string line;
        while(readings < current_patient.pr){
            getline(file,line);
            cout << "\n" << "DATA SET " << to_string(readings + 1) << endl;
            Reading curr = storeReadings(line);
            evaluate_cholesterol(curr);
            evaluate_blood_pressure(curr);
            readings++;
        }
        read++;
    }
    return 0;
}
