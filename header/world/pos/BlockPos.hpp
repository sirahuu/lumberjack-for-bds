#pragma once

struct BlockPos{
 int32_t x;
 int32_t y;
 int32_t z;

 BlockPos(int32_t _x,int32_t _y,int32_t _z){
  this->x=_x;
  this->y=_y;
  this->z=_z;
 }
};
