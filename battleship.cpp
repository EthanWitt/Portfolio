// Header Files
#include <iostream>
#include "ship.h"

using namespace std;

// Global Constants 
const int SIZE = 72;
const int MAX_STR_LEN = 25;
const int COL = 8;
const int ROW = 8;
const char BOARD_NULL = '~';
const char NULL_CHAR = '0';


// Function Prototypes
/*
input-user defined board size
output-none
process-calls all functions, direct or indirectly
*/
void menuProcess( ofstream &fout, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, ship temp,  int rows, int cols );

/*
input-none
output-the user's menuSelection
process-displays all choices and user responds
*/
char menuDisplay();

/*
input-user input
output-put the user prompted data in appropriate arrays
process-put the user prompted data in appropriate arrays, then assigns pointers
        to them
*/
void getInfo( ship &temp, int &index, int rows, int cols, int &startRow, int &startCol, int &startSize );

/*
input-array to be nullified
output-inserts a null at every point in the array
process-cycles thru and inserts a null in the array
*/
void nullArray2D( char * * bsPtr,  char * * bsHomePtr, char * bsColHomePtr, int rows, int cols, int &index );


/*
input-boardPtr, boardSizePtr, all the data from getInfo, menuSelection
output-true or false 
process-checks all spots for ship, direction, placement and returns true or false
        and possibly places object
*/
bool checkArray(  ship temp,  char menuSelection, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int &index, int rows, int cols, int startRow, int startCol, int startSize );


/*
input-boardPtr, boardSizePtr, all the data from getInfo, menuSelection
output-true or false
process- checks the direction and placement, returns true or false
*/
bool checkDir( ship temp, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int &index, int rows, int cols, char dir, int startRow, int startCol, int startSize);

/*
input-boardPtr, boardSizePtr, all the data from getInfo, menuSelection
output-places the object in array
process-places object in array after acquiring the proper positioning
*/
void placement( ship temp, char menuSelection, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int index, char dir, int startRow, int startCol, int startSize );

/*
input-getInfo data, boardSize
output-(to file) shipName, startRow, startCol, shipSize, boardSize, direction
process-cycles thru an array and outputs the data
*/
void outputFile( ofstream &fout, ship s1, ship s2, ship s3, ship s4, ship s5, int index, int rows, int cols );

/*
input-boardArrayPtr, gameBoardSize
output-displays the gameboard to screen
process-cycles thru array, displays at every instance except when * ptr == 0
*/
void displayBoard( char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int rows, int cols );

/*
input-error char array
output-(to screen) error message
process-outputs the whole array via ptrs.
*/
void errorMessage( const char * ePtr );


/*

input-the struct data, mainly we are looking at the direction
output-the char for the direction
process-changes uppercase letters to lowercase
*/
char lowercase( ship temp, int index );

/*

input-the class data, index
output-the temp that will do the grunt work
process-test for what number index is and set accordingly
*/
ship shipSet( int index, ship s1, ship s2, ship s3, ship s4, ship s5, const ship temp );

// Main Function
int main()
{
  // initialize variables
  ofstream fout;
  const char* prompt = "What would you like the gameboard size to be? ";


  char * * bsPtr;
  char * * bsHomePtr;
  char * bsColHomePtr;
  char dummyName[] = "name";
  char * dummyPtr = dummyName;
  char * null;
  null = '\0';
  int rows, cols, index, Size = 0, dummyInt = 4;
  ship temp;
  ship dummy( dummyPtr, dummyInt, dummyInt, dummyInt, dummyPtr);
  ship dummy2( dummy );

 
  // get gameboard size
    // get the rows
    cout << endl << endl << prompt;

    cin >> Size;

    // get the row & column size    
    rows = Size;
    cols = Size;

  // set the board size
  bsPtr = new char * [ rows ];
  bsHomePtr = bsPtr;

  for( index = 0; index < cols; index ++ )
  {
    *bsPtr = new char [ cols ];
    bsPtr ++;
  }
  
  // set bsPtr back to home
  bsPtr = bsHomePtr;
  bsColHomePtr = * bsPtr;
  

  // display menu/begin main ops
    // call menu process function
     menuProcess(fout, bsPtr, bsHomePtr, bsColHomePtr, temp, rows, cols );
 

  // deallocate the columns of the board pointer

   bsColHomePtr = NULL;

  for( index = 0; index < cols; index ++ )
  {
    delete[] * bsPtr;
    *bsPtr = NULL;
    // increment pointer
    bsPtr ++;
  } 

  // deallocate the pointer home
  delete[] bsHomePtr;
  bsHomePtr = NULL;
  bsPtr = NULL;


  // return zero
  return 0;
}

