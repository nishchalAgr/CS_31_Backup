#include <iostream>
#include <string>
#include <cctype>
#include <locale>

using namespace std;

bool isValidUppercaseStateCode(string stateCode);
string makeUpper(string pollData);
char makeUpper(char pollData);
bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);
int convertToInt(string numText);
int convertToDigit(char numC);

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
  const string codes =
      "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
      "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
      "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
  return (stateCode.size() == 2  &&
          stateCode.find('.') == string::npos  &&  // no '.' in stateCode
          codes.find(stateCode) != string::npos);  // match found
}

string makeUpper(string pollData){

  locale loc;
  string a = pollData;
  for(int i = 0; i < a.size(); i++){

    a[i] = toupper(a[i],loc);

  }

  return a;
}

char makeUpper(char pollData){

  locale loc;
  char a = pollData;

  a = toupper(a, loc);

  return a;

}
//below function checks the poll data for the following syntax:
//no spaces
//state codes in lower or upper uppercase
//number of seats followed by state codes
bool hasProperSyntax(string pollData){

  string upper = makeUpper(pollData);
  string stateCode = "AA";

  int stateCodeCounter = 0;
  int numCounter = 0;

  for(int i = 0; i < upper.size(); i++){

    if(stateCodeCounter == 2){//checks wheter the state code is valid

      if(!isValidUppercaseStateCode(stateCode)) return false;

    }

    if(upper[i] == ','){ //resets counters if runs into a comma

      if(stateCodeCounter != 2) return false;

      stateCodeCounter = 0;
      numCounter = 0;
      stateCode = "AA";

    }

    else if(isalpha(upper[i]) && numCounter == 0){ //checks if the letter is part of a state code
      //cerr << stateCodeCounter << endl;
      stateCode[stateCodeCounter] = upper[i];
      stateCodeCounter++;

    }

    if(isdigit(upper[i])) numCounter++;

    else if(!isdigit(upper[i]) && numCounter != 0){//checks if the letter is a party code

      if(isalpha(upper[i-1]) || isalpha(i+1)){//checks if party code is valid - the party code should should not have letters on either side

        return false;

      }

    }

    if(stateCodeCounter > 2){
      //cerr << 2 << endl;
      return false; //checks for state codes that are longer the 2
     }

     if(isdigit(upper[i])) numCounter++;

  }

  return true;

}

int convertToDigit(char numC){

  if(numC == '1') return 1;
  else if(numC == '2') return 2;
  else if(numC == '3') return 3;
  else if(numC == '4') return 4;
  else if(numC == '5') return 5;
  else if(numC == '6') return 6;
  else if(numC == '7') return 7;
  else if(numC == '8') return 8;
  else if(numC == '9') return 9;
  else if(numC == '0') return 0;


}

int convertToInt(string numText){

  int factor = 1;
  int num = 0;

  for(int i = 0; i < numText.size() - 1; i++){

    factor *= 10;

  }

  for(int i = 0; i < numText.size(); i++){

      num += convertToDigit(numText[i]) * factor;
      factor = factor / 10;

  }

  return num;

}

//returns 1 if pollData is not valid
//returns 2 if party is not valid
//returns 0 if neither occurs
int tallySeats(string pollData, char party, int& seatTally){

  string num;
  int ans = 0;

  if(!hasProperSyntax(pollData)) return 1;
  if(!isalpha(party)) return 2;

  party = makeUpper(party);
  pollData = makeUpper(pollData);

  for(int i = 0; i < pollData.size(); i++){

    if(pollData[i] == ','){
      num = "";

    }
    else if(isdigit(pollData[i])){

      num += pollData[i];

    }
    else if(i > 0 && !isalpha(pollData[i-1]) && !isalpha(pollData[i+1]) && isalpha(pollData[i])){

      if(pollData[i] == party){

        ans += convertToInt(num);

      }

      num = "";
    }

    //cout << "ans on loop" << i << " " << pollData[i] <<  ":" << ans << endl;

  }

  seatTally = ans;
  return 0;

}

int main(){

  if (hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"))
		cerr << "Passed test 1: hasProperSyntax('CT5D,NY9R17D1I,VT,ne3r00D')" << endl;

	if (!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"))
		cerr << "Passed test 2: !hasProperSyntax('ZT5D,NY9R17D1I,VT,ne3r00D')" << endl;

	int seats;
	seats = -999;    // so we can detect whether tallySeats sets seats
	if (tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22)
		cerr << "Passed test 3: tallySeats('CT5D,NY9R17D1I,VT,ne3r00D', 'd', seats)" << endl;
    //cout << "seats:" << seats << endl;

	seats = -999;    // so we can detect whether tallySeats sets seats
	if (tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999)
		cerr << "Passed test 4: tallySeats('CT5D,NY9R17D1I,VT,ne3r00D', '%', seats)" << endl;

}
