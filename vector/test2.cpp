#include <iostream>
using std::cout;
using std::endl;

#include <vector>    // vector class-template definition
#include <algorithm> // copy algorithm
#include <iterator>  // ostream_iterator iterator
#include <stdexcept> // out_of_range exception

int main()
{
   int array[ 6 ] = { 1, 2, 3, 4, 5, 6 };
   std::vector< int > integers( array, array + 6 );
   std::ostream_iterator< int > output( cout, " " );

   integers.push_back( 2 );
   integers.push_back( 3 );
   integers.push_back( 4 );

   cout << "Vector integers contains: ";
   std::copy( integers.begin(), integers.end(), output );// I do not quite understand the iterator
   cout << "\nLast element of integers: " << integers.back();

   return 0;
}
