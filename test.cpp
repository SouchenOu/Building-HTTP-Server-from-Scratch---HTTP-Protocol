
Content-Disposition: form-data; name="image"; filename="test.cpp"
Content-Type: application/octet-stream

#include <fstream>
#include <iostream>

// int main()
// {
//     // Open a new file for input/output operations discarding any current
//     // content in the file (assumes a length of zero on opening)
//     std::fstream myFile("test.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
//     // Add the characters "Hello World" to the file
//     myFile << "Hello World hgjkfghfjhgkghkhfjkfhjlfhkhfjjhklhjf";
    
//     // Seek to 6 characters from the beginning of the file
//     //myFile.seekg(6, std::ios::cur);
    
//     // Read the next 5 characters from the file into a buffer
//     char buffer[6];
//     myFile.read(buffer, 5);
    
//     // End the buffer with a null terminating character
//     //buffer[5] = 0;
    
//     // Output the contents read from the file and close it 
//     std::cout << "buffer->" << buffer << std::endl;
    
//     myFile.close();
// }

#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::string line;

    // Creates a new ifstream object and associates it with a file passed in via the parameters.
    // The object is then checked to see if the end-of-file has been reached, if the file has data
    // then this will be false.
    std::fstream myFile("test2.txt", std::ios::in | std::ios::out | std::ios::trunc);
    myFile << "Hello World hgjkfghfjhgkghkhfjkfhjlfhkhfjjhklhjf";
    std::cout << myFile.eof() << std::endl;
    
    // Continuously loops over each line of the file until the end of the file
    while (!myFile.eof()) {
        std::getline(myFile, line);
    }    
    
    // Again outputs the end-of-file status for the stream, this time the answer will be true
    std::cout << myFile.eof() << std::endl;
    
    // Seeks to the very beginning of the file, clearing any fail bits first (such as the end-of-file bit)
    myFile.clear();
    myFile.seekg(0, std::ios::beg);
    
    // Outputs the status of the stream again, the result will be false
    std::cout << myFile.eof() << std::endl;
    
    myFile.close();
}





// #include <iostream>
// #include <fstream>
// using namespace std;
// int main () 
// {
//   fstream obj;
//   obj.open ("test.txt", ios::in);
//   char ch;
//   int pos;
//   while(!obj.eof())
//   {
//     obj>>ch;
//     pos = obj.tellg();
//     cout<<pos<<"."<<ch<<"\n";
//   }
//   obj.close();
// }



// Let us see it line by line:

// obj.open (“test.txt”, ios::in);
// Here we are opening a text file called test with main purpose to read.
// I already have “Hello World” written in the test file.
// char ch;
// int pos;
// We are defining 2 variables: “ch” of type char to read each character, and “pos” of type into to get the position of the get pointer.
// while(!obj.eof())

// {

// obj>>ch;

// pos = obj.tellg();

// cout<<pos<<"."<<ch<<"\n";

// }
// So this is the basic code to read a file.
// Here we are using pos=obj.tellg() to get the pointer value of character being read.
// Finally, we are printing the position and the character each on a separate line.

// obj.close();
// And finally, we are closing the text file we opened.
// Hence the output would be:

// 1.H    
// 2.e   
// 3.l 
// 4.l  
// 5.o 
// 7.W  
// 8.o  
// 9.r 
// 10.l 
// 11.d


/*****



------WebKitFormBoundarybgQhkojX1vgcKD7Q--



/