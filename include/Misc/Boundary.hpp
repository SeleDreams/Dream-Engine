#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP
struct Boundary{
int MinX,MaxX,MinY,MaxY = 0;
 inline bool CollidesWith(const Boundary &boundary) const
 { 
    bool x,y;
    x =  (MinX > boundary.MaxX || MaxX < boundary.MinX);
    y=   (MinY > boundary.MaxY || MaxY < boundary.MinY);

     if (x || y)
     {
        // std::cout << "not displayed" << std::endl;
     }
return !(x || y)
     ;};
};
#endif