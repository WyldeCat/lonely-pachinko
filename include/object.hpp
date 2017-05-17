//
// object.hpp
//

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

class Object {
// interface class
public:
  virtual void Draw() = 0;
  virtual ~Object() = default;
};

class Sphere : public Object /* */ {
public:
  virtual void Draw();
private:

}

class Face : public Object /* */ {
public:
  virtual void Draw();
private:

}

class Mesh : public Object {
public:
  virtual void Draw();
private:
  // continer<Face_ptr> faces;
}

#endif
