# Derived Datatypes:

The Java bindings in Open MPI support various derived datatypes, including contiguous, vector, and indexed datatypes. 

These datatypes provide efficient ways to describe non-contiguous data layouts or portions of arrays. Methods such as getSize(), getExtent(), and getLb() offer insights into the size and extent of derived datatypes, aiding in memory layout understanding. 

Additionally, the createResized() method allows for the creation of derived datatypes with adjusted lower bounds and extents, enhancing data description flexibility. When dealing with struct-like datatypes, a specialized approach involving a subclass of Struct is employed, where data fields are defined along with corresponding access methods. 

Once defined, these struct-like datatypes can be instantiated to create objects representing their type, facilitating efficient data manipulation.

An example - 
```
public class Complex extends Struct {
    // This section defines the offsets of the fields.
    private final int real = addDouble(),
    imag = addDouble();
    
    // This method tells the super class how to create a data object.
    @Override protected Data newData() { return new Data(); }
    
    public class Data extends Struct.Data {
        // These methods read from the buffer:
        public double getReal() { return getDouble(real); }
        public double getImag() { return getDouble(imag); }
    
        // These methods write to the buffer:
        public void putReal(double r) { putDouble(real, r); }
        public void putImag(double i) { putDouble(imag, i); }
    } // Data
} // Complex
```
