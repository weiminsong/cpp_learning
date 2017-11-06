      
int main(){

      //char *data = new char[200];
      char data[100] = "00100100010010";
      // char is only for one character

      int offset = -1;
      int oneCount = 0;
      // Find string of 63*2 ones
      for(int i=0; data[i] != 0; i++) {
        data[i]=1;
        switch(data[i]) {
        case '0': oneCount = 0; break;
        case '1': oneCount ++; break;
        }
        if(oneCount == 126) {
          if(i<128) {
            offset = i + 1024-128;
          } else {
            offset = i - 128;
          }
          offset += 1;
        }
      }

        return 0;

}
