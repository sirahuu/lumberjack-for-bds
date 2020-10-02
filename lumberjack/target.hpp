#include <vector>

#include "../header/world/block/VanillaBlocks.hpp"

std::vector<uint64_t**>* targetBlock(){
 return new std::vector<uint64_t**>{
  (uint64_t**)&VanillaBlocks::mLog,
  (uint64_t**)&VanillaBlocks::mLog2,
  (uint64_t**)&VanillaBlocks::mBrownMushroomBlock,
  (uint64_t**)&VanillaBlocks::mRedMushroomBlock
 };
}
std::vector<uint64_t>* targetItem(){
 return new std::vector<uint64_t>{
 271,
 275,
 258,
 286,
 279
 };
}

