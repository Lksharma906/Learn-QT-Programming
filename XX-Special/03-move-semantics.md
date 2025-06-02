# Move Semantics


## L Value & R Value

### L-value
- Has a name.
- All variables are l-values.
- Can be assigned values.
- Some expression return l-values.
- l-value will persist beyond the expression.
- Functions that return by reference return l-value.
- Reference to l-value ( called l-value reference) 

### R-value
- Does not have a name.
- R-value is a temporary value.
- Cannot be assigned values.
- some expressions return r-value.
- does not persist beyond the expression.
- function that return by value that return r-value.
- reference to r-value(called r-value reference) from cpp11

```cpp

// x, y, z are l-value, 10,4,3 are r-value.
int x =10;
int y = 4;
int z = 3; 

// this expression on right hand side return a r-value.
int result = (x+y)*z;

// below expression return a l-value.
++x = 7;


//return r-value
int add(int x, int y) { return x + y; }

//return l-value.
int & transform(int &x) { x *= x; return x; }
```


#### R-Value references

- r-value reference are needed for implementing move semantics.
- A r-value reference created to a temporary.
- Reference to a temporary.
- Created using && operator.
- **Cannot point to l-values**.
- R-value reference always bind to temporaries.
- L-value reference always bind to l-values.
- **a l-value ref may bind to a temporary is the reference is a constant**.
- **purpose of r-value ref is that they allowed us to detect temporaries and constant, based on this we can write function overload based on l-value and r-value references.**

```cpp
int &&r1 = 10; // r-value reference
int &&r2 = add(10,5); // add returns by value (temporary)
int &&r3 = 7+2; // expression return a temporary

int x = 0; // l-value.
int &&r4 = x; // Invalid.

int &ref = x; // l-value ref bind to l-value.
int &ref1 = transform(x); // return by ref.

const int &ref3 = 10; // l-value can bind to temporary if reference is constant.
```



```cpp
void print(int &x) // takes a l-value
{
	cout<<"print(int &x)" 
}
void print(const int &x) // takes a l-value, but can take temporaries also.
{
	cout<<"print(const int &x)" 
}
void print(int &&x) // takes a r-value
{
	cout<<"print(int &&x)" 
}

int main()
{
	int x = 10;
	print(x); // will print cout<<"print(int &x)" 
	print(3); // will bind to print(const int &x) if print(int &&x) is not available. If r-value refence one is avaliable , temporaries will always bound to that one.
}
```


## COPY & MOVE Semantics
- copy is implemented through copy constructor. 
- Copy of the object state is created.
- wasteful in case copy is created from temporary.
- instead the state can be moved from source object.
- implemented through move semantics.

#### Deep Copy Illustration

    +----------------------+         +----------------------+
    |     Object A         |         |     Object B         |
    |----------------------|         |----------------------|
    | data ---> [ "Hi!" ]  |<--copy--| data ---> [ "Hi!" ]  |
    +----------------------+         +----------------------+

 * Object A and Object B each have their own memory.
 * Changes in one won't affect the other.
 * Deep copy duplicates the memory contents.

MyString a("Hi!");
MyString b = a;  // deep copy
#### Shallow Copy Illustration (Bad)

    +----------------------+         +----------------------+
    |     Object A         |         |     Object B         |
    |----------------------|         |----------------------|
    | data ---+            |<--copy--| data ---+            |
    +---------|------------+         +---------|------------+
              |                            |
              v                            v
           [ "Hi!" ]  <-- Shared memory (bad!)

 * Both objects point to the same memory.
 * Destruction of one leads to dangling pointer in the other.
 * This often causes crashes or double delete errors.

MyString a("Hi!");
MyString b = a;  // shallow copy

#### Move Semantics: Resource Stealing

Before move:

    +----------------------+         
    |     Object A         |         
    |----------------------|         
    | data ---> [ "Hi!" ]  |         
    +----------------------+

After move to Object B:

    +----------------------+         +----------------------+
    |     Object A         |         |     Object B         |
    |----------------------|         |----------------------|
    | data ---> nullptr    | --move->| data ---> [ "Hi!" ]  |
    +----------------------+         +----------------------+

 * Object A no longer owns the resource (data is set to nullptr).
 * Object B "steals" the memory.
 * No deep copy is made — just pointer reassignment.
 * Avoids unnecessary allocation and copying.

MyString a("Hi!");
MyString b = std::move(a);  // move constructor


| Operation        | Memory Copied? | Ownership Transferred? | Performance |
| ---------------- | -------------- | ---------------------- | ----------- |
| Copy Constructor | ✅ Yes          | ❌ No                   | Slow        |
| Move Constructor | ❌ No           | ✅ Yes                  | Fast        |


### When to use move semantics.
- If an expression yield a temporary and that has to be copied in another object then we should use move semantics.
- To detect that temporary , we have to use a constructor that accepts a r-value reference and temporary will automatically bind to that one.
