#include <string>
#include <vector>

#include "../header/world/pos/BlockPos.hpp"
#include "../header/world/item/ItemInstance.hpp"

#include "target.hpp"

bool (*_Mob$isSneaking)(void*);
void* (*_Player$getSelectedItem)(void*);
void* (*_Actor$getRegion)(void*);
bool (*_ItemStack$isNull)(void*);
void* (*_ItemStack$getItem)(void*);
bool (*_ItemInstance$sameItemAndAux)(ItemInstance*,ItemInstance const&);
void* (*_BlockSource$getBlock)(void*,const BlockPos&);
int16_t (*_ItemStack$getId)(void*);
int16_t (*_Item$getId)(void*);
ItemInstance (*_Block$getSilkTouchItemInstance)(void*);

void (*_SurvivalMode$destroyBlock)(void** self, const BlockPos& pos, uint8_t side);

void loopBreak(void** self, const BlockPos& pos, uint8_t side,ItemInstance block){
 if(!_ItemStack$isNull(_Player$getSelectedItem(self[1]))){
  if(_ItemInstance$sameItemAndAux(&block,_Block$getSilkTouchItemInstance(_BlockSource$getBlock(_Actor$getRegion(self[1]),pos)))){
   _SurvivalMode$destroyBlock(self,pos,side);
   loopBreak(self,{pos.x+1,pos.y,pos.z},side,block);
   loopBreak(self,{pos.x-1,pos.y,pos.z},side,block);
   loopBreak(self,{pos.x,pos.y+1,pos.z},side,block);
   loopBreak(self,{pos.x,pos.y-1,pos.z},side,block);
   loopBreak(self,{pos.x,pos.y,pos.z+1},side,block);
   loopBreak(self,{pos.x,pos.y,pos.z-1},side,block);
  }
 }
}
void SurvivalMode$destroyBlock(void** self, const BlockPos& pos, uint8_t side){
 ItemInstance block=_Block$getSilkTouchItemInstance(_BlockSource$getBlock(_Actor$getRegion(self[1]),pos));
 _SurvivalMode$destroyBlock(self,pos,side);
 if(!_Mob$isSneaking(self[1])){
  std::vector<uint64_t>* items=targetItem();
  for(std::size_t i=0;i<items->size();i++){
   if(_ItemStack$getId(_Player$getSelectedItem(self[1]))==(*items)[i]){
    std::vector<uint64_t**>* blocks=targetBlock();
    for(std::size_t j=0;j<blocks->size();j++){
     if(_ItemInstance$sameItemAndAux(&block,_Block$getSilkTouchItemInstance((*blocks)[j][0]))){
      loopBreak(self,{pos.x+1,pos.y,pos.z},side,block);
      loopBreak(self,{pos.x-1,pos.y,pos.z},side,block);
      loopBreak(self,{pos.x,pos.y+1,pos.z},side,block);
      loopBreak(self,{pos.x,pos.y-1,pos.z},side,block);
      loopBreak(self,{pos.x,pos.y,pos.z+1},side,block);
      loopBreak(self,{pos.x,pos.y,pos.z-1},side,block);
      break;
     }
    }
    delete blocks;
   }
  }
  delete items;
 }
}

void loadMod(void* replace,void* rewrite,void* symbol){
 void (*replaceSymbol)(const std::string&,void*,void**);
 replaceSymbol=(void(*)(const std::string&,void*,void**))replace;
 void (*getSymbol)(const std::string&,void**);
 getSymbol=(void(*)(const std::string&,void**))symbol;

 replaceSymbol("_ZN12SurvivalMode12destroyBlockERK8BlockPosh",(void*)&SurvivalMode$destroyBlock,(void**)&_SurvivalMode$destroyBlock);
 /*getSymbol("_ZNK3Mob10isSneakingEv",(void**)&_Mob$isSneaking);
 getSymbol("_ZNK5Actor9getRegionEv",(void**)&_Actor$getRegion);
 getSymbol("_ZNK6Player15getSelectedItemEv",(void**)&_Player$getSelectedItem);
 getSymbol("_ZNK9ItemStack6isNullEv",(void**)&_ItemStack$isNull);
 getSymbol("_ZNK9ItemStack5getIdEv",(void**)&_ItemStack$getId);
 getSymbol("_ZNK9ItemStack7getItemEv",(void**)&_ItemStack$getItem);
 getSymbol("_ZNK4Item5getIdEv",(void**)&_Item$getId);
 getSymbol("_ZNK12ItemInstance14sameItemAndAuxERKS_",(void**)&_ItemInstance$sameItemAndAux);
 getSymbol("_ZNK11BlockSource8getBlockERK8BlockPos",(void**)&_BlockSource$getBlock);
 getSymbol("_ZNK5Block24getSilkTouchItemInstanceEv",(void**)&_Block$getSilkTouchItemInstance);*/
}
