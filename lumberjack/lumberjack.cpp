#include <string>
#include <vector>

#include "../header/world/pos/BlockPos.hpp"
#include "../header/world/item/ItemInstance.hpp"

#include "target.hpp"

bool (*_Actor$isSneaking)(void*);
void* (*_Player$getSelectedItem)(void*);
void* (*_Actor$getRegion)(void*);
bool (*_ItemStackBase$isNull)(void*);
void* (*_ItemStackBase$getItem)(void*);
bool (*_ItemStackBase$sameItemAndAux)(ItemInstance*,ItemInstance const&);
void* (*_BlockSource$getBlock)(void*,const BlockPos&);
int16_t (*_ItemStackBase$getId)(void*);
int16_t (*_Item$getId)(void*);
ItemInstance (*_Block$getSilkTouchItemInstance)(void*);

void (*_SurvivalMode$destroyBlock)(void** self, const BlockPos& pos, uint8_t side);

void loopBreak(void** self, const BlockPos& pos, uint8_t side,ItemInstance block){
 if(!_ItemStackBase$isNull(_Player$getSelectedItem(self[1]))){
  if(_ItemStackBase$sameItemAndAux(&block,_Block$getSilkTouchItemInstance(_BlockSource$getBlock(_Actor$getRegion(self[1]),pos)))){
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
 if(!_Actor$isSneaking(self[1])){
  std::vector<uint64_t>* items=targetItem();
  for(std::size_t i=0;i<items->size();i++){
   if(_ItemStackBase$getId(_Player$getSelectedItem(self[1]))==(*items)[i]){
    std::vector<uint64_t**>* blocks=targetBlock();
    for(std::size_t j=0;j<blocks->size();j++){
     if(_ItemStackBase$sameItemAndAux(&block,_Block$getSilkTouchItemInstance((*blocks)[j][0]))){
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
 getSymbol("_ZNK5Actor10isSneakingEv",(void**)&_Actor$isSneaking);
 getSymbol("_ZNK5Actor9getRegionEv",(void**)&_Actor$getRegion);
 getSymbol("_ZNK6Player15getSelectedItemEv",(void**)&_Player$getSelectedItem);
 getSymbol("_ZNK13ItemStackBase6isNullEv",(void**)&_ItemStackBase$isNull);
 getSymbol("_ZNK13ItemStackBase5getIdEv",(void**)&_ItemStackBase$getId);
 getSymbol("_ZNK13ItemStackBase7getItemEv",(void**)&_ItemStackBase$getItem);
 getSymbol("_ZNK4Item5getIdEv",(void**)&_Item$getId);
 getSymbol("_ZNK13ItemStackBase14sameItemAndAuxERKS_",(void**)&_ItemStackBase$sameItemAndAux);
 getSymbol("_ZNK11BlockSource8getBlockERK8BlockPos",(void**)&_BlockSource$getBlock);
 getSymbol("_ZNK5Block24getSilkTouchItemInstanceEv",(void**)&_Block$getSilkTouchItemInstance);
}