// Supporting Functions

void menuProcess( ofstream &fout, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, ship temp,  int rows, int cols )
{
  // initialize variables
  int index = 0;
  char menuSelection;
  const char * eI = "There are too many ships on the board.";
  int startRow, startCol, startSize;
  ship s1, s2, s3, s4, s5;
  
  // nullify the gameboard
  // function call: nullArray2D
  nullArray2D( bsPtr, bsHomePtr, bsColHomePtr, rows, cols, index );

  // display menu
  // start a do-while loop
  do
  {
    // function call: displayMenu
    // use response from displayMenu
    menuSelection = menuDisplay();

  // switch statement
  switch( menuSelection )
    {  
    case '1':
    case 'n':
    case 'N':
    // if 1 clear screen-menuSelection = 'N'
      menuSelection = 'N';

      // function call: nullArray2D
      nullArray2D( bsPtr, bsHomePtr, bsColHomePtr, rows, cols, index );
    break;

    case '2':
    case 'b':
    case 'B':
    // if 2 get battleship info-menuSelection = 'B'
      menuSelection = 'B';

      // functions call: getInfo, checkArray
      if( index < 5 )
       {
      getInfo( temp, index, rows, cols, startRow, startCol, startSize );
      shipSet( index, s1, s2, s3, s4, s5, temp );
      checkArray( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, startRow, startCol, startSize );        
       }
      else
       {
        errorMessage( eI );
       }
    break;

    case '3':
    case 'c':
    case 'C':
    // if 3 get carrier info-menuSelection = 'C'
      menuSelection = 'C';

      // functions call: getInfo, checkArray
      if( index < 5 )
       {
      getInfo( temp, index, rows, cols, startRow, startCol, startSize );
      shipSet( index, s1, s2, s3, s4, s5, temp );
      checkArray( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, startRow, startCol, startSize );        
       }
    break;

    case '4':
    case 'd':
    case 'D':
    // if 4 get destroyer info-menuSelection = 'D'
      menuSelection = 'D';

      // functions call: getInfo, checkArray
      if( index < 5 )
       {
      getInfo( temp, index, rows, cols, startRow, startCol, startSize );
      shipSet( index, s1, s2, s3, s4, s5, temp );
      checkArray( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, startRow, startCol, startSize );        
       }
    break;

    case '5':
    case 's':
    case 'S':
    // if 5 get sub info-menuSelection = 'S'
      menuSelection = 'S';

      // functions call: getInfo, checkArray
      if( index < 5 )
       {
      getInfo( temp, index, rows, cols, startRow, startCol, startSize );
      shipSet( index, s1, s2, s3, s4, s5, temp );
      checkArray( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, startRow, startCol, startSize );        
       }
    break;

    case '6':
    case 'u':
    case 'U':
    // if 6 get U-Boat info-menuSelection = 'U'
      menuSelection = 'U';

      // functions call: getInfo, checkArray
      if( index < 5 )
       {
      getInfo( temp, index, rows, cols, startRow, startCol, startSize );
      shipSet( index, s1, s2, s3, s4, s5, temp );
      checkArray( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, startRow, startCol, startSize );        
       }
    break;

    case '7':
    case 'f':
    case 'F':
    // if 7 get output to file-menuSelection = 'F' 
      menuSelection = 'F';

      // functions call: outputFile
      outputFile( fout, s1, s2, s3, s4, s5, index, rows, cols );
    break;

    case '8':
    case 'q':
    case 'Q':
  // if 8-menuSelection = 'Q'
    menuSelection = 'Q';
    break;

    case '9':
    displayBoard(bsPtr, bsHomePtr,bsColHomePtr, rows, cols );
    break;

    }
  }
// loop will end when menuSelection == 'Q'
  while( menuSelection != 'Q' );

}



