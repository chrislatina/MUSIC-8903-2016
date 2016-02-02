#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include <algorithm>
#include <cmath>

#include "Util.h"

template <class T> 
class CRingBuffer
{
public:
    CRingBuffer (int iBufferLengthInSamples){
        
        this->iBufferLengthInSamples = iBufferLengthInSamples;

        tBuffer = new float[iBufferLengthInSamples];
        
        tWrite = *buffer;
        tRead = tWrite;
        iWritePos = 0;
        iReadPos = 0;

    }

    virtual ~CRingBuffer ();

    /*! add a new value of type T to write index and increment write index
    \param T tNewValue the new value
    \return void
    */
    void putPostInc (T tNewValue){
        put(T tNewValue)
        iWritePos = iWritePos+1 % iBufferLengthInSamples;
    }

    /*! add a new value of type T to write index
    \param T tNewValue the new value
    \return void
    */
    void put(T tNewValue){
        *tWrite = tNewValue;
    }

    /*! return the value at the current read index and increment the read pointer
    \return float the value from the read index
    */
    T getPostInc (){
        T readVal = *tRead;
        iReadPos = iReadPos+1 % iBufferLengthInSamples;

        return readVal;
    }
    
    /*! return the value at the current read index
    \param int iOffset: read at offset from read index
    \return T the value from the read index
    */
    T get (int iOffset = 0) const{
        var iNewPos = (iReadPos + iOffset) % iBufferLengthInSamples;
        return tBuffer[iNewPos];
    }
    
    /*! set buffer content and indices to 0
    \return void
    */
    void reset (){
        for(int i=0; i<iBufferLengthInSamples; i++){
            fBuffer[i] = 0;
        }
    }
    
    /*! return the current index for writing/put
    \return int
    */
    int getWriteIdx () const{
        return iWritePos;
    }
    
    /*! move the write index to a new position
    \param int iNewWriteIdx: new position
    \return void
    */
    void setWriteIdx (int iNewWriteIdx){
        
        // TODO Bounds check
        iWritePos = iNewWriteIdx % iBufferLengthInSamples;
    }
    
    /*! return the current index for reading/get
    \return int
    */
    int getReadIdx () const{
        return iReadPos;
    }
    
    /*! move the read index to a new position
    \param int iNewReadIdx: new position
    \return void
    */
    void setReadIdx (int iNewReadIdx){
        iReadPos = iNewReadIdx % iBufferLengthInSamples;
    }
    
    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer () const{
        
    }
    
    /*! returns the length of the internal buffer
    \return int
    */
    int getLength () const{
        return iBufferLengthInSamples;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    // implement if you find time
    /*! add new values of type T to write index and increment write index
    \param const T * ptNewBuff: new values
    \param int iLength: number of values
    \return void
    */
    void putPostInc (const T* ptNewBuff, int iLength);

    /*! add new values of type T to write index
    \param const T * ptNewBuff: new values
    \param int iLength: number of values
    \return void
    */
    void put(const T* ptNewBuff, int iLength);
 
    /*! return the values starting at the current read index and increment the read pointer
    \param T * ptBuff: pointer to where the values will be written
    \param int iLength: number of values
    \return void
    */
    void getPostInc (T* ptBuff, int iLength);
    
    /*! return the values starting at the current read index
    \param T * ptBuffpointer to where the values will be written
    \param int iLength: number of values
    \return void
    */
    void get (T* ptBuff, int iLength) const;

private:
    CRingBuffer(const CRingBuffer& that);
    
    int iBufferLengthInSamples;
    T *tBuffer;
    T *tWrite;
    T *tRead;
    int iWritePos;
    int iReadPos;
    
};
#endif // __RingBuffer_hdr__
