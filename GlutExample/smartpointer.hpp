//
//  smartpointer.hpp
//  GlutA2
//
//  Created by Manuel Baumgartner on 29/11/2017.
//  Copyright © 2017 Hevselavier Lines Ver. All rights reserved.
//

#ifndef smartpointer_h
#define smartpointer_h

//----------------------------------------------------------
// ofPtr is a smart pointer that is able to delete the memory
// by itself when no other pointer is referencing it.
//----------------------------------------------------------
template <typename T>
using ofPtr = std::shared_ptr<T>;

#endif /* smartpointer_h */
