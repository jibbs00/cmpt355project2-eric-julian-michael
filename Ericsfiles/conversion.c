
#include <stdio.h>
#include <stdlib.h>

string conversion(int spot[]){
  int count=0, counter=0;
  const int size=8;
  if(spot[0]==0&&spot[1]==0)return "A1";
  if(spot[0]==0&&spot[1]==1)return "A2";
  if(spot[0]==0&&spot[1]==2)return "A3";
  if(spot[0]==0&&spot[1]==3)return "A4";
  if(spot[0]==0&&spot[1]==4)return "A5";
  if(spot[0]==0&&spot[1]==5)return "A6";
  if(spot[0]==0&&spot[1]==6)return "A7";
  if(spot[0]==0&&spot[1]==7)return "A8"

     if(spot[0]==1&&spot[1]==0)return "B1";
     if(spot[0]==1&&spot[1]==1)return "B2";
     if(spot[0]==1&&spot[1]==2)return "B3";
     if(spot[0]==1&&spot[1]==3)return "B4";
     if(spot[0]==1&&spot[1]==4)return "B5";
     if(spot[0]==1&&spot[1]==5)return "B6";
     if(spot[0]==1&&spot[1]==6)return "B7";
     if(spot[0]==1&&spot[1]==7)return "B8";

     if(spot[0]==2&&spot[2]==0)return "C1";
     if(spot[0]==2&&spot[2]==1)return "C2";
     if(spot[0]==2&&spot[2]==2)return "C3";
     if(spot[0]==2&&spot[2]==3)return "C4";
     if(spot[0]==2&&spot[2]==4)return "C5";
     if(spot[0]==2&&spot[2]==5)return "C6";
     if(spot[0]==2&&spot[2]==6)return "C7";
     if(spot[0]==2&&spot[2]==7)return "C8";

     if(spot[0]==3&&spot[1]==0)return "D1";
     if(spot[0]==3&&spot[1]==1)return "D2";
     if(spot[0]==3&&spot[1]==2)return "D3";
     if(spot[0]==3&&spot[1]==3)return "D4";
     if(spot[0]==3&&spot[1]==4)return "D5";
     if(spot[0]==3&&spot[1]==5)return "D6";
     if(spot[0]==3&&spot[1]==6)return "D7";
     if(spot[0]==3&&spot[1]==7)return "D8";

     if(spot[0]==4&&spot[2]==0)return "E1";
     if(spot[0]==4&&spot[2]==1)return "E2";
     if(spot[0]==4&&spot[2]==2)return "E3";
     if(spot[0]==4&&spot[2]==3)return "E4";
     if(spot[0]==4&&spot[2]==4)return "E5";
     if(spot[0]==4&&spot[2]==5)return "E6";
     if(spot[0]==4&&spot[2]==6)return "E7";
     if(spot[0]==4&&spot[2]==7)return "E8";

     if(spot[0]==5&&spot[1]==0)return "F1";
     if(spot[0]==5&&spot[1]==1)return "F2";
     if(spot[0]==5&&spot[1]==2)return "F3";
     if(spot[0]==5&&spot[1]==3)return "F4";
     if(spot[0]==5&&spot[1]==4)return "F5";
     if(spot[0]==5&&spot[1]==5)return "F6";
     if(spot[0]==5&&spot[1]==6)return "F7";
     if(spot[0]==5&&spot[1]==7)return "F8";

     if(spot[0]==6&&spot[2]==0)return "G1";
     if(spot[0]==6&&spot[2]==1)return "G2";
     if(spot[0]==6&&spot[2]==2)return "G3";
     if(spot[0]==6&&spot[2]==3)return "G4";
     if(spot[0]==6&&spot[2]==4)return "G5";
     if(spot[0]==6&&spot[2]==5)return "G6";
     if(spot[0]==6&&spot[2]==6)return "G7";
     if(spot[0]==6&&spot[2]==7)return "G8";

     if(spot[0]==7&&spot[1]==0)return "H1";
     if(spot[0]==7&&spot[1]==1)return "H2";
     if(spot[0]==7&&spot[1]==2)return "H3";
     if(spot[0]==7&&spot[1]==3)return "H4";
     if(spot[0]==7&&spot[1]==4)return "H5";
     if(spot[0]==7&&spot[1]==5)return "H6";
     if(spot[0]==7&&spot[1]==6)return "H7";
     if(spot[0]==7&&spot[1]==7)return "H8";

}
