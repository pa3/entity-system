#pragma once

class ClassId {
 public:
  template<class T>
  static int ofType() {return ClassIdHolder<T>::getId();};
  template<class T>
  static int ofInstance( const T& instance ) { return ClassIdHolder<T>::getId(); };
 private:
  template<class T>
  class ClassIdHolder {
   public:
    static int getId() {
      static const int id = idCounter++;
      return id;
    }
  };
  static int idCounter;
};
