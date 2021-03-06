#include "SPArrayList.h"

/**
 * SPArrayList summary:
 *
 * A container that represents a fixed size linked list. The capcity of the list
 * is specified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. A summary of the supported functions
 * is given below:
 *
 * spArrayListCreate       - Creates an empty array list with a specified
 *                           max capacity.
 * spArrayListCopy         - Creates an exact copy of a specified array list.
 * spArrayListDestroy      - Frees all memory resources associated with an array
 *                           list.
 * spArrayListClear        - Clears all elements from a specified array list.
 * spArrayListAddAt        - Inserts an element at a specified index, elements
 *                           will be shifted to make place.
 * spArrayListAddFirst     - Inserts an element at the beginning of the array
 *                           list, elements will be shifted to make place.
 * spArrayListAddLast      - Inserts an element at the end of the array list.
 * spArrayListRemoveAt     - Removes an element at the specified index, elements
 *                           elements will be shifted as a result.
 * spArrayListRemoveFirst  - Removes an element from the beginning of the array
 *                           list, elements will be shifted as a result.
 * spArrayListRemoveLast   - Removes an element from the end of the array list
 * spArrayListGetAt        - Accesses the element at the specified index.
 * spArrayListGetFirst     - Accesses the first element of the array list.
 * spArrayListGetLast      - Accesses the last element of the array list.
 * spArrayListMaxCapcity   - Returns the maximum capcity of the array list.
 * spArrayListSize         - Returns the number of elements in that array list.
 * spArrayListIsFull       - Returns if the array list reached its max capacity.
 * spArrayListIsEmpty      - Returns true if the array list contains no elements.
 */

/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
SPArrayList* spArrayListCreate(int maxSize){
	if(maxSize <= 0){
		return NULL;
	}
	
	SPArrayList* list = malloc(sizeof(SPArrayList));
	if(list == 0)
		return NULL;
	
	list -> maxSize = maxSize;
	list -> actualSize = 0;
	list -> elements = malloc(sizeof(int) * maxSize);
	
	if(list -> elements == 0){
		free(list);
		return NULL;
	}
	
	return list;
}

/**
 *	Creates an exact copy of the src array list. Elements in the new copy will
 *	be in the same order as they appeared in the source list.
 *	@param src - the source array list.
 *	@return
 *	NULL if either an allocation error occurs or src == NULL.
 *	A new copy of the source array list, otherwise.
 */
SPArrayList* spArrayListCopy(SPArrayList* src){
	if(src == NULL)
		return NULL;
	SPArrayList* list2 = spArrayListCreate(src->maxSize);
	if(list2 == NULL)
		return NULL;
	list2 -> actualSize = src->actualSize;
	
	for(int i = 0; i < src->actualSize; i++){
		list2 -> elements[i] = src->elements[i];
	}
	
	return list2;
}

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void spArrayListDestroy(SPArrayList* src){
	if(src == NULL)
		return;
	free(src->elements);
	free(src);
}

/**
 * Clears all elements from the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * SP_ARRAY_LIST_SUCCESS otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	src -> actualSize = 0;
	return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Inserts element at a specified index. The elements residing at and after the
 * specified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){
	if(src == NULL || index >= src->maxSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(spArrayListIsFull(src))
		return SP_ARRAY_LIST_FULL;
	
	for(int i = src->actualSize; i>=index; i--){
		src -> elements[i] = src -> elements[i-1];
	}
	src -> elements[index] = elem;
	src -> actualSize ++;
	
	return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
 SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem){
	 return spArrayListAddAt(src, elem, 0);
 }

/**
 * Inserts element at a the end of the source element. If the array list
 * reached its maximum capacity and error message is returned and the source
 * list is not affected.
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem){
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	
	return spArrayListAddAt(src, elem, src->actualSize);
}

/**
 * Removes an element from a specified index. The elements residing after the
 * specified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @param index - The index from where the new element will be removed.
 *                The index is 0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
	if(src == NULL || index >= src->maxSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(spArrayListIsEmpty(src))
		return SP_ARRAY_LIST_EMPTY;
	
	for(int i = index; i < src->actualSize-1; i++){
		src -> elements[i] = src -> elements[i+1];
	}
	
	src -> actualSize --;
	
	return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
	return spArrayListRemoveAt(src, 0);
}

/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise.
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	
	return spArrayListRemoveAt(src, src->actualSize-1);
}

/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
int spArrayListGetAt(SPArrayList* src, int index){
	if(src == NULL || src->actualSize == 0 || index >= src->actualSize)
		return -1;
	return src -> elements[index];
}

/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
int spArrayListGetFirst(SPArrayList* src){
	if(src == NULL || src->actualSize == 0)
		return -1;
	return src -> elements[0];
}

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
int spArrayListGetLast(SPArrayList* src){
	if(src == NULL || src->actualSize == 0)
		return -1;
	return src -> elements[src -> actualSize - 1];
}

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int spArrayListMaxCapacity(SPArrayList* src){
	if(src == NULL)
		return -1;
	return src -> maxSize;
}

/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int spArrayListSize(SPArrayList* src){
	if(src == NULL)
		return -1;
	return src -> actualSize;
}

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool spArrayListIsFull(SPArrayList* src){
	if(src == NULL)
		return false;
	if(src -> actualSize == src -> maxSize)
		return true;
	return false;
}

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool spArrayListIsEmpty(SPArrayList* src){
	if(src == NULL)
		return false;
	if(src -> actualSize == 0)
		return true;
	return false;
}