char menuDisplay()
  {
	  // initialize variables 
	  char menuSelection;
	  int OptionNum = 9;
	  int index;
	  const char * menuOption1 = "Clear <G>ame Board";
	  const char * menuOption2 = "Enter <B>attleship Data";
	  const char * menuOption3 = "Enter <C>arrier Data";
	  const char * menuOption4 = "Enter <D>estroyer Data";
	  const char * menuOption5 = "Enter <S>ubmarine Data";
	  const char * menuOption6 = "Enter S<u>bmarine Data";
	  const char * menuOption7 = "Save <F>ile";
	  const char * menuOption8 = "Quit";
	  const char * selection = "Please enter selection letter: "; 
	  const char * * menuOpt = new const char * [ OptionNum ]; 
       const char * * menuHomePtr = menuOpt;
       const char * col;

       // assignment
	  * menuOpt = menuOption1;
	   menuOpt ++;
	  * menuOpt = menuOption2;
	   menuOpt ++;
	  * menuOpt = menuOption3;
	   menuOpt ++;
	  * menuOpt = menuOption4;
	   menuOpt ++;
	  * menuOpt = menuOption5;
	   menuOpt ++;
	  * menuOpt = menuOption6;
	   menuOpt ++;
	  * menuOpt = menuOption7;
	   menuOpt ++;
	  * menuOpt = menuOption8;
	   menuOpt ++;
	  * menuOpt = selection;

	  // display selections
	  cout << endl;
       menuOpt = menuHomePtr;
      for( index = 0; index < OptionNum - 1; index++)
       {
	  cout << *menuOpt << endl;
       menuOpt ++;
       }

	  cout << endl << endl << *menuOpt;

	  // get the selection the user wants 
	  cin >> menuSelection;

	  cout << endl;

       // deallocate
       menuOpt = menuHomePtr;    
       delete[] menuOpt;
       menuHomePtr = NULL; 
       menuOpt = NULL; 

	  // return the selection
	  return menuSelection;
  }



void getInfo( ship &temp, int &index, int rows, int cols, int &startRow, int &startCol, int &startSize )
  {

	// initialize variables
	char comma = ',';
	char space = ' ';
	int len, checkIndex;
	char * tempN;
	char * tempD;
	int tempRow, tempCol, tempSize;
    

	// create temporary pointers for the name and direction
	tempN = new char [ MAX_STR_LEN ];
	tempD = new char [ MAX_STR_LEN ];
	char * tempNHome = tempN;
	char * tempDHome = tempD; 
     startRow = 0;
     startCol = 0;
     startSize = 0;

	while( ( startRow < 1 || startRow > rows ||              startCol < 1 || startCol > cols || startSize < 1 ||  startSize > rows )  )
	  {

		 // prompt user for the ship type
		 cout << "Enter the ship type: ";
		 cin >> tempN;
		 cout << endl;

	    // prompt user for the starting row
		 cout << "Enter the starting row( > 0 ): ";
		 cin >> tempRow;
		 cout << endl;

	    // prompt user for the starting column 
		 cout << "Enter the starting column( > 0 ): ";
		 cin >> tempCol;
		 cout << endl;
	    
	    // prompt user for the ship size
		 cout << "Enter the ship size( > 0 ): ";
		 cin >> tempSize;
		 cout << endl;

	    // prompt the user for the direction of the ship
		 cout << "Enter the ship's direction <up, down, left, or right>: ";
		 cin >> tempD;
		 cout << endl << endl;

		 // get the length of the name
		 temp.setName( tempN );

		 // get the length of the direction
		 temp.setDir( tempD );

           temp.setRow( tempRow );
           startRow = temp.getRow();
           temp.setCol( tempCol );
           startCol = temp.getCol();
           temp.setSize( tempSize );
		 startSize = temp.getSize();

	  }
		 // increment
		 index ++;

	  // deallocate the temps
	  tempN = tempNHome;
	  delete[] tempNHome;
	  tempNHome = NULL;
	  tempN = NULL;
	  tempD = tempDHome;
	  delete[] tempDHome;
	  tempDHome = NULL;
	  tempD = NULL;

  }



