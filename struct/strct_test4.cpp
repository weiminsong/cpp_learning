#include <iostream>
#include <cstring>
 
using namespace std;

typedef struct {
    int regs[128];
} ABC130Chip;

enum {
  ABC130_REG_CFG0 = 0x20,
};

int st_configure_abc130_chip_variable (float var ){

int intVar = int(var+0.5) ;
ABC130Chip * config;
   config->regs[ABC130_REG_CFG0] &= ~0x00001f00;
   config->regs[ABC130_REG_CFG0] |= ((intVar & 0x1f) << 8);

} 	
 
int main() {
   st_configure_abc130_chip_variable(31);
   return 0;
}
