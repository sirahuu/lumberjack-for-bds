#pragma once

class Item;
class Block;
class BlockLegacy;

class ItemInstance{
public:
 uint8_t tmp[0x18];
 uint8_t aux; // 0x18
 uint8_t tmp2[0x78-0x19];

 ItemInstance(Item const&,int,int);
 ItemInstance(BlockLegacy const&,int,short);

 int64_t getId() const;
};