void nullArray2D( char * * bsPtr,  char * * bsHomePtr, char * bsColHomePtr, int rows, int cols, int &index )
  {
	  // initialize variables
	  int rowIndex = 0, colIndex = 0;
	  char * colPtr;

	  // set points to home
	  bsPtr = bsHomePtr;
	  *bsPtr = bsColHomePtr;
	    colPtr = * bsPtr;

	  for(rowIndex = 0; rowIndex < rows; rowIndex ++ )
	  {
	    for( colIndex = 0; colIndex < cols; colIndex ++ )
	    {
	    // inserts a '~' at every spot

	    * colPtr = '~';
	    colPtr ++;

	    }
	    // increment
	    bsPtr ++;
	    colPtr = * bsPtr;
	  }

	  index = 0;
  }


bool checkArray(  ship temp, char menuSelection, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int &index, int rows, int cols, int startRow, int startCol, int startSize )
  {
	  // initialize variables
	  char dir;
	  const char * ePtr = "There is already a ship of that type on the board.";
	  int rowIndex = 0, colIndex = 0;
	  bool dirBool;
	  char * colPtr;

	  // set position
	  bsPtr = bsHomePtr;
	  *bsPtr = bsColHomePtr;
	  colPtr = * bsPtr;

	  // goes thru the array and checks to see if the menuSelection is already in array
	    // loop 
	  for(rowIndex = 0; rowIndex < rows; rowIndex ++ )
	    {
	    for(colIndex = 0; colIndex < cols; colIndex ++ )
		 {
		 if( *colPtr == menuSelection )
		   {
		   // return error
		   errorMessage( ePtr );
             index --;
		   return false;

		   }
		   // increment "columns"
		   colPtr ++;
		 }
	    // increment "rows"/reset "columns"

	    bsPtr ++;
	    colPtr = * bsPtr;
	    }

	  // reset position
	  bsPtr = bsHomePtr;
	 *bsPtr = bsColHomePtr;
 
	  dir = lowercase( temp, index );
	  // check if the direction and size keep the ship on the board 
	  // also check to see if there is a ship in the way for placement 
	    // function call: checkDir
	  dirBool = checkDir( temp, bsPtr, bsHomePtr, bsColHomePtr, index, rows, cols, dir, startRow, startCol, startSize );
	    if( dirBool == false )
	    {
           index --;
		 return false;
	    }

	  // if all good
	    // function call: placement
	  placement( temp, menuSelection, bsPtr, bsHomePtr, bsColHomePtr, index, dir, startRow, startCol, startSize);

	  displayBoard( bsPtr, bsHomePtr, bsColHomePtr, rows, cols );

	return true;
  }




