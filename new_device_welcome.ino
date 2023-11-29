/*
This program is for new lab devices. It prints out a customizable message to serial.

Customize the device for the event and team by changing guestOrg and teamNumber.

The script output looks like this:

      _   __                     ____    ______  
     / | / /___  _____________  /  _/___/_  __/  
    /  |/ / __ \/ ___/ ___/ _ \ / // __ \/ /     
   / /|  / /_/ / /  (__  )  __// // /_/ / /      
  /_/ |_/\____/_/  /____/\___/___/\____/_/       
                     and the  
             College of Informatics  
        welcomes iLead - Team 001 to NKU!  
+-------------------------------------------------+
*/

#include <Arduino.h>

String guestOrg = "iLead";
String teamNumber = "001";

// Separate each line with a \n. 
String inputMessage = "and the\nCollege of Informatics\nwelcome " + guestOrg + " - Team " + teamNumber + " to NKU!";

#define SERIAL_BAUD 115200 // 115200 is the NorseIoT club standard

void centerAndPrintLine(String line, int maxLength) {
  int lineLength = line.length();
  int padding = (maxLength - lineLength) / 2;

  // Center the line and print it
  for (int j = 0; j < padding; j++) {
    Serial.print(" ");
  }
  Serial.print("  "); // Two extra spaces on the left
  Serial.print(line);
  Serial.print("  "); // Two extra spaces on the right
  Serial.println();
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();

  // Add a return character to the end of inputMessage
  inputMessage += "\n";

  // Calculate the maximum length for ASCII art
  int maxArtLength = 0;


  /* If the ASCII art contains a backslash, it must be escaped with a backslash!
  Each line of the ASCII art should be a separate element in the array.
  This program correctly handles larger or smaller ASCII artwork */
  String asciiArt[] = {
    "    _   __                     ____    ______",
    "   / | / /___  _____________  /  _/___/_  __/",
    "  /  |/ / __ \\/ ___/ ___/ _ \\ / // __ \\/ /   ",
    " / /|  / /_/ / /  (__  )  __// // /_/ / /    ",
    "/_/ |_/\\____/_/  /____/\\___/___/\\____/_/     "
  };

  // Calculate the maximum length for ASCII art
  for (int i = 0; i < sizeof(asciiArt) / sizeof(asciiArt[0]); i++) {
    int lineLength = asciiArt[i].length();
    if (lineLength > maxArtLength) {
      maxArtLength = lineLength;
    }
  }

  int totalLines = 0; // Count the total number of lines in inputMessage
  int maxMessageLength = 0;
  int startIndex = 0;

  for (int i = 0; i < inputMessage.length(); i++) {
    if (inputMessage.charAt(i) == '\n' || i == inputMessage.length() - 1) {
      totalLines++; // Increment the total line count
      String line = inputMessage.substring(startIndex, i);
      int currentLength = line.length();
      if (currentLength > maxMessageLength) {
        maxMessageLength = currentLength;
      }
      startIndex = i + 1;
    }
  }

  // Calculate the total width for centering (the wider of the two)
  int totalWidth = max(maxArtLength, maxMessageLength);

  // Output centered ASCII art
  for (int i = 0; i < sizeof(asciiArt) / sizeof(asciiArt[0]); i++) {
    centerAndPrintLine(asciiArt[i], totalWidth);
  }

  // Output centered inputMessage
  startIndex = 0;
  for (int i = 0; i < totalLines; i++) {
    int endIndex = inputMessage.indexOf('\n', startIndex);
    String line = inputMessage.substring(startIndex, endIndex); // Extract each line
    centerAndPrintLine(line, totalWidth);
    startIndex = endIndex + 1;
  }

  // Print a line of dashes of the same width as the total width
  Serial.print("+");
  for (int j = 0; j < totalWidth + 4; j++) { // Add 4 extra spaces
    Serial.print("-");
  }
  Serial.println("+");
}

void loop() {
  // Your loop code (if any) goes here
}
