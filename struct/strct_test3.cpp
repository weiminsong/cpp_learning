#include <iostream>
#include <cstring>
 
using namespace std;

void printBook( struct Books book );
void printBook2( struct Books *book );

struct Books {
   char title[50]="aaa";
   char author[50]="bbb";
   char subject[100]="ccc";
   int   book_id;
};
 
int main() {
   struct Books Book1;        // Declare Book1 of type Book
   struct Books Book2;        // Declare Book2 of type Book
 
   // book 1 specification
   // strcpy( Book1.title, "Learn C++ Programming");
   // strcpy( Book1.author, "Chand Miyan"); 
   // strcpy( Book1.subject, "C++ Programming");
   Book1.book_id = 6495407;

   // Print Book1 info
   printBook( Book1 );


   // Print Book1 info, passing address of structure
   printBook2( &Book1 );


   return 0;
}
void printBook( struct Books book ) {
   cout << "Book title : " << book.title <<endl;
   cout << "Book author : " << book.author <<endl;
   cout << "Book subject : " << book.subject <<endl;
   cout << "Book id : " << book.book_id <<endl;
}
// This function accept pointer to structure as parameter.
void printBook2( struct Books *book ) {
   cout << "Book title : " << book->title <<endl;
   cout << "Book author : " << book->author <<endl;
   cout << "Book subject : " << book->subject <<endl;
   cout << "Book id : " << book->book_id <<endl;
}
