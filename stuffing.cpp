#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()

vector<string> byteSeq;

void bitStuffed(string& data)
{
    int cnt = 0;
    for (int i = 0; i < sz(data); i++){
        if (data[i] == '0'){        //reset the counter
            cnt = 0;
            continue;
        }
        ++cnt;
        if (cnt == 5){
            data.insert(i + 1, "0");
            cnt = 0;
        }
    }
}

void byteStuffed()
{
    int i = 0;
    while(i < sz(byteSeq)){
	string byte = byteSeq[i];
	if (byte == "7D" or byte == "7E"){
		byteSeq.insert(byteSeq.begin() + i, "7D");
		i += 2;
	}
	else i++;
    }
}

int main() 
{
    int choice; 
    cout << "1. Bit stuffing \n2. Byte stuffing\n\n";
    cout << "Enter your choice: "; cin >> choice;
    cin.ignore();
	
    string data;
    
    switch(choice){
        case 1: {
            cout << "\nEnter bit sequence: "; cin >> data;
            bitStuffed(data);
            cout << "Bit-stuffed data: " << data << endl;	
	    	break;
		}	
        
        case 2: {
            cout << "\nEnter space-separated byte sequence: ";
            getline(cin, data);
		    string byte;
		    for (char c: data){
		        if (c == ' ') {
			    byteSeq.push_back(byte);
			    byte.clear();	
			}
			else byte += c;
		    }
		    byteSeq.push_back(byte);
	            
		    byteStuffed();
	            cout << "Byte-stuffed data: ";
	            for (string s: byteSeq) cout << s << ' ';
	            cout << endl;
		    break;
		}
    	
        default: cout << "Invalid input!";
    }
    return 0;
}