bool checkDir( ship temp, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int &index, int rows, int cols, char dir, int startRow, int startCol, int startSize )
  { 
	  // initialize variables    
	  const char * eOOB = "This ship will fall off the edge of the earth, please place it somewhere else to prevent the loss of sailors.";
	  const char * eC = "COLLISION WARNING! Two ships will collide if you put the ship there. Have a nice day.";
	  int sizeIndex = 0, checkIndex, rowIndex, colIndex;
	  char * colPtr;
       char comma = ',';
  


	    for(rowIndex = 0; rowIndex < ( startRow -1 ); rowIndex ++ )
		   {
		     bsPtr ++;
		   }

	    colPtr = *bsPtr;

	    for( colIndex = 0; colIndex < ( startCol - 1 ); colIndex ++ )
		   {
		     colPtr ++;
		   }

		 // loop (up to the size of the ship)
	    for( sizeIndex = 0; sizeIndex < startSize; sizeIndex ++ )
		 {
	 
		  // check to see if there is anything in that spot in the array
            if( *colPtr != BOARD_NULL )
	        {
	         // if there is, report error of collision (eC)
		    cout << "Error at: " << rowIndex << comma << colIndex;
	         errorMessage( eC );
	         // return false
	         return false;
	        }

		  if( dir == 'u' )
		   {
		     // check to see if the ship stays on the board
		       if( ( ( startRow -1 ) - ( startSize -1 ) )< 0 )
		         {
		         // if it does not, report error of out-of-bounds (eOOB)
		         errorMessage( eOOB );
		         // return false
		     return false;
		         }
		     
		     // decrement the "row" of the array
		       bsPtr --;
			}

		     // case "down"
		    else if (dir == 'd')
		      {
		     // check to see if the ship stays on the board
		       if( ( ( startRow ) + ( startSize - 1 ) ) > rows )
		         {
		         // if it does not, report error of out-of-bounds (eOOB)
		         errorMessage( eOOB );

		         // return false

		     return false;
		         }
		     
		     // increment the "row" of the array
		        bsPtr ++;

		      }



		     // case "left"
		     else if ( dir == 'l')
			 {

		     // check to see if the ship stays on the board
		       if( ( ( startCol ) - ( startSize - 1 ) ) < 0 )
		         {
		         // if it does not, report error of out-of-bounds (eOOB)
		         errorMessage( eOOB );
		         // return false
		     return false;
		         }
		     
		     // decrement the "column" of the array
		       colPtr --;
			 }



		     // case "right"
			else
		      {
		     // check to see if the ship stays on the board
		       if( ( ( startCol ) + ( startSize ) ) > cols )
		         {
		         // if it does not, report error of out-of-bounds (eOOB)
		         errorMessage( eOOB );
		         // return false
		     return false;
		         }
		     
		     // increment the "column" of the array
		       colPtr ++;
			 }
		 }

   return true;
  }





void placement( ship temp, char menuSelection, char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int index, char dir, int startRow, int startCol, int startSize )
{
  // initialize variables
  int boardIndex = 0, sizeIndex = 0, checkIndex;
  char * colPtr;

  // reset the row and column pointers for the 2D array
  bsPtr = bsHomePtr;
 // *bsPtr = bsColHomePtr;


 
  // place the index at the proper row and column  

    for( sizeIndex = 0; sizeIndex < startRow - 1; sizeIndex ++)
        {
          bsPtr ++;
        }
         colPtr = *bsPtr;

    for( sizeIndex = 0; sizeIndex < startCol - 1; sizeIndex ++ )
        {
          colPtr ++;
        }



  // put the menuSelection in the array
  // loop
    *colPtr = menuSelection;
    cout << startSize << dir << endl;
    // cycle until index = shipSize
  for(boardIndex = 0; boardIndex < ( startSize -1 ); boardIndex ++ )
  {
   
    // determine direction
    switch( dir )
    {
      // if it is going up
      case 'u':
        // adjust the pointer of pointers to -1
        bsPtr --;
        colPtr = *bsPtr;
      for( sizeIndex = 0; sizeIndex < ( startCol - 1 ); sizeIndex ++ )
        {

         colPtr ++;
        }
    // insert menuSelection
	   *colPtr = menuSelection;


      break;

      // if it is going down
      case 'd':
        // adjust the pointer of pointers to +1
        bsPtr ++;
        colPtr = * bsPtr;
        for( sizeIndex = 0; sizeIndex < ( startCol - 1 ); sizeIndex ++ )
        {
          colPtr ++;
        }
        *colPtr = menuSelection;

      break;

      // if it is going left
      case 'l':
        // adjust the pointer of chars to -1
        colPtr --;
        *colPtr = menuSelection;
      break;

      // if it is going right
      case 'r': 
        // adjust the pointer of chars to +1
        colPtr ++;
        *colPtr = menuSelection;
      break;

    }

  }



}



