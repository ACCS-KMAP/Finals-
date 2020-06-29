//libs
#include <SPI.h>
#include <SD.h>

//SD vars
File myFile;

//parse data vals
int dataarr[60] = {};     //array of parsed data
int arrpointer = 0;       //array pointer
int column = 4;           //column to parse
int columncount = 1;      //start at column 1 not 0
int rowincrement = 2;     //increment the number of parse rows - set to 1 for all rows
int rowcount = 1;         //start at row 1 not 0
String datatemp;          //temp to store datapoint

void setup(){

  Serial.begin(9600);
  
  //test SD - change the pin number
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  //Read file
  myFile = SD.open("data.csv");
  
  if(myFile) {
    
    Serial.println();
    
    while (myFile.available()) {
      
      int filedata = myFile.read();
      
      //////////////
      // parse  
      //////////////

      //read data vals into string
      if((filedata != ',')&&(filedata != ' ')){
        
        //test for row increment
        if(rowcount % rowincrement == 0){

          //look for column
           if(columncount == column){
             
             //push datapoint to array  
             Serial.print("*");  
             datatemp = datatemp += (filedata -'0');
             dataarr[arrpointer] = datatemp.toInt();

           }
      
        }
         
      }
      
      Serial.write(filedata);
      
     //end of datapoint
      if (filedata == ','){
         columncount++;  
      }

      //end of row
      if (filedata == '\n'){
        
        //print data temp at end of line
        Serial.write(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        Serial.print(datatemp.toInt());
        Serial.println();
        
        //reset vars to read next row
        rowcount++; 
        columncount = 1; 
        datatemp = "";
        //arrpointer++;  
 
      }
      
      //////////////
      // end parse  
      //////////////

    }
  }
  
  Serial.println();
  Serial.println();
  Serial.println("--------------------------");
      
  //cycle through data array
  for(int i = 0; i < arrpointer; i++){ 
    Serial.print("Selected Data >>>>>>> ");
    Serial.println(dataarr[i]);
    Serial.print(", ");
  }
  
  myFile.close();
  
}

void loop()
{
  
}
