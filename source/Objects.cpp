/**************
 * GEMWIRE    *
 *    PURPURI *
 **************/

#include "../headers/Objects.hpp"
#include "../headers/Class.hpp"

#include <cstring>

ObjectHeap::ObjectHeap() {
    NextObjectID = 1;
}

ObjectHeap::~ObjectHeap() {}

Object ObjectHeap::CreateObject(Class *Class) {
    Object object;
    object.Heap = 0;
    object.Type = 0;

    if(Class == NULL) return object;

    size_t ObjectSize = Class->GetClassFieldCount() + 1;
    Variable* ClassObj = new Variable[ObjectSize];
    if(!ClassObj) return object;

    memset(ClassObj, 0, sizeof(Variable) * ObjectSize);

    object.Heap = NextObjectID++;

    ClassObj[0].pointerVal = (size_t) Class;

    ObjectMap.emplace((size_t) object.Heap, (size_t) &ClassObj);

    return object;
}

Variable* ObjectHeap::GetObjectPtr(Object obj) {
    size_t Obj = 0;

    std::map<size_t, size_t>::iterator objIter;
    objIter = ObjectMap.find((size_t) &obj);

    if(objIter == ObjectMap.end())
        return NULL;

    return (Variable*) objIter->second;
}