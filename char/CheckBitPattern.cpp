#include <iostream>
#include <vector>
#include <stdio.h>
// For debugging
bool printCounters = true;

/// Test bit string against pattern string
/**
 Pattern is sequence of chars with meanings as follows:
  0 - 0%
  S - Skip over many 0%
  1 - 100%
  I - ID (ignore)
  C - Chip/channel address
    - Skip
  { - Start repeat
  } - End repeat (skip back to start if following 0/1 doesn't match)
*/
bool checkPattern(const char *pattern, const char *bitString,
                  std::vector<int> &numbers) {
  int bitOffset = 0;
  int patternOffset = 0;

  // Where to repeat back to (in the pattern)
  int repeatOffset = 0;
  int repeats = 0;

  int counter = 0;

  char lastPattern = ' ';

  while(pattern[patternOffset] != 0 && bitString[bitOffset] != 0) {
    char pCh = pattern[patternOffset];
    char bCh = bitString[bitOffset];

    printf("Check '%c' with '%c' %d %d\n", bCh, pCh, bitOffset, patternOffset);

/*    if(bCh == 'x' && pCh != 'I') {
      printf("Compare x to '%c'\n", pCh);
    } */
    
    switch(pCh) {
    case '0':  // 0%
    case '1':  // 100%
      if(bCh == pCh) {
        bitOffset++;
        patternOffset++;
      } else {
        printf("Failed to find '%c' ('%c') at offset (patt: %d tst: %d)\n",
               pCh, bCh, patternOffset, bitOffset);
        return false;
      }
      break;
    case 'S':  // 0%
      while(bitString[bitOffset] == '0' && bitString[bitOffset] != 0) {
        bitOffset++;
      }
      patternOffset++;
      // printf("Skip to %d %d\n", bitOffset, patternOffset);
      break;
    case ' ':  // Skip, reset counter
      patternOffset++;

      if(lastPattern == 'C') {
        if(printCounters)
          printf("%d \n", counter);
        numbers.push_back(counter);
        counter = 0;
      }
      break;
    case 'I':  // ID, ignore
      patternOffset++;
      bitOffset++;
      break;

    case 'C':  // Counter (chip/channel)
      patternOffset++;
      bitOffset++;

      counter <<= 1;
      if(bCh == '1') {
        counter += 1;
      } else if(bCh != '0') {
        printf("Failed to find 0 or 1 in number %c at offset (patt: %d tst: %d)\n", bCh, patternOffset, bitOffset);
        return false;
      }

      break;

    case '{':  // Simple repetition
      // Remember where we are for jump back
      repeatOffset = patternOffset;

      patternOffset++;
      repeats ++;
      break;

    case '}':  // End repetition
      patternOffset++;
      // Split counters
      if(printCounters)
        printf("\n");
      switch(pattern[patternOffset]) {
      case '0':
      case '1':
        if(bCh == pattern[patternOffset]) {
          // Keep going
        } else {
          // Jump back to '{'
          patternOffset = repeatOffset;
        }
        break;
      default:
        printf("Unexpected char ('%c')after } in pattern\n", pattern[patternOffset]);
        return false;
      }
      break;

    default:
      printf("Unrecognised pattern character '%c'\n", pCh);
      return false;
    }

    lastPattern = pCh;
  }

  if(printCounters)
    printf("Matching complete, repeats %d\n", repeats);

  // printf("Matching complete %d %d\n", bitOffset, patternOffset);

  return true;
}

int main(){

    const char *abcForm = "{1     IIIII IIII CCCCCCCC CCCCCCCC IIIIIIII IIIIIIII IIIIIIII IIIIIIII IIS }0"; 
    char *str="10000101011111111111111111110100000000000000000000000000000000010010000101101111111111111000111100000000000000000000000000000000010010000101111111111111111001000000000000000000000000000000000000010010000110001111111111110011001100000000000000000000000000000000010010000110011111111111111000111100000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    std::vector<int> numbers;

    checkPattern(abcForm, str, numbers);
 
    for(size_t i=0; i<numbers.size(); i++) {
       std::cout<<numbers[i]<<std::endl;;
    }

}