void outputFile( ofstream &fout,  ship s1, ship s2, ship s3, ship s4, ship s5, int index, int rows, int cols )
  {
	  // initialize variables
	  char space = ' ';
	  char fileName[] = "outputFile.txt";
	  char board[] = "Game board size <row, col>: ";
	  char * bPtr = board;
	  int fileIndex;
	  char comma = ',';
	  char colon = ':';



	  // create a text file
	  fout.open( fileName );

	  // output the board size
	  fout << bPtr << colon << space << rows << comma << space << cols << endl;

	    // output the data thru the class, line by line
       switch( index )
        {
         case 1:
          s1.print(fout);
         break;
         
	    case 2:
       	s1.print(fout);
       	s2.print(fout);
         break;

         case 3:
      	s1.print(fout);
          s2.print(fout);
          s3.print(fout);
         break;

         case 4:
          s1.print(fout);
          s2.print(fout);
          s3.print(fout);
          s4.print(fout);
         break;

         case 5:
          s1.print(fout);
          s2.print(fout);
          s3.print(fout);
          s4.print(fout);
          s5.print(fout);
         break;

        }

	  // close text file
	  fout.close();
  }




void displayBoard( char * * bsPtr, char * * bsHomePtr, char * bsColHomePtr, int rows, int cols )
  {
	  // initialize variables
	  int rowIndex = 0, colIndex = 0, sizeIndex = 0;
	  char space = ' ', openPar = '(', closePar = ')', comma = ',';
	  char * colPtr;

	  bsPtr = bsHomePtr;
	  // loop thru and display the game board

	  colPtr = * bsPtr;
	  // loop thru array unitl !< rows
	  for( rowIndex = 0; rowIndex < rows; rowIndex ++ )
	  {

	    // loop thru array until !< cols
	    for( colIndex = 0; colIndex < cols; colIndex ++ )
	    { 
	    // display items in the array
	    cout << * colPtr << space;

	    // increment colIndex and the once-referenced battleship pointer pointing to the columns
	    colPtr ++;
	  
	    }
	    
	    // set columns back to home, increment bsPtr and rowIndex
	    cout << endl;

		     bsPtr ++;

	    colPtr = *bsPtr;
	    
	  }
	  cout << endl << endl;

  }



void errorMessage( const char * ePtr )
  {
	  // initialize variables
	    // none

	  // cout error
	  cout << ePtr << endl << endl;
  }




char lowercase( ship temp, int index )
  {
   // initialize variables
   char firstLetter;
   int checkIndex;

 firstLetter = temp.getDir();
 cout << temp.getDir() << endl;

   // if sPtr.Dir[0] < 97, + 32
   if( firstLetter < 'a' )
    {
     firstLetter + 32;
    }
   return firstLetter;
  }

ship shipSet( int index, ship s1, ship s2, ship s3, ship s4, ship s5, const ship temp )
  {
   // initialize variables

   // switch for setting the ship
   switch( index )
    {
   // set temp to s due to index
     case 1:
     s1 = temp;
     break;

     case 2:
     s2 = temp;
     break;

     case 3:
     s3 = temp;
     break;

     case 4:
     s4 = temp;
     break;

     case 5:
     s5 = temp;
     break;    
    }

   return temp;
  }

