#include <iostream>
#include <cstring>
 
using namespace std;

struct{
    int regs[128]={0};
} ABC130Chip;

int st_configure_abc130_chip_variable (float var ){

   int intVar = int(var+0.5) ;
   ABC130Chip.regs[0x20] &= ~0x00001f00;
   //ABC130Chip.regs[0x20] = ~0x00001f00;
   ABC130Chip.regs[0x20] |= ((intVar & 0x1f) << 8);

} 	
 
int main() {
   st_configure_abc130_chip_variable(31);
   cout<<ABC130Chip.regs[0x20]<<endl;
   return 0;
}
